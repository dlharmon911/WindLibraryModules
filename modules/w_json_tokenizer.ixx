export module wind:json.tokenizer;

import <cstdint>;
import <vector>;
import <string>;
import allegro;
import :hex;
import :json.error;
import :base;
import :string;

namespace WIND
{
	namespace JSON
	{
		namespace TOKEN
		{
			export enum class TYPE : int32_t
			{
				UNDEFINED = -1,
				EMPTY,
				BOOLEAN,
				NUMBER,
				STRING,
				OBJECT_START,
				OBJECT_END,
				ARRAY_START,
				ARRAY_END,
				COLON,
				COMMA
			};
		}

		namespace TOKENIZER
		{
			constexpr wind::uchar_t CHAR_OBJECT_START{ 0x7b };
			constexpr wind::uchar_t CHAR_OBJECT_END{ 0x7d };
			constexpr wind::uchar_t CHAR_ARRAY_START{ 0x5b };
			constexpr wind::uchar_t CHAR_ARRAY_END{ 0x5d };
			constexpr wind::uchar_t CHAR_COLON{ 0x3a };
			constexpr wind::uchar_t CHAR_COMMA{ 0x2c };
			constexpr wind::uchar_t CHAR_BACK_SLASH{ 0x5c };
			constexpr wind::uchar_t CHAR_FORWARD_SLASH{ 0x2f };
			constexpr wind::uchar_t CHAR_QUOTATION{ 0x22 };
			constexpr wind::uchar_t CHAR_MINUS{ 0x2d };
			constexpr wind::uchar_t CHAR_PLUS{ 0x2b };
			constexpr wind::uchar_t CHAR_DECIMAL{ 0x2e };
			constexpr wind::uchar_t CHAR_E_UPPER{ 0x45 };
			constexpr wind::uchar_t CHAR_E_LOWER{ 0x65 };
			constexpr wind::uchar_t CHAR_SPACE{ 0x20 };
			constexpr wind::uchar_t CHAR_TAB{ 0x09 };
			constexpr wind::uchar_t CHAR_NEW_LINE{ 0x0a };
			constexpr wind::uchar_t CHAR_CARRIAGE_RETURN{ 0x0d };
			constexpr wind::uchar_t CHAR_BACKSPACE{ 0x08 };
			constexpr wind::uchar_t CHAR_FORMFEED{ 0x0c };
		}
	}
}

namespace wind
{
	export class json_token_t
	{
	public:
		json_token_t();
		json_token_t(WIND::JSON::TOKEN::TYPE type, const string_t& str);
		json_token_t(const json_token_t& token);
		~json_token_t();
		auto operator = (const json_token_t& token)->json_token_t&;
		auto clear() -> void;
		auto set_type(WIND::JSON::TOKEN::TYPE type) -> void;
		auto get_type() const->WIND::JSON::TOKEN::TYPE;
		auto set_string(const string_t& str) -> void;
		auto get_string() -> string_t&;
		auto get_string() const -> const string_t&;

	private:
		WIND::JSON::TOKEN::TYPE m_type;
		string_t m_ustring;
	};

	export template <typename iterator>
		class json_tokenizer_t
	{
	public:

		json_tokenizer_t() : m_char(0), m_begin(), m_end() {}
		json_tokenizer_t(iterator begin, iterator end) : m_char(0), m_begin(begin), m_end(end) {}
		json_tokenizer_t(const json_tokenizer_t& tokenizer) : m_char(tokenizer.m_char), m_begin(tokenizer.m_begin), m_end(tokenizer.m_end) {}
		json_tokenizer_t(json_tokenizer_t& tokenizer) : m_char(tokenizer.m_char), m_begin(tokenizer.m_begin), m_end(tokenizer.m_end) {}
		~json_tokenizer_t() = default;

		auto operator = (const json_tokenizer_t& tokenizer) -> json_tokenizer_t&
		{
			this->m_char = tokenizer.m_char;
			this->m_begin = tokenizer.m_begin;
			this->m_end = tokenizer.m_end;

			return *this;
		}

		auto get_next() -> json_token_t
		{
			json_token_t rv;

			this->remove_whitespace();

			switch (this->m_char)
			{
			case WIND::JSON::TOKENIZER::CHAR_QUOTATION:
			{
				rv = this->parse_quoted_string();
			} break;

			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case WIND::JSON::TOKENIZER::CHAR_MINUS:
			{
				rv = this->parse_number();
			} break;

			case WIND::JSON::TOKENIZER::CHAR_OBJECT_START: rv = json_token_t(WIND::JSON::TOKEN::TYPE::OBJECT_START, wind::string::create(this->m_char, 1)); this->pop(); break;
			case WIND::JSON::TOKENIZER::CHAR_OBJECT_END: rv = json_token_t(WIND::JSON::TOKEN::TYPE::OBJECT_END, wind::string::create(this->m_char, 1)); this->pop(); break;
			case WIND::JSON::TOKENIZER::CHAR_ARRAY_START: rv = json_token_t(WIND::JSON::TOKEN::TYPE::ARRAY_START, wind::string::create(this->m_char, 1)); this->pop(); break;
			case WIND::JSON::TOKENIZER::CHAR_ARRAY_END: rv = json_token_t(WIND::JSON::TOKEN::TYPE::ARRAY_END, wind::string::create(this->m_char, 1)); this->pop(); break;
			case WIND::JSON::TOKENIZER::CHAR_COLON: rv = json_token_t(WIND::JSON::TOKEN::TYPE::COLON, wind::string::create(this->m_char, 1)); this->pop(); break;
			case WIND::JSON::TOKENIZER::CHAR_COMMA: rv = json_token_t(WIND::JSON::TOKEN::TYPE::COMMA, wind::string::create(this->m_char, 1)); this->pop(); break;

			default:
			{
				if ((this->m_char >= 'a' && this->m_char <= 'z') ||
					(this->m_char >= 'A' && this->m_char <= 'Z'))
				{
					rv = this->parse_unquoted_string();
				}
			} break;
			}

			return rv;
		}

		static auto tokenize(std::vector<json_token_t>& tokens, iterator begin, iterator end) -> size_t
		{
			json_tokenizer_t tokenizer(begin, end);

			tokens.clear();

			tokenizer.pop();
			tokenizer.remove_whitespace();

			if (tokenizer.m_char)
			{
				while (tokenizer.m_char)
				{
					json_token_t token = tokenizer.get_next();

					if (token.get_type() != WIND::JSON::TOKEN::TYPE::UNDEFINED)
					{
						tokens.push_back(token);
					}
					else
					{
						do_json_error(WIND::JSON::ERROR_INVALID_TOKEN_TYPE, wind::string_t(__FILE__), __LINE__);
						return 0;
					}

					tokenizer.remove_whitespace();
				}
			}

			return tokens.size();
		}

	private:

		auto pop() -> int32_t
		{
			if (this->m_begin == this->m_end)
			{
				this->m_char = 0;
			}
			else
			{
				this->m_char = ((int32_t)(*this->m_begin));
				++this->m_begin;
			}

			return this->m_char;
		}

		auto parse_unquoted_string() -> json_token_t
		{
			json_token_t rv;

			while ((this->m_char >= 'a' && this->m_char <= 'z') ||
				(this->m_char >= 'A' && this->m_char <= 'Z'))
			{
				if (this->m_char >= 'A' && this->m_char <= 'Z')
				{
					this->m_char = std::tolower(this->m_char);
				}

				rv.get_string().push_back(this->m_char);

				this->pop();
			}

			if (rv.get_string().compare("null") == 0)
			{
				rv.set_type(WIND::JSON::TOKEN::TYPE::EMPTY);
			}
			else
			{
				if (rv.get_string().compare("true") == 0 || rv.get_string().compare("false") == 0)
				{
					rv.set_type(WIND::JSON::TOKEN::TYPE::BOOLEAN);
				}
				else
				{
					do_json_error(WIND::JSON::ERROR_UNQUOTED_STRING, wind::string_t(__FILE__), __LINE__);
					rv.clear();
				}
			}

			return rv;
		}

		auto parse_escape_chars(string_t& str) -> int32_t
		{
			int32_t rv = 0;

			this->pop();

			if (this->m_char)
			{
				switch (this->m_char)
				{
				case WIND::JSON::TOKENIZER::CHAR_QUOTATION:
				case WIND::JSON::TOKENIZER::CHAR_BACK_SLASH:
				case WIND::JSON::TOKENIZER::CHAR_FORWARD_SLASH: break;
				case 'b': this->m_char = WIND::JSON::TOKENIZER::CHAR_BACKSPACE; break;
				case 'f': this->m_char = WIND::JSON::TOKENIZER::CHAR_FORMFEED; break;
				case 'n': this->m_char = WIND::JSON::TOKENIZER::CHAR_NEW_LINE; break;
				case 'r': this->m_char = WIND::JSON::TOKENIZER::CHAR_CARRIAGE_RETURN; break;
				case 't': this->m_char = WIND::JSON::TOKENIZER::CHAR_TAB; break;
				case 'u':
				{
					size_t s = 0;
					int32_t v = 0;

					this->pop();

					while (is_hex(this->m_char))
					{
						v = (v << 4) + hex_from_char(this->m_char);
						this->pop();
						++s;
					}

					if (s != 4)
					{
						do_json_error(WIND::JSON::ERROR_HEX_LENGTH, wind::string_t(__FILE__), __LINE__);
						rv = -1;
						break;
					}

					str.append(v);
				} break;
				default:
				{
					do_json_error(WIND::JSON::ERROR_ESCAPE_CHAR, wind::string_t(__FILE__), __LINE__);
					rv = -1;
				} break;
				}
			}
			else
			{
				do_json_error(WIND::JSON::ERROR_STREAM_ENDED_EARLY, wind::string_t(__FILE__), __LINE__);
				rv = -1;
			}

			if (rv == 0)
			{
				str.push_back(this->m_char);
			}

			return rv;
		}

		auto parse_quoted_string() -> json_token_t
		{
			json_token_t rv;

			// remove quotation
			this->pop();

			while (this->m_char)
			{
				if (this->m_char == WIND::JSON::TOKENIZER::CHAR_QUOTATION)
				{
					this->pop();
					rv.set_type(WIND::JSON::TOKEN::TYPE::STRING);
					return rv;
				}

				if (this->m_char < 32 || this->m_char >= 127)
				{
					// unknown
					do_json_error(WIND::JSON::ERROR_CHAR_VALUE, wind::string_t(__FILE__), __LINE__);
					rv.clear();
					return rv;
				}
				else
				{
					if (this->m_char == WIND::JSON::TOKENIZER::CHAR_BACK_SLASH)
					{
						if (this->parse_escape_chars(rv.get_string()) < 0)
						{
							rv.clear();
							return rv;
						}
					}
					else
					{
						rv.get_string().push_back(this->m_char);
					}
				}

				this->pop();
			}

			return rv;
		}

		auto parse_fragment_exp(string_t& string) -> size_t
		{
			string_t epart = wind::string::create(this->m_char, 1);

			this->pop();

			if (this->m_char == WIND::JSON::TOKENIZER::CHAR_MINUS ||
				this->m_char == WIND::JSON::TOKENIZER::CHAR_PLUS)
			{
				epart.push_back(this->m_char);
				this->pop();
			}

			if (this->m_char >= '0' && this->m_char <= '9')
			{
				while (this->m_char >= '0' && this->m_char <= '9')
				{
					epart.push_back(this->m_char);
					this->pop();
				}
			}
			else
			{
				epart.clear();
			}

			string.append(epart);

			return epart.length();
		}

		auto parse_fragment_int(string_t& string) -> size_t
		{
			string_t ipart;

			if (this->m_char == '0')
			{
				ipart.push_back(this->m_char);
				this->pop();

				if (this->m_char >= '0' && this->m_char <= '9')
				{
					ipart.clear();
				}
			}
			else
			{
				if (this->m_char >= '1' && this->m_char <= '9')
				{
					while (this->m_char >= '0' && this->m_char <= '9')
					{
						ipart.push_back(this->m_char);
						this->pop();
					}
				}
			}

			string.append(ipart);

			return ipart.length();
		}

		auto parse_digits(string_t& string) -> size_t
		{
			size_t count = 0;

			while (this->m_char >= '0' && this->m_char <= '9')
			{
				string.push_back(this->m_char);
				this->pop();
				++count;
			}

			return count;
		}

		auto parse_number() -> json_token_t
		{
			bool error = false;
			json_token_t rv;
			string_t string;

			// '-'? INT ('.' [0-9]+)? EXP?

			if (this->m_char == WIND::JSON::TOKENIZER::CHAR_MINUS)
			{
				string.push_back(this->m_char);
				this->pop();
			}

			if (!this->parse_fragment_int(string))
			{
				return rv;
			}

			if (this->m_char == WIND::JSON::TOKENIZER::CHAR_DECIMAL)
			{
				string.push_back(this->m_char);
				this->pop();

				if (parse_digits(string) < 1)
				{
					return rv;
				}

				if ((this->m_char == WIND::JSON::TOKENIZER::CHAR_E_LOWER ||
					this->m_char == WIND::JSON::TOKENIZER::CHAR_E_UPPER) &&
					!this->parse_fragment_exp(string))
				{
					return rv;
				}
						
			}

			if (!error)
			{
				rv = json_token_t(WIND::JSON::TOKEN::TYPE::NUMBER, string);
			}

			return rv;
		}

		auto remove_whitespace() -> void
		{
			while (this->m_char)
			{
				if (this->m_char == WIND::JSON::TOKENIZER::CHAR_SPACE ||
					this->m_char == WIND::JSON::TOKENIZER::CHAR_TAB ||
					this->m_char == WIND::JSON::TOKENIZER::CHAR_NEW_LINE ||
					this->m_char == WIND::JSON::TOKENIZER::CHAR_CARRIAGE_RETURN ||
					this->m_char == WIND::JSON::TOKENIZER::CHAR_BACKSPACE ||
					this->m_char == WIND::JSON::TOKENIZER::CHAR_FORMFEED)
				{
					this->pop();
				}
				else
				{
					return;
				}
			}
		}

		wind::uchar_t m_char;
		iterator m_begin;
		iterator m_end;
	};
}