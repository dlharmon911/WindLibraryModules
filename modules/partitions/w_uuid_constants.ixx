export module wind:uuid.constants;

import :base;
import :string;

namespace WIND::UUID
{
	export const wind::string_t NIL_STRING{ "00000000-0000-0000-0000-000000000000" };
	export constexpr size_t STRING_LENGTH{ 32 };
}
