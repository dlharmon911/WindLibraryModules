export module wind:nbt.file.read.payload.compound;

import :base;
import :file;
import :nbt.constants;
import :nbt.types;
import :nbt.file.read.node;

namespace wind::nbt::payload::compound
{
	export auto read(ALLEGRO::FILE& file, compound_t& compound) -> int32_t
	{
		int32_t total_bytes{ 0 };
		int32_t bytes_read{ 0 };

		while (true)
		{
			u8string_t name{};
			node_t node{};

			bytes_read = node::read(file, node);
			if (bytes_read == ALLEGRO::FILE_EOF)
			{
				return file::error(__FILE__, __LINE__);
			}
			total_bytes += bytes_read;

			if (node.m_tag.m_type == WIND::NBT::TAG_TYPE::END)
			{
				break;
			}

			compound[node.m_name] = node.m_tag;
		}

		return total_bytes;
	}
}
