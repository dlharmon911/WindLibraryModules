export module wind:json.object;

import <vector>;
import <unordered_map>;
import <string>;
import <memory>;
import allegro;
import :hex;
import :file;
import :base;
import :string;

namespace WIND
{
	namespace JSON
	{
		export enum
		{
			TYPE_NULL,
			TYPE_BOOLEAN,
			TYPE_NUMBER,
			TYPE_STRING,
			TYPE_OBJECT,
			TYPE_ARRAY
		};
	}
}

namespace wind
{
	class json_object_t;
	class json_array_t;

	export class json_t
	{
	public:
		json_t();
		json_t(bool val);
		json_t(double val);
		json_t(const string_t& val);
		json_t(const json_object_t& val);
		json_t(const json_array_t& val);
		json_t(const json_t& json);
		~json_t();

		auto operator = (const json_t& json)->json_t&;

		auto is_defined() const -> bool;

		auto clear() -> void;

		auto get_type() const->int32_t;

		auto set_as_boolean(bool val) -> bool;
		auto set_as_number(double val) -> bool;
		auto set_as_string(const string_t& val) -> bool;
		auto set_as_object(const json_object_t& val) -> bool;
		auto set_as_array(const json_array_t& val) -> bool;

		auto get_as_boolean() const -> bool;
		auto get_as_number() const -> double;
		auto get_as_string() const->string_t;
		auto get_as_object() -> json_object_t&;
		auto get_as_object() const -> const json_object_t&;
		auto get_as_array() -> json_array_t&;
		auto get_as_array() const -> const json_array_t&;

		explicit operator bool() const;
		explicit operator double() const;
		explicit operator string_t();
		explicit operator const string_t() const;
		explicit operator json_object_t& ();
		explicit operator const json_object_t& () const;
		explicit operator json_array_t& ();
		explicit operator const json_array_t& () const;

	private:
		int32_t m_type;
		std::shared_ptr<void> m_data;
	};

	using json_key_t = string_t;

	export using json_pair_t = std::pair<json_key_t, json_t>;

	export class json_object_t
	{
	private:
		using vector_t = std::unordered_map<json_key_t, json_t>;
		using allocator_t = vector_t::allocator_type;

	public:
		using element_type = json_t;
		using pointer_element_type = wind::add_pointer<element_type>::type;
		using const_pointer_element_type = wind::add_pointer<wind::add_const<element_type>::type>::type;
		using reference_element_type = wind::add_reference<element_type>::type;
		using const_reference_element_type = wind::add_reference<wind::add_const<element_type>::type>::type;

		json_object_t();
		json_object_t(const json_object_t& object);
		json_object_t(json_object_t& object);
		~json_object_t();

		auto operator = (const json_object_t& object)->json_object_t&;
		auto operator = (json_object_t& object)->json_object_t&;
		auto clear() noexcept -> void;
		auto size() const noexcept -> size_t;
		auto is_empty() const noexcept -> bool;

		auto at(const json_key_t& key) -> reference_element_type;
		auto at(const json_key_t& key) const->const_reference_element_type;
		auto operator [](const json_key_t& key)->reference_element_type;

		auto add(const json_key_t& key, const element_type& val) -> void;
		auto add(const json_pair_t& pair) -> void;
		auto remove(const json_key_t& key) -> void;

		class iterator
		{
		private:
			iterator() = default;
		public:
			iterator(vector_t::iterator it) : m_it(it) {}
			auto key() -> const json_key_t& { return this->m_it->first; }
			auto operator == (const iterator& it) const -> bool { return (this->m_it == it.m_it); }
			auto operator != (const iterator& it) const -> bool { return !operator == (it); }
			auto operator ++ () -> iterator& { ++this->m_it; return *this; }
			auto operator ++ (int32_t) -> iterator { iterator tmp = *this; ++(*this); return tmp; }
			auto operator * () -> reference_element_type { return this->m_it->second; }
			auto operator -> () -> pointer_element_type { return &this->m_it->second; }

			friend class json_object_t;
		private:
			vector_t::iterator m_it;
		};

		class const_iterator
		{
		private:
			const_iterator() = default;
		public:
			const_iterator(vector_t::const_iterator it) : m_it(it) {}

			auto key() const -> const json_key_t& { return this->m_it->first; }
			auto operator == (const const_iterator& it) const -> bool { return (this->m_it == it.m_it); }
			auto operator != (const const_iterator& it) const -> bool { return !operator == (it); }
			auto operator ++ () -> const_iterator& { ++this->m_it; return *this; }
			auto operator ++ (int32_t) -> const_iterator { const_iterator tmp = *this; ++(*this); return tmp; }
			auto operator * () const -> const_reference_element_type { return this->m_it->second; }
			auto operator -> () const -> const_pointer_element_type { return &this->m_it->second; }

			friend class json_object_t;
		private:
			vector_t::const_iterator m_it;
		};

		auto find(const json_key_t& key) -> iterator;
		auto find(const json_key_t& key) const->const_iterator;

		auto begin() -> iterator;
		auto end() -> iterator;
		auto cbegin() const->const_iterator;
		auto cend() const->const_iterator;

	private:

		vector_t m_data;
	};

	/****************************************************************************************************/

	export class json_array_t
	{
	public:
		using element_type = json_t;
		using pointer_element_type = wind::add_pointer<element_type>::type;
		using const_pointer_element_type = wind::add_pointer<wind::add_const<element_type>::type>::type;
		using reference_element_type = wind::add_reference<element_type>::type;
		using const_reference_element_type = wind::add_reference<wind::add_const<element_type>::type>::type;

		json_array_t();
		explicit json_array_t(size_t n);
		json_array_t(size_t n, const element_type& val);
		template <class InputIterator> json_array_t(InputIterator first, InputIterator last) : m_data(vector_t(first, last)) {}
		json_array_t(const json_array_t& array);
		json_array_t(json_array_t& array);
		json_array_t(std::initializer_list<element_type> il);
		~json_array_t();

		auto operator = (const json_array_t& array)->json_array_t&;
		auto operator = (json_array_t& array)->json_array_t&;
		auto operator = (std::initializer_list<element_type> il)->json_array_t&;
		auto clear() noexcept -> void;
		auto size() const noexcept -> size_t;
		auto is_empty() const noexcept -> bool;
		auto at(size_t index) -> reference_element_type;
		auto at(size_t index) const->const_reference_element_type;
		auto operator [](size_t index)->reference_element_type;
		auto operator [](size_t index) const->const_reference_element_type;

		auto push_back(const element_type& val) -> void;
		auto pop_back() -> void;

		class iterator
		{
		private:
			iterator() = default;
		public:
			iterator(std::vector<element_type>::iterator it) : m_it(it) {}
			auto operator == (const iterator& it) const -> bool { return (this->m_it == it.m_it); }
			auto operator != (const iterator& it) const -> bool { return !operator == (it); }
			auto operator ++ () -> iterator& { ++this->m_it; return *this; }
			auto operator ++ (int32_t) -> iterator { iterator tmp = *this; ++(*this); return tmp; }
			auto operator * () -> reference_element_type { return (*this->m_it); }
			auto operator -> () -> pointer_element_type { return &(*this->m_it); }

			friend class json_array_t;
		private:
			std::vector<element_type>::iterator m_it;
		};

		class const_iterator
		{
		private:
			const_iterator() = default;
		public:
			const_iterator(std::vector<element_type>::const_iterator it) : m_it(it) {}
			auto operator == (const const_iterator& it) const -> bool { return (this->m_it == it.m_it); }
			auto operator != (const const_iterator& it) const -> bool { return !operator == (it); }
			auto operator ++ () -> const_iterator& { ++this->m_it; return *this; }
			auto operator ++ (int32_t) -> const_iterator { const_iterator tmp = *this; ++(*this); return tmp; }
			auto operator * () const -> const_reference_element_type { return (*this->m_it); }
			auto operator -> () -> const_pointer_element_type const { return &(*this->m_it); }

			friend class json_array_t;
		private:
			std::vector<element_type>::const_iterator m_it;
		};

		class reverse_iterator
		{
		private:
			reverse_iterator() = default;
		public:
			reverse_iterator(std::vector<element_type>::reverse_iterator it) : m_it(it) {}
			auto operator == (const reverse_iterator& it) const -> bool { return (this->m_it == it.m_it); }
			auto operator != (const reverse_iterator& it) const -> bool { return !operator == (it); }
			auto operator -- () -> reverse_iterator& { --this->m_it; return *this; }
			auto operator -- (int32_t) -> reverse_iterator { reverse_iterator tmp = *this; --(*this); return tmp; }
			auto operator * () -> reference_element_type { return (*this->m_it); }
			auto operator -> () -> pointer_element_type { return &(*this->m_it); }

			friend class json_array_t;
		private:
			std::vector<element_type>::reverse_iterator m_it;
		};

		class const_reverse_iterator
		{
		private:
			const_reverse_iterator() = default;
		public:
			const_reverse_iterator(std::vector<element_type>::const_reverse_iterator it) : m_it(it) {}
			auto operator == (const const_reverse_iterator& it) const -> bool { return (this->m_it == it.m_it); }
			auto operator != (const const_reverse_iterator& it) const -> bool { return !operator == (it); }
			auto operator -- () -> const_reverse_iterator& { ++this->m_it; return *this; }
			auto operator -- (int32_t) -> const_reverse_iterator { const_reverse_iterator tmp = *this; --(*this); return tmp; }
			auto operator * () const -> const_reference_element_type { return (*this->m_it); }
			auto operator -> () -> const_pointer_element_type const { return &(*this->m_it); }

			friend class json_array_t;
		private:
			std::vector<element_type>::const_reverse_iterator m_it;
		};

		auto insert(const_iterator position, const element_type& val) -> iterator;
		auto insert(const_iterator position, size_t n, const element_type& val) -> iterator;
		auto insert(const_iterator position, std::initializer_list<element_type> il) -> iterator;
		template <class InputIterator> auto insert(const_iterator position, InputIterator first, InputIterator last) -> iterator
		{
			return iterator(this->m_data.insert(position, first, last));
		}

		auto erase(const_iterator position) -> iterator;
		auto erase(const_iterator first, const_iterator last) -> iterator;

		template <class InputIterator>
		auto assign(InputIterator first, InputIterator last) -> void
		{
			this->m_data.assign(first, last);
		}

		auto assign(size_t n, const element_type& val) -> void;
		auto assign(std::initializer_list<element_type> il) -> void;

		auto begin() -> iterator;
		auto end() -> iterator;
		auto cbegin() const->const_iterator;
		auto cend() const->const_iterator;
		auto rbegin() -> reverse_iterator;
		auto rend() -> reverse_iterator;
		auto crbegin() const->const_reverse_iterator;
		auto crend() const->const_reverse_iterator;

	private:
		std::vector<element_type> m_data;
	};
}