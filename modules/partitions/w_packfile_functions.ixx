export module wind:packfile.functions;

import :base;
import :file;
import <zlib.h>;
import :packfile.constants;
import :packfile.types;

#ifdef TRANSPARENT
#undef TRANSPARENT
#endif

namespace wind::packfile
{
	namespace internal
	{
		export inline auto destroy_gzfile(internal::data_ptr_t data) -> void
		{
			gzclose(data);
		}

		static auto append_compression_to_mode_string(std::string& mode_str, int32_t level, WIND::PACKFILE::COMPRESSION::TYPE type) -> void
		{
			if (level < 0 || level > 9)
			{
				level = WIND::PACKFILE::COMPRESSION::DEFAULT_LEVEL;
			}
			mode_str += std::to_string(level);

			switch (type)
			{
				using enum WIND::PACKFILE::COMPRESSION::TYPE;
			case DEFAULT: break;
			case FILTERED: mode_str += "f"; break;
			case HUFFMAN_ONLY: mode_str += "h"; break;
			case RLE: mode_str += "r"; break;
			default: break;
			}
		}

		static auto convert_mode_to_string(int32_t mode, int32_t level, WIND::PACKFILE::COMPRESSION::TYPE type) -> std::string
		{
			std::string mode_str{};

			if (mode & WIND::PACKFILE::MODE::READ) mode_str += "r";
			if (mode & WIND::PACKFILE::MODE::WRITE) mode_str += "w";
			if (mode & WIND::PACKFILE::MODE::BINARY) mode_str += "b";
			if (mode & WIND::PACKFILE::MODE::APPEND) mode_str += "a";
			if (mode & WIND::PACKFILE::MODE::TRANSPARENT) mode_str += "t";


			if (level != WIND::PACKFILE::COMPRESSION::DEFAULT_LEVEL)
			{
				append_compression_to_mode_string(mode_str, level, type);
			}

			return mode_str;
		}
	}

	export inline auto fopen(const std::string& path, int32_t mode, int32_t level = WIND::PACKFILE::COMPRESSION::DEFAULT_LEVEL, WIND::PACKFILE::COMPRESSION::TYPE type = WIND::PACKFILE::COMPRESSION::TYPE::DEFAULT) -> packfile_t
	{
		std::string mode_str{ internal::convert_mode_to_string(mode, level, type) };

		return packfile_t(reinterpret_cast<internal::data_ptr_t>(gzopen(path.c_str(), mode_str.c_str())), internal::destroy_gzfile);
	}

	export inline auto fopen_fd(int32_t fd, int32_t mode, int32_t level = WIND::PACKFILE::COMPRESSION::DEFAULT_LEVEL, WIND::PACKFILE::COMPRESSION::TYPE type = WIND::PACKFILE::COMPRESSION::TYPE::DEFAULT) -> packfile_t
	{
		std::string mode_str{ internal::convert_mode_to_string(mode, level, type) };

		return packfile_t(reinterpret_cast<internal::data_ptr_t>(gzdopen(fd, mode_str.c_str())), internal::destroy_gzfile);
	}

	export inline auto set_buffer_size(packfile_t& file, size_t size) -> int32_t
	{
		return gzbuffer(file.get(), static_cast<unsigned>(size));
	}

	export auto set_parameters(packfile_t& file, int32_t level, int32_t strategy) -> int32_t
	{
		return gzsetparams(file.get(), level, strategy);
	}

	export template <typename T> auto read(packfile_t& file, T* buf, int32_t len) -> int32_t
	{
		return gzread(file.get(), buf, len);
	}

	export template <typename T> auto fread(packfile_t& file, T* buf, size_t size, size_t nitems) -> z_size_t
	{
		return gzfread(buf, size, nitems, file.get());
	}

	export template <typename T> auto write(packfile_t& file, const T* buf, int32_t len) -> int32_t
	{
		return gzwrite(file.get(), buf, static_cast<unsigned>(len));
	}

	export template <typename T> auto fwrite(packfile_t& file, const T* buf, int32_t size, size_t nitems) -> z_size_t
	{
		return gzfwrite(buf, size, nitems, file.get());
	}

	export template<typename... Args>
		auto fprintf(packfile_t& file, const char* format, Args&&... args) -> int32_t
	{
		static_assert((std::is_trivially_copyable_v<std::decay_t<Args>> && ...),
			"fprintf: all argument types must be trivially copyable to be passed through C varargs");
		return static_cast<int32_t>(gzprintf(file.get(), format, std::forward<Args>(args)...));
	}

	export auto write_cstr(packfile_t& file, const char* str) -> int32_t
	{
		return gzputs(file.get(), str);
	}

	export auto read_cstr(packfile_t& file, char* buf, int32_t len) -> char*
	{
		return gzgets(file.get(), buf, len);
	}

	export auto write_str(packfile_t& file, const std::string& str) -> int32_t
	{
		int32_t len{ static_cast<int32_t>(str.length()) };

		return write(file, str.c_str(), len);
	}

	export auto read_str(packfile_t& file, std::string& str, int32_t len) -> int32_t
	{
		str.resize(len);
		auto read_bytes = read(file, str.data(), len);
		if (read_bytes != static_cast<int32_t>(len))
		{
			return file::error(__FILE__, __LINE__);
		}
		return static_cast<int32_t>(len);
	}


	export auto write_c(packfile_t& file, int32_t c) -> int32_t
	{
		return gzputc(file.get(), c);
	}

	export auto read_c(packfile_t& file) -> int32_t
	{
		return gzgetc(file.get());
	}

	export auto ungetc(packfile_t& file, int32_t c) -> int32_t
	{
		return gzungetc(c, file.get());
	}

	export auto flush(packfile_t& file, int32_t flush_mode) -> int32_t
	{
		return gzflush(file.get(), flush_mode);
	}

	export auto seek(packfile_t& file, int64_t offset, int32_t whence) -> int64_t
	{
		return gzseek(file.get(), static_cast<long>(offset), whence);
	}

	export auto rewind(packfile_t& file) -> int64_t
	{
		return gzrewind(file.get());
	}

	export auto tell(packfile_t& file) -> int64_t
	{
		return gztell(file.get());
	}

	export auto offset(packfile_t& file) -> int64_t
	{
		return gzoffset(file.get());
	}

	export auto eof(packfile_t& file) -> bool
	{
		return gzeof(file.get()) != 0;
	}

	export auto direct(packfile_t& file) -> int32_t
	{
		return gzdirect(file.get());
	}

	export auto error(packfile_t& file, int32_t* errnum) -> const char*
	{
		return gzerror(file.get(), errnum);
	}

	export auto clearerr(packfile_t& file) -> void
	{
		gzclearerr(file.get());
	}

	template<typename T> auto write_integral_type(packfile_t& file, T value) -> int32_t requires std::is_integral_v<T>
	{
		if constexpr (std::endian::native == std::endian::big)
		{
			value = std::byteswap(value);
		}

		return write<T>(file, &value, static_cast<int32_t>(sizeof(T)));
	}

	template<typename T> auto read_integral_type(packfile_t& file, T& value) -> int32_t requires std::is_integral_v<T>
	{
		auto read_bytes = read(file, &value, sizeof(T));

		if (read_bytes != sizeof(T))
		{
			return file::error(__FILE__, __LINE__);
		}

		if constexpr (std::endian::native == std::endian::big)
		{
			value = std::byteswap(value);
		}

		return sizeof(T);
	}

	template <typename I, typename F> auto read_floating_point(packfile_t& file, F& value) -> int32_t requires std::is_floating_point_v<F>&& std::is_integral_v<I>
	{
		static_assert(sizeof(F) == sizeof(I), "Unexpected floating point size");

		I as_int{ 0 };

		auto byte_count{ read_integral_type(file, as_int) };

		if (byte_count != sizeof(I))
		{
			return file::error(__FILE__, __LINE__);
		}

		value = std::bit_cast<F>(as_int);

		return byte_count;
	}

	template <typename I, typename F> auto write_floating_point(packfile_t& file, F value) -> int32_t requires std::is_floating_point_v<F>&& std::is_integral_v<I>
	{
		static_assert(sizeof(F) == sizeof(I), "Unexpected floating point size");

		I as_int{ std::bit_cast<I>(value) };

		auto byte_count{ write_integral_type(file, as_int) };

		if (byte_count != sizeof(I))
		{
			return file::error(__FILE__, __LINE__);
		}

		return byte_count;
	}

	export template<typename T> auto write(packfile_t& file, const T& value) -> int32_t
	{
		return 0;
	}

	export template <> auto write<int8_t>(packfile_t& file, const int8_t& value) -> int32_t
	{
		return write_integral_type<int8_t>(file, value);
	}

	export template <> auto write<uint8_t>(packfile_t& file, const uint8_t& value) -> int32_t
	{
		return write_integral_type<uint8_t>(file, value);
	}

	export template <> auto write<int16_t>(packfile_t& file, const int16_t& value) -> int32_t
	{
		return write_integral_type<int16_t>(file, value);
	}

	export template <> auto write<uint16_t>(packfile_t& file, const uint16_t& value) -> int32_t
	{
		return write_integral_type<uint16_t>(file, value);
	}

	export template <> auto write<int32_t>(packfile_t& file, const int32_t& value) -> int32_t
	{
		return write_integral_type<int32_t>(file, value);
	}

	export template <> auto write<uint32_t>(packfile_t& file, const uint32_t& value) -> int32_t
	{
		return write_integral_type<uint32_t>(file, value);
	}

	export template <> auto write<int64_t>(packfile_t& file, const int64_t& value) -> int32_t
	{
		return write_integral_type<int64_t>(file, value);
	}

	export template <> auto write<uint64_t>(packfile_t& file, const uint64_t& value) -> int32_t
	{
		return write_integral_type<uint64_t>(file, value);
	}

	export template <> auto write<float>(packfile_t& file, const float& value) -> int32_t
	{
		return write_floating_point<uint32_t, float>(file, value);
	}

	export template <> auto write<double>(packfile_t& file, const double& value) -> int32_t
	{
		return write_floating_point<uint64_t, double>(file, value);
	}

	export template <> auto write<bool>(packfile_t& file, const bool& value) -> int32_t
	{
		uint8_t temp{ static_cast<uint8_t>(value) };
		return write_integral_type(file, temp);
	}

	export template<typename T> auto read(packfile_t& file, T& value) -> int32_t
	{
		return 0;
	}

	export template <> auto read<int8_t>(packfile_t& file, int8_t& value) -> int32_t
	{
		return read_integral_type<int8_t>(file, value);	
	}

	export template <> auto read<uint8_t>(packfile_t& file, uint8_t& value) -> int32_t
	{
		return read_integral_type<uint8_t>(file, value);
	}

	export template <> auto read<int16_t>(packfile_t& file, int16_t& value) -> int32_t
	{
		return read_integral_type<int16_t>(file, value);
	}

	export template <> auto read<uint16_t>(packfile_t& file, uint16_t& value) -> int32_t
	{
		return read_integral_type<uint16_t>(file, value);
	}

	export template <> auto read<int32_t>(packfile_t& file, int32_t& value) -> int32_t
	{
		return read_integral_type<int32_t>(file, value);
	}

	export template <> auto read<uint32_t>(packfile_t& file, uint32_t& value) -> int32_t
	{
		return read_integral_type<uint32_t>(file, value);
	}

	export template <> auto read<int64_t>(packfile_t& file, int64_t& value) -> int32_t
	{
		return read_integral_type<int64_t>(file, value);
	}

	export template <> auto read<uint64_t>(packfile_t& file, uint64_t& value) -> int32_t
	{
		return read_integral_type<uint64_t>(file, value);
	}

	export template <> auto read<float>(packfile_t& file, float& value) -> int32_t
	{
		return read_floating_point<uint32_t, float>(file, value);
	}

	export template <> auto read<double>(packfile_t& file, double& value) -> int32_t
	{
		return read_floating_point<uint64_t, double>(file, value);
	}

	export template <> auto read<bool>(packfile_t& file, bool& value) -> int32_t
	{
		uint8_t temp{ 0 };

		auto result{ read_integral_type<uint8_t>(file, temp) };
		value = static_cast<bool>(temp);

		return result;
	}

}
