export module wind:json.functions;

import :base;
import :hex;
import :file.iterator;
import :json.constants;
import :json.base;
import :json.tokenizer;
import :string;
import :log;

namespace wind::json
{
	namespace parser
	{
		export auto parse_json(const json::object_t& object, const string_t& name, std::any& any) -> int32_t
		{
			auto it = object.find(name);

			if (it == object.cend())
			{
				wind::lout << "Missing key in JSON object: " << name << "\n";
				return -1;
			}

			any = it->second;

			return 0;
		}

		export auto parse_json_object(const json::object_t& object, const string_t& name, std::any& any) -> int32_t
		{
			auto it = object.find(name);

			if (it == object.cend())
			{
				wind::lout << "Missing key in JSON object: " << name << "\n";
				return -1;
			}
			if (it->second.get_type() != WIND::JSON::TYPE::OBJECT)
			{
				wind::lout << "Invalid JSON format: Key '" << name << "' is not an object\n";
				return -1;
			}

			any = it->second.get_as_object();

			return 0;
		}

		export auto parse_json_array(const json::object_t& object, const string_t& name, std::any& any) -> int32_t
		{
			auto it = object.find(name);

			if (it == object.cend())
			{
				wind::lout << "Missing key in JSON object: " << name << "\n";
				return -1;
			}
			if (it->second.get_type() != WIND::JSON::TYPE::ARRAY)
			{
				wind::lout << "Invalid JSON format: Key '" << name << "' is not an array\n";
				return -1;
			}

			any = it->second.get_as_array();

			return 0;
		}

		export auto parse_json_string(const json::object_t& object, const string_t& name, std::any& any) -> int32_t
		{
			auto it = object.find(name);
			
			if (it == object.cend())
			{
				wind::lout << "Missing key in JSON object: " << name << "\n";
				return -1;
			}
			
			if (it->second.get_type() != WIND::JSON::TYPE::STRING)
			{
				wind::lout << "Invalid JSON format: Key '" << name << "' is not a string\n";
				return -1;
			}
			
			any = it->second.get_as_string();
			
			return 0;
		}

		export template <typename T> auto parse_json_number(const json::object_t& object, const string_t& name, std::any& any) -> int32_t requires std::is_arithmetic_v<T>
		{
			auto it = object.find(name);
			
			if (it == object.cend())
			{
				wind::lout << "Missing key in JSON object: " << name << "\n";
				return -1;
			}
			
			if (it->second.get_type() != WIND::JSON::TYPE::NUMBER)
			{
				wind::lout << "Invalid JSON format: Key '" << name << "' is not a number\n";
				return -1;
			}

			any = static_cast<T>(it->second.get_as_number());

			return 0;
		}

		using ftype = std::function< auto (const json::object_t& object, const string_t& name, std::any& any) -> int32_t>;

		const std::unordered_map<WIND::JSON::DATA_TYPE, ftype> parsers
		{
			{ WIND::JSON::DATA_TYPE::JSON, parse_json },
			{ WIND::JSON::DATA_TYPE::OBJECT, parse_json_object },
			{ WIND::JSON::DATA_TYPE::ARRAY, parse_json_array },
			{ WIND::JSON::DATA_TYPE::STRING, parse_json_string },
			{ WIND::JSON::DATA_TYPE::FLOAT, parse_json_number<float> },
			{ WIND::JSON::DATA_TYPE::DOUBLE, parse_json_number<double> },
			{ WIND::JSON::DATA_TYPE::INT8, parse_json_number<int8_t> },
			{ WIND::JSON::DATA_TYPE::INT16, parse_json_number<int16_t> },
			{ WIND::JSON::DATA_TYPE::INT32, parse_json_number<int32_t> },
			{ WIND::JSON::DATA_TYPE::INT64, parse_json_number<int64_t> },
			{ WIND::JSON::DATA_TYPE::UINT8, parse_json_number<uint8_t> },
			{ WIND::JSON::DATA_TYPE::UINT16, parse_json_number<uint16_t> },
			{ WIND::JSON::DATA_TYPE::UINT32, parse_json_number<uint32_t> },
			{ WIND::JSON::DATA_TYPE::UINT64, parse_json_number<uint64_t> },
			{ WIND::JSON::DATA_TYPE::BOOLEAN, parse_json_number<bool> }
		};

		export auto parse(const json::object_t& object, const string_t& name, std::any& any, WIND::JSON::DATA_TYPE type) -> int32_t
		{
			auto it = parsers.find(type);

			if (it == parsers.cend())
			{
				wind::lout << "No parser for type: 0x" << hex_to_string(std::to_underlying(type)) << "\n";
				return -1;
			}

			return it->second(object, name, any);
		}

		export template <typename T> auto parse(const json::object_t& obj, const string_t& name, T& value) -> int32_t
		{
			return -1;
		}

		export template <> inline auto parse<string_t>(const json::object_t& obj, const string_t& name, string_t& value) -> int32_t
		{
			return parse_json_string(obj, name, (std::any&)value);
		}

		export template <> inline auto parse<bool>(const json::object_t& obj, const string_t& name, bool& value) -> int32_t
		{
			return parse_json_number<bool>(obj, name, (std::any&)value);
		}

		export template <> inline auto parse<int8_t>(const json::object_t& obj, const string_t& name, int8_t& value) -> int32_t
		{
			return parse_json_number<int8_t>(obj, name, (std::any&)value);
		}

		export template <> inline auto parse<int16_t>(const json::object_t& obj, const string_t& name, int16_t& value) -> int32_t
		{
			return parse_json_number<int16_t>(obj, name, (std::any&)value);
		}

		export template <> inline auto parse<int32_t>(const json::object_t& obj, const string_t& name, int32_t& value) -> int32_t
		{
			return parse_json_number<int32_t>(obj, name, (std::any&)value);
		}

		export template <> inline auto parse<int64_t>(const json::object_t& obj, const string_t& name, int64_t& value) -> int32_t
		{
			return parse_json_number<int64_t>(obj, name, (std::any&)value);
		}

		export template <> inline auto parse<uint8_t>(const json::object_t& obj, const string_t& name, uint8_t& value) -> int32_t
		{
			return parse_json_number<uint8_t>(obj, name, (std::any&)value);
		}

		export template <> inline auto parse<uint16_t>(const json::object_t& obj, const string_t& name, uint16_t& value) -> int32_t
		{
			return parse_json_number<uint16_t>(obj, name, (std::any&)value);
		}

		export template <> inline auto parse<uint32_t>(const json::object_t& obj, const string_t& name, uint32_t& value) -> int32_t
		{
			return parse_json_number<uint32_t>(obj, name, (std::any&)value);
		}

		export template <> inline auto parse<uint64_t>(const json::object_t& obj, const string_t& name, uint64_t& value) -> int32_t
		{
			return parse_json_number<uint64_t>(obj, name, (std::any&)value);
		}

		export template <> inline auto parse<float>(const json::object_t& obj, const string_t& name, float& value) -> int32_t
		{
			return parse_json_number<float>(obj, name, (std::any&)value);
		}

		export template <> inline auto parse<double>(const json::object_t& obj, const string_t& name, double& value) -> int32_t
		{
			return parse_json_number<double>(obj, name, (std::any&)value);
		}

		export template <> inline auto parse<json_t>(const json::object_t& obj, const string_t& name, json_t& value)->int32_t
		{
			return parse_json(obj, name, (std::any&)value);
		}

		export template <> inline auto parse<json::object_t>(const json::object_t& obj, const string_t& name, json::object_t& value)->int32_t
		{
			return parse_json_object(obj, name, (std::any&)value);
		}

		export template <> inline auto parse<json::array_t>(const json::object_t& obj, const string_t& name, json::array_t& value)->int32_t
		{
			return parse_json_array(obj, name, (std::any&)value);
		}
	}
}
