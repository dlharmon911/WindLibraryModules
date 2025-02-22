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
		export auto to_lower(const string_t& string) -> string_t;
	}

	export class string_t
	{
	public:
		static constexpr size_t npos = -1;

		class codepoint_t
		{
		public:
			codepoint_t() = default;
			codepoint_t(const ALLEGRO::USTRING& string, int32_t offset);
			codepoint_t(const codepoint_t& ref);
			~codepoint_t() = default;

			operator uchar_t () const;

			auto operator = (const codepoint_t& ref)->codepoint_t&;
			auto get_string() -> ALLEGRO::USTRING&;
			auto get_string() const ->const ALLEGRO::USTRING&;
			auto get_offset() const->int32_t;
			auto set_offset(int32_t offset) -> void;
			auto get_codepoint() const->uchar_t;
			auto get_size() const->size_t;
			auto set_codepoint(uchar_t codepoint) -> size_t;
			auto operator = (uchar_t codepoint) ->const codepoint_t&;
			auto operator == (const codepoint_t& codepoint) const -> bool;

		private:
			ALLEGRO::USTRING m_string{};
			int32_t m_offset{ 0 };
		};

		string_t();
		string_t(const string_t& string);
		explicit string_t(const ALLEGRO::USTRING& string);
		explicit string_t(const std::string& string);
		string_t(const char* string);
		explicit string_t(const std::initializer_list<uchar_t> il);

		template <size_t N>
		string_t(const char string[N]) : m_data(al::ustr_new(""))
		{
			ALLEGRO::ASSERT(this->m_data);

			size_t i = 0;

			do
			{
				this->push_back(static_cast<int32_t>(string[i]));
			} while (i != N);
		}

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

		auto assign(const ALLEGRO::USTRING& string) -> string_t&;
		auto assign(const std::string& string) -> string_t&;
		auto assign(const string_t& string) -> string_t&;
		auto assign(const char* string) -> string_t&;
		auto assign(std::initializer_list<uchar_t> il) -> string_t&;
		template <class InputIterator> auto assign(InputIterator first, InputIterator last) -> string_t&
		{
			return this->assign(string_t(first, last));
		}

		auto operator = (const ALLEGRO::USTRING& string)->string_t&;
		auto operator = (const std::string& string)->string_t&;
		auto operator = (const char* string)->string_t&;
		auto operator = (const string_t& string)->string_t&;
		auto operator = (std::initializer_list<uchar_t> il)->string_t&;

		auto operator += (const ALLEGRO::USTRING& string)->string_t&;
		auto operator += (const std::string& string)->string_t&;
		auto operator += (const char* string)->string_t&;
		auto operator += (const string_t& string)->string_t&;
		auto operator += (std::initializer_list<uchar_t> il)->string_t&;

		auto c_str() const -> const char*;
		explicit operator const char* () const;

		auto u_str() const -> const ALLEGRO::USTRING&;
		auto u_str() -> ALLEGRO::USTRING&;

		explicit operator const ALLEGRO::USTRING& () const;
		explicit operator ALLEGRO::USTRING& ();

		auto size() const->size_t;
		auto length() const->size_t;
		auto empty() const -> bool;
		auto clear() -> void;

		auto substr(size_t pos = 0, size_t count = npos) const->string_t;

		auto operator[] (size_t pos)->codepoint_t;
		auto operator[] (size_t pos) const -> const codepoint_t;
		auto at(size_t pos) -> codepoint_t;
		auto at(size_t pos) const -> const codepoint_t;

		auto push_back(uchar_t c) -> void;
		auto pop_back() -> void;

		class iterator
		{
		public:
			iterator(const ALLEGRO::USTRING& string, int32_t offset) : m_codepoint(string, offset) {}

			auto operator == (const iterator& it) const -> bool
			{
				return this->m_codepoint == it.m_codepoint;
			}

			auto operator != (const iterator& it) const -> bool
			{
				return !operator == (it);
			}

			auto operator ++() -> iterator&
			{
				int32_t offset = this->m_codepoint.get_offset();

				if (offset < al::ustr_size(this->m_codepoint.get_string()))
				{
					al::ustr_next(this->m_codepoint.get_string(), offset);
					this->m_codepoint.set_offset(offset);
				}

				return *this;
			}

			auto operator ++ (int32_t) -> iterator
			{
				iterator tmp = *this;
				++(*this);
				return tmp;
			}

			auto get_string() -> ALLEGRO::USTRING&
			{
				return this->m_codepoint.get_string();
			}

			auto get_string() const -> const ALLEGRO::USTRING&
			{
				return this->m_codepoint.get_string();
			}

			auto get_offset() const -> int32_t
			{
				return this->m_codepoint.get_offset();
			}

			auto operator *() -> codepoint_t&
			{
				return this->m_codepoint;
			}

		private:
			codepoint_t m_codepoint{};
		};

		class const_iterator
		{
		public:
			const_iterator(const ALLEGRO::USTRING& string, int32_t offset) : m_codepoint(string, offset) {}

			auto operator == (const const_iterator& it) const -> bool
			{
				return this->m_codepoint == it.m_codepoint;
			}

			auto operator != (const const_iterator& it) const -> bool
			{
				return !operator == (it);
			}

			auto operator ++() -> const_iterator&
			{
				int32_t offset = this->m_codepoint.get_offset();

				if (offset < al::ustr_size(this->m_codepoint.get_string()))
				{
					al::ustr_next(this->m_codepoint.get_string(), offset);
					this->m_codepoint.set_offset(offset);
				}

				return *this;
			}

			auto operator ++ (int32_t) -> const_iterator
			{
				const_iterator tmp = *this;
				++(*this);
				return tmp;
			}

			auto get_string() const -> const ALLEGRO::USTRING&
			{
				return this->m_codepoint.get_string();
			}

			auto get_offset() const -> int32_t
			{
				return this->m_codepoint.get_offset();
			}

			auto operator *() const -> const codepoint_t&
			{
				return this->m_codepoint;
			}

		private:
			codepoint_t m_codepoint{};
		};

		class reverse_iterator
		{
		public:
			reverse_iterator(const ALLEGRO::USTRING& string, int32_t offset) : m_codepoint(string, offset) {}

			auto operator == (const reverse_iterator& it) const -> bool
			{
				return this->m_codepoint == it.m_codepoint;
			}

			auto operator != (const reverse_iterator& it) const -> bool
			{
				return !operator == (it);
			}

			auto operator --() -> reverse_iterator&
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

			auto operator -- (int32_t) -> reverse_iterator
			{
				reverse_iterator tmp = *this;
				--(*this);
				return tmp;
			}

			auto get_string() -> ALLEGRO::USTRING&
			{
				return this->m_codepoint.get_string();
			}

			auto get_string() const -> const ALLEGRO::USTRING&
			{
				return this->m_codepoint.get_string();
			}

			auto get_offset() const -> int32_t
			{
				return this->m_codepoint.get_offset();
			}

			auto operator *() -> codepoint_t&
			{
				return this->m_codepoint;
			}

		private:
			codepoint_t m_codepoint{};
		};

		class const_reverse_iterator
		{
		public:
			const_reverse_iterator(const ALLEGRO::USTRING& string, int32_t offset) : m_codepoint(string, offset) {}

			auto operator == (const const_reverse_iterator& it) const -> bool
			{
				return this->m_codepoint == it.m_codepoint;
			}

			auto operator != (const const_reverse_iterator& it) const -> bool
			{
				return !operator == (it);
			}

			auto operator --() -> const_reverse_iterator&
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

			auto operator -- (int32_t) -> const_reverse_iterator
			{
				const_reverse_iterator tmp = *this;
				--(*this);
				return tmp;
			}

			auto get_string() const -> const ALLEGRO::USTRING&
			{
				return this->m_codepoint.get_string();
			}

			auto get_offset() const -> int32_t
			{
				return this->m_codepoint.get_offset();
			}

			auto operator *() const -> const codepoint_t&
			{
				return this->m_codepoint;
			}

		private:
			codepoint_t m_codepoint{};
		};

		auto begin() const->iterator;
		auto end() const->iterator;
		auto cbegin() const->const_iterator;
		auto cend() const->const_iterator;
		auto rbegin() const->reverse_iterator;
		auto rend() const->reverse_iterator;
		auto crbegin() const->const_reverse_iterator;
		auto crend() const->const_reverse_iterator;

		auto append(const string_t& rhs) -> string_t&;
		auto append(const std::string& rhs) -> string_t&;
		auto append(const char* rhs) -> string_t&;
		auto append(uchar_t rhs) -> string_t&;
		auto append(const std::initializer_list<uchar_t> il) -> string_t&;
		template <class InputIterator>
		auto append(InputIterator first, InputIterator last) -> string_t&
		{
			return this->append(string_t(first, last));
		}

		auto prepend(const string_t& rhs) -> string_t&;
		auto prepend(const std::string& rhs) -> string_t&;
		auto prepend(const char* rhs) -> string_t&;
		auto prepend(uchar_t rhs) -> string_t&;
		auto prepend(const std::initializer_list<uchar_t> il) -> string_t&;
		template <class InputIterator>
		auto prepend(InputIterator first, InputIterator last) -> string_t&
		{
			return this->prepend(string_t(first, last));
		}

		auto compare(const string_t& rhs)const noexcept->int32_t;
		auto compare(const std::string& rhs) const->int32_t;
		auto compare(const char* rhs) const->int32_t;

		auto insert(size_t pos, const string_t& rhs) -> string_t&;
		auto insert(size_t pos, const std::string& rhs) -> string_t&;
		auto insert(size_t pos, const char* rhs) -> string_t&;
		auto insert(size_t pos, uchar_t rhs) -> string_t&;
		auto insert(size_t pos, const std::initializer_list<uchar_t> il) -> string_t&;

		template <class InputIterator>
		auto insert(iterator p, InputIterator first, InputIterator last) -> iterator
		{
			int32_t offset = p.get_offset();

			this->insert(offset, string_t(first, last));

			return iterator(this->m_data, offset);
		}

		auto erase(size_t pos = 0, size_t length = string_t::npos) -> string_t&;
		auto replace(size_t pos, size_t length, const string_t& rhs) -> string_t&;
		auto replace(size_t pos, size_t length, const std::string& rhs) -> string_t&;
		auto replace(size_t pos, size_t length, const char* rhs) -> string_t&;
		auto starts_with(const string_t& rhs) const->bool;
		auto starts_with(const std::string& rhs) const->bool;
		auto starts_with(const char* rhs) const->bool;
		auto starts_with(uchar_t rhs) const->bool;
		auto ends_with(const string_t& rhs) const->bool;
		auto ends_with(const std::string& rhs) const->bool;
		auto ends_with(const char* rhs) const->bool;
		auto ends_with(uchar_t rhs) const->bool;
		auto contains(const string_t& rhs) const->bool;
		auto contains(const std::string& rhs) const->bool;
		auto contains(const char* rhs) const->bool;
		auto contains(uchar_t rhs) const->bool;
		auto find(const string_t& rhs, size_t pos = 0) const->size_t;
		auto find(const std::string& rhs, size_t pos = 0) const->size_t;
		auto find(const char* rhs, size_t pos = 0) const->size_t;
		auto find(uchar_t rhs, size_t pos = 0) const->size_t;
		auto rfind(const string_t& rhs, size_t pos = string_t::npos) const->size_t;
		auto rfind(const std::string& rhs, size_t pos = string_t::npos) const->size_t;
		auto rfind(const char* rhs, size_t pos = string_t::npos) const->size_t;
		auto rfind(uchar_t rhs, size_t pos = string_t::npos) const->size_t;

		template <typename T>
		auto get_as() const -> T
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

		template <> auto get_as<string_t>() const -> string_t
		{
			return *this;
		}

		template <> auto get_as<bool>() const -> bool
		{
			return string::to_lower(*this).compare("true") == 0;
		}

		auto operator == (const wind::string_t& rhs) const noexcept -> bool;
		auto operator <=> (const wind::string_t& rhs) const noexcept -> std::strong_ordering;

		template <typename E, typename TR = std::char_traits<E>>
		friend auto operator << (std::basic_ostream<E, TR>& stream, const wind::string_t& string) -> std::basic_ostream<E, TR>&
		{
			stream.write(string.c_str(), string.size());
			return stream;
		}

		template <class E, class TR = std::char_traits<E>>
		friend auto operator >> (std::basic_istream<E, TR>& stream, wind::string_t& string) -> std::basic_istream<E, TR>&
		{
			return stream >> (string.u_str());
		}

	private:
		ALLEGRO::USTRING m_data;
	};

	namespace string
	{
		export auto to_string(const char* format, ...) -> string_t;
		export auto create(uchar_t c, size_t n) -> string_t;
		export auto to_lower(const string_t& string) -> string_t;
		export auto to_upper(const string_t& string) -> string_t;
		export auto fuse(const std::vector<string_t> vector, char separator) -> string_t;
		export auto separate(const string_t& string, std::vector<string_t>& vector, const char separator) -> size_t;

		export template <typename T> inline auto to_string(T value) -> string_t = delete;
		export template <> auto to_string(bool value) -> string_t;
		export template <> auto to_string(int32_t value) -> string_t;
		export template <> auto to_string(uint32_t value) -> string_t;
		export template <> auto to_string(int64_t value) -> string_t;
		export template <> auto to_string(uint64_t value) -> string_t;
		export template <> auto to_string(float value) -> string_t;
		export template <> auto to_string(double value) -> string_t;
		export template <> auto to_string(const char* value) -> string_t;

		export template <typename T> inline auto from_string(const string_t& string) -> T = delete;
		export template <> auto from_string(const string_t& string) -> bool;
		export template <> auto from_string(const string_t& string) -> int32_t;
		export template <> auto from_string(const string_t& string) -> uint32_t;
		export template <> auto from_string(const string_t& string) -> int64_t;
		export template <> auto from_string(const string_t& string) -> uint64_t;
		export template <> auto from_string(const string_t& string) -> float;
		export template <> auto from_string(const string_t& string) -> double;
		export template <> auto from_string(const string_t& string) -> const char*;
	}
}

export auto operator + (const wind::string_t& lhs, const wind::string_t& rhs)->wind::string_t;
export auto operator + (const wind::string_t& lhs, const char* rhs)->wind::string_t;
export auto operator + (const char* rhs, const wind::string_t& lhs)->wind::string_t;
export auto operator + (const wind::string_t& lhs, char rhs)->wind::string_t;
export auto operator + (char lhs, const wind::string_t& rhs)->wind::string_t;

export auto operator == (const char* lhs, const wind::string_t& rhs) -> bool;
export auto operator != (const char* lhs, const wind::string_t& rhs) -> bool;
export auto operator <  (const char* lhs, const wind::string_t& rhs) -> bool;
export auto operator <= (const char* lhs, const wind::string_t& rhs) -> bool;
export auto operator >  (const char* lhs, const wind::string_t& rhs) -> bool;
export auto operator >= (const char* lhs, const wind::string_t& rhs) -> bool;
export auto operator == (const wind::string_t& lhs, const char* rhs) -> bool;
export auto operator != (const wind::string_t& lhs, const char* rhs) -> bool;
export auto operator <  (const wind::string_t& lhs, const char* rhs) -> bool;
export auto operator <= (const wind::string_t& lhs, const char* rhs) -> bool;
export auto operator >  (const wind::string_t& lhs, const char* rhs) -> bool;
export auto operator >= (const wind::string_t& lhs, const char* rhs) -> bool;

namespace std
{
	export template <> struct hash<wind::string_t>
	{
	public:
		auto operator()(const wind::string_t& str) const -> size_t
		{
			size_t s = hash<int32_t>{}(-1);

			for (size_t i = 0; (i < 3 && i < str.size()); ++i)
			{
				s ^= hash<int32_t>{}(str[i]);
			}

			return s;
		}
	};
}
