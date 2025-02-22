export module wind:flag;

import <cstdint>;
import <unordered_map>;
import <vector>;
import :base;
import :string;

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

	static auto get_flag_from_map(const std::unordered_map<string_t, int32_t>& map, const string_t& string) -> int32_t
	{
		auto it = map.find(string);
		if (it == map.cend())
		{
			return -1;
		}

		return it->second;
	}

	export auto parse_map(const std::unordered_map<string_t, int32_t>& map, const string_t& string, char separator = '|') -> int32_t
	{
		std::vector<string_t> flags{};
		int32_t rv{ 0 };

		if (string::separate(string, flags, separator) == 0)
		{
			return -1;
		}

		for (auto& a : flags)
		{
			int32_t flag = get_flag_from_map(map, a);

			if (flag < 0)
			{
				return -1;
			}

			rv |= flag;
		}

		return rv;
	}
}
