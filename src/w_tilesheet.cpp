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
import wind.datafile_addon;

namespace wind
{
	tilesheet_t::tilesheet_t() : m_bitmaps(), m_tile_size({ 0, 0 }) {}

	tilesheet_t::tilesheet_t(const std::vector<ALLEGRO::BITMAP>& bitmaps, const ALLEGRO::SIZE<size_t>& tile_size) : m_bitmaps(bitmaps), m_tile_size(tile_size) {}

	tilesheet_t::tilesheet_t(const tilesheet_t& tilesheet) : m_bitmaps(tilesheet.m_bitmaps), m_tile_size(tilesheet.m_tile_size) {}

	tilesheet_t::~tilesheet_t() {}

	auto tilesheet_t::operator = (const tilesheet_t& tilesheet) -> wind::add_reference_t<tilesheet_t>
	{
		this->m_bitmaps = tilesheet.m_bitmaps;
		this->m_tile_size = tilesheet.m_tile_size;

		return *this;
	}

	auto tilesheet_t::clear() -> void
	{
		this->m_bitmaps.clear();
		this->m_tile_size = { 0,0 };
	}

	auto tilesheet_t::count() const -> size_t
	{
		return this->m_bitmaps.size();
	}

	auto tilesheet_t::is_empty() const -> bool
	{
		return !this->m_bitmaps.size();
	}

	auto tilesheet_t::tile_size() const -> wind::add_reference_t <const ALLEGRO::SIZE<size_t>>
	{
		return this->m_tile_size;
	}

	auto tilesheet_t::at(size_t index) -> tilesheet_t::reference_element_type
	{
		ALLEGRO::ASSERT(index < this->m_bitmaps.size());
		return this->m_bitmaps[index];
	}

	auto tilesheet_t::at(size_t index) const -> tilesheet_t::const_reference_element_type
	{
		ALLEGRO::ASSERT(index < this->m_bitmaps.size());
		return this->m_bitmaps[index];
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
		return iterator(this->m_bitmaps.begin());
	}

	auto tilesheet_t::end() -> tilesheet_t::iterator
	{
		return iterator(this->m_bitmaps.end());
	}

	auto tilesheet_t::cbegin() const -> tilesheet_t::const_iterator
	{
		return const_iterator(this->m_bitmaps.cbegin());
	}

	auto tilesheet_t::cend() const -> tilesheet_t::const_iterator
	{
		return const_iterator(this->m_bitmaps.cend());
	}

	auto tilesheet_t::rbegin() -> tilesheet_t::reverse_iterator
	{
		return reverse_iterator(this->m_bitmaps.rbegin());
	}

	auto tilesheet_t::rend() -> tilesheet_t::reverse_iterator
	{
		return reverse_iterator(this->m_bitmaps.rend());
	}

	auto tilesheet_t::crbegin() const -> tilesheet_t::const_reverse_iterator
	{
		return const_reverse_iterator(this->m_bitmaps.crbegin());
	}

	auto tilesheet_t::crend() const -> tilesheet_t::const_reverse_iterator
	{
		return const_reverse_iterator(this->m_bitmaps.crend());
	}

	namespace tilesheet
	{
		size_t populate_vector(ALLEGRO::BITMAP& bitmap, ALLEGRO::SIZE<size_t> tile_size, std::vector<ALLEGRO::BITMAP>& bitmaps)
		{
			ALLEGRO::SIZE<size_t> bitmap_size{ al::get_bitmap_dimensions(bitmap) };
			ALLEGRO::BITMAP sub{ nullptr };
			ALLEGRO::BITMAP target{};
			ALLEGRO::RECTANGLE<size_t> source = { {0,0}, tile_size };

			for (source.position.y = 0; source.position.y < bitmap_size.height; source.position.y += tile_size.height)
			{
				for (source.position.x = 0; source.position.x < bitmap_size.width; source.position.x += tile_size.width)
				{
					if (!(sub = al::create_sub_bitmap(bitmap, source)))
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

	namespace datafile
	{
		namespace object
		{
			bool tilesheet_parser(data_t& data, object_t& object)
			{
				ALLEGRO::SIZE<int32_t> size{ 0,0 };
				int32_t index{ -1 };
				string_t file{};
				json_t json{};
				string_t name{};
				std::vector<ALLEGRO::BITMAP> bitmaps{};
				std::vector<ALLEGRO::BITMAP> tiles{};

				if (!data.find_data("file", file))
				{
					return false;
				}

				if (load_json(json, file) < 0)
				{
					return false;
				}

				if (json.get_type() != WIND::JSON::TYPE_OBJECT)
				{
					return false;
				}

				const json_object_t& json_object = json.get_as_object();

				if (json_object.size())
				{
					const json_t& tilesheet_object = (*json_object.cbegin());

					if (tilesheet_object.get_type() != WIND::JSON::TYPE_OBJECT)
					{
						return false;
					}

					const json_object_t& json_data = tilesheet_object.get_as_object();

					if (json_data.size())
					{
						json_object_t::const_iterator it = json_data.find("name");
						if (it == json_data.cend())
						{
							return false;
						}

						name = it->get_as_string();

						it = json_data.find("bitmaps");
						if (it == json_data.cend())
						{
							return false;
						}

						const json_array_t bitmap_array = it->get_as_array();

						for (auto bit = bitmap_array.cbegin(); bit != bitmap_array.cend(); ++bit)
						{
							if (bit->get_type() != WIND::JSON::TYPE_STRING)
							{
								return false;
							}

							string_t bitmap_name = bit->get_as_string();

							object_t bitmap = data.find_object(bitmap_name);

							if (!bitmap.m_object)
							{
								return false;
							}

							bitmaps.push_back(std::static_pointer_cast<ALLEGRO::BITMAP_DATA>(bitmap.m_object));
						}
					}
				}

				if (!data.find_data("width", size.width))
				{
					return false;
				}

				if (!data.find_data("height", size.height))
				{
					return false;
				}

				tiles.push_back(al::create_bitmap(size));

				if (!tiles[0])
				{
					return false;
				}

				ALLEGRO::BITMAP target{ al::get_target_bitmap() };
				al::set_target_bitmap(tiles[0]);
				al::clear_to_color(wind::map_rgb_i(0xff00ff));
				al::convert_mask_to_alpha(tiles[0], wind::map_rgb_i(0xff00ff));
				al::set_target_bitmap(target);

				for (auto b : bitmaps)
				{
					if (tilesheet::populate_vector(b, size, tiles) == 0)
					{
						return false;
					}
				}

				object.m_object = std::make_shared<tilesheet_t>(tiles, size);

				return true;
			}
		}
	}
}