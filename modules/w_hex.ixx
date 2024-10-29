export module wind:hex;

import <cstdint>;
import :base;
import :string;

namespace wind
{
	export bool is_hex(int32_t c);
	export uint32_t hex_from_string(const string_t& string);
	export string_t hex_to_string(uint32_t value);
	export string_t hex_to_string(uint32_t value, const string_t& prefix, int32_t string_size = -1);
	export uint32_t hex_from_char(int32_t c);
	export char hex_to_char(uint32_t v);
}
