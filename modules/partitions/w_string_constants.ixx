export module wind:string.constants;

import :base;

namespace WIND::STRING
{
	export constexpr int32_t CHAR_OBJECT_START{ 0x7b };
	export constexpr int32_t CHAR_OBJECT_END{ 0x7d };
	export constexpr int32_t CHAR_ARRAY_START{ 0x5b };
	export constexpr int32_t CHAR_ARRAY_END{ 0x5d };
	export constexpr int32_t CHAR_COLON{ 0x3a };
	export constexpr int32_t CHAR_COMMA{ 0x2c };
	export constexpr int32_t CHAR_BACK_SLASH{ 0x5c };
	export constexpr int32_t CHAR_FORWARD_SLASH{ 0x2f };
	export constexpr int32_t CHAR_QUOTATION{ 0x22 };
	export constexpr int32_t CHAR_MINUS{ 0x2d };
	export constexpr int32_t CHAR_PLUS{ 0x2b };
	export constexpr int32_t CHAR_DECIMAL{ 0x2e };
	export constexpr int32_t CHAR_E_UPPER{ 0x45 };
	export constexpr int32_t CHAR_E_LOWER{ 0x65 };
	export constexpr int32_t CHAR_SPACE{ 0x20 };
	export constexpr int32_t CHAR_TAB{ 0x09 };
	export constexpr int32_t CHAR_NEW_LINE{ 0x0a };
	export constexpr int32_t CHAR_CARRIAGE_RETURN{ 0x0d };
	export constexpr int32_t CHAR_BACKSPACE{ 0x08 };
	export constexpr int32_t CHAR_FORMFEED{ 0x0c };
}
