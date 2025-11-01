export module wind:path;

import :base;
import :string;

namespace wind::path
{
	export auto set_working_directory() -> bool
	{
		ALLEGRO::PATH base_path = al::get_standard_path(ALLEGRO::RESOURCES_PATH);

		if (base_path)
		{
			al::make_path_canonical(base_path);
			al::change_directory(al::path_cstr(base_path, ALLEGRO::NATIVE_PATH_SEP));
			return true;
		}

		return false;
	}

	export auto get_working_directory() -> string_t
	{
		constexpr size_t size = 2048;
		std::array<char, size> buffer{ "" };

		return string_t(_getcwd(buffer.data(), size));
	}

	export auto is_local_path(const wind::string_t& path) -> bool
	{
		wind::string_t working{ wind::path::get_working_directory() + ALLEGRO::NATIVE_PATH_SEP + path };
		ALLEGRO::FS_ENTRY entry{ al::create_fs_entry(working.c_str()) };

		if (al::get_fs_entry_mode(entry) & ALLEGRO::FILE_MODE_ISDIR)
		{
			return true;
		}

		return false;
	}


	export auto get_file_part(const string_t& filepath) -> string_t
	{
		string_t out;
		ALLEGRO::PATH path = al::create_path(filepath.c_str());
		if (path)
		{
			out = al::get_path_filename(path);
		}
		return out;
	}

	export auto get_path_part(const string_t& filepath) -> string_t
	{
		string_t filename = get_file_part(filepath);

		return filepath.substr(0, filepath.length() - filename.size());
	}

	export auto make_canonical(const string_t& str) -> string_t
	{
		string_t out;

		for (string_t::const_iterator it = str.cbegin(); it != str.cend(); ++it)
		{
			auto& c = (*it);

			if (c == '/' || c == '\\')
			{
				out.push_back(ALLEGRO::NATIVE_PATH_SEP);
			}
			else
			{
				out.push_back(c);
			}
		}

		return out;
	}

	export auto get_extension_part(const string_t& filepath) -> string_t
	{
		size_t size = filepath.rfind('.');

		if (size == string_t::npos || (size + 1) == filepath.size())
		{
			return "";
		}

		return filepath.substr(size + 1);
	}

	export auto process_entry(std::vector<string_t>& vec, const string_t& ext, const ALLEGRO::FS_ENTRY& next) -> int32_t
	{
		ALLEGRO::PATH path{};
		string_t filename{};
		string_t extension{};

		if (!(al::get_fs_entry_mode(next) & ALLEGRO::FILE_MODE_ISFILE))
		{
			return 0;
		}

		path = al::create_path(al::get_fs_entry_name(next));
		if (!path)
		{
			return -1;
		}

		filename = al::get_path_filename(path);
		extension = al::get_path_extension(path);

		if (extension.size() > 0 && extension[0] == '.')
		{
			extension = extension.substr(1, extension.size() - 1);
		}

		if (ext == "*" || ext == extension)
		{
			vec.push_back(path::get_file_part(al::get_fs_entry_name(next)));
		}

		return 0;
	}

	export auto find_all_files(const string_t& filepath, const string_t& ext, std::vector<string_t>& vec) -> size_t
	{
		ALLEGRO::FS_ENTRY next;
		size_t size = vec.size();
		ALLEGRO::FS_ENTRY entry = al::create_fs_entry(filepath.c_str());

		if (!entry || !(al::get_fs_entry_mode(entry) & ALLEGRO::FILE_MODE_ISDIR) || al::open_directory(entry))
		{
			return 0;
		}

		while (next = al::read_directory(entry))
		{
			if (process_entry(vec, ext, next) < 0)
			{
				break;
			}
		}

		al::close_directory(entry);

		return vec.size() - size;
	}

	export auto split_filepath(const string_t& path, string_t& dir, string_t& basename, string_t& extension) -> void
	{
		string_t ptemp = make_canonical(path);

		string_t filename = get_file_part(ptemp);
		size_t pos = filename.rfind('.');

		dir.clear();
		basename.clear();
		extension.clear();

		if (pos == string_t::npos)
		{
			basename = filename;
		}
		else
		{
			basename = filename.substr(0, pos);

			++pos;

			if (pos < filename.length())
			{
				extension = filename.substr(pos);
			}
		}

		if (ptemp.size() > filename.size())
		{
			dir = ptemp.substr(0, ptemp.size() - filename.size());
		}
	}
}
