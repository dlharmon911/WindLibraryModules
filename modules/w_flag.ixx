export module wind:flag;

import <cstdint>;
import :base;

namespace wind::flag
{
	export template<typename T> bool contains(T value, T mask, bool verify_all_match = false)
	{
		if (verify_all_match)
		{
			return (mask == (value & mask));
		}

		return (value & mask);
	}

	export template<typename T> auto remove(T value, T mask) -> T
	{
		return ((value | mask) ^ mask);
	}

	export template<typename T> auto add(T value, T mask) -> T
	{
		return (value | mask);
	}

	export template<typename T> auto toggle(T value, T mask) -> T
	{
		return (value ^ mask);
	}
}
