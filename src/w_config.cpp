module wind;

import <string>;
import <cstdint>;
import std;
import :base;
import :dson;
import :config;
import :string;

namespace wind
{
	namespace config
	{
		auto read(const string_t& filename, dson_t& config_file) -> int32_t
		{
			dson_t manifest;

			if (!dson_t::read(manifest, filename))
			{
				return -1;
			}

			config_file.clear();

			if (!manifest.contains("manifest"))
			{
				return -1;
			}

			dson_t& _manifest = manifest["manifest"];

			if (!_manifest.contains("path"))
			{
				return -1;
			}

			dson_t& _manifest_path = _manifest["path"];

			for (auto it = _manifest_path.cbegin(); it != _manifest_path.cend(); ++it)
			{
				string_t key = it.key();
				string_t input = it->get_content();

				config_file["path"][key].set_content(input);
			}

			if (!_manifest.contains("file"))
			{
				return -1;
			}

			dson_t& _manifest_file = _manifest["file"];

			for (auto it = _manifest_file.begin(); it != _manifest_file.end(); ++it)
			{
				string_t key = it.key();
				string_t input = it->get_content();
				string_t filename;
				dson_t data;

				config_file["file"][key].set_content(input);

				if (config::expand_string(config_file, input, filename) < 0)
				{
					return -1;
				}

				if (!dson_t::read(data, filename))
				{
					return -1;
				}
				auto dit = data.begin();
				config_file[dit.key()] = (*dit);
			}

			return 0;
		}

		auto write(const string_t& filename, dson_t& config_file) -> int32_t
		{
			for (auto i = config_file.begin(); i != config_file.end(); ++i)
			{
				string_t key = i.key();

				if (!(key == "path" || key == "file"))
				{
					string_t file_shortcut = string_t("$(file.") + key + ")";
					string_t file_name;
					if (expand_string(config_file, file_shortcut, file_name) < 0)
					{
						return -1;
					}

					dson_t temp;
					temp[key] = *i;

					if (!dson_t::write(temp, file_name))
					{
						return -1;
					}
				}
			}

			return 0;
		}

		auto expand_string(const dson_t& config_file, const string_t& name, string_t& output) -> int32_t
		{
			bool has_shortcut = false;
			size_t i = 0;

			output.clear();

			while (i < name.size())
			{
				if (name[i] == '$')
				{
					has_shortcut = true;
					string_t s;

					++i;
					if (name[i] != '(')
					{
						return -1;
					}
					++i;
					while (name[i] != ')')
					{
						if (i == name.size())
						{
							return -1;
						}
						s.push_back(name[i]);
						++i;
					}
					dson_t sk = config_file.get_property(s);
					string_t shortcut = sk.get_content();
					if (shortcut.size() <= 0)
					{
						return -1;
					}

					output.append(shortcut);
				}
				else
				{
					output.push_back(name[i]);
				}
				++i;
			}

			if (has_shortcut)
			{
				string_t input = output;
				output.clear();
				return expand_string(config_file, input, output);
			}

			return 0;
		}

		auto get_content(dson_t& config_file, const string_t& name, const string_t& default_value) -> string_t
		{
			string_t expansion;

			if (expand_string(config_file, name, expansion) < 0)
			{
				return string_t();
			}

			dson_t& d = config_file.get_property(expansion);
			if (d.empty())
			{
				d.set_content(default_value);
			}

			if (expand_string(config_file, d.get_content(), expansion) < 0)
			{
				return string_t();
			}

			return expansion;
		}

		auto set_content(dson_t& config_file, const string_t& name, const string_t& value) -> void
		{
			config_file.get_property(name).set_content(value);
		}

		template <>
		auto get_as(dson_t& config_file, const string_t& name, const int32_t default_value) -> int32_t
		{
			string_t str = config::get_content(config_file, name, std::to_string(default_value));
			return std::atoi(str.c_str());
		}

		template <>
		auto get_as(dson_t& config_file, const string_t& name, const double default_value) -> double
		{
			string_t str = config::get_content(config_file, name, std::to_string(default_value));
			return std::atof(str.c_str());
		}

		template <>
		auto get_as(dson_t& config_file, const string_t& name, const bool default_value) -> bool
		{
			string_t str = config::get_content(config_file, name, (default_value ? "true" : "false"));
			return string::to_lower(str) == "true";
		}

		template <>
		auto set_as(dson_t& config_file, const string_t& name, int32_t value) -> void
		{
			config::set_content(config_file, name, std::to_string(value));
		}

		template <>
		auto set_as(dson_t& config_file, const string_t& name, double value) -> void
		{
			config::set_content(config_file, name, std::to_string(value));
		}

		template <>
		auto set_as(dson_t& config_file, const string_t& name, bool value) -> void
		{
			config::set_content(config_file, name, string_t(value ? "true" : "false"));
		}
	}
}