export module wind:hex;

import <cstdint>;
import :base;
import :string;

namespace wind
{
	export auto is_hex(int32_t c) -> bool;
	export auto hex_from_string(const string_t& string) -> uint32_t;
	export auto hex_to_string(uint32_t value) -> string_t;
	export auto hex_to_string(uint32_t value, const string_t& prefix, int32_t string_size = -1) -> string_t;
	export auto hex_from_char(int32_t c) -> uint32_t;
	export auto hex_to_char(uint32_t v) -> char;
}
