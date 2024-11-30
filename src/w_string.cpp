module wind;

import <string>;
import <vector>;
import <cstdint>;
import <cstdarg>;
import allegro;
import :base;
import :string;

namespace wind
{
	const char* empty_string = "";

	namespace string
	{
		auto validate_string(const char* string)
		{
			if (string)
			{
				return string;
			}

			return empty_string;
		}
	}

	string_t::codepoint_t::codepoint_t(const ALLEGRO::USTRING& string, int32_t offset) : m_string(string), m_offset(offset) {}
	string_t::codepoint_t::codepoint_t(const codepoint_t& ref) : m_string(ref.m_string), m_offset(ref.m_offset) {}

	auto string_t::codepoint_t::operator = (const codepoint_t& ref) -> const codepoint_t&
	{
		this->m_string = ref.m_string;
		this->m_offset = ref.m_offset;
		return *this;
	}

	auto string_t::codepoint_t::get_string() -> ALLEGRO::USTRING&
	{
		return this->m_string;
	}

	auto string_t::codepoint_t::get_string() const -> const ALLEGRO::USTRING&
	{
		return this->m_string;
	}

	auto string_t::codepoint_t::get_offset() const -> int32_t
	{
		return this->m_offset;
	}

	auto string_t::codepoint_t::set_offset(int32_t offset) -> void
	{
		this->m_offset = offset;
	}

	auto string_t::codepoint_t::get_codepoint() const -> uchar_t
	{
		return al::ustr_get(this->m_string, (uchar_t)this->m_offset);
	}

	auto string_t::codepoint_t::get_size() const -> size_t
	{
		static const int32_t MinimumValue = 0;
		static const int32_t MaximumValue = 0x10ffff;

		int32_t c = al::ustr_get(this->m_string, this->m_offset);

		if (c >= MinimumValue && c <= MaximumValue)
		{
			if (c <= 0x007f) return 1;
			if (c <= 0x07ff) return 2;
			if (c <= 0xffff) return 3;

			return 4;
		}

		return 0;
	}

	string_t::codepoint_t::operator uchar_t () const
	{
		return al::ustr_get(this->m_string, (uchar_t)this->m_offset);
	}

	auto string_t::codepoint_t::set_codepoint(uchar_t codepoint) -> size_t
	{
		return al::ustr_set_chr(this->m_string, (int32_t)this->m_offset, codepoint);
	}

	auto string_t::codepoint_t::operator = (uchar_t codepoint) -> const codepoint_t&
	{
		al::ustr_set_chr(this->m_string, (int32_t)this->m_offset, codepoint);
		return *this;
	}

	auto string_t::codepoint_t::operator == (const string_t::codepoint_t& codepoint) const -> bool
	{
		return (this->m_string == codepoint.m_string && this->m_offset == codepoint.m_offset);
	}

	auto string_t::codepoint_t::operator != (const string_t::codepoint_t& codepoint) const -> bool
	{
		return !operator == (codepoint);
	}

	/***************************************************************************************/

	string_t::string_t() : m_data(al::ustr_new(""))
	{
		ALLEGRO::ASSERT(this->m_data);
	}

	string_t::string_t(const ALLEGRO::USTRING& string) : m_data((bool)string ? al::ustr_dup(string) : al::ustr_new(""))
	{
		ALLEGRO::ASSERT(this->m_data);
	}

	string_t::string_t(const std::string& string) : m_data(al::ustr_new(string.c_str()))
	{
		ALLEGRO::ASSERT(this->m_data);
	}

	string_t::string_t(const char* string) : m_data(al::ustr_new(string::validate_string(string)))
	{
		ALLEGRO::ASSERT(this->m_data);
	}

	string_t::string_t(const string_t& string) : m_data(al::ustr_dup(string.m_data))
	{
		ALLEGRO::ASSERT(this->m_data);
	}

	string_t::string_t(const std::initializer_list<uchar_t> il) : m_data(al::ustr_new(""))
	{
		ALLEGRO::ASSERT(this->m_data);

		for (auto a : il)
		{
			al::ustr_append_chr(this->m_data, a);
		}
	}

	string_t::~string_t()
	{
	}

	auto string_t::assign(const ALLEGRO::USTRING& string) -> string_t&
	{
		this->m_data = ((bool)string ? al::ustr_dup(string) : al::ustr_new(""));
		ALLEGRO::ASSERT(this->m_data);
		return *this;
	}

	auto string_t::assign(const std::string& string) -> string_t&
	{
		this->m_data = al::ustr_new(string.c_str());
		ALLEGRO::ASSERT(this->m_data);
		return *this;
	}

	auto string_t::assign(const string_t& str) -> string_t&
	{
		this->m_data = al::ustr_dup(str.m_data);
		ALLEGRO::ASSERT(this->m_data);
		return *this;
	}

	auto string_t::assign(const char* string) -> string_t&
	{
		this->m_data = al::ustr_new(string::validate_string(string));
		ALLEGRO::ASSERT(this->m_data);
		return *this;
	}

	auto string_t::assign(const std::initializer_list<uchar_t> il) -> string_t&
	{
		return this->assign(string_t(il));
	}

	auto string_t::operator = (const ALLEGRO::USTRING& string) -> string_t&
	{
		this->m_data = ((bool)string ? al::ustr_dup(string) : al::ustr_new(""));
		ALLEGRO::ASSERT(this->m_data);
		return *this;
	}

	auto string_t::operator = (const std::string& string) -> string_t&
	{
		this->m_data = al::ustr_new(string.c_str());
		ALLEGRO::ASSERT(this->m_data);
		return *this;
	}

	auto string_t::operator = (const char* string) -> string_t&
	{
		this->m_data = al::ustr_new(string::validate_string(string));
		ALLEGRO::ASSERT(this->m_data);
		return *this;
	}

	auto string_t::operator = (const string_t& string) -> string_t&
	{
		this->m_data = al::ustr_dup(string.m_data);
		ALLEGRO::ASSERT(this->m_data);
		return *this;
	}

	auto string_t::operator = (const std::initializer_list<uchar_t> il) -> string_t&
	{
		return this->assign(string_t(il));
	}

	auto string_t::operator += (const ALLEGRO::USTRING& string) -> string_t&
	{
		return this->append(string);
	}

	auto string_t::operator += (const std::string& string) -> string_t&
	{
		return this->append(string);
	}

	auto string_t::operator += (const char* string) -> string_t&
	{
		return this->append(string::validate_string(string));
	}

	auto string_t::operator += (const string_t& string) -> string_t&
	{
		return this->append(string);
	}

	auto string_t::operator += (const std::initializer_list<uchar_t> il) -> string_t&
	{
		return this->append(il);
	}

	auto string_t::operator == (const string_t& u) const -> bool
	{
		return al::ustr_equal(this->u_str(), u.u_str());
	}

	auto string_t::operator != (const string_t& u) const -> bool
	{
		return !(this->operator == (u));
	}

	auto string_t::operator == (const std::string& s) const -> bool
	{
		return (std::strcmp(s.c_str(), this->c_str()) == 0);
	}

	auto string_t::operator != (const std::string& s) const -> bool
	{
		return !(this->operator == (s));
	}

	auto string_t::operator == (const char* string) const -> bool
	{
		return (std::strcmp(string::validate_string(string), this->c_str()) == 0);
	}

	auto string_t::operator != (const char* string) const -> bool
	{
		return !(this->operator == (string));
	}

	auto string_t::c_str() const -> const char*
	{
		return al::c_str(this->m_data);
	}

	string_t::operator const char* () const
	{
		return al::c_str(this->m_data);
	}

	auto string_t::u_str() const -> const ALLEGRO::USTRING&
	{
		return this->m_data;
	}

	auto string_t::u_str() -> ALLEGRO::USTRING&
	{
		return this->m_data;
	}

	string_t::operator const ALLEGRO::USTRING& () const
	{
		return this->m_data;
	}

	string_t::operator ALLEGRO::USTRING& ()
	{
		return this->m_data;
	}

	auto string_t::size() const -> size_t
	{
		return al::ustr_size(this->m_data);
	}

	auto string_t::length() const -> size_t
	{
		return al::ustr_length(this->m_data);
	}

	auto string_t::empty() const -> bool
	{
		return (al::ustr_length(this->m_data) == 0);
	}

	auto string_t::clear() -> void
	{
		al::ustr_truncate(this->m_data, 0);
	}

	auto string_t::substr(size_t pos, size_t count) const -> string_t
	{
		int32_t end = 0;

		if (count == npos)
		{
			end = (int32_t)al::ustr_length(this->m_data);
		}
		else
		{
			end = (int32_t)(pos + count);
		}

		ALLEGRO::USTRING t = al::ustr_dup_substr(this->m_data, (int32_t)pos, end);

		string_t rv{ t };

		return rv;
	}

	auto string_t::operator[] (size_t pos) -> string_t::codepoint_t
	{
		return this->at(pos);
	}

	auto string_t::operator[] (size_t pos) const -> const string_t::codepoint_t
	{
		return this->at(pos);
	}

	auto string_t::at(size_t pos) -> string_t::codepoint_t
	{
		ALLEGRO::ASSERT(pos < al::ustr_length(this->m_data));

		return codepoint_t(this->m_data, (int32_t)pos);
	}

	auto string_t::at(size_t pos) const -> const string_t::codepoint_t
	{
		ALLEGRO::ASSERT(pos < al::ustr_length(this->m_data));

		return codepoint_t(this->m_data, (int32_t)pos);
	}

	auto string_t::push_back(uchar_t c) -> void
	{
		al::ustr_append_chr(this->m_data, c);
	}

	auto string_t::pop_back() -> void
	{
		ALLEGRO::ASSERT(al::ustr_size(this->m_data) > 0);
		al::ustr_remove_chr(this->m_data, (int32_t)al::ustr_size(this->m_data) - 1);
	}

	auto string_t::begin() -> string_t::iterator
	{
		return string_t::iterator(this->m_data, 0);
	}

	auto string_t::end() -> string_t::iterator
	{
		return string_t::iterator(this->m_data, (int32_t)this->length());
	}

	auto string_t::cbegin() const -> string_t::const_iterator
	{
		return string_t::const_iterator(this->m_data, 0);
	}

	auto string_t::cend() const -> string_t::const_iterator
	{
		return string_t::const_iterator(this->m_data, (int32_t)this->length());
	}

	auto string_t::rbegin() -> string_t::reverse_iterator
	{
		return reverse_iterator(this->m_data, (int32_t)this->length() - 1);
	}

	auto string_t::rend() -> string_t::reverse_iterator
	{
		return reverse_iterator(this->m_data, -1);
	}

	auto string_t::crbegin() const -> string_t::const_reverse_iterator
	{
		return const_reverse_iterator(this->m_data, (int32_t)this->length() - 1);
	}

	auto string_t::crend() const -> string_t::const_reverse_iterator
	{
		return const_reverse_iterator(this->m_data, -1);
	}

	auto string_t::append(const string_t& rhs) -> string_t&
	{
		al::ustr_append(this->u_str(), rhs.u_str());
		return *this;
	}

	auto string_t::append(const std::string& rhs) -> string_t&
	{
		al::ustr_append_cstr(this->u_str(), rhs.c_str());
		return *this;
	}

	auto string_t::append(const char* string) -> string_t&
	{
		al::ustr_append_cstr(this->u_str(), string::validate_string(string));
		return *this;
	}

	auto string_t::append(uchar_t rhs) -> string_t&
	{
		this->push_back(rhs);
		return *this;
	}

	auto string_t::append(const std::initializer_list<uchar_t> il) -> string_t&
	{
		return this->append(string_t(il));
	}

	auto string_t::prepend(const string_t& rhs) -> string_t&
	{
		al::ustr_insert(this->u_str(), 0, rhs.u_str());
		return *this;
	}

	auto string_t::prepend(const std::string& rhs) -> string_t&
	{
		al::ustr_insert_cstr(this->u_str(), 0, rhs.c_str());
		return *this;
	}

	auto string_t::prepend(const char* string) -> string_t&
	{
		al::ustr_insert_cstr(this->u_str(), 0, string::validate_string(string));
		return *this;
	}

	auto string_t::prepend(uchar_t rhs) -> string_t&
	{
		return this->insert(0, rhs);
	}

	auto string_t::prepend(const std::initializer_list<uchar_t> il) -> string_t&
	{
		return this->append(string_t(il));
	}

	auto string_t::compare(const string_t& rhs) const -> int32_t
	{
		return al::ustr_compare(this->u_str(), rhs.u_str());
	}

	auto string_t::compare(const std::string& rhs) const -> int32_t
	{
		return al::ustr_compare(this->u_str(), string_t(rhs).u_str());
	}

	auto string_t::compare(const char* string) const -> int32_t
	{
		return al::ustr_compare(this->u_str(), string_t(string::validate_string(string)).u_str());
	}

	auto string_t::insert(size_t pos, const string_t& rhs) -> string_t&
	{
		al::ustr_insert(this->u_str(), (int32_t)pos, rhs.u_str());
		return *this;
	}

	auto string_t::insert(size_t pos, const std::string& rhs) -> string_t&
	{
		al::ustr_insert_cstr(this->u_str(), (int32_t)pos, rhs.c_str());
		return *this;
	}

	auto string_t::insert(size_t pos, const char* rhs) -> string_t&
	{
		al::ustr_insert_cstr(this->u_str(), (int32_t)pos, (rhs ? rhs : ""));
		return *this;
	}

	auto string_t::insert(size_t pos, uchar_t rhs) -> string_t&
	{
		al::ustr_insert_chr(this->u_str(), (int32_t)pos, rhs);
		return *this;
	}

	auto string_t::insert(size_t pos, const std::initializer_list<uchar_t> il) -> string_t&
	{
		return this->insert(pos, string_t(il));
	}

	auto string_t::erase(size_t pos, size_t length) -> string_t&
	{
		int32_t end = 0;

		if (length == npos)
		{
			end = (int32_t)al::ustr_length(this->m_data);
		}
		else
		{
			end = (int32_t)(pos + length);
		}

		al::ustr_remove_range(this->u_str(), (int32_t)pos, end);
		return *this;
	}

	auto string_t::replace(size_t pos, size_t length, const string_t& rhs) -> string_t&
	{
		al::ustr_replace_range(this->u_str(), (int32_t)pos, (int32_t)length, rhs.u_str());
		return *this;
	}

	auto string_t::replace(size_t pos, size_t length, const std::string& rhs) -> string_t&
	{
		al::ustr_replace_range(this->u_str(), (int32_t)pos, (int32_t)length, string_t(rhs).u_str());
		return *this;
	}

	auto string_t::replace(size_t pos, size_t length, const char* rhs) -> string_t&
	{
		al::ustr_replace_range(this->u_str(), (int32_t)pos, (int32_t)length, string_t(rhs).u_str());
		return *this;
	}

	auto string_t::starts_with(const string_t& rhs) const -> bool
	{
		return al::ustr_has_prefix(this->u_str(), rhs.u_str());
	}

	auto string_t::starts_with(const std::string& rhs) const->bool
	{
		return al::ustr_has_prefix_cstr(this->u_str(), rhs.c_str());
	}

	auto string_t::starts_with(const char* string) const -> bool
	{
		return al::ustr_has_prefix_cstr(this->u_str(), string::validate_string(string));
	}

	auto string_t::starts_with(uchar_t rhs) const -> bool
	{
		if (this->size())
		{
			if ((*this)[0] == rhs)
			{
				return true;
			}
		}

		return false;
	}

	auto string_t::ends_with(const string_t& rhs) const -> bool
	{
		return al::ustr_has_suffix(this->u_str(), rhs.u_str());
	}

	auto string_t::ends_with(const std::string& rhs) const -> bool
	{
		return al::ustr_has_suffix_cstr(this->u_str(), rhs.c_str());
	}

	auto string_t::ends_with(const char* string) const -> bool
	{
		return al::ustr_has_suffix_cstr(this->u_str(), string::validate_string(string));
	}

	auto string_t::ends_with(uchar_t rhs) const -> bool
	{
		if (this->size())
		{
			if ((*this)[this->length() - 1] == rhs)
			{
				return true;
			}
		}

		return false;
	}

	auto string_t::contains(const string_t& rhs) const -> bool
	{
		return (al::ustr_find_str(this->u_str(), 0, rhs.u_str()) >= 0);
	}

	auto string_t::contains(const std::string& rhs) const -> bool
	{
		return (al::ustr_find_cstr(this->u_str(), 0, rhs.c_str()) >= 0);
	}

	auto string_t::contains(const char* string) const -> bool
	{
		return (al::ustr_find_cstr(this->u_str(), 0, string::validate_string(string)) >= 0);
	}

	auto string_t::contains(uchar_t rhs) const -> bool
	{
		return (al::ustr_find_chr(this->u_str(), 0, rhs) >= 0);
	}

	auto string_t::find(const string_t& rhs, size_t pos) const -> size_t
	{
		return (size_t)al::ustr_find_str(this->u_str(), (int32_t)pos, rhs.u_str());
	}

	auto string_t::find(const std::string& rhs, size_t pos) const -> size_t
	{
		return (size_t)al::ustr_find_cstr(this->u_str(), (int32_t)pos, rhs.c_str());
	}

	auto string_t::find(const char* string, size_t pos) const -> size_t
	{
		return (size_t)al::ustr_find_cstr(this->u_str(), (int32_t)pos, string::validate_string(string));
	}

	auto string_t::find(uchar_t rhs, size_t pos) const -> size_t
	{
		return (size_t)al::ustr_find_chr(this->u_str(), (int32_t)pos, rhs);
	}

	auto string_t::rfind(const string_t& rhs, size_t pos) const -> size_t
	{
		if (pos == npos)
		{
			pos = al::ustr_length(this->m_data) - 1;
		}

		return (size_t)al::ustr_rfind_str(this->u_str(), (int32_t)pos, rhs.u_str());
	}

	auto string_t::rfind(const std::string& rhs, size_t pos) const -> size_t
	{
		if (pos == npos)
		{
			pos = al::ustr_length(this->m_data) - 1;
		}

		return (size_t)al::ustr_rfind_cstr(this->u_str(), (int32_t)pos, rhs.c_str());
	}

	auto string_t::rfind(const char* string, size_t pos) const -> size_t
	{
		if (pos == npos)
		{
			pos = al::ustr_length(this->m_data) - 1;
		}

		return (size_t)al::ustr_rfind_cstr(this->u_str(), (int32_t)pos, string::validate_string(string));
	}

	auto string_t::rfind(uchar_t rhs, size_t pos) const -> size_t
	{
		if (pos == npos)
		{
			pos = al::ustr_length(this->m_data);
		}

		return (size_t)al::ustr_rfind_chr(this->u_str(), (int32_t)pos, rhs);
	}

	namespace string
	{
		auto to_string(const char* format, ...) -> string_t
		{
			string_t rv;
			va_list args;
			int32_t len;
			char* buffer;

			va_start(args, format);
			len = _vscprintf(format, args) // _vscprintf doesn't count
				+ 1; // terminating '\0'
			buffer = (char*)malloc(len * sizeof(char));

			if (NULL != buffer)
			{
				vsprintf_s(buffer, len, format, args);
				rv = buffer;
				free(buffer);
			}
			va_end(args);

			return rv;
		}

		auto create(uchar_t c, size_t n) -> string_t
		{
			ALLEGRO::USTRING u = al::ustr_new("");

			ALLEGRO::ASSERT(u);

			for (size_t i = 0; i < n; ++i)
			{
				al::ustr_append_chr(u, c);
			}

			return string_t(u);
		}

		auto to_lower(const string_t& string) -> string_t
		{
			string_t output;

			for (string_t::const_iterator it = string.cbegin(); it != string.cend(); ++it)
			{
				output.push_back(std::tolower(*it));
			}

			return output;
		}

		auto to_upper(const string_t& string) -> string_t
		{
			string_t output;

			for (auto it = string.cbegin(); it != string.cend(); ++it)
			{
				output.push_back(std::toupper(*it));
			}

			return output;
		}

		auto fuse(const std::vector<string_t> vector, char separator) -> string_t
		{
			string_t output;

			for (auto h : vector)
			{
				if (output.size() > 0)
				{
					output.push_back(separator);
				}

				output.append(string::to_upper(h));
			}

			return output;
		}

		auto separate(const string_t& string, std::vector<string_t>& vector, const char separator) -> size_t
		{
			size_t x = string.find(0, separator);

			if (x != string_t::npos)
			{
				vector.push_back(string.substr(0, x));
				separate(string.substr(x + 1, string.size() - x), vector, separator);
			}
			else
			{
				vector.push_back(string);
			}

			return vector.size();
		}

		template <> auto to_string(bool value) -> string_t
		{
			string_t string = (value ? "true" : "false");

			return string;
		}

		template <> auto to_string(int32_t value) -> string_t
		{
			return string_t(std::to_string(value));
		}

		template <> auto to_string(uint32_t value) -> string_t
		{
			return string_t(std::to_string(value));
		}

		template <> auto to_string(int64_t value) -> string_t
		{
			return string_t(std::to_string(value));
		}

		template <> auto to_string(uint64_t value) -> string_t
		{
			return string_t(std::to_string(value));
		}

		template <> auto to_string(float value) -> string_t
		{
			return string_t(std::to_string(value));
		}

		template <> auto to_string(double value) -> string_t
		{
			return string_t(std::to_string(value));
		}

		template <> auto to_string(const char* value) -> string_t
		{
			return string_t(value);
		}

		template <> auto from_string(const string_t& string) -> bool
		{
			return (string::to_lower(string) == "true");
		}

		template <> auto from_string(const string_t& string) -> int32_t
		{
			return std::stol(string.c_str());
		}

		template <> auto from_string(const string_t& string) -> uint32_t
		{
			return std::stoul(string.c_str());
		}

		template <> auto from_string(const string_t& string) -> int64_t
		{
			return std::stoll(string.c_str());
		}

		template <> auto from_string(const string_t& string) -> uint64_t
		{
			return std::stoull(string.c_str());
		}

		template <> auto from_string(const string_t& string) -> float
		{
			return std::stof(string.c_str());
		}

		template <> auto from_string(const string_t& string) -> double
		{
			return std::stod(string.c_str());
		}

		template <> auto from_string(const string_t& string) -> const char*
		{
			return string.c_str();
		}
	}
}

auto operator + (const wind::string_t& lhs, const wind::string_t& rhs) -> wind::string_t
{
	wind::string_t rv = lhs;
	rv.append(rhs);
	return rv;
}

auto operator + (const wind::string_t& lhs, const std::string& rhs) -> wind::string_t
{
	wind::string_t rv = lhs;
	rv.append(rhs);
	return rv;
}

auto operator + (const wind::string_t& lhs, const char* rhs) -> wind::string_t
{
	wind::string_t rv = lhs;
	rv.append(rhs);
	return rv;
}

auto operator + (const char* lhs, const wind::string_t& rhs) -> wind::string_t
{
	wind::string_t rv = lhs;
	rv.append(rhs);
	return rv;
}

auto operator + (const std::string& lhs, const wind::string_t& rhs) -> wind::string_t
{
	wind::string_t rv = lhs;
	rv.append(rhs);
	return rv;
}

auto operator + (const wind::string_t& lhs, wind::uchar_t rhs) -> wind::string_t
{
	wind::string_t rv = lhs;
	rv.push_back(rhs);
	return rv;
}

auto operator + (wind::uchar_t lhs, const wind::string_t& rhs) -> wind::string_t
{
	wind::string_t rv = wind::string::create(lhs, 1);
	rv.append(rhs);
	return rv;
}

auto operator + (const wind::string_t& lhs, char rhs) -> wind::string_t
{
	wind::string_t rv = lhs;
	rv.push_back(rhs);
	return rv;
}

auto operator + (char lhs, const wind::string_t& rhs) -> wind::string_t
{
	wind::string_t rv = wind::string::create(lhs, 1);
	rv.append(rhs);
	return rv;
}