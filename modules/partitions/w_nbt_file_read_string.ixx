export module wind:nbt.file.read.string;

import :base;
import :file;
import :u8string;

namespace wind::nbt::string
{
	export auto read(ALLEGRO::FILE& file, u8string_t& string) -> int32_t
	{
		int16_t name_size{ 0 };
		int32_t bytes_read{ 0 };
		std::vector<char> buffer{};

		// Read the size of the string
		bytes_read = file::read_integral_type<int16_t>(file, name_size, sizeof(int16_t));
		
		if (bytes_read != sizeof(int16_t))
		{
			file::error(__FILE__, __LINE__);
			return u8string_t{};
		}
		
		// Read the string
		buffer.resize(static_cast<size_t>(name_size));
		
		bytes_read = al::fread(file, buffer.data(), static_cast<size_t>(name_size));
		
		if (bytes_read != name_size)
		{
			file::error(__FILE__, __LINE__);
			return -1;
		}

		string = u8string_t{ al::ustr_new_from_buffer(buffer.data(), static_cast<size_t>(name_size)) };

		return static_cast<int32_t>(string.size());
	}
}
