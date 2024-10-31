export module wind:string;

import std;
import <vector>;
import <string>;
import <string_view>;
import <cstdint>;
import <sstream>;
import allegro;
import :base;

namespace wind
{
	export using uchar_t = int32_t;

	class string_t;

	namespace string
	{
		auto to_lower(const string_t& string) -> string_t;
	}

	export class string_t : public class_t<string_t>
	{
	public:
		static constexpr size_t npos = -1;

		class codepoint_t
		{
		public:
			codepoint_t() = delete;
			codepoint_t(const ALLEGRO::USTRING& string, int32_t offset);
			codepoint_t(const codepoint_t& ref);
			~codepoint_t() = default;

			operator uchar_t () const;

			auto operator = (const codepoint_t& ref)->codepoint_t&;
			auto get_string() -> ALLEGRO::USTRING&;
			auto get_string() const -> const ALLEGRO::USTRING&;
			auto get_offset() const -> int32_t;
			auto set_offset(int32_t offset) -> void;
			auto get_codepoint() const -> uchar_t;
			auto get_size() const -> size_t;
			auto set_codepoint(uchar_t codepoint) -> size_t;
			auto operator = (uchar_t codepoint) -> codepoint_t&;
			auto operator == (const codepoint_t& codepoint) const -> bool;
			auto operator != (const codepoint_t& codepoint) const -> bool;

		protected:
			ALLEGRO::USTRING m_string;
			int32_t m_offset;
		};


		string_t();
		string_t(const ALLEGRO::USTRING& string);
		string_t(const std::string& string);
		string_t(const char* string);
		string_t(const string_t& string);
		string_t(const std::initializer_list<uchar_t> il);

		template <class InputIterator>
		string_t(InputIterator first, InputIterator last) : m_data(al::ustr_new(""))
		{
			ALLEGRO::ASSERT(this->m_data);

			InputIterator it = first;

			do
			{
				this->push_back((int32_t)(*it));
			} while (it != last);
		}

		virtual ~string_t();

		string_t& assign(const ALLEGRO::USTRING& string);
		string_t& assign(const std::string& string);
		string_t& assign(const string_t& string);
		string_t& assign(const char* string);
		string_t& assign(std::initializer_list<uchar_t> il);
		template <class InputIterator>
		string_t& assign(InputIterator first, InputIterator last)
		{
			return this->assign(string_t(first, last));
		}

		string_t& operator = (const ALLEGRO::USTRING& string);
		string_t& operator = (const std::string& string);
		string_t& operator = (const char* string);
		string_t& operator = (const string_t& string);
		string_t& operator = (std::initializer_list<uchar_t> il);

		string_t& operator += (const ALLEGRO::USTRING& string);
		string_t& operator += (const std::string& string);
		string_t& operator += (const char* string);
		string_t& operator += (const string_t& string);
		string_t& operator += (std::initializer_list<uchar_t> il);

		bool operator == (const string_t& u) const;
		bool operator != (const string_t& u) const;
		bool operator == (const std::string& s) const;
		bool operator != (const std::string& s) const;
		bool operator == (const char* s) const;
		bool operator != (const char* s) const;


		const char* c_str() const;
		explicit operator const char* () const;

		const ALLEGRO::USTRING& u_str() const;
		ALLEGRO::USTRING& u_str();

		operator const ALLEGRO::USTRING& () const;
		operator ALLEGRO::USTRING& ();

		size_t size() const;
		size_t length() const;
		bool empty() const;
		void clear();

		string_t substr(size_t pos = 0, size_t count = npos) const;

		codepoint_t operator[] (size_t pos);
		const codepoint_t operator[] (size_t pos) const;
		codepoint_t at(size_t pos);
		const codepoint_t at(size_t pos) const;

		void push_back(uchar_t c);
		void pop_back();

		class iterator
		{
		public:
			iterator(const ALLEGRO::USTRING& string, int32_t offset) : m_codepoint(string, offset) {}

			bool operator == (const iterator& it) const
			{
				return this->m_codepoint == it.m_codepoint;
			}

			bool operator != (const iterator& it) const
			{
				return !operator == (it);
			}

			iterator& operator ++()
			{
				int32_t offset = this->m_codepoint.get_offset();

				if (offset < al::ustr_size(this->m_codepoint.get_string()))
				{
					al::ustr_next(this->m_codepoint.get_string(), offset);
					this->m_codepoint.set_offset(offset);
				}

				return *this;
			}

			iterator operator ++ (int32_t)
			{
				iterator tmp = *this;
				++(*this);
				return tmp;
			}

			ALLEGRO::USTRING& get_string()
			{
				return this->m_codepoint.get_string();
			}

			const ALLEGRO::USTRING& get_string() const
			{
				return this->m_codepoint.get_string();
			}

			int32_t get_offset() const
			{
				return this->m_codepoint.get_offset();
			}

			codepoint_t& operator *()
			{
				return this->m_codepoint;
			}

		protected:
			codepoint_t m_codepoint;
		};

		class const_iterator
		{
		public:
			const_iterator(const ALLEGRO::USTRING& string, int32_t offset) : m_codepoint(string, offset) {}

			bool operator == (const const_iterator& it) const
			{
				return this->m_codepoint == it.m_codepoint;
			}

			bool operator != (const const_iterator& it) const
			{
				return !operator == (it);
			}

			const_iterator& operator ++()
			{
				int32_t offset = this->m_codepoint.get_offset();

				if (offset < al::ustr_size(this->m_codepoint.get_string()))
				{
					al::ustr_next(this->m_codepoint.get_string(), offset);
					this->m_codepoint.set_offset(offset);
				}

				return *this;
			}

			const_iterator operator ++ (int32_t)
			{
				const_iterator tmp = *this;
				++(*this);
				return tmp;
			}

			const ALLEGRO::USTRING& get_string() const
			{
				return this->m_codepoint.get_string();
			}

			int32_t get_offset() const
			{
				return this->m_codepoint.get_offset();
			}

			codepoint_t& operator *()
			{
				return this->m_codepoint;
			}

		protected:
			codepoint_t m_codepoint;
		};

		class reverse_iterator
		{
		public:
			reverse_iterator(const ALLEGRO::USTRING& string, int32_t offset) : m_codepoint(string, offset) {}

			bool operator == (const reverse_iterator& it) const
			{
				return this->m_codepoint == it.m_codepoint;
			}

			bool operator != (const reverse_iterator& it) const
			{
				return !operator == (it);
			}

			reverse_iterator& operator --()
			{
				int32_t offset = this->m_codepoint.get_offset();

				if (offset == 0)
				{
					offset = -1;
				}
				else
				{
					al::ustr_prev(this->m_codepoint.get_string(), offset);
				}

				this->m_codepoint.set_offset(offset);

				return *this;
			}

			reverse_iterator operator -- (int32_t)
			{
				reverse_iterator tmp = *this;
				--(*this);
				return tmp;
			}

			ALLEGRO::USTRING& get_string()
			{
				return this->m_codepoint.get_string();
			}

			const ALLEGRO::USTRING& get_string() const
			{
				return this->m_codepoint.get_string();
			}

			int32_t get_offset() const
			{
				return this->m_codepoint.get_offset();
			}

			codepoint_t& operator *()
			{
				return this->m_codepoint;
			}

		protected:
			codepoint_t m_codepoint;
		};

		class const_reverse_iterator
		{
		public:
			const_reverse_iterator(const ALLEGRO::USTRING& string, int32_t offset) : m_codepoint(string, offset) {}

			bool operator == (const const_reverse_iterator& it) const
			{
				return this->m_codepoint == it.m_codepoint;
			}

			bool operator != (const const_reverse_iterator& it) const
			{
				return !operator == (it);
			}

			const_reverse_iterator& operator --()
			{
				int32_t offset = this->m_codepoint.get_offset();

				if (offset == 0)
				{
					offset = -1;
				}
				else
				{
					al::ustr_prev(this->m_codepoint.get_string(), offset);
				}

				this->m_codepoint.set_offset(offset);

				return *this;
			}

			const_reverse_iterator operator -- (int32_t)
			{
				const_reverse_iterator tmp = *this;
				--(*this);
				return tmp;
			}

			const ALLEGRO::USTRING& get_string() const
			{
				return this->m_codepoint.get_string();
			}

			int32_t get_offset() const
			{
				return this->m_codepoint.get_offset();
			}

			const codepoint_t& operator * () const
			{
				return this->m_codepoint;
			}

		protected:
			codepoint_t m_codepoint;
		};

		iterator begin();
		iterator end();
		const_iterator cbegin() const;
		const_iterator cend() const;
		reverse_iterator rbegin();
		reverse_iterator rend();
		const_reverse_iterator crbegin() const;
		const_reverse_iterator crend() const;

		string_t& append(const string_t& rhs);
		string_t& append(const std::string& rhs);
		string_t& append(const char* rhs);
		string_t& append(uchar_t rhs);
		string_t& append(const std::initializer_list<uchar_t> il);
		template <class InputIterator>
		string_t& append(InputIterator first, InputIterator last)
		{
			return this->append(string_t(first, last));
		}

		string_t& prepend(const string_t& rhs);
		string_t& prepend(const std::string& rhs);
		string_t& prepend(const char* rhs);
		string_t& prepend(uchar_t rhs);
		string_t& prepend(const std::initializer_list<uchar_t> il);
		template <class InputIterator>
		string_t& prepend(InputIterator first, InputIterator last)
		{
			return this->prepend(string_t(first, last));
		}

		int32_t compare(const string_t& rhs) const;
		int32_t compare(const std::string& rhs) const;
		int32_t compare(const char* rhs) const;

		string_t& insert(size_t pos, const string_t& rhs);
		string_t& insert(size_t pos, const std::string& rhs);
		string_t& insert(size_t pos, const char* rhs);
		string_t& insert(size_t pos, uchar_t rhs);
		string_t& insert(size_t pos, const std::initializer_list<uchar_t> il);
		template <class InputIterator>
		iterator insert(iterator p, InputIterator first, InputIterator last)
		{
			int32_t offset = p.get_offset();

			this->insert(offset, string_t(first, last));

			return iterator(this->m_data, offset);
		}

		string_t& erase(size_t pos = 0, size_t length = string_t::npos);
		string_t& replace(size_t pos, size_t length, const string_t& rhs);
		string_t& replace(size_t pos, size_t length, const std::string& rhs);
		string_t& replace(size_t pos, size_t length, const char* rhs);
		bool starts_with(const string_t& rhs) const;
		bool starts_with(const std::string& rhs) const;
		bool starts_with(const char* rhs) const;
		bool starts_with(uchar_t rhs) const;
		bool ends_with(const string_t& rhs) const;
		bool ends_with(const std::string& rhs) const;
		bool ends_with(const char* rhs) const;
		bool ends_with(uchar_t rhs) const;
		bool contains(const string_t& rhs) const;
		bool contains(const std::string& rhs) const;
		bool contains(const char* rhs) const;
		bool contains(uchar_t rhs) const;
		size_t find(const string_t& rhs, size_t pos = 0) const;
		size_t find(const std::string& rhs, size_t pos = 0) const;
		size_t find(const char* rhs, size_t pos = 0) const;
		size_t find(uchar_t rhs, size_t pos = 0) const;
		size_t rfind(const string_t& rhs, size_t pos = string_t::npos) const;
		size_t rfind(const std::string& rhs, size_t pos = string_t::npos) const;
		size_t rfind(const char* rhs, size_t pos = string_t::npos) const;
		size_t rfind(uchar_t rhs, size_t pos = string_t::npos) const;

		template <typename T>
		T get_as() const
		{
			T value{};

			std::string str(this->c_str());
			std::stringstream ss(str);

			if ((ss >> value).fail())
			{
				throw std::bad_cast();
			}

			if (!(ss >> std::ws).eof())
			{
				throw std::bad_cast();
			}

			return value;
		}

		template <> string_t get_as<string_t>() const
		{
			return *this;
		}

		template <> bool get_as<bool>() const
		{
			return string::to_lower(*this) == "true";
		}

	protected:
		ALLEGRO::USTRING m_data;
	};

	namespace string
	{
		export string_t to_string(const char* format, ...);
		export string_t create(uchar_t c, size_t n);
		export string_t to_lower(const string_t& string);
		export string_t to_upper(const string_t& string);
		export string_t fuse(const std::vector<string_t> vector, char separator);
		export size_t separate(const string_t& string, std::vector<string_t>& vector, const char separator);

		export template <typename T> inline string_t to_string(const T& value)
		{
			string_t string;
			std::stringstream stream;

			stream << value;

			string.assign(stream.str());

			return string;
		}

		export template <> inline string_t to_string(const bool& value)
		{
			string_t string = (value ? "true" : "false");

			return string;
		}

		export template <> inline string_t to_string(const string_t& value)
		{
			return value;
		}
	}
}

export wind::string_t operator + (const wind::string_t& lhs, const wind::string_t& rhs);
export wind::string_t operator + (const wind::string_t& lhs, const std::string& rhs);
export wind::string_t operator + (const wind::string_t& lhs, const char* rhs);
export wind::string_t operator + (const wind::string_t& lhs, wind::uchar_t rhs);
export wind::string_t operator + (const wind::string_t& lhs, char rhs);
export wind::string_t operator + (const std::string& rhs, const wind::string_t& lhs);
export wind::string_t operator + (const char* rhs, const wind::string_t& lhs);
export wind::string_t operator + (wind::uchar_t rhs, const wind::string_t& lhs);
export wind::string_t operator + (char rhs, const wind::string_t& lhs);

template <typename E, typename TR = std::char_traits<E>> std::basic_ostream<E, TR>& operator << (std::basic_ostream<E, TR>& stream, const wind::string_t& string)
{
	stream.write(string.c_str(), string.size());
	return stream;
}

export template <class E, class TR = std::char_traits<E>>
std::basic_istream<E, TR>& operator >> (std::basic_istream<E, TR>& stream, wind::string_t& string)
{
	return stream >> (string.u_str());
}

namespace std
{
	export template <> struct hash<wind::string_t>
	{
	public:
		auto operator()(const wind::string_t& str) const -> size_t
		{
			size_t s = std::hash<int32_t>{}(1);

			for (size_t i = 0; (i < 3 && i < str.size()); ++i)
			{
				s ^= std::hash<int32_t>{}(str[i]);
			}

			return s;
		}
	};
}