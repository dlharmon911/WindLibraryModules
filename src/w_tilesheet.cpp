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

	tilesheet_t& tilesheet_t::operator = (const tilesheet_t& tilesheet)
	{
		this->m_bitmaps = tilesheet.m_bitmaps;
		this->m_tile_size = tilesheet.m_tile_size;

		return *this;
	}

	void tilesheet_t::clear()
	{
		this->m_bitmaps.clear();
		this->m_tile_size = { 0,0 };
	}

	size_t tilesheet_t::count() const
	{
		return this->m_bitmaps.size();
	}

	bool tilesheet_t::is_empty() const
	{
		return !this->m_bitmaps.size();
	}

	const ALLEGRO::SIZE<size_t>& tilesheet_t::tile_size() const
	{
		return this->m_tile_size;
	}

	tilesheet_t::reference_element_type tilesheet_t::at(size_t index)
	{
		ALLEGRO::ASSERT(index < this->m_bitmaps.size());
		return this->m_bitmaps[index];
	}

	tilesheet_t::const_reference_element_type tilesheet_t::at(size_t index) const
	{
		ALLEGRO::ASSERT(index < this->m_bitmaps.size());
		return this->m_bitmaps[index];
	}

	tilesheet_t::reference_element_type tilesheet_t::operator [](size_t index)
	{
		return this->at(index);
	}

	tilesheet_t::const_reference_element_type tilesheet_t::operator [](size_t index) const
	{
		return this->at(index);
	}

	tilesheet_t::iterator tilesheet_t::begin()
	{
		return iterator(this->m_bitmaps.begin());
	}

	tilesheet_t::iterator tilesheet_t::end()
	{
		return iterator(this->m_bitmaps.end());
	}

	tilesheet_t::const_iterator tilesheet_t::cbegin() const
	{
		return const_iterator(this->m_bitmaps.cbegin());
	}

	tilesheet_t::const_iterator tilesheet_t::cend() const
	{
		return const_iterator(this->m_bitmaps.cend());
	}

	tilesheet_t::reverse_iterator tilesheet_t::rbegin()
	{
		return reverse_iterator(this->m_bitmaps.rbegin());
	}

	tilesheet_t::reverse_iterator tilesheet_t::rend()
	{
		return reverse_iterator(this->m_bitmaps.rend());
	}

	tilesheet_t::const_reverse_iterator tilesheet_t::crbegin() const
	{
		return const_reverse_iterator(this->m_bitmaps.crbegin());
	}

	tilesheet_t::const_reverse_iterator tilesheet_t::crend() const
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

				if (json.type() != WIND::JSON::TYPE_OBJECT)
				{
					return false;
				}

				const json_object_t& json_object = json.get_as_object();

				if (json_object.size())
				{
					const json_t& tilesheet_object = (*json_object.cbegin());

					if (tilesheet_object.type() != WIND::JSON::TYPE_OBJECT)
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
							if (bit->type() != WIND::JSON::TYPE_STRING)
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

				ALLEGRO::BITMAP target{al::get_target_bitmap()};
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
