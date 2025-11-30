export module wind:file.read.primitives;

import :base;
import :file.error;
import :u8string;

namespace wind::file
{
	export template <typename T> auto read_integral_type(ALLEGRO::FILE& file, T& buffer, size_t size) -> int32_t  requires(std::is_integral_v<T>)
	{
		if (size == 1)
		{
			int32_t value = al::fgetc(file);

			if (value == ALLEGRO::FILE_EOF)
			{
				return file::error(__FILE__, __LINE__);
			}

			buffer = static_cast<int8_t>(value);

			return sizeof(int8_t);
		}

		if (al::fread(file, &buffer, size) != size)
		{
			return file::error(__FILE__, __LINE__);
		}

		if (std::endian::native == std::endian::little)
		{
			buffer = std::byteswap(buffer);
		}

		return static_cast<int32_t>(size);
	}

	export template <typename T> auto read_floating_point_type(ALLEGRO::FILE& file, T& buffer, size_t size) -> int32_t  requires(std::is_floating_point_v<T>)
	{
		if (al::fread(file, &buffer, size) != size)
		{
			return file::error(__FILE__, __LINE__);
		}

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

		return static_cast<int32_t>(size);
	}

	export template <typename T> auto read_array_type(ALLEGRO::FILE& file, std::vector<T>& buffer,int32_t size) -> int32_t requires(std::is_integral_v<T>)
	{
		if (read_integral_type<int32_t>(file, size, sizeof(int32_t)) != sizeof(int32_t))
		{
			return file::error(__FILE__, __LINE__);
		}

		buffer.resize(size);

		for (auto& element : buffer)
		{
			if constexpr (std::is_integral_v<T>)
			{
				if (read_integral_type<T>(file, element, sizeof(T)) != sizeof(T))
				{
					return file::error(__FILE__, __LINE__);
				}
			}
			else if constexpr (std::is_floating_point_v<T>)
			{
				if (read_floating_point_type<T>(file, element, sizeof(T)) != sizeof(T))
				{
					return file::error(__FILE__, __LINE__);
				}
			}
		}
		return static_cast<int32_t>(sizeof(int32_t) + (size * sizeof(T)));
	}
}
