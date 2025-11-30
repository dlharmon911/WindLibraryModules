export module wind:nbt.file.read.node;

import :base;
import :file;
import :nbt.constants;
import :nbt.types;
import :nbt.file.read.payload;
import :nbt.file.read.string;

namespace wind::nbt::node
{
	export auto read(ALLEGRO::FILE& file, node_t& node) -> int32_t
	{
		int32_t total_bytes{ 0 };
		int32_t bytes_read{ 0 };

		// read the type
		int8_t type{};
		bytes_read = file::read_integral_type<int8_t>(file, type, sizeof(int8_t));
		if (bytes_read == ALLEGRO::FILE_EOF)
		{
			return file::error(__FILE__, __LINE__);
		}
		total_bytes += bytes_read;

		node.m_tag.m_type = static_cast<WIND::NBT::TAG_TYPE>(type);

		if (node.m_tag.m_type == WIND::NBT::TAG_TYPE::END)
		{
			return total_bytes;
		}

		// Read the name
		bytes_read = string::read(file, node.m_name);
		if (bytes_read == ALLEGRO::FILE_EOF)
		{
			return file::error(__FILE__, __LINE__);
		}
		total_bytes += bytes_read;

		// Read the payload
		bytes_read = payload::read(file, node.m_tag.m_type, node.m_tag.m_payload);
		if (bytes_read == ALLEGRO::FILE_EOF)
		{
			return file::error(__FILE__, __LINE__);
		}
		total_bytes += bytes_read;

		return total_bytes;
	}
}

