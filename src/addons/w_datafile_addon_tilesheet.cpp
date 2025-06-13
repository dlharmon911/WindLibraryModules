module wind.datafile_addon;

import <string>;
import <cstdint>;
import <vector>;
import <any>;
import allegro;
import wind;
import :base;
import :object;

namespace wind
{
	namespace datafile::object::tilesheet
	{
		using element_type = typename tilesheet_t;

		using data_t = struct data_tag_t
		{
			std::vector<ALLEGRO::BITMAP> m_bitmaps{};
			ALLEGRO::VECTOR_2D<int32_t> m_size{ 0, 0 };
		};

		static auto generate_object(const data_t& data, std::any& any) -> int32_t
		{
			tilesheet_t tilesheet{};

			if (tilesheet.generate(data.m_bitmaps, data.m_size) < 0)
			{
				return -1;
			}

			any = tilesheet;

			return 0;
		}

		static auto parse_bitmaps(const json_t& json, std::vector<ALLEGRO::BITMAP>& bitmap_array) -> int32_t
		{
			bitmap_array.clear();

			if (json.get_type() == WIND::JSON::TYPE::OBJECT)
			{
				std::any any{};

				if (bitmap::parse(json, any) < 0)
				{
					return -1;
				}

				bitmap_array.push_back(std::any_cast<ALLEGRO::BITMAP>(any));
			}
			else
			{
				if (json.get_type() == WIND::JSON::TYPE::ARRAY)
				{
					std::vector<std::any> any_array{};

					if (object::parse_array(json, any_array, bitmap::parse) < 0)
					{
						return -1;
					}

					for (auto& any : any_array)
					{
						bitmap_array.push_back(std::any_cast<ALLEGRO::BITMAP>(any));
					}
				}
				else
				{
					return -1;
				}
			}

			return 0;
		}

		static auto parse_data(const json_t& json, data_t& value) -> int32_t
		{
			if (json.get_type() != WIND::JSON::TYPE::OBJECT)
			{
				return -1;
			}

			const json_object_t& object = static_cast<const json_object_t&>(json);

			auto it = object.find("bitmap");
			if (it == object.cend())
			{
				return -1;
			}
			if (parse_bitmaps(*it, value.m_bitmaps) < 0)
			{
				return -1;
			}

			it = object.find("width");
			if (it == object.cend())
			{
				return -1;
			}
			if (wind::json::initializer::parse<int32_t>(*it, value.m_size.get_x()) < 0)
			{
				return -1;
			}

			it = object.find("height");
			if (it == object.cend())
			{
				return -1;
			}
			if (wind::json::initializer::parse<int32_t>(*it, value.m_size.get_y()) < 0)
			{
				return -1;
			}


			return 0;
		}

		auto parse(const json_t& json, std::any& any) -> int32_t
		{
			data_t data{};

			if (parse_data(json, data) < 0)
			{
				return -1;
			}

			if (generate_object(data, any) < 0)
			{
				return -1;
			}

			return 0;
		}
	}
}
