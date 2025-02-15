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
		export auto set_working_directory() -> bool;
		export auto get_working_directory() -> string_t;
		export auto get_path_part(const string_t& filepath) -> string_t;
		export auto get_file_part(const string_t& filepath) -> string_t;
		export auto get_extension_part(const string_t& filepath) -> string_t;
		export auto find_all_files(const string_t& filepath, const string_t& ext, std::vector<string_t>& vec) -> size_t;
		export auto split_filepath(const string_t& path, string_t& dir, string_t& basename, string_t& extension) -> void;
		export auto make_canonical(const string_t& str) -> string_t;
	}
}
