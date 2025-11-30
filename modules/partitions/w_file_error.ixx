export module wind:file.error;

import :base;

namespace wind::file
{
	export auto error(const std::string& file, int32_t line_no) -> int32_t
	{
		return ALLEGRO::FILE_EOF;
	}
}