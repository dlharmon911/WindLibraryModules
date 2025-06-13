module wind.datafile_addon;

import <string>;
import <cstdint>;
import <any>;
import allegro;
import wind;
import :base;
import :object;

namespace wind
{
	namespace datafile::object::text
	{
		using element_type = typename string_t;

		using data_t = struct data_tag_t
		{
			string_t m_text{};
		};
		
		static auto generate_object(const data_t& data, std::any& any) -> int32_t
		{
			if (data.m_text.length() == 0)
			{
				return -1;
			}

			any = data.m_text;

			return 0;
		}

		static auto parse_data(const json_t& json, data_t& value) -> int32_t
		{
			if (json.get_type() != WIND::JSON::TYPE::STRING)
			{
				return -1;
			}

			value.m_text = json.get_as<string_t>();

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
