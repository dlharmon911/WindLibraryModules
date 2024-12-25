module wind;

import <cassert>;
import <string>;
import <cstdint>;
import std;
import allegro;
import :json.error;
import :base;
import :string;

namespace wind
{
	namespace internal
	{
		const std::array<const wind::string_t, WIND::JSON::ERROR_COUNT> error_messages
		{
			"ERROR_STREAM_ENDED_EARLY",
			"ERROR_FILE_OUTPUT_ERROR",
			"ERROR_INVALID_TOKEN",
			"ERROR_NON_UNIQUE_KEY",
			"ERROR_APPENDING_CHAR",
			"ERROR_UNQUOTED_STRING",
			"ERROR_HEX_LENGTH",
			"ERROR_ESCAPE_CHAR",
			"ERROR_CHAR_VALUE"
		};
	}

	auto message(size_t index, int32_t line, const wind::string_t& filename) -> void
	{
		if (index < internal::error_messages.size())
		{
			wind::lout << "\n\n*********************************************************************\n"
				<< "Error at line #:" << line << " in file \"" << filename << "\"\n"
				<< "Message: \"" << internal::error_messages[index] << "\"\n"
				<< "\n*********************************************************************" << wind::endl;
		}
	}

	auto do_json_error(size_t index, const string_t file, int32_t line) -> void
	{
		message(index, line, file.c_str());
	}
}