export module wind:json.initializer;

import <any>;
import <functional>;
import <vector>;
import <map>;
import <string>;
import <memory>;
import allegro;
import :base;
import :string;
import :error;
import :json.error;
import :json.object;

namespace WIND
{
	namespace JSON
	{
		namespace INITIALIZER
		{
			namespace TYPE
			{
				export enum
				{
					INVALID = -1,
					BOOLEAN,
					INT8,
					UINT8,
					INT16,
					UINT16,
					INT32,
					UINT32,
					INT64,
					UINT64,
					FLOAT,
					DOUBLE,
					STRING,
					USER_TYPE = 0x100
				};
			}
		}
	}
}

namespace wind
{
	namespace json
	{
		namespace initializer
		{
			export template <typename T>
				auto parse(const json_t& json, T& value) -> int32_t
			{
				return -1;
			}

			export template <> auto parse(const json_t& json, bool& value) -> int32_t;
			export template <> auto parse(const json_t& json, double& value) -> int32_t;
			export template <> auto parse(const json_t& json, float& value) -> int32_t;
			export template <> auto parse(const json_t& json, int8_t& value) -> int32_t;
			export template <> auto parse(const json_t& json, uint8_t& value) -> int32_t;
			export template <> auto parse(const json_t& json, int16_t& value) -> int32_t;
			export template <> auto parse(const json_t& json, uint16_t& value) -> int32_t;
			export template <> auto parse(const json_t& json, int32_t& value) -> int32_t;
			export template <> auto parse(const json_t& json, uint32_t& value) -> int32_t;
			export template <> auto parse(const json_t& json, int64_t& value) -> int32_t;
			export template <> auto parse(const json_t& json, uint64_t& value) -> int32_t;
			export template <> auto parse(const json_t& json, wind::string_t& value) -> int32_t;

			export auto parse(const json_t& json, std::any& value, int32_t type) -> int32_t;

			export using func_t = std::function<auto (const json_t& json, std::any& value)->int32_t>;

			export auto register_defaults(bool register_functions = true) -> void;
			export auto register_function(int32_t type, func_t function) -> int32_t;
			export auto unregister_function(int32_t type) -> int32_t;


			namespace object
			{
				export template <typename T> auto parse(const json_object_t& json, const string_t& id, T& value) -> int32_t
				{
					auto it{ json.find(id) };
					if (it == json.cend())
					{
						wind::error::report_error("Could not find \"" + id + "\" inside JSON Object");
						return -1;
					}

					return initializer::parse<T>(*it, value);
				}


				export template <typename T, typename Q> auto parse(const json_object_t& json, const string_t& id, std::pair<T, Q>& value) -> int32_t
				{
					auto it{ json.find(id) };
					if (it == json.cend())
					{
						wind::error::report_error("Could not find \"" + id + "\" inside JSON Object");
						return -1;
					}

					if (initializer::parse<T>(*it, value.first) < 0)
					{
						return -1;
					}

					if (initializer::parse<Q>(*it, value.second) < 0)
					{
						return -1;
					}

					return 0;
				}
			}
		}
	}
}