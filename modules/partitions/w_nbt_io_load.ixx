export module wind:nbt.io.load;

import :base;
import :file;
import :packfile;
import :nbt.constants;
import :nbt.types;
import :nbt.file.read.node;

namespace wind::nbt
{
	static auto load_nbt_file(const std::string& filename, node_t& root) -> int32_t
	{
		ALLEGRO::FILE file{ al::fopen(filename.c_str(), "rb") };
		if (!file)
		{
			return file::error(__FILE__, __LINE__);
		}

		auto result{ node::read(file, root) };

		if (result == ALLEGRO::FILE_EOF)
		{
			return file::error(__FILE__, __LINE__);
		}

		if (root.m_tag.m_type != WIND::NBT::TAG_TYPE::COMPOUND)
		{
			return file::error(__FILE__, __LINE__);
		}

		return result;
	}

	static auto load_nbt_file_compressed(const std::string& filename, node_t& root) -> int32_t
	{
		const ALLEGRO_FILE_INTERFACE& old_interface{ al::get_new_file_interface() };
		packfile::set_file_interface();

		auto result{ load_nbt_file(filename, root) };

		al::set_new_file_interface(old_interface);

		return result;
	}

	export auto load(const std::string& filename, node_t& root, bool compressed = true) -> int32_t
	{
		if (compressed)
		{
			return load_nbt_file_compressed(filename, root);
		}
		else
		{
			return load_nbt_file(filename, root);
		}
	}
}
