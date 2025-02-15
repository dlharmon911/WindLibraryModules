export module wind.d_addon:object;

import <cassert>;
import <memory>;
import <vector>;
import <string>;
import <cstdint>;
import <any>;
import <functional>;
import <array>;
import allegro;
import wind;
import :base;

namespace WIND::DATAFILE
{
	export const std::array<wind::string_t, OBJECT_TYPE::COUNT> DEFAULT_OBJECT_NAMES
	{ {
		"DATAFILE",
		"BITMAP",
		"FONT",
		"TEXT",
		"SAMPLE",
		"TILESHEET"
	} };
}

namespace wind
{
	namespace datafile
	{
		export using object_t = struct object_tag_t
		{
			std::any m_any{};
			int32_t m_type{ WIND::DATAFILE::OBJECT_TYPE::INVALID };
		};

		export auto get_object_name(int32_t type, string_t& name) -> int32_t;
		export auto get_object_type(const string_t& name) -> int32_t;
		export auto register_object_type(int32_t type, const string_t& name, std::function<auto(const json_t&, std::any&)->int32_t>& function) -> int32_t;
		export auto register_object_defaults() -> void;
		export auto unregister_object_defaults() -> void;
		export auto get_object_function(int32_t type, std::function<auto(const json_t&, std::any&)->int32_t>& function) -> int32_t;
	}
	export using d_t = typename wind::array_t<datafile::object_t>;
}
