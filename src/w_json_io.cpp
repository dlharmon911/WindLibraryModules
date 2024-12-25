module wind;

import <cassert>;
import <string>;
import <cstdint>;
import std;
import allegro;
import allegro.physfs_addon;
import :json.error;
import :base;
import :string;

namespace wind
{
	namespace json
	{
		auto load(json_t& json, const string_t& filename) -> int32_t
		{
			return json_parser_t::file::parse(json, filename);
		}

		auto parse_buffer(json_t& json, const string_t& buffer) -> int32_t
		{
			return json_parser_t::string::parse(json, buffer);
		}

		auto save(const json_t& json, const string_t& filename) -> int32_t
		{
			return json_parser_t::value::write(json, filename);
		}

		auto load_from_archive(json_t& json, const string_t& archive_filename, const string_t& filename) -> int32_t
		{
			string_t filepath{ path::make_canonical(archive_filename) };
			string_t base{};
			string_t ext{};
			string_t path{};
			bool archive{ false };
			bool error{ false };
			int32_t rv{ -1 };

			path::split_filepath(filepath, path, base, ext);

			const PHYSFS_ArchiveInfo** i{ nullptr };
			for (i = PHYSFS_supportedArchiveTypes(); *i != nullptr; i++)
			{
				if (string::to_upper(ext) == (*i)->extension)
				{
					archive = true;
					break;
				}
			}

			if (archive)
			{
				const ALLEGRO::FILE_INTERFACE file_interface = al::get_new_file_interface();

				if (PHYSFS_mount(filename.c_str(), nullptr, 1))
				{
					al::physfs_addon::set_file_interface();
					rv = json::load(json, filename);
					PHYSFS_unmount(filename.c_str());
				}

				al::set_new_file_interface(file_interface);
			}

			return rv;
		}
	}
}