export module wind:word;

import <cstdint>;
import :base;

namespace wind
{
	export auto get_low_byte(word_t w) -> byte_t
	{
		return ((byte_t)(word_t)(w));
	}

	export auto get_high_byte(word_t w) -> byte_t
	{
		return ((byte_t)((word_t)(w) >> 8));
	}

	export auto make_word(byte_t low, byte_t high) -> word_t
	{
		return ((word_t)(((byte_t)(low)) | (((word_t)((byte_t)(high))) << 8)));
	}
}