export module wind:nbt.file.write.node;

import :base;
import :file;
import :nbt.constants;
import :nbt.types;
import :nbt.file.write.payload;
import :nbt.file.write.string;

namespace wind::nbt::node
{
	export auto write(ALLEGRO::FILE& file, const node_t& node) -> int32_t
	{
		int32_t total_bytes{ 0 };
		int32_t bytes_written{ 0 };

		// Write the type
		int8_t type{ static_cast<int8_t>(std::to_underlying(node.m_tag.m_type)) };
		bytes_written = file::write_integral_type<int8_t>(file, type, sizeof(int8_t));
		if (bytes_written != sizeof(int8_t))
		{
			return file::error(__FILE__, __LINE__);
		}
		total_bytes += bytes_written;

		if (node.m_tag.m_type == WIND::NBT::TAG_TYPE::END)
		{
			return total_bytes;
		}

		// Write the name
		bytes_written = string::write(file, node.m_name);
		if (bytes_written == ALLEGRO::FILE_EOF)
		{
			return file::error(__FILE__, __LINE__);
		}
		total_bytes += bytes_written;

		// Write the payload
		bytes_written = payload::write(file, node.m_tag.m_type, node.m_tag.m_payload);
		if (bytes_written == ALLEGRO::FILE_EOF)
		{
			return file::error(__FILE__, __LINE__);
		}
		total_bytes += bytes_written;

		return total_bytes;
	}
}