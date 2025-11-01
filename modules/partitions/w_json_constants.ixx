export module wind:json.constants;

import :base;
import :string.base;

namespace WIND::JSON
{
	export enum class TYPE : uint8_t
	{
		NULL,
		BOOLEAN,
		NUMBER,
		STRING,
		ARRAY,
		OBJECT
	};

	export enum class DATA_TYPE : int32_t
	{
		JSON,
		ARRAY,
		OBJECT,
		DOUBLE,
		FLOAT,
		INT64,
		INT32,
		INT16,
		INT8,
		UINT64,
		UINT32,
		UINT16,
		UINT8,
		STRING,
		BOOLEAN
	};

	namespace STRING
	{
		export inline const wind::string_t NULL_{ "null" };
		export inline const wind::string_t TRUE_{ "true" };
		export inline const wind::string_t FALSE_{ "false" };
		export inline const wind::string_t EMPTY{ "" };
	}
}
