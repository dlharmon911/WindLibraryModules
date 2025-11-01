export module wind:json.tokenizer;

import :base;
import :string;
import :json.constants;
import :json.base;
import :hex;
import :string.base;

namespace WIND::JSON::TOKENIZER
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
}

namespace wind::json
{
	namespace tokenizer
	{
		export using type_t = WIND::JSON::TOKENIZER::TOKEN::TYPE;

		export class token_t
		{
		public:
			token_t() = default;
			explicit token_t(type_t type) : m_type(type), m_string() {}
			token_t(type_t type, const string_t& string) : m_type(type), m_string(string) {}
			token_t(const token_t& token) = default;
			~token_t() = default;
			auto operator = (const token_t& token)->token_t & = default;

			auto clear() -> void
			{
				this->m_type = type_t::UNDEFINED;
				this->m_string.clear();
			}

			auto set_type(type_t type) -> void
			{
				this->m_type = type;
			}

			auto get_type() const -> type_t
			{
				return this->m_type;
			}

			auto set_string(const string_t& string) -> void
			{
				this->m_string = string;
			}

			auto get_string() const -> const string_t&
			{
				return this->m_string;
			}

			auto get_string() -> string_t&
			{
				return this->m_string;
			}

			auto c_str() const -> const char*
			{
				return this->m_string.c_str();
			}

		private:
			type_t m_type{ type_t::UNDEFINED };
			string_t m_string{};
		};
	}

	export template <typename iterator> class tokenizer_t
	{
	public:
		tokenizer_t() : m_char(0), m_begin(), m_end() {}
		tokenizer_t(iterator begin, iterator end) : m_char(0), m_begin(begin), m_end(end) {}
		tokenizer_t(const tokenizer_t& tokenizer) : m_char(tokenizer.m_char), m_begin(tokenizer.m_begin), m_end(tokenizer.m_end) {}
		tokenizer_t(tokenizer_t& tokenizer) : m_char(tokenizer.m_char), m_begin(tokenizer.m_begin), m_end(tokenizer.m_end) {}
		~tokenizer_t() = default;

		auto operator = (const tokenizer_t& tokenizer) -> tokenizer_t&
		{
			this->m_char = tokenizer.m_char;
			this->m_begin = tokenizer.m_begin;
			this->m_end = tokenizer.m_end;

			return *this;
		}

		auto get_next() -> tokenizer::token_t
		{
			tokenizer::token_t rv;

			this->remove_whitespace();

			switch (this->m_char)
			{
			case WIND::STRING::CHAR_QUOTATION:
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
			case WIND::STRING::CHAR_MINUS:
			{
				rv = this->parse_number();
			} break;

			case WIND::STRING::CHAR_OBJECT_START: rv = tokenizer::token_t(WIND::JSON::TOKENIZER::TOKEN::TYPE::OBJECT_START, string_t(this->m_char, 1)); this->pop(); break;
			case WIND::STRING::CHAR_OBJECT_END: rv = tokenizer::token_t(WIND::JSON::TOKENIZER::TOKEN::TYPE::OBJECT_END, string_t(this->m_char, 1)); this->pop(); break;
			case WIND::STRING::CHAR_ARRAY_START: rv = tokenizer::token_t(WIND::JSON::TOKENIZER::TOKEN::TYPE::ARRAY_START, string_t(this->m_char, 1)); this->pop(); break;
			case WIND::STRING::CHAR_ARRAY_END: rv = tokenizer::token_t(WIND::JSON::TOKENIZER::TOKEN::TYPE::ARRAY_END, string_t(this->m_char, 1)); this->pop(); break;
			case WIND::STRING::CHAR_COLON: rv = tokenizer::token_t(WIND::JSON::TOKENIZER::TOKEN::TYPE::COLON, string_t(this->m_char, 1)); this->pop(); break;
			case WIND::STRING::CHAR_COMMA: rv = tokenizer::token_t(WIND::JSON::TOKENIZER::TOKEN::TYPE::COMMA, string_t(this->m_char, 1)); this->pop(); break;

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

		static auto tokenize(std::vector<tokenizer::token_t>& tokens, iterator begin, iterator end) -> int32_t
		{
			tokenizer_t tokenizer(begin, end);

			tokens.clear();

			tokenizer.pop();
			tokenizer.remove_whitespace();

			if (tokenizer.m_char)
			{
				while (tokenizer.m_char)
				{
					tokenizer::token_t token = tokenizer.get_next();

					if (token.get_type() != WIND::JSON::TOKENIZER::TOKEN::TYPE::UNDEFINED)
					{
						tokens.push_back(token);
					}
					else
					{
						return -1;
					}

					tokenizer.remove_whitespace();
				}
			}

			return static_cast<int32_t>(tokens.size());
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

		auto parse_unquoted_string() -> tokenizer::token_t
		{
			tokenizer::token_t rv;

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

			if (rv.get_string().compare(WIND::JSON::STRING::NULL_) == 0)
			{
				rv.set_type(WIND::JSON::TOKENIZER::TOKEN::TYPE::EMPTY);
			}
			else
			{
				if (rv.get_string().compare(WIND::JSON::STRING::TRUE_) == 0 || rv.get_string().compare(WIND::JSON::STRING::FALSE_) == 0)
				{
					rv.set_type(WIND::JSON::TOKENIZER::TOKEN::TYPE::BOOLEAN);
				}
				else
				{
					rv.clear();
				}
			}

			return rv;
		}

		auto parse_escape_chars(string_t& str) -> int32_t
		{
			this->pop();

			if (this->m_char <= 0)
			{
				return -1;
			}

			switch (this->m_char)
			{
			case WIND::STRING::CHAR_QUOTATION:
			case WIND::STRING::CHAR_BACK_SLASH:
			case WIND::STRING::CHAR_FORWARD_SLASH: break;
			case 'b': this->m_char = WIND::STRING::CHAR_BACKSPACE; break;
			case 'f': this->m_char = WIND::STRING::CHAR_FORMFEED; break;
			case 'n': this->m_char = WIND::STRING::CHAR_NEW_LINE; break;
			case 'r': this->m_char = WIND::STRING::CHAR_CARRIAGE_RETURN; break;
			case 't': this->m_char = WIND::STRING::CHAR_TAB; break;
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
					return -1;
					break;
				}

				str.push_back(v);
			} break;
			default:
			{
				return -1;
			} break;
			}

			str.push_back(this->m_char);

			return 0;
		}

		auto parse_quoted_string() -> tokenizer::token_t
		{
			tokenizer::token_t rv;

			// remove quotation
			this->pop();

			while (this->m_char)
			{
				if (this->m_char == WIND::STRING::CHAR_QUOTATION)
				{
					this->pop();
					rv.set_type(WIND::JSON::TOKENIZER::TOKEN::TYPE::STRING);
					return rv;
				}

				if (this->m_char < 32 || this->m_char >= 127)
				{
					// uknown control character
					rv.clear();
					return rv;
				}
				else
				{
					if (this->m_char == WIND::STRING::CHAR_BACK_SLASH)
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
			string_t epart = string_t(this->m_char, 1);

			this->pop();

			if (this->m_char == WIND::STRING::CHAR_MINUS ||
				this->m_char == WIND::STRING::CHAR_PLUS)
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

		auto parse_number() -> tokenizer::token_t
		{
			bool error = false;
			tokenizer::token_t rv;
			string_t string;

			// '-'? INT ('.' [0-9]+)? EXP?

			if (this->m_char == WIND::STRING::CHAR_MINUS)
			{
				string.push_back(this->m_char);
				this->pop();
			}

			if (!this->parse_fragment_int(string))
			{
				return rv;
			}

			if (this->m_char == WIND::STRING::CHAR_DECIMAL)
			{
				string.push_back(this->m_char);
				this->pop();

				if (parse_digits(string) < 1)
				{
					return rv;
				}

				if ((this->m_char == WIND::STRING::CHAR_E_LOWER ||
					this->m_char == WIND::STRING::CHAR_E_UPPER) &&
					!this->parse_fragment_exp(string))
				{
					return rv;
				}
			}

			if (!error)
			{
				rv = tokenizer::token_t(WIND::JSON::TOKENIZER::TOKEN::TYPE::NUMBER, string);
			}

			return rv;
		}

		auto remove_whitespace() -> void
		{
			while (this->m_char)
			{
				if (this->m_char == WIND::STRING::CHAR_SPACE ||
					this->m_char == WIND::STRING::CHAR_TAB ||
					this->m_char == WIND::STRING::CHAR_NEW_LINE ||
					this->m_char == WIND::STRING::CHAR_CARRIAGE_RETURN ||
					this->m_char == WIND::STRING::CHAR_BACKSPACE ||
					this->m_char == WIND::STRING::CHAR_FORMFEED)
				{
					this->pop();
				}
				else
				{
					return;
				}
			}
		}

		int32_t m_char;
		iterator m_begin;
		iterator m_end;
	};
}
