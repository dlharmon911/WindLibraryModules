export module wind:flag;

export import <cmath>;
import :base;

namespace wind::flag
{
	export template <typename T> constexpr auto is_set(const T value, const T flag) -> bool
	{
		return (value & flag) == flag;
	}

	export template <typename T> constexpr auto set_flag(T& value, const T flag) -> void
	{
		value |= flag;
	}

	export template <typename T> constexpr auto unset_flag(T& value, const T flag) -> void
	{
		value &= ~flag;
	}

	export template <typename T> constexpr auto toggle_flag(T& value, const T flag) -> void
	{
		value ^= flag;
	}

	export template<typename T> bool contains(T value, T mask, bool verify_all_match = false)
	{
		if (verify_all_match)
		{
			return (value & mask) == mask;
		}
	
		return (value & mask) != 0;
	}
}
