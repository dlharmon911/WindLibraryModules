export module wind:nbt.file.read.payload.list;

import :base;
import :file;
import :nbt.constants;
import :nbt.types;
import :nbt.file.read.payload;

namespace wind::nbt::payload::list
{
	export auto read(ALLEGRO::FILE& file, list_t& list) -> int32_t
	{
		int32_t bytes_read{ 0 };
		byte_t type{ 0 };
		if (file::read_integral_type<byte_t>(file, type, sizeof(byte_t)) != sizeof(byte_t))
		{
			return file::error(__FILE__, __LINE__);
		}
		bytes_read += static_cast<int32_t>(sizeof(byte_t));
		list.m_type = static_cast<type_t>(type);

		// Read the length of the list
		int_t length{ 0 };
		if (file::read_integral_type<int_t>(file, length, sizeof(int_t)) != sizeof(int_t))
		{
			return file::error(__FILE__, __LINE__);
		}
		bytes_read += static_cast<int32_t>(sizeof(int_t));

		list.m_data.resize(length);

		for (auto& item : list.m_data)
		{
			int32_t size = payload::read(file, list.m_type, item);

			if (size == ALLEGRO::FILE_EOF)
			{
				return file::error(__FILE__, __LINE__);
			}
			bytes_read += size;
		}

		return bytes_read;
	}
}
