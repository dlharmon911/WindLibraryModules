export module wind:path;

import <vector>;
import <cstdint>;
import allegro;
import :base;
import :string;

namespace wind
{
	namespace path
	{
		export bool set_working_directory();
		export string_t get_working_directory();
		export string_t get_path_part(const string_t& filepath);
		export string_t get_file_part(const string_t& filepath);
		export string_t get_extension_part(const string_t& filepath);
		export size_t find_all_files(const string_t& filepath, const string_t& ext, std::vector<string_t>& vec);
		export void split_filepath(const string_t& path, string_t& dir, string_t& basename, string_t& extension);
		export string_t make_canonical(const string_t& str);
	}

}
