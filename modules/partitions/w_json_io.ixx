export module wind:json.io;

import :base;
import :string;
import :json.base;
import :json.parser;

namespace wind::json
{
	export auto load(json_t& json, const string_t& filename) -> int32_t
	{
		return parser::file::parse(json, filename);
	}

	export auto save(const json_t& json, const string_t& filename) -> int32_t
	{
		return parser::value::write(json, filename);
	}

	export auto parse(json_t& json, const string_t& buffer) -> int32_t
	{
		return parser::string::parse(json, buffer);
	}
}
