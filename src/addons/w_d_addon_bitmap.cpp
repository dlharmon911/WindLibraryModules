module wind.d_addon;

import <cassert>;
import <memory>;
import <vector>;
import <string>;
import <cstdint>;
import <any>;
import <functional>;
import <unordered_map>;
import allegro;
import wind;
import :base;
import :object;

namespace wind
{
	namespace datafile::object::bitmap
	{
		using element_type = typename ALLEGRO::BITMAP;

		using data_t = struct data_tag_t
		{
			string_t m_file{};
			bool m_masked{ false };
		};

		static auto load_data(const data_t& data, element_type& object) -> int32_t
		{
			object = al::load_bitmap(data.m_file.c_str());

			if (!object)
			{
				return -1;
			}

			if (data.m_masked)
			{
				al::convert_mask_to_alpha(object, wind::map_rgb_i(0xff00ff));
			}

			return 0;
		}
	}

	namespace json
	{
		namespace initializer
		{
			template <> auto parse(const json_t& json, datafile::object::bitmap::data_t & value) -> int32_t
			{
				if (json.get_type() != WIND::JSON::TYPE::OBJECT)
				{
					return -1;
				}

				const json_object_t& object = json.get_as_object();

				auto it = object.find("file");
				if (it == object.cend())
				{
					return -1;
				}

				if (parse<string_t>(*it, value.m_file) < 0)
				{
					return -1;
				}
				
				it = object.find("masked");
				if (it == object.cend())
				{
					value.m_masked = false;
				}
				else
				{
					if (parse<bool>(*it, value.m_masked) < 0)
					{
						return -1;
					}
				}
				return 0;
			}
		}
	}
	
	namespace datafile::object::bitmap
	{
		auto parse(const json_t& json, std::any& any) -> int32_t
		{
			element_type object{};
			data_t data{};

			if (json::initializer::parse<data_t>(json, data) < 0)
			{
				return -1;
			}

			if (load_data(data, object) < 0)
			{
				return -1;
			}

			any = object;

			return 0;
		}
	}
}
