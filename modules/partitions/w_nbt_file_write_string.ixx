export module wind:nbt.file.write.string;

import :base;
import :file;
import :u8string;

namespace wind::nbt::string
{
	export auto write(ALLEGRO::FILE& file, const u8string_t& string) -> int32_t
	{
		int32_t total_bytes{ 0 };
		int32_t bytes_written{ 0 };
		// write the size of the string
		int16_t name_size{ static_cast<int16_t>(string.size()) };
		bytes_written = file::write_integral_type<int16_t>(file, name_size, sizeof(int16_t));
		if (bytes_written != sizeof(int16_t))
		{
			return file::error(__FILE__, __LINE__);
		}
		total_bytes += bytes_written;
		// Write the string
		bytes_written = static_cast<int32_t>(al::fwrite(file, string.c_str(), string.size()));
		if (bytes_written == ALLEGRO::FILE_EOF)
		{
			return file::error(__FILE__, __LINE__);
		}
		total_bytes += bytes_written;
		return total_bytes;
	}
}
