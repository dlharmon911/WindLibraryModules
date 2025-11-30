export module wind:nbt.file.write.compound;

import :base;
import :file;
import :nbt.constants;
import :nbt.types;
import :nbt.file.write.node;

namespace wind::nbt::payload::compound
{
	export auto write(ALLEGRO::FILE& file, const compound_t& compound) -> int32_t
	{
		int32_t total_bytes{ 0 };
		int32_t bytes_written{ 0 };

		for (const auto& [name, tag] : compound)
		{
			node_t node{};

			node.m_name = name;
			node.m_tag = tag;

			// Write the tag node
			bytes_written = node::write(file, node);
			if (bytes_written == ALLEGRO::FILE_EOF)
			{
				return file::error(__FILE__, __LINE__);
			}
			total_bytes += bytes_written;
		}

		// Write the end tag
		int8_t end_type = static_cast<int8_t>(WIND::NBT::TAG_TYPE::END);
		int32_t result = file::write_integral_type<int8_t>(file, end_type, sizeof(int8_t));
		if (result != sizeof(int8_t))
		{
			return file::error(__FILE__, __LINE__);
		}
		bytes_written += result;

		return bytes_written;
	}
}
