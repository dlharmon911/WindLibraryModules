export module wind:nbt.file.write.list;

import :base;
import :file;
import :nbt.constants;
import :nbt.types;
import :nbt.file.write.payload;

namespace wind::nbt::payload::list
{
	export auto write(ALLEGRO::FILE& file, const list_t& list) -> int32_t
	{
		int32_t bytes_written{ 0 };

		byte_t type{ std::to_underlying(list.m_type) };

		if (file::write_integral_type(file, type, sizeof(byte_t)) != sizeof(byte_t))
		{
			return file::error(__FILE__, __LINE__);
		}

		bytes_written += static_cast<int32_t>(sizeof(byte_t));

		// Write the length of the list
		int_t length{ static_cast<int_t>(list.m_data.size()) };
		if (file::write_integral_type(file, length, sizeof(int_t)) != sizeof(int_t))
		{
			return file::error(__FILE__, __LINE__);
		}
		bytes_written += static_cast<int32_t>(sizeof(int_t));

		for (const auto& item : list.m_data)
		{
			int32_t size = payload::write(file, list.m_type, item);

			if (size == ALLEGRO::FILE_EOF)
			{
				return file::error(__FILE__, __LINE__);
			}
			bytes_written += size;
		}

		return bytes_written;
	}
}
