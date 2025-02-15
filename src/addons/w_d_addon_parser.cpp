module wind.d_addon;

import <cassert>;
import <memory>;
import <array>;
import <string>;
import <cstdint>;
import <any>;
import <functional>;
import allegro;
import wind;
import :base;
import :object;
import :parser;

namespace wind
{
	namespace datafile
	{
		parser_t::parser_t(d_t& datafile) : m_datafile(datafile) {}

		auto parser_t::parse(const json_t& json, d_t& datafile) -> int32_t
		{
			parser_t parser{datafile};

			return parser.parse_json(json);
		}

		auto parser_t::parse_json(const json_t& json) -> int32_t
		{
			if (json.get_type() != WIND::JSON::TYPE::OBJECT)
			{
				return -1;
			}

			const json_object_t& object = json.get_as_object();

			auto it = object.cbegin();
			if (it == object.cend())
			{
				return -1;
			}

			const json_t& j = (*it);

			if (j.get_type() != WIND::JSON::TYPE::ARRAY)
			{
				return -1;
			}

			return this->parse_array(j.get_as_array());
		}

		auto parser_t::parse_array(const json_array_t& array) -> int32_t
		{
			size_t size{ array.size() };

			if (size == 0)
			{
				return -1;
			}

			this->m_datafile = d_t(size);

			for (size_t index = 0; index < size; ++index)
			{
				const json_t& json{ array[index] };

				if (this->parse_object(json, this->m_datafile[index]) < 0)
				{
					return -1;
				}
			}

			return 0;
		}

		static auto get_type(const json_object_t& object) -> int32_t
		{
			auto it{ object.find("type") };
			if (it == object.cend())
			{
				return -1;
			}

			if (it->get_type() != WIND::JSON::TYPE::STRING)
			{
				return -1;
			}

			string_t name{ it->get_as_string() };

			return get_object_type(name);
		}

		static auto get_name(const json_object_t& object, string_t& name) -> int32_t
		{
			auto it{ object.find("name") };
			if (it == object.cend())
			{
				return -1;
			}

			if (it->get_type() != WIND::JSON::TYPE::STRING)
			{
				return -1;
			}

			name = it->get_as_string();

			return 0;
		}
;
		auto parser_t::parse_object(const json_t& json, datafile::object_t& dobject)->int32_t
		{
			std::function<auto(const json_t&, std::any&)->int32_t> function{};

			if (json.get_type() != WIND::JSON::TYPE::OBJECT)
			{
				return -1;
			}

			const json_object_t& object = json.get_as_object();

			dobject.m_type = get_type(object);

			if (dobject.m_type < 0)
			{
				return -1;
			}

			if (get_object_function(dobject.m_type, function) < 0)
			{
				return -1;
			}

			return function(json, dobject.m_any);
		}
	}
}
