export module wind:file.write.primitives;

import :base;
import :file.error;
import :u8string;

namespace wind::file
{
	export template <typename T> auto write_integral_type(ALLEGRO::FILE& file, T buffer, size_t size) -> int32_t  requires(std::is_integral_v<T>)
	{
		if (size == 1)
		{
			if (al::fputc(file, static_cast<int>(buffer)) == ALLEGRO::FILE_EOF)
			{
				return file::error(__FILE__, __LINE__);
			}
			return sizeof(int8_t);
		}

		if (std::endian::native == std::endian::little)
		{
			buffer = std::byteswap(buffer);
		}

		if (al::fwrite(file, &buffer, size) != size)
		{
			return file::error(__FILE__, __LINE__);
		}

		return static_cast<int32_t>(size);
	}

	export template <typename T> auto write_floating_point_type(ALLEGRO::FILE& file, T buffer, size_t size) -> int32_t  requires(std::is_floating_point_v<T>)
	{
		if (std::endian::native == std::endian::little)
		{
			if constexpr (sizeof(T) == sizeof(float))
			{
				auto temp = std::bit_cast<uint32_t>(buffer);
				temp = std::byteswap(temp);
				buffer = std::bit_cast<T>(temp);
			}
			else if constexpr (sizeof(T) == sizeof(double))
			{
				auto temp = std::bit_cast<uint64_t>(buffer);
				temp = std::byteswap(temp);
				buffer = std::bit_cast<T>(temp);
			}
		}

		if (al::fwrite(file, &buffer, size) != size)
		{
			return file::error(__FILE__, __LINE__);
		}

		return static_cast<int32_t>(size);
	}

	export template <typename T> auto write_array_type(ALLEGRO::FILE& file, const std::vector<T>& buffer) -> int32_t requires(std::is_integral_v<T>)
	{
		int32_t total_bytes{ 0 };
		int32_t bytes_written{ 0 };
		int32_t size = static_cast<int32_t>(buffer.size());
		bytes_written = write_integral_type<int32_t>(file, size, sizeof(int32_t));
		if (bytes_written == ALLEGRO::FILE_EOF)
		{
			return file::error(__FILE__, __LINE__);
		}
		total_bytes += bytes_written;
		for (const auto& element : buffer)
		{
			bytes_written = write_integral_type<T>(file, element, sizeof(T));

			if (bytes_written == ALLEGRO::FILE_EOF)
			{
				return file::error(__FILE__, __LINE__);
			}

			total_bytes += bytes_written;
		}

		return total_bytes;
	}
}
