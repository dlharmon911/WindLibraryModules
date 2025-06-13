module wind;

import <cstdint>;
import allegro;
import allegro.image_addon;
import :bitmap;
import :base;
import :string;
import :ninepatch;

namespace wind
{
	ninepatch_t::ninepatch_t() : m_bitmap(), m_partition({ 0, 0, 0, 0 }), m_margin({ 0, 0, 0, 0 })
	{
	}

	ninepatch_t::ninepatch_t(const string_t& filename) : m_bitmap(), m_partition({ 0, 0, 0, 0 }), m_margin({ 0, 0, 0, 0 })
	{
		this->load(filename);
	}

	ninepatch_t::ninepatch_t(const ALLEGRO::BITMAP& bitmap) : m_bitmap(), m_partition({ 0, 0, 0, 0 }), m_margin({ 0, 0, 0, 0 })
	{
		this->create(bitmap);
	}

	ninepatch_t::ninepatch_t(const ninepatch_t& ninepatch) : m_bitmap(ninepatch.m_bitmap), m_partition(ninepatch.m_partition), m_margin(ninepatch.m_margin)
	{
	}

	ninepatch_t::~ninepatch_t()
	{
	}

	ninepatch_t::operator bool() const
	{
		return (bool)this->m_bitmap;
	}

	auto ninepatch_t::get_bitmap() const-> const ALLEGRO::BITMAP&
	{
		return this->m_bitmap;
	}

	auto ninepatch_t::get_partition() const -> const ALLEGRO::BOX<int32_t>&
	{
		return this->m_partition;
	}

	auto ninepatch_t::get_margin() const -> const ALLEGRO::BOX<int32_t>&
	{
		return this->m_margin;
	}

	namespace ninepatch
	{
		static void get_vertical_positions(const ALLEGRO::BITMAP& bitmap, int32_t height, int32_t x, int32_t& y1, int32_t& y2)
		{
			ALLEGRO::COLOR color = al::get_pixel(bitmap, { 0.0f, 0.0f });
			ALLEGRO::COLOR pixel{ 0.0f, 0.0f, 0.0f, 0.0f };
			bool first_found = false;

			for (int32_t j = 0; j < height; ++j)
			{
				pixel = al::get_pixel(bitmap, { static_cast<float>(x), static_cast<float>(j) });

				if (color != pixel)
				{
					if (first_found)
					{
						y2 = j - 1;
						return;
					}
					else
					{
						y1 = j;
						first_found = true;
					}
					color = pixel;
				}
			}
		}

		static void get_horizontal_positions(const ALLEGRO::BITMAP& bitmap, int32_t width, int32_t y, int32_t& x1, int32_t& x2)
		{
			ALLEGRO::COLOR color = al::get_pixel(bitmap, { 0.0f, 0.0f });
			ALLEGRO::COLOR pixel{ 0.0f, 0.0f, 0.0f, 0.0f };
			bool first_found = false;

			for (int32_t i = 0; i < width; ++i)
			{
				pixel = al::get_pixel(bitmap, { static_cast<float>(i), static_cast<float>(y) });

				if (color != pixel)
				{
					if (first_found)
					{
						x2 = i - 1;
						return;
					}
					else
					{
						x1 = i;
						first_found = true;
					}
					color = pixel;
				}
			}
		}
	}

	auto ninepatch_t::create(const ALLEGRO::BITMAP& bitmap) -> bool
	{
		if (bitmap)
		{
			ALLEGRO::VECTOR_2D<int32_t> dimensions = al::get_bitmap_dimensions(bitmap);

			this->m_bitmap = al::create_bitmap({ dimensions.get_x() - 2, dimensions.get_y() - 2 });

			if (this->m_bitmap)
			{
				ALLEGRO::BITMAP target = al::get_target_bitmap();
				al::set_target_bitmap(this->m_bitmap);
				al::draw_bitmap(bitmap, { 1.0f, 1.0f });
				al::set_target_bitmap(target);

				auto region = al::lock_bitmap(bitmap, ALLEGRO::PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);

				ninepatch::get_vertical_positions(bitmap, dimensions.get_y(), 0, this->m_partition.get_top_left().get_y(), this->m_partition.get_bottom_right().get_y());
				ninepatch::get_horizontal_positions(bitmap, dimensions.get_x(), 0, this->m_partition.get_top_left().get_x(), this->m_partition.get_bottom_right().get_x());

				ninepatch::get_vertical_positions(bitmap, dimensions.get_y(), dimensions.get_x() - 1, this->m_margin.get_top_left().get_y(), this->m_margin.get_bottom_right().get_y());
				ninepatch::get_horizontal_positions(bitmap, dimensions.get_x(), dimensions.get_y() - 1, this->m_margin.get_top_left().get_x(), this->m_margin.get_bottom_right().get_x());

				al::unlock_bitmap(bitmap);
			}
		}

		return false;
	}

	auto ninepatch_t::load(const string_t& filename) -> bool
	{
		if (filename.size())
		{
			ALLEGRO::BITMAP bitmap = al::load_bitmap(filename.c_str());

			if (bitmap)
			{
				return create(bitmap);
			}
		}

		return false;
	}

	namespace ninepatch
	{
		auto draw(const ninepatch_t& ninepatch, const ALLEGRO::VECTOR_2D<int32_t>& position, const ALLEGRO::VECTOR_2D<int32_t>& size, WIND::NINEPATCH::DRAW::FLAG flag) -> void
		{
			ALLEGRO::VECTOR_2D<int32_t> dimensions{ al::get_bitmap_dimensions(ninepatch.m_bitmap) };
			ALLEGRO::VECTOR_2D<int32_t> bsize[3] =
			{
				{ninepatch.m_partition.get_top_left().get_x(),ninepatch.m_partition.get_top_left().get_y()},
				{ninepatch.m_partition.get_bottom_right().get_x() - ninepatch.m_partition.get_top_left().get_x() + 1, ninepatch.m_partition.get_bottom_right().get_y() - ninepatch.m_partition.get_top_left().get_y() + 1},
				{dimensions.get_x() - ninepatch.m_partition.get_bottom_right().get_x(), dimensions.get_y() - ninepatch.m_partition.get_bottom_right().get_y()}
			};

			ALLEGRO::RECTANGLE<int32_t> source{ {0, 0}, {0, 0} };
			ALLEGRO::RECTANGLE<int32_t> destination{ {0, 0}, {0, 0} };

			for (int32_t j = 0; j < 3; ++j)
			{
				source.get_size().get_y() = bsize[j].get_y();

				if (j == 2)
				{
					destination.get_size().get_y() = size.get_y() - (bsize[0].get_y() + bsize[2].get_y());
				}
				else
				{
					destination.get_size().get_y() = bsize[j].get_y();
				}

				for (int32_t i = 0; i < 3; ++i)
				{
					source.get_size().get_x() = bsize[i].get_x();

					if (i == 2)
					{
						destination.get_size().get_x() = size.get_x() - (bsize[0].get_x() + bsize[2].get_x());
					}
					else
					{
						destination.get_size().get_x() = bsize[i].get_x();
					}

					al::draw_scaled_bitmap(ninepatch.get_bitmap(), static_cast<ALLEGRO::RECTANGLE<float>>(source), static_cast<ALLEGRO::RECTANGLE<float>>(destination));

					source.get_position().get_x() += source.get_size().get_x();
					destination.get_position().get_x() += destination.get_size().get_x();
				}

				source.get_position().get_y() += source.get_size().get_y();
				destination.get_position().get_y() += destination.get_size().get_y();
			}
		}
	}
}
