export module wind:ustring.base;

import :base;

export using uchar_t = uint8_t;

namespace wind
{
	export using ustring_t = typename std::basic_string<uchar_t>;
}