export module wind:hex;

import :base;
import :string.base;

namespace wind
{
	export auto is_hex(int32_t c) -> bool
	{
		return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
	}

	export auto hex_from_char(int32_t c) -> uint32_t
	{
		uint32_t out{ 0 };

		if (c >= '0' && c <= '9')
		{
			out = c - '0';
		}
		else
		{
			if (c >= 'a' && c <= 'f')
			{
				out = c - 'a' + 10;
			}
			else
			{
				if (c >= 'A' && c <= 'F')
				{
					out = c - 'A' + 10;
				}
			}
		}

		return out;
	}

	export auto hex_to_char(uint32_t v) -> char
	{
		int32_t out{ 0 };

		if (v >= 0 && v <= 9)
		{
			out = '0' + v;
		}
		else
		{
			if (v >= 10 && v <= 15)
			{
				out = 'a' + v - 10;
			}
		}

		return out;
	}

	export auto hex_from_string(const string_t& string) -> uint32_t
	{
		size_t index{ 0 };
		uint32_t rv{ 0 };

		while (index < string.size())
		{
			rv = rv << 4;
			rv = rv + hex_from_char(string[index]);
			++index;
		}

		return rv;
	}

	export auto hex_to_string(uint32_t value) -> string_t
	{
		string_t rv{};

		rv.clear();

		while (value > 0)
		{
			int32_t c = hex_to_char(value & 0xf);

			rv.insert(0, 1, c);
			value = value >> 4;
		}

		return rv;
	}

	export auto hex_to_string(uint32_t value, const string_t& prefix, int32_t string_size) -> string_t
	{
		string_t rv{ hex_to_string(value) };

		if (string_size > 0 && rv.length() < string_size)
		{
			size_t diff = string_size - rv.length();
			rv.insert(0, diff, '0');
		}

		rv.insert(0, prefix);

		return rv;
	}
}
