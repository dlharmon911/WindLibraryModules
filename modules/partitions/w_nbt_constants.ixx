export module wind:nbt.constants;

import :base;

namespace WIND::NBT
{
	enum class TAG_TYPE : int8_t
	{
		INVALID = -1,
		END,
		BYTE,
		SHORT,
		INT,
		LONG,
		FLOAT,
		DOUBLE,
		BYTE_ARRAY,
		STRING,
		LIST,
		COMPOUND,
		INT_ARRAY,
		LONG_ARRAY
	};
}
