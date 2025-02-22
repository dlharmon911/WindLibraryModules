export module wind:json.io;

import <string>;
import :json.object;
import :json.parser;
import :base;
import :string;

namespace wind
{
	namespace json
	{
		export auto load(json_t& json, const string_t& filename) -> int32_t;
		export auto parse_buffer(json_t& json, const string_t& buffer) -> int32_t;
		export auto save(const json_t& json, const string_t& filename) -> int32_t;
		export auto load_from_archive(wind::json_t& json, const wind::string_t& archive_filename, const wind::string_t& filename) -> int32_t;
	}
}
