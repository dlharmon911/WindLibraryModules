export module wind:json.io;

import <string>;
import :json.object;
import :json.parser;
import :base;
import :string;

namespace wind
{
	export auto load_json(json_t& json, const string_t& filename) -> int32_t
	{
		return json_parser_t::file::parse(json, filename);
	}

	export auto parse_json_buffer(json_t& json, const string_t& buffer) -> int32_t
	{
		return json_parser_t::string::parse(json, buffer);
	}

	export auto save_json(const json_t& json, const string_t& filename) -> int32_t
	{
		return json_parser_t::value::write(json, filename);
	}
}