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
			ALLEGRO::COLOR color = al::get_pixel(bitmap, { 0, 0 });
			ALLEGRO::COLOR pixel{ 0.0f, 0.0f, 0.0f, 0.0f };
			bool first_found = false;

			for (int32_t j = 0; j < height; ++j)
			{
				pixel = al::get_pixel(bitmap, { x, j });

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
			ALLEGRO::COLOR color = al::get_pixel(bitmap, { 0, 0 });
			ALLEGRO::COLOR pixel{ 0.0f, 0.0f, 0.0f, 0.0f };
			bool first_found = false;

			for (int32_t i = 0; i < width; ++i)
			{
				pixel = al::get_pixel(bitmap, { i, y });

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
			ALLEGRO::SIZE<int32_t> dimensions = al::get_bitmap_dimensions(bitmap);

			this->m_bitmap = al::create_bitmap({ dimensions.width - 2, dimensions.height - 2 });

			if (this->m_bitmap)
			{
				ALLEGRO::BITMAP target = al::get_target_bitmap();
				al::set_target_bitmap(this->m_bitmap);
				al::draw_bitmap(bitmap, { 1, 1 });
				al::set_target_bitmap(target);

				auto region = al::lock_bitmap(bitmap, ALLEGRO::PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);

				ninepatch::get_vertical_positions(bitmap, dimensions.height, 0, this->m_partition.top_left.y, this->m_partition.bottom_right.y);
				ninepatch::get_horizontal_positions(bitmap, dimensions.width, 0, this->m_partition.top_left.x, this->m_partition.bottom_right.x);

				ninepatch::get_vertical_positions(bitmap, dimensions.height, dimensions.width - 1, this->m_margin.top_left.y, this->m_margin.bottom_right.y);
				ninepatch::get_horizontal_positions(bitmap, dimensions.width, dimensions.height - 1, this->m_margin.top_left.x, this->m_margin.bottom_right.x);

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
		auto draw(const ninepatch_t& ninepatch, const ALLEGRO::POINT<int32_t>& position, const ALLEGRO::SIZE<int32_t>& size, WIND::NINEPATCH::DRAW::FLAG flag) -> void
		{
			ALLEGRO::SIZE<int32_t> dimensions{ al::get_bitmap_dimensions(ninepatch.m_bitmap) };
			ALLEGRO::SIZE<int32_t> bsize[3] =
			{
				{ninepatch.m_partition.top_left.x,ninepatch.m_partition.top_left.y},
				{ninepatch.m_partition.bottom_right.x - ninepatch.m_partition.top_left.x + 1, ninepatch.m_partition.bottom_right.y - ninepatch.m_partition.top_left.y + 1},
				{dimensions.width - ninepatch.m_partition.bottom_right.x, dimensions.height - ninepatch.m_partition.bottom_right.y}
			};

			ALLEGRO::RECTANGLE<int32_t> source{ {0, 0}, {0, 0} };
			ALLEGRO::RECTANGLE<int32_t> destination{ {0, 0}, {0, 0} };

			for (int32_t j = 0; j < 3; ++j)
			{
				source.size.height = bsize[j].height;

				if (j == 2)
				{
					destination.size.height = size.height - (bsize[0].height + bsize[2].height);
				}
				else
				{
					destination.size.height = bsize[j].height;
				}

				for (int32_t i = 0; i < 3; ++i)
				{
					source.size.width = bsize[i].width;

					if (i == 2)
					{
						destination.size.width = size.width - (bsize[0].width + bsize[2].width);
					}
					else
					{
						destination.size.width = bsize[i].width;
					}

					al::draw_scaled_bitmap(ninepatch.get_bitmap(), static_cast<ALLEGRO::RECTANGLE<float>>(source), static_cast<ALLEGRO::RECTANGLE<float>>(destination));

					source.position.x += source.size.width;
					destination.position.x += destination.size.width;
				}

				source.position.y += source.size.height;
				destination.position.y += destination.size.height;
			}
		}
	}
}