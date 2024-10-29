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
	const char* error_text[] =
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

	inline void message(size_t index, const char** message_list, size_t n, int32_t line, const char* filename)
	{
		if (index < n)
		{
			std::cout << "\n\n*********************************************************************\n"
				<< "Error at line #:" << line << " in file \"" << filename << "\"\n"
				<< "Message: \"" << message_list[index] << "\"\n"
				<< "\n*********************************************************************" << std::endl;
		}
	}

	void do_json_error(size_t index, const string_t& file, int32_t line)
	{
		message(index, error_text, sizeof(error_text), line, file.c_str());
	}
}
