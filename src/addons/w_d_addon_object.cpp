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

namespace wind
{
	namespace datafile
	{
		namespace internal
		{
			static std::unordered_map<int32_t, std::function<auto(const json_t&, std::any&)->int32_t>> function_map{};
			static std::unordered_map<string_t, int32_t> name_map{};
		}

		namespace object
		{

			namespace bitmap
			{
				auto parse(const json_t& json, std::any& any) -> int32_t;
			}

			namespace datafile
			{
				auto parse(const json_t& json, std::any& any) -> int32_t;
			}

			namespace font
			{
				auto parse(const json_t& json, std::any& any) -> int32_t;
			}

			namespace sample
			{
				auto parse(const json_t& json, std::any& any) -> int32_t;
			}

			namespace text
			{
				auto parse(const json_t& json, std::any& any) -> int32_t;
			}

			namespace tilesheet
			{
				auto parse(const json_t& json, std::any& any) -> int32_t;
			}
		}

		static auto do_registration(bool reg) -> void
		{
			static bool are_defaults_registered{ false };
			static bool was_registered{ false };

			if (reg)
			{
				if (are_defaults_registered)
				{
					return;
				}

				if (!was_registered)
				{
					was_registered = true;
					atexit(unregister_object_defaults);
				}

				std::array<std::function<auto(const json_t&, std::any&)->int32_t>, WIND::DATAFILE::OBJECT_TYPE::COUNT> function_array
				{ {
					object::datafile::parse,
					object::bitmap::parse,
					object::font::parse,
					object::text::parse,
					object::sample::parse,
					object::tilesheet::parse
				} };

				for (int32_t i = 0; i < WIND::DATAFILE::OBJECT_TYPE::COUNT; ++i)
				{
					register_object_type(i, WIND::DATAFILE::DEFAULT_OBJECT_NAMES[i], function_array[i]);
				}

				are_defaults_registered = true;
			}
			else
			{
				if (!are_defaults_registered)
				{
					internal::function_map.clear();
					internal::name_map.clear();
				}

				are_defaults_registered = false;
			}
		}

		auto unregister_object_defaults() -> void
		{
			do_registration(false);
		}

		auto register_object_defaults() -> void
		{
			do_registration(true);
		}

		auto get_object_name(int32_t type, string_t& name) -> int32_t
		{
			for (auto it = internal::name_map.cbegin(); it != internal::name_map.cend(); ++it)
			{
				if (it->second == type)
				{
					name = it->first;
					return 0;
				}
			}

			return -1;
		}

		auto get_object_type(const string_t& name) -> int32_t
		{
			auto it = internal::name_map.find(string::to_lower(name));
			if (it == internal::name_map.cend())
			{
				return -1;
			}

			return it->second;
		}

		auto register_object_type(int32_t type, const string_t& name, std::function<auto(const json_t&, std::any&)->int32_t>& function) -> int32_t
		{
			if (type < 0 || !name.size() || !function)
			{
				return -1;
			}

			// verify name is either undefined or returned type matches argument type
			auto t = get_object_type(name);
			if (t >= 0 && t != type)
			{
				return -1;
			}

			// verify type is either undefined or returned name matches argument name
			string_t n{};
			if (get_object_name(type, n) > 0 && n != name)
			{
				return -1;
			}

			internal::function_map[type] = function;
			internal::name_map[string::to_lower(name)] = type;

			return 0;
		}

		auto get_object_function(int32_t type, std::function<auto(const json_t&, std::any&)->int32_t>& function) -> int32_t
		{
			auto it = internal::function_map.find(type);
			if (it != internal::function_map.cend())
			{
				function = it->second;
				return 0;
			}

			return -1;
		}
	}
}
