module wind;

import <vector>;
import <string>;
import <cstdint>;
import allegro;
import :tilesheet;
import :base;
import :bitmap;
import :color;
import :json;
import :string;

namespace wind
{
	tilesheet_t::tilesheet_t() : m_sub_bitmaps(), m_tile_size({ 0, 0 }) {}

	tilesheet_t::tilesheet_t(const tilesheet_t& tilesheet) : m_sub_bitmaps(tilesheet.m_sub_bitmaps), m_tile_size(tilesheet.m_tile_size) {}

	tilesheet_t::~tilesheet_t() {}

	auto tilesheet_t::operator = (const tilesheet_t& tilesheet) -> tilesheet_t&
	{
		this->m_sub_bitmaps = tilesheet.m_sub_bitmaps;
		this->m_tile_size = tilesheet.m_tile_size;

		return *this;
	}

	auto tilesheet_t::clear() -> void
	{
		this->m_sub_bitmaps.clear();
		this->m_tile_size.zero_out();
	}

	auto tilesheet_t::count() const -> size_t
	{
		return this->m_sub_bitmaps.size();
	}

	auto tilesheet_t::is_empty() const -> bool
	{
		return !this->m_sub_bitmaps.size();
	}

	auto tilesheet_t::tile_size() const -> const ALLEGRO::VECTOR_2D<int32_t>&
	{
		return this->m_tile_size;
	}

	auto tilesheet_t::at(size_t index) -> tilesheet_t::reference_element_type
	{
		ALLEGRO::ASSERT(index < this->m_sub_bitmaps.size());
		return this->m_sub_bitmaps[index];
	}

	auto tilesheet_t::at(size_t index) const -> tilesheet_t::const_reference_element_type
	{
		ALLEGRO::ASSERT(index < this->m_sub_bitmaps.size());
		return this->m_sub_bitmaps[index];
	}

	auto tilesheet_t::operator [](size_t index) -> tilesheet_t::reference_element_type
	{
		return this->at(index);
	}

	auto tilesheet_t::operator [](size_t index) const -> tilesheet_t::const_reference_element_type
	{
		return this->at(index);
	}

	auto tilesheet_t::begin() -> tilesheet_t::iterator
	{
		return iterator(this->m_sub_bitmaps.begin());
	}

	auto tilesheet_t::end() -> tilesheet_t::iterator
	{
		return iterator(this->m_sub_bitmaps.end());
	}

	auto tilesheet_t::cbegin() const -> tilesheet_t::const_iterator
	{
		return const_iterator(this->m_sub_bitmaps.cbegin());
	}

	auto tilesheet_t::cend() const -> tilesheet_t::const_iterator
	{
		return const_iterator(this->m_sub_bitmaps.cend());
	}

	auto tilesheet_t::rbegin() -> tilesheet_t::reverse_iterator
	{
		return reverse_iterator(this->m_sub_bitmaps.rbegin());
	}

	auto tilesheet_t::rend() -> tilesheet_t::reverse_iterator
	{
		return reverse_iterator(this->m_sub_bitmaps.rend());
	}

	auto tilesheet_t::crbegin() const -> tilesheet_t::const_reverse_iterator
	{
		return const_reverse_iterator(this->m_sub_bitmaps.crbegin());
	}

	auto tilesheet_t::crend() const -> tilesheet_t::const_reverse_iterator
	{
		return const_reverse_iterator(this->m_sub_bitmaps.crend());
	}

	static auto generate_sub_bitmaps(const ALLEGRO::BITMAP& bitmap, const ALLEGRO::VECTOR_2D<int32_t>& tsize, std::vector<ALLEGRO::BITMAP>& sub_bitmap_array) -> int32_t
	{
		ALLEGRO::VECTOR_2D<int32_t> bsize{ al::get_bitmap_dimensions(bitmap) };
		ALLEGRO::RECTANGLE<int32_t> rectangle{ {0, 0}, tsize };

		for (rectangle.get_position().get_y() = 0; rectangle.get_position().get_y() < bsize.get_y(); rectangle.get_position().get_y() += tsize.get_y())
		{
			for (rectangle.get_position().get_x() = 0; rectangle.get_position().get_x() < bsize.get_x(); rectangle.get_position().get_x() += tsize.get_x())
			{
				ALLEGRO::BITMAP sub{ al::create_sub_bitmap(bitmap, rectangle) };

				if (!sub)
				{
					return -1;
				}

				if (!wind::bitmap::is_empty(sub))
				{
					sub_bitmap_array.push_back(sub);
				}
			}
		}

		return 0;
	}

	static auto create_empty_bitmap(std::vector<ALLEGRO::BITMAP>& bitmaps, const ALLEGRO::VECTOR_2D<int32_t>& tile_size) -> int32_t
	{
		ALLEGRO::BITMAP sub{ al::create_bitmap(tile_size) };

		if (!sub)
		{
			return -1;
		}

		ALLEGRO::BITMAP target{ al::get_target_bitmap() };
		al::clear_to_color(al::map_rgb(255, 0, 255));
		al::set_target_bitmap(target);
		al::convert_mask_to_alpha(sub, al::map_rgb(255, 0, 255));
		bitmaps.push_back(sub);

		return 0;
	}

	auto tilesheet_t::generate(const std::vector<element_type>& bitmaps, const ALLEGRO::VECTOR_2D<int32_t>& tile_size) -> int32_t
	{
		this->m_bitmaps.clear();
		this->m_sub_bitmaps.clear();
		this->m_tile_size = tile_size;

		if (create_empty_bitmap(this->m_sub_bitmaps, this->m_tile_size) < 0)
		{
			return -1;
		}

		for (auto& bitmap : bitmaps)
		{
			this->m_bitmaps.push_back(bitmap);

			if (generate_sub_bitmaps(bitmap, this->m_tile_size, this->m_sub_bitmaps) < 0)
			{
				return -1;
			}
		}

		return 0;
	}

	namespace tilesheet
	{
		static size_t populate_vector(ALLEGRO::BITMAP& bitmap, ALLEGRO::VECTOR_2D<size_t> tile_size, std::vector<ALLEGRO::BITMAP>& bitmaps)
		{
			ALLEGRO::VECTOR_2D<size_t> bitmap_size{ al::get_bitmap_dimensions(bitmap) };
			ALLEGRO::BITMAP sub{ nullptr };
			ALLEGRO::BITMAP target{};
			ALLEGRO::RECTANGLE<size_t> source = { ALLEGRO::VECTOR_2D<size_t>(), tile_size};

			bitmap_size.get_x() -= (bitmap_size.get_x() % tile_size.get_x());
			bitmap_size.get_y() -= (bitmap_size.get_y() % tile_size.get_y());

			for (source.get_position().get_y() = 0; source.get_position().get_y() < bitmap_size.get_y(); source.get_position().get_y() += tile_size.get_y())
			{
				for (source.get_position().get_x() = 0; source.get_position().get_x() < bitmap_size.get_x(); source.get_position().get_x() += tile_size.get_x())
				{
					if (!(sub = al::create_sub_bitmap(bitmap, static_cast<ALLEGRO::RECTANGLE<int32_t>>(source))))
					{
						return 0;
					}

					if (!wind::bitmap::is_empty(sub))
					{
						bitmaps.push_back(sub);
					}
				}
			}

			return bitmaps.size();
		}
	}
}

