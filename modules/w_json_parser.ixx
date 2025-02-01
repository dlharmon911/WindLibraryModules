export module wind:json.parser;

import <vector>;
import <map>;
import <string>;
import <memory>;
import allegro;
import :hex;
import :file;
import :json.error;
import :json.object;
import :json.tokenizer;
import :base;
import :string;

namespace wind
{
	namespace json_parser_t
	{
		export using token_t = json_token_t;
		export using array_t = std::vector<token_t>;
		export using iterator_t = array_t::iterator;
		export using const_iterator_t = array_t::const_iterator;

		namespace value
		{
			auto parse(json_t& json, const_iterator_t& begin, const_iterator_t& end) -> int32_t;
			auto write(const json_t& json, const string_t& filename) -> int32_t;
		}

		export template <typename iterator_t>
			auto parse(json_t& json, iterator_t begin, iterator_t end) -> int32_t
		{
			int32_t rv = 0;
			array_t tokens;
			size_t count = json_tokenizer_t<iterator_t>::tokenize(tokens, begin, end);

			if (count)
			{
				const_iterator_t begin = tokens.cbegin();
				const_iterator_t end = tokens.cend();

				rv = value::parse(json, begin, end);

				if (rv == 0)
				{
					if (json.get_type() != WIND::JSON::TYPE::OBJECT || json.get_type() == WIND::JSON::TYPE::ARRAY)
					{
						json.clear();
						rv = -1;
					}
				}
			}
			else
			{
				rv = -1;
			}

			return rv;
		}

		namespace file
		{
			export auto parse(json_t& json, const string_t& filename) -> int32_t;
		}

		namespace string
		{
			export auto parse(json_t& json, const string_t& string) -> int32_t;
		}
	}
}