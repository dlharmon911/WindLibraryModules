export module wind:json.io;

import <string>;
import :json.object;
import :json.parser;
import :base;
import :string;

namespace wind
{
	export int32_t load_json(json_t& json, const string_t& filename)
	{
		return json_parser_t::file::parse(json, filename);
	}

	export int32_t parse_json_buffer(json_t& json, const string_t& buffer)
	{
		return json_parser_t::string::parse(json, buffer);
	}

	export int32_t save_json(const json_t& json, const string_t& filename)
	{
		return json_parser_t::value::write(json, filename);
	}
}

