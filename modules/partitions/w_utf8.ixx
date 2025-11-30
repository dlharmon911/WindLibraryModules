export module wind:u8string;

import std;
import allegro;
import <cstdarg>;
import :base;

namespace wind
{
	namespace string
	{
		static auto validate_string(const char* string)
		{
			static const char* empty_string = "";

			if (string)
			{
				return string;
			}

			return empty_string;
		}
	}

	export using uchar_t = int32_t;

	class u8string_t;

	namespace string
	{
		export auto to_lower(const u8string_t& string) -> u8string_t;
	}

	export class u8string_t
	{
	public:
		static constexpr size_t npos = -1;

		class codepoint_t
		{
		public:
			codepoint_t() = default;

			codepoint_t(const ALLEGRO::USTRING& string, int32_t offset) : m_string(string), m_offset(offset) {}

			codepoint_t(const codepoint_t& ref) : m_string(ref.m_string), m_offset(ref.m_offset) {}

			auto operator = (const codepoint_t& ref) -> codepoint_t&
			{
				this->m_string = ref.m_string;
				this->m_offset = ref.m_offset;
				return *this;
			}

			auto get_string() -> ALLEGRO::USTRING&
			{
				return this->m_string;
			}

			auto get_string() const -> const ALLEGRO::USTRING&
			{
				return this->m_string;
			}

			auto get_offset() const -> int32_t
			{
				return this->m_offset;
			}

			auto set_offset(int32_t offset) -> void
			{
				this->m_offset = offset;
			}

			auto get_codepoint() const -> uchar_t
			{
				return al::ustr_get(this->m_string, (uchar_t)this->m_offset);
			}

			auto get_size() const -> size_t
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

			operator uchar_t () const
			{
				return al::ustr_get(this->m_string, (uchar_t)this->m_offset);
			}

			auto set_codepoint(uchar_t codepoint) -> size_t
			{
				return al::ustr_set_chr(this->m_string, (int32_t)this->m_offset, codepoint);
			}

			auto operator = (uchar_t codepoint) -> const codepoint_t&
			{
				al::ustr_set_chr(this->m_string, (int32_t)this->m_offset, codepoint);
				return *this;
			}

			auto operator == (const codepoint_t& codepoint) const -> bool
			{
				return (this->m_string == codepoint.m_string && this->m_offset == codepoint.m_offset);
			}

		private:
			ALLEGRO::USTRING m_string{};
			int32_t m_offset{ 0 };
		};

		u8string_t() : m_data(al::ustr_new(""))
		{
			ALLEGRO::ASSERT(this->m_data);
		}

		u8string_t(const u8string_t& string) : m_data(al::ustr_new(string.c_str()))
		{
			ALLEGRO::ASSERT(this->m_data);
		}

		template <typename T>
		explicit u8string_t(const T& value) : m_data()
		{
			std::stringstream ss{};

			ss << value;

			this->m_data = al::ustr_new(ss.str().c_str());
			ALLEGRO::ASSERT(this->m_data);
		}

		template <> explicit u8string_t(const ALLEGRO::USTRING& string) : m_data((bool)string ? al::ustr_dup(string) : al::ustr_new(""))
		{
			ALLEGRO::ASSERT(this->m_data);
		}

		u8string_t(const char* string) : m_data(al::ustr_new(string::validate_string(string)))
		{
			ALLEGRO::ASSERT(this->m_data);
		}

		explicit u8string_t(const std::initializer_list<uchar_t> il) : m_data(al::ustr_new(""))
		{
			ALLEGRO::ASSERT(this->m_data);

			for (auto a : il)
			{
				al::ustr_append_chr(this->m_data, a);
			}
		}

		template <size_t N> u8string_t(const char string[N]) : m_data(al::ustr_new(""))
		{
			ALLEGRO::ASSERT(this->m_data);

			size_t i = 0;

			do
			{
				this->push_back(static_cast<int32_t>(string[i]));
			} while (i != N);
		}

		template <class InputIterator>
		u8string_t(InputIterator first, InputIterator last) : m_data(al::ustr_new(""))
		{
			ALLEGRO::ASSERT(this->m_data);

			InputIterator it = first;

			do
			{
				this->push_back((int32_t)(*it));
			} while (it != last);
		}

		virtual ~u8string_t() = default;

		auto c_str() const -> const char*
		{
			return al::c_str(this->m_data);
		}

		operator bool() const
		{
			return (this->m_data && al::ustr_length(this->m_data) > 0);
		}

		explicit operator const char* () const
		{
			return al::c_str(this->m_data);
		}


		auto u_str() const -> const ALLEGRO::USTRING&
		{
			return this->m_data;
		}

		auto u_str() -> ALLEGRO::USTRING&
		{
			return this->m_data;
		}

		explicit operator const ALLEGRO::USTRING& () const
		{
			return this->m_data;
		}

		explicit operator ALLEGRO::USTRING& ()
		{
			return this->m_data;
		}

		auto size() const -> size_t
		{
			return al::ustr_size(this->m_data);
		}

		auto length() const -> size_t
		{
			return al::ustr_length(this->m_data);
		}

		auto empty() const -> bool
		{
			return (al::ustr_length(this->m_data) == 0);
		}

		auto clear() -> void
		{
			al::ustr_truncate(this->m_data, 0);
		}

		auto substr(size_t pos = 0, size_t count = npos) const -> u8string_t
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

			u8string_t rv{ t };

			return rv;
		}


		auto operator[] (size_t pos)->codepoint_t
		{
			ALLEGRO::ASSERT(pos < al::ustr_length(this->m_data));

			return codepoint_t(this->m_data, (int32_t)pos);
		}

		auto operator[] (size_t pos) const -> const codepoint_t
		{
			ALLEGRO::ASSERT(pos < al::ustr_length(this->m_data));

			return codepoint_t(this->m_data, (int32_t)pos);
		}

		auto at(size_t pos) -> codepoint_t
		{
			ALLEGRO::ASSERT(pos < al::ustr_length(this->m_data));

			return codepoint_t(this->m_data, (int32_t)pos);
		}

		auto at(size_t pos) const -> const codepoint_t
		{
			ALLEGRO::ASSERT(pos < al::ustr_length(this->m_data));

			return codepoint_t(this->m_data, (int32_t)pos);
		}

		auto push_back(uchar_t c) -> void
		{
			al::ustr_append_chr(this->m_data, c);
		}

		auto pop_back() -> void
		{
			ALLEGRO::ASSERT(al::ustr_size(this->m_data) > 0);
			al::ustr_remove_chr(this->m_data, (int32_t)al::ustr_size(this->m_data) - 1);
		}

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

		auto begin() const -> iterator
		{
			return iterator(this->m_data, 0);
		}

		auto end() const -> iterator
		{
			return iterator(this->m_data, (int32_t)this->length());
		}

		auto cbegin() const -> const_iterator
		{
			return const_iterator(this->m_data, 0);
		}

		auto cend() const -> const_iterator
		{
			return const_iterator(this->m_data, (int32_t)this->length());
		}

		auto rbegin() const -> reverse_iterator
		{
			return reverse_iterator(this->m_data, (int32_t)this->length() - 1);
		}

		auto rend() const -> reverse_iterator
		{
			return reverse_iterator(this->m_data, -1);
		}

		auto crbegin() const -> const_reverse_iterator
		{
			return const_reverse_iterator(this->m_data, (int32_t)this->length() - 1);
		}

		auto crend() const -> const_reverse_iterator
		{
			return const_reverse_iterator(this->m_data, -1);
		}

		template <typename T> auto assign(const T& value) -> u8string_t&
		{
			std::stringstream ss{};

			ss << value;

			this->m_data = al::ustr_new(ss.str().c_str());
			ALLEGRO::ASSERT(this->m_data);
			return *this;
		}
		template <>	auto assign(const ALLEGRO::USTRING& string) -> u8string_t&;
		template <> auto assign(const u8string_t& string) -> u8string_t&;
		auto assign(const char* string) -> u8string_t&;
		auto assign(std::initializer_list<uchar_t> il) -> u8string_t&;
		template <class InputIterator> auto assign(InputIterator first, InputIterator last) -> u8string_t&
		{
			return this->assign(u8string_t(first, last));
		}

		template <typename T> auto operator = (const T& value) -> u8string_t&
		{
			this->assign(value);
			return *this;
		}
		auto operator = (const char* string) -> u8string_t&;
		auto operator = (std::initializer_list<uchar_t> il)->u8string_t&;

		template <typename T> auto append(const T& value) -> u8string_t&
		{
			std::stringstream ss{};

			ss << value;

			al::ustr_append_cstr(this->u_str(), ss.str().c_str());
			return *this;
		}
		
		template <> auto append(const u8string_t& rhs) -> u8string_t&
		{
			al::ustr_append(this->u_str(), rhs.u_str());
			return *this;
		}

		template <>	auto append(const ALLEGRO::USTRING& string) -> u8string_t&
		{
			al::ustr_append(this->u_str(), string);
			return *this;
		}

		auto append(const char* rhs) -> u8string_t&
		{
			al::ustr_append_cstr(this->u_str(), string::validate_string(rhs));
			return *this;
		}

		auto append(uchar_t rhs) -> u8string_t&
		{
			this->push_back(rhs);
			return *this;
		}

		auto append(const std::initializer_list<uchar_t> il) -> u8string_t&
		{
			return this->append(u8string_t(il));
		}

		template <class InputIterator> auto append(InputIterator first, InputIterator last) -> u8string_t&
		{
			return this->append(u8string_t(first, last));
		}

		template <typename T> auto operator += (const T& value) -> u8string_t&
		{
			this->append(value);
			return *this;
		}

		auto operator += (const char* rhs)->u8string_t&
		{
			al::ustr_append_cstr(this->u_str(), string::validate_string(rhs));
			return *this;
		}

		auto operator += (std::initializer_list<uchar_t> il)->u8string_t&
		{
			return this->append(u8string_t(il));
		}

		template <typename T> auto prepend(const T& value) -> u8string_t&
		{
			std::stringstream ss{};

			ss << value;

			al::ustr_insert_cstr(this->u_str(), 0, ss.str().c_str());
			return *this;
		}
		template <> auto prepend(const u8string_t& rhs) -> u8string_t&
		{
			al::ustr_insert(this->u_str(), 0, rhs.u_str());
			return *this;
		}

		template <>	auto prepend(const ALLEGRO::USTRING& string) -> u8string_t&
		{
			al::ustr_insert(this->u_str(), 0, string);
			return *this;
		}

		auto prepend(const char* rhs) -> u8string_t&
		{
			al::ustr_insert_cstr(this->u_str(), 0, string::validate_string(rhs));
			return *this;
		}

		auto prepend(uchar_t rhs) -> u8string_t&
		{
			al::ustr_insert_chr(this->u_str(), 0, rhs);
			return *this;
		}

		auto prepend(const std::initializer_list<uchar_t> il) -> u8string_t&
		{
			return this->prepend(u8string_t(il));
		}

		template <class InputIterator> auto prepend(InputIterator first, InputIterator last) -> u8string_t&
		{
			return this->prepend(u8string_t(first, last));
		}

		auto compare(const u8string_t& rhs)const noexcept -> int32_t
		{
			return al::ustr_compare(this->u_str(), rhs.u_str());
		}

		auto compare(const std::string& rhs) const -> int32_t
		{
			return al::ustr_compare(this->u_str(), u8string_t(rhs).u_str());
		}

		auto compare(const char* rhs) const -> int32_t
		{
			return al::ustr_compare(this->u_str(), u8string_t(string::validate_string(rhs)).u_str());
		}

		auto insert(size_t pos, const u8string_t& rhs) -> u8string_t&
		{
			al::ustr_insert(this->u_str(), (int32_t)pos, rhs.u_str());
			return *this;
		}

		auto insert(size_t pos, const std::string& rhs) -> u8string_t&
		{
			al::ustr_insert_cstr(this->u_str(), (int32_t)pos, rhs.c_str());
			return *this;
		}

		auto insert(size_t pos, const char* rhs) -> u8string_t&
		{
			al::ustr_insert_cstr(this->u_str(), (int32_t)pos, (rhs ? rhs : ""));
			return *this;
		}

		auto insert(size_t pos, uchar_t rhs) -> u8string_t&
		{
			al::ustr_insert_chr(this->u_str(), (int32_t)pos, rhs);
			return *this;
		}

		auto insert(size_t pos, const std::initializer_list<uchar_t> il) -> u8string_t&
		{
			return this->insert(pos, u8string_t(il));
		}

		template <class InputIterator> auto insert(iterator p, InputIterator first, InputIterator last) -> iterator
		{
			int32_t offset = p.get_offset();

			this->insert(offset, u8string_t(first, last));

			return iterator(this->m_data, offset);
		}


		auto erase(size_t pos, size_t length) -> u8string_t&
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

		auto replace(size_t pos, size_t length, const u8string_t& rhs) -> u8string_t&
		{
			al::ustr_replace_range(this->u_str(), (int32_t)pos, (int32_t)length, rhs.u_str());
			return *this;
		}

		auto replace(size_t pos, size_t length, const std::string& rhs) -> u8string_t&
		{
			al::ustr_replace_range(this->u_str(), (int32_t)pos, (int32_t)length, u8string_t(rhs).u_str());
			return *this;
		}

		auto replace(size_t pos, size_t length, const char* rhs) -> u8string_t&
		{
			al::ustr_replace_range(this->u_str(), (int32_t)pos, (int32_t)length, u8string_t(rhs).u_str());
			return *this;
		}

		auto starts_with(const u8string_t& rhs) const -> bool
		{
			return al::ustr_has_prefix(this->u_str(), rhs.u_str());
		}

		auto starts_with(const std::string& rhs) const -> bool
		{
			return al::ustr_has_prefix_cstr(this->u_str(), rhs.c_str());
		}

		auto starts_with(const char* string) const -> bool
		{
			return al::ustr_has_prefix_cstr(this->u_str(), string::validate_string(string));
		}

		auto starts_with(uchar_t rhs) const -> bool
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

		auto ends_with(const u8string_t& rhs) const -> bool
		{
			return al::ustr_has_suffix(this->u_str(), rhs.u_str());
		}

		auto ends_with(const std::string& rhs) const -> bool
		{
			return al::ustr_has_suffix_cstr(this->u_str(), rhs.c_str());
		}

		auto ends_with(const char* string) const -> bool
		{
			return al::ustr_has_suffix_cstr(this->u_str(), string::validate_string(string));
		}

		auto ends_with(uchar_t rhs) const -> bool
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

		auto contains(const u8string_t& rhs) const -> bool
		{
			return (al::ustr_find_str(this->u_str(), 0, rhs.u_str()) >= 0);
		}

		auto contains(const std::string& rhs) const -> bool
		{
			return (al::ustr_find_cstr(this->u_str(), 0, rhs.c_str()) >= 0);
		}

		auto contains(const char* string) const -> bool
		{
			return (al::ustr_find_cstr(this->u_str(), 0, string::validate_string(string)) >= 0);
		}

		auto contains(uchar_t rhs) const -> bool
		{
			return (al::ustr_find_chr(this->u_str(), 0, rhs) >= 0);
		}

		auto find(const u8string_t& rhs, size_t pos = 0) const -> size_t
		{
			return (size_t)al::ustr_find_str(this->u_str(), (int32_t)pos, rhs.u_str());
		}

		auto find(const std::string& rhs, size_t pos = 0) const -> size_t
		{
			return (size_t)al::ustr_find_cstr(this->u_str(), (int32_t)pos, rhs.c_str());
		}

		auto find(const char* string, size_t pos = 0) const -> size_t
		{
			return (size_t)al::ustr_find_cstr(this->u_str(), (int32_t)pos, string::validate_string(string));
		}

		auto find(uchar_t rhs, size_t pos = 0) const -> size_t
		{
			return (size_t)al::ustr_find_chr(this->u_str(), (int32_t)pos, rhs);
		}

		auto rfind(const u8string_t& rhs, size_t pos = npos) const -> size_t
		{
			if (pos == npos)
			{
				pos = al::ustr_length(this->m_data) - 1;
			}

			return (size_t)al::ustr_rfind_str(this->u_str(), (int32_t)pos, rhs.u_str());
		}

		auto rfind(const std::string& rhs, size_t pos = npos) const -> size_t
		{
			if (pos == npos)
			{
				pos = al::ustr_length(this->m_data) - 1;
			}

			return (size_t)al::ustr_rfind_cstr(this->u_str(), (int32_t)pos, rhs.c_str());
		}

		auto rfind(const char* string, size_t pos = npos) const -> size_t
		{
			if (pos == npos)
			{
				pos = al::ustr_length(this->m_data) - 1;
			}

			return (size_t)al::ustr_rfind_cstr(this->u_str(), (int32_t)pos, string::validate_string(string));
		}

		auto rfind(uchar_t rhs, size_t pos = npos) const -> size_t
		{
			if (pos == npos)
			{
				pos = al::ustr_length(this->m_data);
			}

			return (size_t)al::ustr_rfind_chr(this->u_str(), (int32_t)pos, rhs);
		}

		auto operator == (const wind::u8string_t& rhs) const noexcept -> bool
		{
			return this->compare(rhs) == 0;
		}

		auto operator <=> (const wind::u8string_t& rhs) const noexcept -> std::strong_ordering
		{
			int32_t compare = this->compare(rhs);

			if (compare)
			{
				if (compare < 0)
				{
					return std::strong_ordering::less;
				}

				return std::strong_ordering::greater;
			}

			return std::strong_ordering::equal;
		}

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

		template <> auto get_as<u8string_t>() const -> u8string_t
		{
			return *this;
		}

		template <> auto get_as<bool>() const -> bool
		{
			return string::to_lower(*this).compare("true") == 0;
		}

		template <typename E, typename TR = std::char_traits<E>>
		friend auto operator << (std::basic_ostream<E, TR>& stream, const wind::u8string_t& string) -> std::basic_ostream<E, TR>&
		{
			stream.write(string.c_str(), string.size());
			return stream;
		}

		template <class E, class TR = std::char_traits<E>>
		friend auto operator >> (std::basic_istream<E, TR>& stream, wind::u8string_t& string) -> std::basic_istream<E, TR>&
		{
			return stream >> (string.u_str());
		}

		friend auto operator + (const wind::u8string_t& lhs, const wind::u8string_t& rhs) -> wind::u8string_t
		{
			wind::u8string_t rv = lhs;
			rv.append(rhs);
			return rv;
		}

		friend auto operator + (const wind::u8string_t& lhs, const char* rhs) -> wind::u8string_t
		{
			wind::u8string_t rv = lhs;
			rv.append(rhs);
			return rv;
		}

		friend auto operator + (const char* lhs, const wind::u8string_t& rhs) -> wind::u8string_t
		{
			wind::u8string_t rv = lhs;
			rv.append(rhs);
			return rv;
		}

		friend auto operator + (const wind::u8string_t& lhs, char rhs) -> wind::u8string_t
		{
			wind::u8string_t rv = lhs;
			rv.push_back(rhs);
			return rv;
		}

		friend auto operator + (char lhs, const wind::u8string_t& rhs) -> wind::u8string_t
		{
			wind::u8string_t rv({ lhs });
			rv.append(rhs);
			return rv;
		}

		friend auto operator == (const char* lhs, const wind::u8string_t& rhs) -> bool
		{
			return rhs.compare(lhs) == 0;
		}

		friend auto operator == (const wind::u8string_t& lhs, const char* rhs) -> bool
		{
			return lhs.compare(rhs) == 0;
		}

		friend auto operator <=> (const char* lhs, const wind::u8string_t& rhs) noexcept -> std::strong_ordering
		{
			return rhs.operator<=>(lhs);
		}

		friend auto operator <=> (const wind::u8string_t& rhs, const char* lhs) noexcept -> std::strong_ordering
		{
			return rhs.operator<=>(lhs);
		}


	private:
		ALLEGRO::USTRING m_data;
	};

	namespace string
	{
		export auto create(uchar_t c, size_t n) -> u8string_t
		{
			ALLEGRO::USTRING u = al::ustr_new("");

			ALLEGRO::ASSERT(u);

			for (size_t i = 0; i < n; ++i)
			{
				al::ustr_append_chr(u, c);
			}

			return u8string_t(u);
		}

		export auto to_lower(const u8string_t& string) -> u8string_t
		{
			u8string_t output;

			for (auto it = string.cbegin(); it != string.cend(); ++it)
			{
				output.push_back(std::tolower(*it));
			}

			return output;
		}

		export auto to_upper(const u8string_t& string) -> u8string_t
		{
			u8string_t output;

			for (auto it = string.cbegin(); it != string.cend(); ++it)
			{
				output.push_back(std::toupper(*it));
			}

			return output;
		}

		export auto fuse(const std::vector<u8string_t> vector, char separator) -> u8string_t
		{
			u8string_t output;

			for (auto& h : vector)
			{
				if (output.size() > 0)
				{
					output.push_back(separator);
				}

				output.append(string::to_upper(h));
			}

			return output;
		}

		static auto do_separate(const u8string_t& string, std::vector<u8string_t>& vector, const char separator) -> size_t
		{
			size_t x = string.find(separator);

			if (x != u8string_t::npos)
			{
				vector.push_back(string.substr(0, x));
				do_separate(string.substr(x + 1, string.size() - x), vector, separator);
			}
			else
			{
				vector.push_back(string);
			}

			return vector.size();
		}

		export auto separate(const u8string_t& string, std::vector<u8string_t>& vector, const char separator) -> size_t
		{
			vector.clear();

			do_separate(string, vector, separator);

			return vector.size();
		}

		export template <typename T> inline auto to_string(T value) -> u8string_t
		{
			std::stringstream ss{};

			ss << value;

			return u8string_t(ss.str());
		}

		export template <> auto to_string(const std::string& format) -> u8string_t
		{
			return u8string_t(format);
		}

		export template<typename Arg, typename... Args>
			auto to_string(const std::string& format, Arg arg, Args... args) -> u8string_t
		{
			size_t pos = format.find("{}");

			if (pos == u8string_t::npos)
			{
				to_string(format);
				return;
			}

			return format.substr(0, pos) + to_string(arg) + to_string(format.substr(pos + 2), args...);
		}

		export template <typename T> inline auto from_string(const u8string_t& string) -> T
		{
			return string.get_as<T>();
		}

		export template <> auto to_string(bool value) -> u8string_t
		{
			u8string_t string = (value ? "true" : "false");

			return string;
		}

		export template <> auto to_string(int32_t value) -> u8string_t
		{
			return u8string_t(std::to_string(value));
		}

		export template <> auto to_string(uint32_t value) -> u8string_t
		{
			return u8string_t(std::to_string(value));
		}

		export template <> auto to_string(int64_t value) -> u8string_t
		{
			return u8string_t(std::to_string(value));
		}

		export template <> auto to_string(uint64_t value) -> u8string_t
		{
			return u8string_t(std::to_string(value));
		}

		export template <> auto to_string(float value) -> u8string_t
		{
			return u8string_t(std::to_string(value));
		}

		export template <> auto to_string(double value) -> u8string_t
		{
			return u8string_t(std::to_string(value));
		}

		export template <> auto to_string(const char* value) -> u8string_t
		{
			return u8string_t(value);
		}

		export template <> auto from_string(const u8string_t& string) -> bool
		{
			return (string::to_lower(string) == "true");
		}

		export template <> auto from_string(const u8string_t& string) -> int32_t
		{
			return std::stol(string.c_str());
		}

		export template <> auto from_string(const u8string_t& string) -> uint32_t
		{
			return std::stoul(string.c_str());
		}

		export template <> auto from_string(const u8string_t& string) -> int64_t
		{
			return std::stoll(string.c_str());
		}

		export template <> auto from_string(const u8string_t& string) -> uint64_t
		{
			return std::stoull(string.c_str());
		}

		export template <> auto from_string(const u8string_t& string) -> float
		{
			return std::stof(string.c_str());
		}

		export template <> auto from_string(const u8string_t& string) -> double
		{
			return std::stod(string.c_str());
		}

		export template <> auto from_string(const u8string_t& string) -> const char*
		{
			return string.c_str();
		}
	}
}


namespace std
{
	export template <> struct hash<wind::u8string_t>
	{
	public:
		auto operator()(const wind::u8string_t& str) const -> size_t
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
