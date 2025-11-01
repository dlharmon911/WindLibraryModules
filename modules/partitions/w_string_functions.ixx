export module wind:string.functions;

import :base;
import :string.constants;
import :string.base;
import :hex;
import <ranges>;

namespace wind::string
{
	export auto from_ustring(const ALLEGRO::USTRING& ustring) -> string_t
	{
		string_t s{};
		int32_t pos{ 0 };
		int32_t c{ al::ustr_get(ustring, pos) };

		while (c > 0)
		{
			if (c >= 32 && c < 128)
			{
				s.push_back(c);
			}
			else
			{
				s.push_back(WIND::STRING::CHAR_BACK_SLASH);

				switch (c)
				{
				case WIND::STRING::CHAR_QUOTATION: s.push_back(c); break;
				case WIND::STRING::CHAR_BACK_SLASH: s.push_back(c); break;
				case WIND::STRING::CHAR_FORWARD_SLASH: s.push_back(c); break;
				case WIND::STRING::CHAR_BACKSPACE: s.push_back('b'); break;
				case WIND::STRING::CHAR_FORMFEED: s.push_back('f'); break;
				case WIND::STRING::CHAR_NEW_LINE: s.push_back('n'); break;
				case WIND::STRING::CHAR_CARRIAGE_RETURN: s.push_back('r'); break;
				case WIND::STRING::CHAR_TAB: s.push_back('t'); break;
				default:
				{
					string_t h = hex_to_string(c, "u", 4);
					int32_t p = 0;
				} break;
				}
			}

			c = al::ustr_get(ustring, pos);
		}

		return s;
	}

	export template <typename T> auto convert_from_string(const string_t& str) -> T
	{
		if (!str.empty())
		{
			if constexpr (std::is_same_v<T, float>)
			{
				return std::stof(str);
			}
			else if constexpr (std::is_same_v<T, int32_t>)
			{
				return std::stoi(str);
			}
		}

		return static_cast<T>(0);
	}

	export auto ltrim(string_t& s) -> string_t&
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch);	}));
		return s;
	}

	export auto ltrim(const string_t& s) -> string_t
	{
		string_t result{ s };
		return ltrim(result);
	}

	// Trim from end (rtrim)
	export auto rtrim(string_t& s) -> string_t&
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
		return s;	
	}

	export auto rtrim(const string_t& s) -> string_t
	{
		string_t result{ s };
		return rtrim(result);
	}

	// Trim from both ends
	export auto trim(string_t& s) -> string_t&
	{
		return ltrim(rtrim(s));
	}

	export auto trim(const string_t& s) -> string_t
	{
		string_t result{ s };
		return trim(result);
	}

	export auto tokenize_line(const string_t& line, std::vector<string_t>& out) -> void
	{
		std::stringstream stream{ line };
		string_t token{};
		string_t view{ line };
		out.clear();

		if (line.length() == 0)
		{
			return;
		}

		view.erase(std::remove(view.begin(), view.end(), '\n'), view.end());
		view.erase(std::remove(view.begin(), view.end(), '\r'), view.end());
		trim(view);

		while (stream >> token)
		{
			out.emplace_back(token);
		}

		if (out.size() > 0)
		{
			bool pop{ false };

			do
			{
				pop = false;

				if (out.size() == 0)
				{
					return;
				}

				string_t& string = out.back();

				if (string.length() == 0 || string.at(0) == 0)
				{
					out.pop_back();
					pop = true;
				}
			} while (pop);
		}
	}

	export auto split(const string_t& string, char delimiter, std::vector<string_t>& parts) -> size_t
	{
		std::stringstream ss(string);
		string_t token;

		parts.clear();

		while (std::getline(ss, token, delimiter))
		{			
			parts.push_back(trim(token));
		}

		return parts.size();
	}

	export auto map_flags(const string_t& flag_string, const std::unordered_map<string_t, int32_t>& flag_map) -> int32_t
	{
		int32_t flags{ 0 };
		std::vector<string_t> tokens{};
		split(flag_string, '|', tokens);
		for (const auto& token : tokens)
		{
			auto it{ flag_map.find(token) };
			if (it != flag_map.cend())
			{
				flags |= it->second;
			}
		}
		return flags;
	}
}
