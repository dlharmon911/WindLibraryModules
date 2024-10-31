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
		const char* validate_string(const char* string)
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
	string_t::codepoint_t& string_t::codepoint_t::operator = (const codepoint_t& ref)
	{
		this->m_string = ref.m_string;
		this->m_offset = ref.m_offset;
		return *this;
	}

	ALLEGRO::USTRING& string_t::codepoint_t::get_string()
	{
		return this->m_string;
	}

	const ALLEGRO::USTRING& string_t::codepoint_t::get_string() const
	{
		return this->m_string;
	}

	int32_t string_t::codepoint_t::get_offset() const
	{
		return this->m_offset;
	}

	void string_t::codepoint_t::set_offset(int32_t offset)
	{
		this->m_offset = offset;
	}

	uchar_t string_t::codepoint_t::get_codepoint() const
	{
		return al::ustr_get(this->m_string, (uchar_t)this->m_offset);
	}

	size_t string_t::codepoint_t::get_size() const
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

	size_t string_t::codepoint_t::set_codepoint(uchar_t codepoint)
	{
		return al::ustr_set_chr(this->m_string, (int32_t)this->m_offset, codepoint);
	}

	string_t::codepoint_t& string_t::codepoint_t::operator = (uchar_t codepoint)
	{
		al::ustr_set_chr(this->m_string, (int32_t)this->m_offset, codepoint);
		return *this;
	}

	bool string_t::codepoint_t::operator == (const string_t::codepoint_t& codepoint) const
	{
		return (this->m_string == codepoint.m_string && this->m_offset == codepoint.m_offset);
	}

	bool string_t::codepoint_t::operator != (const string_t::codepoint_t& codepoint) const
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

	string_t& string_t::assign(const ALLEGRO::USTRING& string)
	{
		this->m_data = ((bool)string ? al::ustr_dup(string) : al::ustr_new(""));
		ALLEGRO::ASSERT(this->m_data);
		return *this;
	}

	string_t& string_t::assign(const std::string& string)
	{
		this->m_data = al::ustr_new(string.c_str());
		ALLEGRO::ASSERT(this->m_data);
		return *this;
	}

	string_t& string_t::assign(const string_t& str)
	{
		this->m_data = al::ustr_dup(str.m_data);
		ALLEGRO::ASSERT(this->m_data);
		return *this;
	}

	string_t& string_t::assign(const char* string)
	{
		this->m_data = al::ustr_new(string::validate_string(string));
		ALLEGRO::ASSERT(this->m_data);
		return *this;
	}

	string_t& string_t::assign(const std::initializer_list<uchar_t> il)
	{
		return this->assign(string_t(il));
	}

	string_t& string_t::operator = (const ALLEGRO::USTRING& string)
	{
		this->m_data = ((bool)string ? al::ustr_dup(string) : al::ustr_new(""));
		ALLEGRO::ASSERT(this->m_data);
		return *this;
	}

	string_t& string_t::operator = (const std::string& string)
	{
		this->m_data = al::ustr_new(string.c_str());
		ALLEGRO::ASSERT(this->m_data);
		return *this;
	}

	string_t& string_t::operator = (const char* string)
	{
		this->m_data = al::ustr_new(string::validate_string(string));
		ALLEGRO::ASSERT(this->m_data);
		return *this;
	}

	string_t& string_t::operator = (const string_t& string)
	{
		this->m_data = al::ustr_dup(string.m_data);
		ALLEGRO::ASSERT(this->m_data);
		return *this;
	}

	string_t& string_t::operator = (const std::initializer_list<uchar_t> il)
	{
		return this->assign(string_t(il));
	}

	string_t& string_t::operator += (const ALLEGRO::USTRING& string)
	{
		return this->append(string);
	}

	string_t& string_t::operator += (const std::string& string)
	{
		return this->append(string);
	}

	string_t& string_t::operator += (const char* string)
	{
		return this->append(string::validate_string(string));
	}

	string_t& string_t::operator += (const string_t& string)
	{
		return this->append(string);
	}

	string_t& string_t::operator += (const std::initializer_list<uchar_t> il)
	{
		return this->append(il);
	}

	bool string_t::operator == (const string_t& u) const
	{
		return al::ustr_equal(this->u_str(), u.u_str());
	}

	bool string_t::operator != (const string_t& u) const
	{
		return !(this->operator == (u));
	}

	bool string_t::operator == (const std::string& s) const
	{
		return (std::strcmp(s.c_str(), this->c_str()) == 0);
	}

	bool string_t::operator != (const std::string& s) const
	{
		return !(this->operator == (s));
	}

	bool string_t::operator == (const char* string) const
	{
		return (std::strcmp(string::validate_string(string), this->c_str()) == 0);
	}

	bool string_t::operator != (const char* string) const
	{
		return !(this->operator == (string));
	}

	const char* string_t::c_str() const
	{
		return al::c_str(this->m_data);
	}

	string_t::operator const char* () const
	{
		return al::c_str(this->m_data);
	}

	const ALLEGRO::USTRING& string_t::u_str() const
	{
		return this->m_data;
	}

	string_t::operator const ALLEGRO::USTRING& () const
	{
		return this->m_data;
	}

	ALLEGRO::USTRING& string_t::u_str()
	{
		return this->m_data;
	}

	string_t::operator ALLEGRO::USTRING& ()
	{
		return this->m_data;
	}

	size_t string_t::size() const
	{
		return al::ustr_size(this->m_data);
	}

	size_t string_t::length() const
	{
		return al::ustr_length(this->m_data);
	}

	bool string_t::empty() const
	{
		return (al::ustr_length(this->m_data) == 0);
	}

	void string_t::clear()
	{
		al::ustr_truncate(this->m_data, 0);
	}

	string_t string_t::substr(size_t pos, size_t count) const
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

	string_t::codepoint_t string_t::operator[] (size_t pos)
	{
		return this->at(pos);
	}

	const string_t::codepoint_t string_t::operator[] (size_t pos) const
	{
		return this->at(pos);
	}

	string_t::codepoint_t string_t::at(size_t pos)
	{
		ALLEGRO::ASSERT(pos < al::ustr_length(this->m_data));

		return codepoint_t(this->m_data, (int32_t)pos);
	}

	const string_t::codepoint_t string_t::at(size_t pos) const
	{
		ALLEGRO::ASSERT(pos < al::ustr_length(this->m_data));

		return codepoint_t(this->m_data, (int32_t)pos);
	}

	void string_t::push_back(uchar_t c)
	{
		al::ustr_append_chr(this->m_data, c);
	}

	void string_t::pop_back()
	{
		ALLEGRO::ASSERT(al::ustr_size(this->m_data) > 0);
		al::ustr_remove_chr(this->m_data, (int32_t)al::ustr_size(this->m_data) - 1);
	}

	string_t::iterator string_t::begin()
	{
		return string_t::iterator(this->m_data, 0);
	}

	string_t::iterator string_t::end()
	{
		return string_t::iterator(this->m_data, (int32_t)this->length());
	}

	string_t::const_iterator string_t::cbegin() const
	{
		return string_t::const_iterator(this->m_data, 0);
	}

	string_t::const_iterator string_t::cend() const
	{
		return string_t::const_iterator(this->m_data, (int32_t)this->length());
	}

	string_t::reverse_iterator string_t::rbegin()
	{
		return reverse_iterator(this->m_data, (int32_t)this->length() - 1);
	}

	string_t::reverse_iterator string_t::rend()
	{
		return reverse_iterator(this->m_data, -1);
	}

	string_t::const_reverse_iterator string_t::crbegin() const
	{
		return const_reverse_iterator(this->m_data, (int32_t)this->length() - 1);
	}

	string_t::const_reverse_iterator string_t::crend() const
	{
		return const_reverse_iterator(this->m_data, -1);
	}

	string_t& string_t::append(const string_t& rhs)
	{
		al::ustr_append(this->u_str(), rhs.u_str());
		return *this;
	}

	string_t& string_t::append(const std::string& rhs)
	{
		al::ustr_append_cstr(this->u_str(), rhs.c_str());
		return *this;
	}

	string_t& string_t::append(const char* string)
	{
		al::ustr_append_cstr(this->u_str(), string::validate_string(string));
		return *this;
	}

	string_t& string_t::append(uchar_t rhs)
	{
		this->push_back(rhs);
		return *this;
	}

	string_t& string_t::append(const std::initializer_list<uchar_t> il)
	{
		return this->append(string_t(il));
	}

	string_t& string_t::prepend(const string_t& rhs)
	{
		al::ustr_insert(this->u_str(), 0, rhs.u_str());
		return *this;
	}

	string_t& string_t::prepend(const std::string& rhs)
	{
		al::ustr_insert_cstr(this->u_str(), 0, rhs.c_str());
		return *this;
	}

	string_t& string_t::prepend(const char* string)
	{
		al::ustr_insert_cstr(this->u_str(), 0, string::validate_string(string));
		return *this;
	}

	string_t& string_t::prepend(uchar_t rhs)
	{
		return this->insert(0, rhs);
	}

	string_t& string_t::prepend(const std::initializer_list<uchar_t> il)
	{
		return this->append(string_t(il));
	}

	int32_t string_t::compare(const string_t& rhs) const
	{
		return al::ustr_compare(this->u_str(), rhs.u_str());
	}

	int32_t string_t::compare(const std::string& rhs) const
	{
		return al::ustr_compare(this->u_str(), string_t(rhs).u_str());
	}

	int32_t string_t::compare(const char* string) const
	{
		return al::ustr_compare(this->u_str(), string_t(string::validate_string(string)).u_str());
	}

	string_t& string_t::insert(size_t pos, const string_t& rhs)
	{
		al::ustr_insert(this->u_str(), (int32_t)pos, rhs.u_str());
		return *this;
	}

	string_t& string_t::insert(size_t pos, const std::string& rhs)
	{
		al::ustr_insert_cstr(this->u_str(), (int32_t)pos, rhs.c_str());
		return *this;
	}

	string_t& string_t::insert(size_t pos, const char* rhs)
	{
		al::ustr_insert_cstr(this->u_str(), (int32_t)pos, (rhs ? rhs : ""));
		return *this;
	}

	string_t& string_t::insert(size_t pos, uchar_t rhs)
	{
		al::ustr_insert_chr(this->u_str(), (int32_t)pos, rhs);
		return *this;
	}

	string_t& string_t::insert(size_t pos, const std::initializer_list<uchar_t> il)
	{
		return this->insert(pos, string_t(il));
	}

	string_t& string_t::erase(size_t pos, size_t length)
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

	string_t& string_t::replace(size_t pos, size_t length, const string_t& rhs)
	{
		al::ustr_replace_range(this->u_str(), (int32_t)pos, (int32_t)length, rhs.u_str());
		return *this;
	}

	string_t& string_t::replace(size_t pos, size_t length, const std::string& rhs)
	{
		al::ustr_replace_range(this->u_str(), (int32_t)pos, (int32_t)length, string_t(rhs).u_str());
		return *this;
	}

	string_t& string_t::replace(size_t pos, size_t length, const char* rhs)
	{
		al::ustr_replace_range(this->u_str(), (int32_t)pos, (int32_t)length, string_t(rhs).u_str());
		return *this;
	}

	bool string_t::starts_with(const string_t& rhs) const
	{
		return al::ustr_has_prefix(this->u_str(), rhs.u_str());
	}

	bool string_t::starts_with(const std::string& rhs) const
	{
		return al::ustr_has_prefix_cstr(this->u_str(), rhs.c_str());
	}

	bool string_t::starts_with(const char* string) const
	{
		return al::ustr_has_prefix_cstr(this->u_str(), string::validate_string(string));
	}

	bool string_t::starts_with(uchar_t rhs) const
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

	bool string_t::ends_with(const string_t& rhs) const
	{
		return al::ustr_has_suffix(this->u_str(), rhs.u_str());
	}

	bool string_t::ends_with(const std::string& rhs) const
	{
		return al::ustr_has_suffix_cstr(this->u_str(), rhs.c_str());
	}

	bool string_t::ends_with(const char* string) const
	{
		return al::ustr_has_suffix_cstr(this->u_str(), string::validate_string(string));
	}

	bool string_t::ends_with(uchar_t rhs) const
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

	bool string_t::contains(const string_t& rhs) const
	{
		return (al::ustr_find_str(this->u_str(), 0, rhs.u_str()) >= 0);
	}

	bool string_t::contains(const std::string& rhs) const
	{
		return (al::ustr_find_cstr(this->u_str(), 0, rhs.c_str()) >= 0);
	}

	bool string_t::contains(const char* string) const
	{
		return (al::ustr_find_cstr(this->u_str(), 0, string::validate_string(string)) >= 0);
	}

	bool string_t::contains(uchar_t rhs) const
	{
		return (al::ustr_find_chr(this->u_str(), 0, rhs) >= 0);
	}

	size_t string_t::find(const string_t& rhs, size_t pos) const
	{
		return (size_t)al::ustr_find_str(this->u_str(), (int32_t)pos, rhs.u_str());
	}

	size_t string_t::find(const std::string& rhs, size_t pos) const
	{
		return (size_t)al::ustr_find_cstr(this->u_str(), (int32_t)pos, rhs.c_str());
	}

	size_t string_t::find(const char* string, size_t pos) const
	{
		return (size_t)al::ustr_find_cstr(this->u_str(), (int32_t)pos, string::validate_string(string));
	}

	size_t string_t::find(uchar_t rhs, size_t pos) const
	{
		return (size_t)al::ustr_find_chr(this->u_str(), (int32_t)pos, rhs);
	}

	size_t string_t::rfind(const string_t& rhs, size_t pos) const
	{
		if (pos == npos)
		{
			pos = al::ustr_length(this->m_data) - 1;
		}

		return (size_t)al::ustr_rfind_str(this->u_str(), (int32_t)pos, rhs.u_str());
	}

	size_t string_t::rfind(const std::string& rhs, size_t pos) const
	{
		if (pos == npos)
		{
			pos = al::ustr_length(this->m_data) - 1;
		}

		return (size_t)al::ustr_rfind_cstr(this->u_str(), (int32_t)pos, rhs.c_str());
	}

	size_t string_t::rfind(const char* string, size_t pos) const
	{
		if (pos == npos)
		{
			pos = al::ustr_length(this->m_data) - 1;
		}

		return (size_t)al::ustr_rfind_cstr(this->u_str(), (int32_t)pos, string::validate_string(string));
	}

	size_t string_t::rfind(uchar_t rhs, size_t pos) const
	{
		if (pos == npos)
		{
			pos = al::ustr_length(this->m_data);
		}

		return (size_t)al::ustr_rfind_chr(this->u_str(), (int32_t)pos, rhs);
	}

	namespace string
	{
		string_t to_string(const char* format, ...)
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


		string_t create(uchar_t c, size_t n)
		{
			ALLEGRO::USTRING u = al::ustr_new("");

			ALLEGRO::ASSERT(u);

			for (size_t i = 0; i < n; ++i)
			{
				al::ustr_append_chr(u, c);
			}

			return string_t(u);
		}


		string_t to_lower(const string_t& string)
		{
			string_t output;

			for (string_t::const_iterator it = string.cbegin(); it != string.cend(); ++it)
			{
				output.push_back(std::tolower(*it));
			}

			return output;
		}

		string_t to_upper(const string_t& string)
		{
			string_t output;

			for (auto it = string.cbegin(); it != string.cend(); ++it)
			{
				output.push_back(std::toupper(*it));
			}

			return output;
		}

		string_t fuse(const std::vector<string_t> vector, char separator)
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

		size_t separate(const string_t& string, std::vector<string_t>& vector, const char separator)
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
	}
}

wind::string_t operator + (const wind::string_t& lhs, const wind::string_t& rhs)
{
	wind::string_t rv = lhs;
	rv.append(rhs);
	return rv;
}

wind::string_t operator + (const wind::string_t& lhs, const std::string& rhs)
{
	wind::string_t rv = lhs;
	rv.append(rhs);
	return rv;
}

wind::string_t operator + (const wind::string_t& lhs, const char* rhs)
{
	wind::string_t rv = lhs;
	rv.append(rhs);
	return rv;
}

wind::string_t operator + (const char* lhs, const wind::string_t& rhs)
{
	wind::string_t rv = lhs;
	rv.append(rhs);
	return rv;
}

wind::string_t operator + (const std::string& lhs, const wind::string_t& rhs)
{
	wind::string_t rv = lhs;
	rv.append(rhs);
	return rv;
}

wind::string_t operator + (const wind::string_t& lhs, wind::uchar_t rhs)
{
	wind::string_t rv = lhs;
	rv.push_back(rhs);
	return rv;
}

wind::string_t operator + (wind::uchar_t lhs, const wind::string_t& rhs)
{
	wind::string_t rv = wind::string::create(lhs, 1);
	rv.append(rhs);
	return rv;
}

wind::string_t operator + (const wind::string_t& lhs, char rhs)
{
	wind::string_t rv = lhs;
	rv.push_back(rhs);
	return rv;
}

wind::string_t operator + (char lhs, const wind::string_t& rhs)
{
	wind::string_t rv = wind::string::create(lhs, 1);
	rv.append(rhs);
	return rv;
}

