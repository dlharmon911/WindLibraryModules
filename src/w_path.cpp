module wind;

import <string>;
import <cstdint>;
import :path;
import :base;
import :string;

namespace wind
{
	namespace path
	{
		bool set_working_directory()
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

		string_t get_working_directory()
		{
			constexpr size_t size = 2048;
			char buffer[size];

			return string_t(_getcwd(buffer, size));
		}

		string_t get_file_part(const string_t& filepath)
		{
			string_t out;
			ALLEGRO::PATH path = al::create_path(filepath.c_str());
			if (path)
			{
				out = al::get_path_filename(path);
			}
			return out;
		}

		string_t get_path_part(const string_t& filepath)
		{
			string_t filename = get_file_part(filepath);

			if (filepath.size() > filename.size())
			{
			}

			return filepath.substr(0, filepath.length() - filename.size());
		}

		string_t make_canonical(const string_t& str)
		{
			string_t out;

			for (string_t::const_iterator it = str.cbegin(); it != str.cend(); ++it)
			{
				const string_t::codepoint_t& c = (*it);

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

		string_t get_extension_part(const string_t& filepath)
		{
			size_t size = filepath.rfind('.');

			if (size == string_t::npos || (size + 1) == filepath.size())
			{
				return "";
			}

			return filepath.substr(size + 1);
		}

		size_t find_all_files(const string_t& filepath, const string_t& ext, std::vector<string_t>& vec)
		{
			size_t size = vec.size();
			ALLEGRO::FS_ENTRY entry = al::create_fs_entry(filepath.c_str());

			if (entry)
			{
				ALLEGRO::FS_ENTRY next;

				if (!(al::get_fs_entry_mode(entry) & ALLEGRO::FILEMODE_ISDIR))
				{
					return 0;
				}

				if (!al::open_directory(entry))
				{
					return 0;
				}

				while (true)
				{
					if (!(next = al::read_directory(entry))) break;

					if (al::get_fs_entry_mode(next) & ALLEGRO::FILEMODE_ISFILE)
					{
						string_t filename;
						string_t extension;

						ALLEGRO::PATH path = al::create_path(al::get_fs_entry_name(next));
						if (!path)
						{
							break;
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
					}
				}

				al::close_directory(entry);
			}
			return vec.size() - size;
		}

		void split_filepath(const string_t& path, string_t& dir, string_t& basename, string_t& extension)
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
}
