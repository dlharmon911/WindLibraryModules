module wind.d_addon;

import <cassert>;
import <memory>;
import <array>;
import <string>;
import <cstdint>;
import <any>;
import <functional>;
import <unordered_map>;
import allegro;
import allegro.physfs_addon;
import wind;
import :base;
import :object;
import :parser;

namespace wind
{
	namespace datafile
	{
		static auto load(const string_t& filename, d_t& datafile) -> int32_t
		{
			json_t json{};

			if (!al::filename_exists(filename.c_str()))
			{
				return -1;
			}

			if (wind::json::load(json, filename) < 0)
			{
				return -1;
			}

			if (datafile::parser_t::parse(json, datafile) < 0)
			{
				return -1;
			}

			json.clear();

			return 0;
		}

		static auto is_archive_extension(const string_t& extension) -> bool
		{
			const PHYSFS_ArchiveInfo** i{ nullptr };

			for (i = PHYSFS_supportedArchiveTypes(); *i != nullptr; i++)
			{
				wind::string_t a{ string::to_upper(extension) };
				wind::string_t b{ string::to_upper(static_cast<string_t>((*i)->extension)) };

				if (a == b)
				{
					return true;
				}
			}

			return false;
		}

		static auto load_from_file(const string_t& path, const string_t& filename, d_t& datafile) -> int32_t
		{
			string_t dir{ al::get_current_directory() };
			al::change_directory((dir + ALLEGRO::NATIVE_PATH_SEP + path).c_str());

			if (datafile::load(filename, datafile) < 0)
			{
				return -1;
			}
			al::change_directory(dir.c_str());

			return 0;
		}

		static auto load_from_archive(const string_t& filename, d_t& datafile) -> int32_t
		{
			const ALLEGRO::FILE_INTERFACE file_interface{ al::get_new_file_interface() };

			if (PHYSFS_mount(filename.c_str(), nullptr, 1))
			{
				al::physfs_addon::set_file_interface();

				if (datafile::load(static_cast<string_t>("index.ini"), datafile) < 0)
				{
					return -1;
				}

				PHYSFS_unmount(filename.c_str());
			}

			al::set_new_file_interface(file_interface);

			return 0;
		}
	}

	auto load_datafile(const string_t& filename, d_t& datafile) -> int32_t
	{
		string_t base{};
		string_t extension{};
		string_t path{};

		if (!al::filename_exists(filename.c_str()))
		{
			return -1;
		}

		datafile::register_object_defaults();

		datafile.clear();

		path::split_filepath(path::make_canonical(filename), path, base, extension);

		if (datafile::is_archive_extension(extension))
		{
			return datafile::load_from_archive("index.ini", datafile);
		}
		else
		{
			return datafile::load_from_file(path, base + static_cast<string_t>(".") + extension, datafile);
		}

		if (datafile.size() == 0)
		{
			return-1;
		}

		return 0;
	}
}
