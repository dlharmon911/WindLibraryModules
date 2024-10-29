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
		int32_t read(const string_t& filename, dson_t& config_file);
		int32_t write(const string_t& filename, dson_t& config_file);
		int32_t expand_string(const dson_t& config_file, const string_t& name, string_t& output);

		string_t get_string(dson_t& config_file, const string_t& name, const string_t& default_value);
		void set_string(dson_t& config_file, const string_t& name, const string_t& value);

		template <typename T>
		T get_as(dson_t& config_file, const string_t& name, const T default_value) = delete;

		template <> int32_t get_as(dson_t& config_file, const string_t& name, const int32_t default_value);
		template <> double get_as(dson_t& config_file, const string_t& name, const double default_value);
		template <> bool get_as(dson_t& config_file, const string_t& name, const bool default_value);

		template <typename T>
		void set_as(dson_t& config_file, const string_t& name, const T value) = delete;
		template <> void set_as(dson_t& config_file, const string_t& name, int32_t value);
		template <>	void set_as(dson_t& config_file, const string_t& name, double value);
		template <> void set_as(dson_t& config_file, const string_t& name, bool value);
	}
}
