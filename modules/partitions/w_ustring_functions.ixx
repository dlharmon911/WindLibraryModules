export module wind:ustring.functions;

import :base;
import <ranges>;
import <cstddef>;
import :ustring.base;

namespace wind
{
	export auto ustring(const char* const cstr) -> ustring_t
	{
		return ustring_t(reinterpret_cast<const unsigned char*>(cstr));
	}

	export auto ustring(const std::string& str) -> ustring_t
	{
		return ustring_t(str.cbegin(), str.cend());
	}
}
