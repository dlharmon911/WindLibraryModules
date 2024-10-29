module wind;

import <string>;
import <cstdint>;
import allegro;
import :json.error;
import :json.object;
import :json.parser;
import :json.tokenizer;
import :base;
import :hex;
import :string;

namespace wind
{
	namespace json_parser_t
	{
		namespace string
		{
			string_t from_ustring(const string_t& ustring)
			{
				string_t s;
				int32_t pos = 0;
				int32_t c = ustring[pos];

				while (c > 0)
				{
					if (c >= 32 && c < 128)
					{
						s.push_back(c);
					}
					else
					{
						s.push_back(WIND::JSON::TOKENIZER::CHAR_BACK_SLASH);

						switch (c)
						{
						case WIND::JSON::TOKENIZER::CHAR_QUOTATION: s.push_back(c); break;
						case WIND::JSON::TOKENIZER::CHAR_BACK_SLASH: s.push_back(c); break;
						case WIND::JSON::TOKENIZER::CHAR_FORWARD_SLASH: s.push_back(c); break;
						case WIND::JSON::TOKENIZER::CHAR_BACKSPACE: s.push_back('b'); break;
						case WIND::JSON::TOKENIZER::CHAR_FORMFEED: s.push_back('f'); break;
						case WIND::JSON::TOKENIZER::CHAR_NEW_LINE: s.push_back('n'); break;
						case WIND::JSON::TOKENIZER::CHAR_CARRIAGE_RETURN: s.push_back('r'); break;
						case WIND::JSON::TOKENIZER::CHAR_TAB: s.push_back('t'); break;
						default:
						{
							string_t h = hex_to_string(c, "u", 4);
							int p = 0;
						} break;
						}

					}

					c = ustring[pos];
				}

				return s;
			}
		}

		typedef struct PARSE_INFO
		{
			ALLEGRO::FILE m_file{};
			int32_t m_tab{ 0 };
		} PARSE_INFO;

		namespace tab
		{
			int32_t write(PARSE_INFO& info)
			{
				for (int32_t i = 0; i < info.m_tab; ++i)
				{
					if (al::fputc(info.m_file, WIND::JSON::TOKENIZER::CHAR_TAB) == EOF)
					{
						do_json_error(WIND::JSON::ERROR_STREAM_ENDED_EARLY, __FILE__, __LINE__);
						return -1;
					}
				}
				return 0;
			}
		}

		namespace value
		{
			int32_t parse(json_t& json, const_iterator_t& begin, const_iterator_t& end);
			int32_t write(const json_t& json, PARSE_INFO& info);
		}

		namespace pair
		{
			int32_t parse(json_pair_t& pair, const_iterator_t& begin, const_iterator_t& end);
			int32_t write(const json_pair_t& pair, PARSE_INFO& info);
		}

		namespace object
		{
			int32_t parse(json_object_t& object, const_iterator_t& begin, const_iterator_t& end);
			int32_t write(const json_object_t& object, PARSE_INFO& info);
		}

		namespace array
		{
			int32_t parse(json_array_t& array, const_iterator_t& begin, const_iterator_t& end);
			int32_t write(const json_array_t& array, PARSE_INFO& info);
		}

		namespace value
		{
			int32_t parse(json_t& json, const_iterator_t& begin, const_iterator_t& end)
			{
				int32_t rv = 0;

				if (begin == end)
				{
					do_json_error(WIND::JSON::ERROR_STREAM_ENDED_EARLY, __FILE__, __LINE__);
					rv = -1;
				}
				else
				{
					switch (begin->get_type())
					{
					case WIND::JSON::TOKEN::TYPE_NULL:
					{
						json.clear();
						++begin;
					} break;

					case WIND::JSON::TOKEN::TYPE_BOOLEAN:
					{
						json.set_as_boolean(begin->get_string() == "true");
						++begin;
					} break;

					case WIND::JSON::TOKEN::TYPE_NUMBER:
					{
						json.set_as_number(std::atof(begin->get_string().c_str()));
						++begin;
					} break;

					case WIND::JSON::TOKEN::TYPE_STRING:
					{
						json.set_as_string(begin->get_string());
						++begin;
					} break;

					case WIND::JSON::TOKEN::TYPE_OBJECT_START:
					{
						json_object_t object;

						rv = object::parse(object, begin, end);

						if (rv == 0)
						{
							json.set_as_object(object);
						}
					}break;
					case WIND::JSON::TOKEN::TYPE_ARRAY_START:
					{
						json_array_t array;

						rv = array::parse(array, begin, end);

						if (rv == 0)
						{
							json.set_as_array(array);
						}
					}break;
					default:
					{
						do_json_error(WIND::JSON::ERROR_INVALID_TOKEN_TYPE, __FILE__, __LINE__);
						rv = -1;
					} break;
					}
				}

				return rv;
			}

			int32_t write(const json_t& json, PARSE_INFO& info)
			{
				int32_t rv = 0;

				switch (json.type())
				{
				case WIND::JSON::TYPE_NULL:
				{
					string_t output = "null";
					for (auto c : output)
					{
						if (al::fputc(info.m_file, c) == EOF)
						{
							do_json_error(WIND::JSON::ERROR_STREAM_ENDED_EARLY, __FILE__, __LINE__);
							return -1;
						}
					}
				} break;

				case WIND::JSON::TYPE_BOOLEAN:
				{
					string_t output = ((bool)json ? "true" : "false");
					for (auto c : output)
					{
						if (al::fputc(info.m_file, c) == EOF)
						{
							do_json_error(WIND::JSON::ERROR_STREAM_ENDED_EARLY, __FILE__, __LINE__);
							return -1;
						}
					}
				} break;

				case WIND::JSON::TYPE_NUMBER:
				{
					if (al::fprintf(info.m_file, "%G", (double)json) <= 0)
					{
						do_json_error(WIND::JSON::ERROR_STREAM_ENDED_EARLY, __FILE__, __LINE__);
					}
				} break;

				case WIND::JSON::TYPE_STRING:
				{
					if (al::fputc(info.m_file, WIND::JSON::TOKENIZER::CHAR_QUOTATION) == EOF)
					{
						do_json_error(WIND::JSON::ERROR_STREAM_ENDED_EARLY, __FILE__, __LINE__);
						return -1;
					}

					string_t s = json.get_as_string();

					for (auto c : s)
					{
						if (al::fputc(info.m_file, c) == EOF)
						{
							do_json_error(WIND::JSON::ERROR_STREAM_ENDED_EARLY, __FILE__, __LINE__);
							return -1;
						}
					}

					if (al::fputc(info.m_file, WIND::JSON::TOKENIZER::CHAR_QUOTATION) == EOF)
					{
						do_json_error(WIND::JSON::ERROR_STREAM_ENDED_EARLY, __FILE__, __LINE__);
						return -1;
					}
				} break;

				case WIND::JSON::TYPE_OBJECT:
				{
					rv = object::write((json_object_t)json, info);
				}break;

				case WIND::JSON::TYPE_ARRAY:
				{
					rv = array::write((json_array_t)json, info);
				}break;
				default:
				{
				} break;
				}

				return rv;
			}

			int32_t write(const json_t& json, const string_t& filename)
			{
				int32_t rv = 0;
				PARSE_INFO info;

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
			int32_t parse(json_pair_t& pair, const_iterator_t& begin, const_iterator_t& end)
			{
				int32_t rv = 0;

				if (begin->get_type() != WIND::JSON::TOKEN::TYPE_STRING)
				{
					do_json_error(WIND::JSON::ERROR_INVALID_TOKEN_TYPE, __FILE__, __LINE__);
					return -1;
				}

				pair.first = begin->get_string();

				++begin;

				if (begin == end)
				{
					do_json_error(WIND::JSON::ERROR_STREAM_ENDED_EARLY, __FILE__, __LINE__);
					return -1;
				}

				if (begin->get_type() == WIND::JSON::TOKEN::TYPE_COLON)
				{
					++begin;

					if (begin == end)
					{
						do_json_error(WIND::JSON::ERROR_STREAM_ENDED_EARLY, __FILE__, __LINE__);
						return -1;
					}

					rv = value::parse(pair.second, begin, end);
				}
				else
				{
					do_json_error(WIND::JSON::ERROR_INVALID_TOKEN_TYPE, __FILE__, __LINE__);
					return -1;
				}

				return rv;
			}

			int32_t write(const json_pair_t& pair, PARSE_INFO& info)
			{
				if (al::fputc(info.m_file, WIND::JSON::TOKENIZER::CHAR_QUOTATION) == EOF)
				{
					do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
					return -1;
				}

				string_t s = string::from_ustring(pair.first);

				for (auto c : s)
				{
					if (al::fputc(info.m_file, c) == EOF)
					{
						do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
						return -1;
					}
				}

				if (al::fputc(info.m_file, WIND::JSON::TOKENIZER::CHAR_QUOTATION) == EOF)
				{
					do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
					return -1;
				}

				if (al::fputc(info.m_file, WIND::JSON::TOKENIZER::CHAR_SPACE) == EOF)
				{
					do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
					return -1;
				}

				if (al::fputc(info.m_file, WIND::JSON::TOKENIZER::CHAR_COLON) == EOF)
				{
					do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
					return -1;
				}

				if (al::fputc(info.m_file, WIND::JSON::TOKENIZER::CHAR_SPACE) == EOF)
				{
					do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
					return -1;
				}

				if (pair.second.type() == WIND::JSON::TYPE_ARRAY ||
					pair.second.type() == WIND::JSON::TYPE_OBJECT)
				{
					if (al::fputc(info.m_file, WIND::JSON::TOKENIZER::CHAR_NEW_LINE) == EOF)
					{
						do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
						return -1;
					}
				}

				return value::write(pair.second, info);
			}
		}

		namespace object
		{
			int32_t parse(json_object_t& object, const_iterator_t& begin, const_iterator_t& end)
			{
				int32_t rv = 0;

				do
				{
					json_pair_t pair;

					// pop { or ,
					++begin;

					if (begin == end)
					{
						do_json_error(WIND::JSON::ERROR_STREAM_ENDED_EARLY, __FILE__, __LINE__);
						rv = -1;
						break;
					}

					rv = pair::parse(pair, begin, end);

					if (rv < 0 || begin == end)
					{
						break;
					}

					json_object_t::iterator it = object.find(pair.first);

					if (it == object.end())
					{
						object.add(pair);
					}
					else
					{
						do_json_error(WIND::JSON::ERROR_NON_UNIQUE_KEY, __FILE__, __LINE__);
						rv = -1;
						break;
					}

				} while (begin->get_type() == WIND::JSON::TOKEN::TYPE_COMMA);

				if (rv == 0)
				{
					if (begin->get_type() == WIND::JSON::TOKEN::TYPE_OBJECT_END)
					{
						++begin;
					}
					else
					{
						do_json_error(WIND::JSON::ERROR_INVALID_TOKEN_TYPE, __FILE__, __LINE__);
						rv = -1;
					}
				}

				return rv;
			}

			int32_t write(const json_object_t& object, PARSE_INFO& info)
			{
				size_t size = object.size();
				size_t index = 0;

				if (!size)
				{
					return 0;
				}

				if (tab::write(info) < 0)
				{
					do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
					return -1;
				}

				if (al::fputc(info.m_file, WIND::JSON::TOKENIZER::CHAR_OBJECT_START) == EOF)
				{
					do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
					return -1;
				}

				++info.m_tab;

				for (auto it = object.cbegin(); it != object.cend();)
				{
					if (al::fputc(info.m_file, WIND::JSON::TOKENIZER::CHAR_NEW_LINE) == EOF)
					{
						do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
						return -1;
					}

					if (tab::write(info) < 0)
					{
						do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
						return -1;
					}

					if (pair::write(json_pair_t(it.key(), *it), info) < 0)
					{
						do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
						return -1;
					}

					++it;

					if (it != object.cend())
					{
						if (al::fputc(info.m_file, WIND::JSON::TOKENIZER::CHAR_COMMA) == EOF)
						{
							do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
							return -1;
						}
					}

				}

				if (al::fputc(info.m_file, WIND::JSON::TOKENIZER::CHAR_NEW_LINE) == EOF)
				{
					do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
					return -1;
				}

				--info.m_tab;

				if (tab::write(info) < 0)
				{
					do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
					return -1;
				}

				if (al::fputc(info.m_file, WIND::JSON::TOKENIZER::CHAR_OBJECT_END) == EOF)
				{
					do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
					return -1;
				}

				return 0;
			}
		}

		namespace array
		{
			int32_t parse(json_array_t& array, const_iterator_t& begin, const_iterator_t& end)
			{
				int32_t rv = 0;

				do
				{
					json_t value;

					// pop [ or ,
					++begin;

					if (begin == end)
					{
						do_json_error(WIND::JSON::ERROR_STREAM_ENDED_EARLY, __FILE__, __LINE__);
						rv = -1;
						break;
					}

					rv = value::parse(value, begin, end);

					if (rv < 0 || begin == end)
					{
						break;
					}

					array.push_back(value);

				} while (begin->get_type() == WIND::JSON::TOKEN::TYPE_COMMA);

				if (rv == 0)
				{
					if (begin->get_type() == WIND::JSON::TOKEN::TYPE_ARRAY_END)
					{
						++begin;
					}
					else
					{
						do_json_error(WIND::JSON::ERROR_INVALID_TOKEN_TYPE, __FILE__, __LINE__);
						rv = -1;
					}
				}

				return 0;
			}

			int32_t write(const json_array_t& array, PARSE_INFO& info)
			{
				size_t size = array.size();
				size_t index = 0;

				if (!size)
				{
					return 0;
				}

				if (tab::write(info) < 0)
				{
					do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
					return -1;
				}

				if (al::fputc(info.m_file, WIND::JSON::TOKENIZER::CHAR_ARRAY_START) == EOF)
				{
					do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
					return -1;
				}

				++info.m_tab;

				do
				{
					if (al::fputc(info.m_file, WIND::JSON::TOKENIZER::CHAR_NEW_LINE) == EOF)
					{
						do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
						return -1;
					}

					if (array[index].type() != WIND::JSON::TYPE_ARRAY &&
						array[index].type() != WIND::JSON::TYPE_OBJECT)
					{
						if (tab::write(info) < 0)
						{
							do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
							return -1;
						}
					}

					if (value::write(array[index], info) < 0)
					{
						do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
						return -1;
					}



					++index;

					if (index != size)
					{
						if (al::fputc(info.m_file, WIND::JSON::TOKENIZER::CHAR_COMMA) == EOF)
						{
							do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
							return -1;
						}
					}

				} while (index < size);

				if (al::fputc(info.m_file, WIND::JSON::TOKENIZER::CHAR_NEW_LINE) == EOF)
				{
					do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
					return -1;
				}

				--info.m_tab;

				if (tab::write(info) < 0)
				{
					do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
					return -1;
				}

				if (al::fputc(info.m_file, WIND::JSON::TOKENIZER::CHAR_ARRAY_END) == EOF)
				{
					do_json_error(WIND::JSON::ERROR_FILE_OUTPUT_ERROR, __FILE__, __LINE__);
					return -1;
				}

				return 0;
			}
		}

		namespace file
		{
			int32_t parse(json_t& json, const string_t& filename)
			{
				ALLEGRO::FILE file;
				int32_t rv = 0;

				if (file = al::fopen(filename.c_str(), "rb"))
				{
					rv = json_parser_t::parse<wind::file_iterator_t>(json, wind::file_iterator_t::begin(file), wind::file_iterator_t());
				}

				return rv;
			}
		}
		namespace string
		{
			int32_t parse(json_t& json, const string_t& string)
			{
				return json_parser_t::parse<string_t::const_iterator>(json, string.cbegin(), string.cend());
			}
		}
	}
}