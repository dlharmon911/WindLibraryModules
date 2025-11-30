export module wind:nbt.io.save;

import :base;
import :file;
import :packfile;
import :nbt.constants;
import :nbt.types;
import :u8string;
import :nbt.file.write.node;

namespace wind::nbt
{
	static auto save_file(const std::string& filename, const node_t& root) -> int32_t
	{
		ALLEGRO::FILE file{ al::fopen(filename.c_str(), "wb") };
		if (!file)
		{
			return file::error(__FILE__, __LINE__);
		}

		auto result{ node::write(file, root) };
		return result;
	}

	static auto save_file_compressed(const std::string& filename, const node_t& root) -> int32_t
	{
		const ALLEGRO::FILE_INTERFACE& old_interface{ al::get_new_file_interface() };
		packfile::set_file_interface();
		auto result{ save_file(filename, root) };
		al::set_new_file_interface(old_interface);
		return result;
	}

	export auto save(const std::string& filename, const node_t& root, bool compressed = true) -> int32_t
	{
		if (compressed)
		{
			return save_file_compressed(filename, root);
		}

		return save_file(filename, root);
	}
}
