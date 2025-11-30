export module wind:packfile.interface;

import :base;
import <zlib.h>;
import :packfile.constants;
import :packfile.types;

namespace wind::packfile
{
	static auto gz_fopen_wrapper(const char* path, const char* mode) -> void*
	{
		void* gz = NULL;

		if (!path || !mode)
		{
			return NULL;
		}

		gz = (void*)gzopen(path, mode);

		return gz;
	}

	static auto gz_fclose_wrapper(ALLEGRO::INTERNAL::FILE_DATA* f_ptr) -> bool
	{
		gzFile gz = NULL;

		if (!f_ptr)
		{
			return false;
		}

		gz = (gzFile)al_get_file_userdata(f_ptr);

		if (!gz)
		{
			return false;
		}

		return Z_OK == gzclose(gz);
	}

	static auto gz_fread_wrapper(ALLEGRO::INTERNAL::FILE_DATA* f_ptr, void* ptr, size_t size) -> size_t
	{
		gzFile gz = NULL;
		int32_t byte_count = 0;

		if (!f_ptr)
		{
			return false;
		}

		gz = (gzFile)al_get_file_userdata(f_ptr);

		if (!gz)
		{
			return false;
		}

		byte_count = gzread(gz, ptr, (unsigned int)size);

		if (byte_count != size)
		{
			return 0;
		}

		return byte_count;
	}

	static auto gz_fwrite_wrapper(ALLEGRO::INTERNAL::FILE_DATA* f_ptr, const void* ptr, size_t size) -> size_t
	{
		gzFile gz = NULL;
		int32_t byte_count = 0;

		if (!f_ptr)
		{
			return false;
		}

		gz = (gzFile)al_get_file_userdata(f_ptr);

		if (!gz)
		{
			return false;
		}

		byte_count = gzwrite(gz, ptr, (unsigned int)size);

		if (byte_count != size)
		{
			return 0;
		}

		return byte_count;
	}

	static auto gz_fflush_wrapper(ALLEGRO::INTERNAL::FILE_DATA* f_ptr) -> bool
	{
		gzFile gz = NULL;
		int result = Z_OK;

		if (!f_ptr)
		{
			return false;
		}

		gz = (gzFile)al_get_file_userdata(f_ptr);

		if (!gz)
		{
			return false;
		}

		result = gzflush(gz, Z_SYNC_FLUSH);

		return Z_OK == result;
	}

	static auto gz_ftell_wrapper(ALLEGRO::INTERNAL::FILE_DATA* f_ptr) -> int64_t
	{
		gzFile gz = NULL;
		int64_t position = -1;

		if (!f_ptr)
		{
			return -1;
		}

		gz = (gzFile)al_get_file_userdata(f_ptr);

		if (!gz)
		{
			return -1;
		}

		position = (int64_t)gztell(gz);

		return position;
	}

	static auto gz_fseek_wrapper(ALLEGRO::INTERNAL::FILE_DATA* f_ptr, int64_t offset, int whence) -> bool
	{
		gzFile gz = NULL;
		int result = Z_OK;

		if (!f_ptr)
		{
			return false;
		}

		gz = (gzFile)al_get_file_userdata(f_ptr);

		if (!gz)
		{
			return false;
		}

		result = gzseek(gz, (z_off_t)offset, whence);

		return (result != -1);
	}

	static auto gz_feof_wrapper(ALLEGRO::INTERNAL::FILE_DATA* f_ptr) -> bool
	{
		gzFile gz = NULL;

		if (!f_ptr)
		{
			return false;
		}

		gz = (gzFile)al_get_file_userdata(f_ptr);

		if (!gz)
		{
			return false;
		}

		return gzeof(gz) != 0;
	}

	static auto gz_ferror_wrapper(ALLEGRO::INTERNAL::FILE_DATA* f_ptr) -> int32_t
	{
		gzFile gz = NULL;
		int errnum = 0;

		if (!f_ptr)
		{
			return -1;
		}

		gz = (gzFile)al_get_file_userdata(f_ptr);

		if (!gz)
		{
			return -1;
		}

		gzerror(gz, &errnum);

		return errnum;
	}

	static auto gz_ferrmsg_wrapper(ALLEGRO::INTERNAL::FILE_DATA* f_ptr) -> const char*
	{
		gzFile gz = NULL;

		if (!f_ptr)
		{
			return "Invalid file pointer";
		}

		gz = (gzFile)al_get_file_userdata(f_ptr);

		if (!gz)
		{
			return "Invalid gzFile pointer";
		}

		return gzerror(gz, NULL);
	}

	static auto gz_fclearerr_wrapper(ALLEGRO::INTERNAL::FILE_DATA* f_ptr) -> void
	{
		gzFile gz = NULL;

		if (!f_ptr)
		{
			return;
		}

		gz = (gzFile)al_get_file_userdata(f_ptr);

		if (!gz)
		{
			return;
		}

		gzclearerr(gz);
	}
	static auto gz_fungetc_wrapper(ALLEGRO::INTERNAL::FILE_DATA* f_ptr, int c) -> int32_t
	{
		gzFile gz = NULL;

		if (!f_ptr)
		{
			return -1;
		}

		gz = (gzFile)al_get_file_userdata(f_ptr);

		if (!gz)
		{
			return -1;
		}

		return gzungetc(c, gz);
	}

	static auto gz_fsize_wrapper(ALLEGRO::INTERNAL::FILE_DATA* f_ptr) -> off_t
	{
		gzFile gz = NULL;
		int64_t current_pos = -1;
		int64_t end_pos = -1;

		if (!f_ptr)
		{
			return -1;
		}

		gz = (gzFile)al_get_file_userdata(f_ptr);

		if (!gz)
		{
			return -1;
		}

		current_pos = (int64_t)gztell(gz);

		if (current_pos == -1)
		{
			return -1;
		}

		end_pos = (int64_t)gzseek(gz, 0, SEEK_END);

		if (end_pos == -1)
		{
			return -1;
		}

		if (gzseek(gz, current_pos, SEEK_SET) == -1)
		{
			return -1;
		}

		return (off_t)end_pos;
	}

	export auto set_file_interface() -> void
	{
		static const ALLEGRO::FILE_INTERFACE gz_interface =
		{
			gz_fopen_wrapper,
			gz_fclose_wrapper,
			gz_fread_wrapper,
			gz_fwrite_wrapper,
			gz_fflush_wrapper,
			gz_ftell_wrapper,
			gz_fseek_wrapper,
			gz_feof_wrapper,
			gz_ferror_wrapper,
			gz_ferrmsg_wrapper,
			gz_fclearerr_wrapper,
			gz_fungetc_wrapper,
			gz_fsize_wrapper
		};

		al::set_new_file_interface(gz_interface);
	}
}
