export module wind:json.parser;

import :base;
import :hex;
import :file_iterator;
import :json.constants;
import :json.base;
import :json.tokenizer;
import :string;
import :log;

namespace wind::json
{
	namespace parser
	{
		using token_t = tokenizer::token_t;
		using token_vector_t = std::vector<token_t>;
		using iterator_t = token_vector_t::iterator;
		using const_iterator_t = token_vector_t::const_iterator;

		using parse_info_t = struct parse_info_tag_t
		{
			ALLEGRO::FILE m_file{};
			int32_t m_tab{ 0 };
		};

		namespace value
		{
			auto parse(json_t& json, const_iterator_t& begin, const_iterator_t& end) -> int32_t;
			auto write(const json_t& json, parse_info_t& info) -> int32_t;
		}

		namespace pair
		{
			auto parse(pair_t& pair, const_iterator_t& begin, const_iterator_t& end) -> int32_t;
			auto write(const pair_t& pair, parse_info_t& info) -> int32_t;
		}

		namespace object
		{
			auto parse(object_t& object, const_iterator_t& begin, const_iterator_t& end) -> int32_t;
			auto write(const object_t& object, parse_info_t& info) -> int32_t;
		}

		namespace array
		{
			auto parse(array_t& array, const_iterator_t& begin, const_iterator_t& end) -> int32_t;
			auto write(const json::array_t& array, parse_info_t& info) -> int32_t;
		}

		namespace tab
		{
			static auto write(parse_info_t& info) -> int32_t
			{
				for (int32_t i = 0; i < info.m_tab; ++i)
				{
					if (al::fputc(info.m_file, WIND::STRING::CHAR_TAB) == ALLEGRO::FILE_EOF)
					{
						return -1;
					}
				}
				return 0;
			}
		}

		namespace value
		{
			static auto parse(json_t& json, const_iterator_t& begin, const_iterator_t& end) -> int32_t
			{
				int32_t rv = 0;

				if (begin == end)
				{
					rv = -1;
				}
				else
				{
					switch (begin->get_type())
					{
					case WIND::JSON::TOKENIZER::TOKEN::TYPE::EMPTY:
					{
						json.clear();
						++begin;
					} break;

					case WIND::JSON::TOKENIZER::TOKEN::TYPE::BOOLEAN:
					{
						json.set_as_boolean(begin->get_string() == "true");
						++begin;
					} break;

					case WIND::JSON::TOKENIZER::TOKEN::TYPE::NUMBER:
					{
						json.set_as_number(std::atof(begin->get_string().c_str()));
						++begin;
					} break;

					case WIND::JSON::TOKENIZER::TOKEN::TYPE::STRING:
					{
						json.set_as_string(begin->get_string());
						++begin;
					} break;

					case WIND::JSON::TOKENIZER::TOKEN::TYPE::OBJECT_START:
					{
						json::object_t object;

						rv = object::parse(object, begin, end);

						if (rv == 0)
						{
							json.set_as_object(object);
						}
					}break;
					case WIND::JSON::TOKENIZER::TOKEN::TYPE::ARRAY_START:
					{
						json::array_t array;

						rv = array::parse(array, begin, end);

						if (rv == 0)
						{
							json.set_as_array(array);
						}
					}break;
					default:
					{
						rv = -1;
					} break;
					}
				}

				return rv;
			}

			static auto write(const json_t& json, parse_info_t& info) -> int32_t
			{
				int32_t rv = 0;

				switch (json.get_type())
				{
				case WIND::JSON::TYPE::NULL:
				{
					for (auto& c : WIND::JSON::STRING::NULL_)
					{
						if (al::fputc(info.m_file, c) == ALLEGRO::FILE_EOF)
						{
							return -1;
						}
					}
				} break;

				case WIND::JSON::TYPE::BOOLEAN:
				{
					const string_t& output = ((bool)json ? WIND::JSON::STRING::TRUE_ : WIND::JSON::STRING::FALSE_);

					for (auto& c : output)
					{
						if (al::fputc(info.m_file, c) == ALLEGRO::FILE_EOF)
						{
							return -1;
						}
					}
				} break;

				case WIND::JSON::TYPE::NUMBER:
				{
					if (al::fprintf(info.m_file, "%G", (double)json) <= 0)
					{
						return -1;
					}
				} break;

				case WIND::JSON::TYPE::STRING:
				{
					if (al::fputc(info.m_file, WIND::STRING::CHAR_QUOTATION) == ALLEGRO::FILE_EOF)
					{
						return -1;
					}

					string_t s = json.get_as_string();

					for (auto& c : s)
					{
						if (al::fputc(info.m_file, c) == ALLEGRO::FILE_EOF)
						{
							return -1;
						}
					}

					if (al::fputc(info.m_file, WIND::STRING::CHAR_QUOTATION) == ALLEGRO::FILE_EOF)
					{
						return -1;
					}
				} break;

				case WIND::JSON::TYPE::OBJECT:
				{
					rv = object::write((json::object_t)json, info);
				}break;

				case WIND::JSON::TYPE::ARRAY:
				{
					rv = array::write((json::array_t)json, info);
				}break;
				}

				return rv;
			}

			export auto write(const json_t& json, const string_t& filename) -> int32_t
			{
				int32_t rv = 0;
				parse_info_t info;

				info.m_file = ALLEGRO::FILE(al_fopen(filename.c_str(), "wb"), al_fclose);
				info.m_tab = 0;

				if (info.m_file)
				{
					rv = write(json, info);
				}

				return rv;
			}
		}

		namespace pair
		{
			static auto parse(json::pair_t& pair, const_iterator_t& begin, const_iterator_t& end) -> int32_t
			{
				int32_t rv = 0;

				if (begin->get_type() != WIND::JSON::TOKENIZER::TOKEN::TYPE::STRING)
				{
					return -1;
				}

				pair.first = begin->get_string();

				++begin;

				if (begin == end)
				{
					return -1;
				}

				if (begin->get_type() == WIND::JSON::TOKENIZER::TOKEN::TYPE::COLON)
				{
					++begin;

					if (begin == end)
					{
						return -1;
					}

					rv = value::parse(pair.second, begin, end);
				}
				else
				{
					return -1;
				}

				return rv;
			}

			static auto write(const json::pair_t& pair, parse_info_t& info) -> int32_t
			{
				if (al::fputc(info.m_file, WIND::STRING::CHAR_QUOTATION) == ALLEGRO::FILE_EOF)
				{
					return -1;
				}

				for (auto& c : pair.first)
				{
					if (al::fputc(info.m_file, c) == ALLEGRO::FILE_EOF)
					{
						return -1;
					}
				}

				if (al::fputc(info.m_file, WIND::STRING::CHAR_QUOTATION) == ALLEGRO::FILE_EOF)
				{
					return -1;
				}

				if (al::fputc(info.m_file, WIND::STRING::CHAR_SPACE) == ALLEGRO::FILE_EOF)
				{
					return -1;
				}

				if (al::fputc(info.m_file, WIND::STRING::CHAR_COLON) == ALLEGRO::FILE_EOF)
				{
					return -1;
				}

				if (al::fputc(info.m_file, WIND::STRING::CHAR_SPACE) == ALLEGRO::FILE_EOF)
				{
					return -1;
				}

				if (pair.second.get_type() == WIND::JSON::TYPE::ARRAY ||
					pair.second.get_type() == WIND::JSON::TYPE::OBJECT)
				{
					if (al::fputc(info.m_file, WIND::STRING::CHAR_NEW_LINE) == ALLEGRO::FILE_EOF)
					{
						return -1;
					}
				}

				return value::write(pair.second, info);
			}
		}

		namespace object
		{
			static auto parse(json::object_t& object, const_iterator_t& begin, const_iterator_t& end) -> int32_t
			{
				int32_t rv = 0;

				do
				{
					json::pair_t pair;

					// pop { or ,
					++begin;

					if (begin == end)
					{
						return -1;
					}

					rv = pair::parse(pair, begin, end);

					if (rv < 0 || begin == end)
					{
						break;
					}

					json::object_t::iterator it = object.find(pair.first);

					if (it == object.end())
					{
						object[pair.first] = pair.second;
					}
					else
					{
						return -1;
					}
				} while (begin->get_type() == WIND::JSON::TOKENIZER::TOKEN::TYPE::COMMA);

				if (rv == 0)
				{
					if (begin->get_type() == WIND::JSON::TOKENIZER::TOKEN::TYPE::OBJECT_END)
					{
						++begin;
					}
					else
					{
						rv = -1;
					}
				}

				return rv;
			}

			static auto write(const json::object_t& object, parse_info_t& info) -> int32_t
			{
				size_t size = object.size();
				size_t index = 0;

				if (!size)
				{
					return 0;
				}

				if (tab::write(info) < 0)
				{
					return -1;
				}

				if (al::fputc(info.m_file, WIND::STRING::CHAR_OBJECT_START) == ALLEGRO::FILE_EOF)
				{
					return -1;
				}

				++info.m_tab;

				for (auto it = object.cbegin(); it != object.cend();)
				{
					if (al::fputc(info.m_file, WIND::STRING::CHAR_NEW_LINE) == ALLEGRO::FILE_EOF)
					{
						return -1;
					}

					if (tab::write(info) < 0)
					{
						return -1;
					}

					if (pair::write(*it, info) < 0)
					{
						return -1;
					}

					++it;

					if (it != object.cend())
					{
						if (al::fputc(info.m_file, WIND::STRING::CHAR_COMMA) == ALLEGRO::FILE_EOF)
						{
							return -1;
						}
					}
				}

				if (al::fputc(info.m_file, WIND::STRING::CHAR_NEW_LINE) == ALLEGRO::FILE_EOF)
				{
					return -1;
				}

				--info.m_tab;

				if (tab::write(info) < 0)
				{
					return -1;
				}

				if (al::fputc(info.m_file, WIND::STRING::CHAR_OBJECT_END) == ALLEGRO::FILE_EOF)
				{
					return -1;
				}

				return 0;
			}
		}

		namespace array
		{
			static auto parse(json::array_t& array, const_iterator_t& begin, const_iterator_t& end) -> int32_t
			{
				int32_t rv = 0;

				do
				{
					json_t value;

					// pop [ or ,
					++begin;

					if (begin == end)
					{
						return -1;
					}

					rv = value::parse(value, begin, end);

					if (rv < 0 || begin == end)
					{
						break;
					}

					array.push_back(value);
				} while (begin->get_type() == WIND::JSON::TOKENIZER::TOKEN::TYPE::COMMA);

				if (rv == 0)
				{
					if (begin->get_type() == WIND::JSON::TOKENIZER::TOKEN::TYPE::ARRAY_END)
					{
						++begin;
					}
					else
					{
						rv = -1;
					}
				}

				return 0;
			}

			static auto write(const json::array_t& array, parse_info_t& info) -> int32_t
			{
				size_t size = array.size();
				size_t index = 0;

				if (!size)
				{
					return 0;
				}

				if (tab::write(info) < 0)
				{
					return -1;
				}

				if (al::fputc(info.m_file, WIND::STRING::CHAR_ARRAY_START) == ALLEGRO::FILE_EOF)
				{
					return -1;
				}

				++info.m_tab;

				do
				{
					if (al::fputc(info.m_file, WIND::STRING::CHAR_NEW_LINE) == ALLEGRO::FILE_EOF)
					{
						return -1;
					}

					if (array[index].get_type() != WIND::JSON::TYPE::ARRAY &&
						array[index].get_type() != WIND::JSON::TYPE::OBJECT)
					{
						if (tab::write(info) < 0)
						{
							return -1;
						}
					}

					if (value::write(array[index], info) < 0)
					{
						return -1;
					}

					++index;

					if (index != size)
					{
						if (al::fputc(info.m_file, WIND::STRING::CHAR_COMMA) == ALLEGRO::FILE_EOF)
						{
							return -1;
						}
					}
				} while (index < size);

				if (al::fputc(info.m_file, WIND::STRING::CHAR_NEW_LINE) == ALLEGRO::FILE_EOF)
				{
					return -1;
				}

				--info.m_tab;

				if (tab::write(info) < 0)
				{
					return -1;
				}

				if (al::fputc(info.m_file, WIND::STRING::CHAR_ARRAY_END) == ALLEGRO::FILE_EOF)
				{
					return -1;
				}

				return 0;
			}
		}

		export template <typename iterator_t> auto parse(json_t& json, iterator_t begin, iterator_t end) -> int32_t
		{
			int32_t rv{ 0 };
			token_vector_t tokens{};
			int32_t count{ json::tokenizer_t<iterator_t>::tokenize(tokens, begin, end) };

			if (count <= 0)
			{
				return -1;
			}

			const_iterator_t tokens_cbegin = tokens.cbegin();
			const_iterator_t tokens_cend = tokens.cend();

			rv = value::parse(json, tokens_cbegin, tokens_cend);

			if (rv == 0)
			{
				if (json.get_type() != WIND::JSON::TYPE::OBJECT || json.get_type() == WIND::JSON::TYPE::ARRAY)
				{
					json.clear();
					rv = -1;
				}
			}

			return rv;
		}

		namespace file
		{
			export auto parse(json_t& json, const string_t& filename) -> int32_t
			{
				ALLEGRO::FILE file;
				int32_t rv = -1;

				if (file = al::fopen(filename.c_str(), "rb"))
				{
					rv = parser::parse<file_iterator_t>(json, file_iterator_t::begin(file), file_iterator_t());
				}

				return rv;
			}
		}

		namespace string
		{
			export auto parse(json_t& json, const string_t& string) -> int32_t
			{
				return parser::parse<string_t::const_iterator>(json, string.cbegin(), string.cend());
			}
		}
	}
}
