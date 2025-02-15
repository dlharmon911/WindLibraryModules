module wind;

import <any>;
import <functional>;
import <map>;
import <string>;
import <cstdint>;
import allegro;
import :base;
import :string;
import :json.error;
import :json.object;
import :json.initializer;

namespace wind
{
	namespace json
	{
		namespace initializer
		{
			namespace internal
			{
				std::map<int32_t, func_t> m_map{};
			}

			template <> auto parse(const json_t& json, bool& value) -> int32_t
			{
				if (json.get_type() != WIND::JSON::TYPE::BOOLEAN)
				{
					return -1;
				}

				bool json_value = json.get_as_boolean();

				value = json_value;

				return 0;
			}

			template <> auto parse(const json_t& json, double& value) -> int32_t
			{
				if (json.get_type() != WIND::JSON::TYPE::NUMBER)
				{
					return -1;
				}

				double json_value = json.get_as_number();

				value = json_value;

				return 0;
			}

			template <> auto parse(const json_t& json, float& value) -> int32_t
			{
				double json_value{ 0.0 };

				if (parse(json, json_value) < 0)
				{
					return -1;
				}

				value = (float)json_value;

				return 0;
			}

			template <> auto parse(const json_t& json, int8_t& value) -> int32_t
			{
				double json_value{ 0.0 };

				if (parse(json, json_value) < 0)
				{
					return -1;
				}

				value = (int8_t)json_value;

				return 0;
			}

			template <> auto parse(const json_t& json, uint8_t& value) -> int32_t
			{
				double json_value{ 0.0 };

				if (parse(json, json_value) < 0)
				{
					return -1;
				}

				value = (uint8_t)json_value;

				return 0;
			}

			template <> auto parse(const json_t& json, int16_t& value) -> int32_t
			{
				double json_value{ 0.0 };

				if (parse(json, json_value) < 0)
				{
					return -1;
				}

				value = (int16_t)json_value;

				return 0;
			}

			template <> auto parse(const json_t& json, uint16_t& value) -> int32_t
			{
				double json_value{ 0.0 };

				if (parse(json, json_value) < 0)
				{
					return -1;
				}

				value = (uint16_t)json_value;

				return 0;
			}

			template <> auto parse(const json_t& json, int32_t& value) -> int32_t
			{
				double json_value{ 0.0 };

				if (parse(json, json_value) < 0)
				{
					return -1;
				}

				value = (int32_t)json_value;

				return 0;
			}

			template <> auto parse(const json_t& json, uint32_t& value) -> int32_t
			{
				double json_value{ 0.0 };

				if (parse(json, json_value) < 0)
				{
					return -1;
				}

				value = (uint32_t)json_value;

				return 0;
			}

			template <> auto parse(const json_t& json, int64_t& value) -> int32_t
			{
				double json_value{ 0.0 };

				if (parse(json, json_value) < 0)
				{
					return -1;
				}

				value = (int64_t)json_value;

				return 0;
			}

			template <> auto parse(const json_t& json, uint64_t& value) -> int32_t
			{
				double json_value{ 0.0 };

				if (parse(json, json_value) < 0)
				{
					return -1;
				}

				value = (uint64_t)json_value;

				return 0;
			}

			template <> auto parse(const json_t& json, wind::string_t& value) -> int32_t
			{
				if (json.get_type() != WIND::JSON::TYPE::STRING)
				{
					return -1;
				}

				wind::string_t json_value = json.get_as_string();

				value = json_value;

				return 0;
			}

			auto parse_bool(const json_t& json, std::any& value) -> int32_t
			{
				if (value.type() != typeid(bool))
				{
					return -1;
				}

				bool temp{ false };

				if (parse(json, temp) < 0)
				{
					return -1;
				}

				value = std::make_any<bool>(temp);

				return 0;
			}

			auto parse_int8(const json_t& json, std::any& value) -> int32_t
			{
				if (value.type() != typeid(int8_t))
				{
					return -1;
				}

				int8_t temp{ 0 };

				if (parse(json, temp) < 0)
				{
					return -1;
				}

				value = std::make_any<int8_t>(temp);

				return 0;
			}

			auto parse_uint8(const json_t& json, std::any& value) -> int32_t
			{
				if (value.type() != typeid(uint8_t))
				{
					return -1;
				}

				uint8_t temp{ 0 };

				if (parse(json, temp) < 0)
				{
					return -1;
				}

				value = std::make_any<uint8_t>(temp);

				return 0;
			}

			auto parse_int16(const json_t& json, std::any& value) -> int32_t
			{
				if (value.type() != typeid(int16_t))
				{
					return -1;
				}

				int16_t temp{ 0 };

				if (parse(json, temp) < 0)
				{
					return -1;
				}

				value = std::make_any<int16_t>(temp);

				return 0;
			}

			auto parse_uint16(const json_t& json, std::any& value) -> int32_t
			{
				if (value.type() != typeid(uint16_t))
				{
					return -1;
				}

				uint16_t temp{ 0 };

				if (parse(json, temp) < 0)
				{
					return -1;
				}

				value = std::make_any<uint16_t>(temp);

				return 0;
			}

			auto parse_int32(const json_t& json, std::any& value) -> int32_t
			{
				if (value.type() != typeid(int32_t))
				{
					return -1;
				}

				int32_t temp{ 0 };

				if (parse(json, temp) < 0)
				{
					return -1;
				}

				value = std::make_any<int32_t>(temp);

				return 0;
			}

			auto parse_uint32(const json_t& json, std::any& value) -> int32_t
			{
				if (value.type() != typeid(uint32_t))
				{
					return -1;
				}

				uint32_t temp{ 0 };

				if (parse(json, temp) < 0)
				{
					return -1;
				}

				value = std::make_any<uint32_t>(temp);

				return 0;
			}

			auto parse_int64(const json_t& json, std::any& value) -> int32_t
			{
				if (value.type() != typeid(int64_t))
				{
					return -1;
				}

				int64_t temp{ 0 };

				if (parse(json, temp) < 0)
				{
					return -1;
				}

				value = std::make_any<int64_t>(temp);

				return 0;
			}

			auto parse_uint64(const json_t& json, std::any& value) -> int32_t
			{
				if (value.type() != typeid(uint64_t))
				{
					return -1;
				}

				uint64_t temp{ 0 };

				if (parse(json, temp) < 0)
				{
					return -1;
				}

				value = std::make_any<uint64_t>(temp);

				return 0;
			}

			auto parse_float(const json_t& json, std::any& value) -> int32_t
			{
				if (value.type() != typeid(float))
				{
					return -1;
				}

				float temp{ 0.0f };

				if (parse(json, temp) < 0)
				{
					return -1;
				}

				value = std::make_any<float>(temp);

				return 0;
			}

			auto parse_double(const json_t& json, std::any& value) -> int32_t
			{
				if (value.type() != typeid(double))
				{
					return -1;
				}

				double temp{ 0.0 };

				if (parse(json, temp) < 0)
				{
					return -1;
				}

				value = std::make_any<double>(temp);

				return 0;
			}

			auto parse_string(const json_t& json, std::any& value) -> int32_t
			{
				if (value.type() != typeid(string_t))
				{
					return -1;
				}

				string_t temp{};

				if (parse(json, temp) < 0)
				{
					return -1;
				}

				value = std::make_any<string_t>(temp);

				return 0;
			}

			auto parse(const json_t& json, std::any& value, int32_t type) -> int32_t
			{
				if (!value.has_value())
				{
					return -1;
				}

				auto it = internal::m_map.find(type);
				if (it == internal::m_map.cend())
				{
					return -1;
				}

				return it->second(json, value);
			}

			auto register_defaults(bool register_functions) -> void
			{
				static bool m_registered{ false };

				if (register_functions)
				{
					if (!m_registered)
					{
						internal::m_map[WIND::JSON::INITIALIZER::TYPE::BOOLEAN] = parse_bool;
						internal::m_map[WIND::JSON::INITIALIZER::TYPE::INT8] = parse_int8;
						internal::m_map[WIND::JSON::INITIALIZER::TYPE::UINT8] = parse_uint8;
						internal::m_map[WIND::JSON::INITIALIZER::TYPE::INT16] = parse_int16;
						internal::m_map[WIND::JSON::INITIALIZER::TYPE::UINT16] = parse_uint16;
						internal::m_map[WIND::JSON::INITIALIZER::TYPE::INT32] = parse_int32;
						internal::m_map[WIND::JSON::INITIALIZER::TYPE::UINT32] = parse_uint32;
						internal::m_map[WIND::JSON::INITIALIZER::TYPE::INT64] = parse_int64;
						internal::m_map[WIND::JSON::INITIALIZER::TYPE::UINT64] = parse_uint64;
						internal::m_map[WIND::JSON::INITIALIZER::TYPE::FLOAT] = parse_float;
						internal::m_map[WIND::JSON::INITIALIZER::TYPE::DOUBLE] = parse_double;
						internal::m_map[WIND::JSON::INITIALIZER::TYPE::STRING] = parse_string;

						m_registered = true;
					}
				}
				else
				{
					internal::m_map.clear();
					m_registered = false;
				}
			}

			auto register_function(int32_t type, func_t function) -> int32_t
			{
				if (!function)
				{
					return -1;
				}

				if (type < WIND::JSON::INITIALIZER::TYPE::USER_TYPE)
				{
					return -1;
				}

				internal::m_map[type] = function;

				return 0;
			}

			auto unregister_function(int32_t type) -> int32_t
			{
				if (type < WIND::JSON::INITIALIZER::TYPE::USER_TYPE)
				{
					return -1;
				}

				internal::m_map.erase(type);

				return 0;
			}
		}
	}
}
