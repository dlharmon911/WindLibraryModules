export module wind:json.error;

import <vector>;
import <unordered_map>;
import <string>;
import <memory>;
import allegro;
import :hex;
import :file;
import :base;
import :string;

namespace WIND
{
	namespace JSON
	{
		export enum
		{
			ERROR_STREAM_ENDED_EARLY,
			ERROR_FILE_OUTPUT_ERROR,
			ERROR_INVALID_TOKEN_TYPE,
			ERROR_NON_UNIQUE_KEY,
			ERROR_APPENDING_CHAR,
			ERROR_UNQUOTED_STRING,
			ERROR_HEX_LENGTH,
			ERROR_ESCAPE_CHAR,
			ERROR_CHAR_VALUE,
			ERROR_COUNT
		};
	}
}

namespace wind
{
	export auto do_json_error(size_t index, const string_t& file, int32_t line) -> void;
}

