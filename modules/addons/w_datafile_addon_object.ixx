export module wind.datafile_addon:object;

import <cassert>;
import <memory>;
import <vector>;
import <string>;
import <cstdint>;
import <any>;
import <functional>;
import <array>;
import allegro;
import allegro.font_addon;
import allegro.audio_addon;
import wind;
import :base;

namespace wind
{
	namespace datafile
	{
		export using object_t = struct object_tag_t
		{
			std::any m_any{};
			int32_t m_type{ WIND::DATAFILE::OBJECT_TYPE::INVALID };
		};

		export auto get_object_type_name(int32_t type, string_t& name) -> int32_t;
		export auto get_object_type(const string_t& name) -> int32_t;
		export auto register_object_type(int32_t type, const string_t& name, std::function<auto(const json_t&, std::any&)->int32_t>& function) -> int32_t;
		export auto register_object_defaults() -> void;
		export auto unregister_object_defaults() -> void;
		export auto get_object_function(int32_t type, std::function<auto(const json_t&, std::any&)->int32_t>& function) -> int32_t;
	}

	export using datafile_t = typename wind::array_t<datafile::object_t>;

	namespace datafile
	{
		export auto parse(const json_t& json, datafile_t& datafile) -> int32_t;

		namespace object
		{
			export auto parse_array(const json_t& json, std::vector<std::any>& vector, std::function<auto(const json_t&, std::any&)->int32_t> function) -> int32_t;

			namespace datafile
			{
				export auto parse(const json_t& json, std::any& any) -> int32_t;
			}

			namespace bitmap
			{
				export auto parse(const json_t& json, std::any& any) -> int32_t;
			}

			namespace font
			{
				export auto parse(const json_t& json, std::any& any) -> int32_t;
			}

			namespace sample
			{
				export auto parse(const json_t& json, std::any& any) -> int32_t;
			}

			namespace text
			{
				export auto parse(const json_t& json, std::any& any) -> int32_t;
			}

			namespace tilesheet
			{
				export auto parse(const json_t& json, std::any& any) -> int32_t;
			}
		}
	}
}
