export module wind:config;

import <vector>;
import <unordered_map>;
import <string>;
import <cstdint>;
import allegro;
import :base;
import :dson;
import :string;

namespace wind
{
	namespace config
	{
		export auto read(const string_t& filename, dson_t& config_file) -> int32_t;
		export auto write(const string_t& filename, dson_t& config_file) -> int32_t;
		export auto expand_string(const dson_t& config_file, const string_t& name, string_t& output) -> int32_t;

		export template <typename T> auto get_as(dson_t& config_file, const string_t& name, const T default_value) -> T = delete;

		export template <> auto get_as(dson_t& config_file, const string_t& name, const int32_t default_value) -> int32_t;
		export template <> auto get_as(dson_t& config_file, const string_t& name, const double default_value) -> double;
		export template <> auto get_as(dson_t& config_file, const string_t& name, const bool default_value) -> bool;

		export template <typename T> auto set_as(dson_t& config_file, const string_t& name, const T value) -> void = delete;
		export template <> auto set_as(dson_t& config_file, const string_t& name, int32_t value) -> void;
		export template <>	auto set_as(dson_t& config_file, const string_t& name, double value) -> void;
		export template <> auto set_as(dson_t& config_file, const string_t& name, bool value) -> void;
	}
}