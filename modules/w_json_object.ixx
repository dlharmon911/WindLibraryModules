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
		json_t& operator = (const json_t& json);

		bool is_defined() const;

		void clear();

		int32_t type() const;

		bool set_as_boolean(bool val);
		bool set_as_number(double val);
		bool set_as_string(const string_t& val);
		bool set_as_object(const json_object_t& val);
		bool set_as_array(const json_array_t& val);

		bool get_as_boolean() const;
		double get_as_number() const;
		string_t get_as_string();
		const string_t get_as_string() const;
		json_object_t& get_as_object();
		const json_object_t& get_as_object() const;
		json_array_t& get_as_array();
		const json_array_t& get_as_array() const;

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
	public:
		using value_t = json_t;

	private:
		using vector_t = std::unordered_map<json_key_t, json_t>;
		using allocator_t = vector_t::allocator_type;

	public:
		using pointer_t = value_t*;
		using reference_t = value_t&;
		using const_pointer_t = const value_t*;
		using const_reference_t = const value_t&;

		json_object_t();
		json_object_t(const json_object_t& object);
		json_object_t(json_object_t& object);
		~json_object_t();
		json_object_t& operator = (const json_object_t& object);
		json_object_t& operator = (json_object_t& object);
		void clear() noexcept;
		size_t size() const noexcept;
		bool is_empty() const noexcept;

		reference_t at(const json_key_t& key);
		const_reference_t at(const json_key_t& key) const;
		reference_t operator [](const json_key_t& key);

		void add(const json_key_t& key, const value_t& val);
		void add(const json_pair_t& pair);
		void remove(const json_key_t& key);

		class iterator
		{
		private:
			iterator() = default;
		public:
			typedef std::ptrdiff_t difference_type;
			const json_key_t& key() { return this->m_it->first; }
			iterator(vector_t::iterator it) : m_it(it) {}
			bool operator == (const iterator& it) const { return (this->m_it == it.m_it); }
			bool operator != (const iterator& it) const { return !operator == (it); }
			iterator& operator ++() { ++this->m_it; return *this; }
			iterator operator ++(int) { iterator tmp = *this; ++(*this); return tmp; }
			reference_t operator *() { return this->m_it->second; }
			pointer_t operator ->() { return &this->m_it->second; }

			friend class json_object_t;
		private:
			vector_t::iterator m_it;
		};

		class const_iterator
		{
		private:
			const_iterator() = default;
		public:
			typedef std::ptrdiff_t difference_type;
			const json_key_t& key() { return this->m_it->first; }
			const_iterator(vector_t::const_iterator it) : m_it(it) {}
			bool operator == (const const_iterator& it) const { return (this->m_it == it.m_it); }
			bool operator != (const const_iterator& it) const { return !operator == (it); }
			const_iterator& operator ++() { ++this->m_it; return *this; }
			const_iterator operator ++(int) { const_iterator tmp = *this; ++(*this); return tmp; }
			const_reference_t operator *() const { return this->m_it->second; }
			const_pointer_t operator ->() const {return  &this->m_it->second; }

			friend class json_object_t;
		private:
			vector_t::const_iterator m_it;
		};

		iterator find(const json_key_t& key);
		const_iterator find(const json_key_t& key) const;

		iterator begin();
		iterator end();
		const_iterator cbegin() const;
		const_iterator cend() const;

	private:

		vector_t m_data;
	};

	/****************************************************************************************************/

	export class json_array_t
	{
	public:
		using value_t = json_t;
		using pointer_t = value_t*;
		using reference_t = value_t&;
		using const_pointer_t = const value_t*;
		using const_reference_t = const value_t&;

		json_array_t();
		explicit json_array_t(size_t n);
		json_array_t(size_t n, const value_t& val);
		template <class InputIterator> json_array_t(InputIterator first, InputIterator last) : m_data(vector_t(first, last)) {}
		json_array_t(const json_array_t& array);
		json_array_t(json_array_t& array);
		json_array_t(std::initializer_list<value_t> il);
		~json_array_t();
		json_array_t& operator = (const json_array_t& array);
		json_array_t& operator = (json_array_t& array);
		json_array_t& operator = (std::initializer_list<value_t> il);
		void clear() noexcept;
		size_t size() const noexcept;
		bool is_empty() const noexcept;
		reference_t at(size_t index);
		const_reference_t at(size_t index) const;
		reference_t operator [](size_t index);
		const_reference_t operator [](size_t index) const;

		void push_back(const value_t& val);
		void pop_back();

		class iterator
		{
		private:
			iterator() = default;
		public:
			typedef std::ptrdiff_t difference_type;

			iterator(std::vector<value_t>::iterator it) : m_it(it) {}
			bool operator == (const iterator& it) const { return (this->m_it == it.m_it); }
			bool operator != (const iterator& it) const { return !operator == (it); }
			iterator& operator ++() { ++this->m_it; return *this; }
			iterator operator ++(int) { iterator tmp = *this; ++(*this); return tmp; }
			reference_t operator *() { return (*this->m_it); }
			pointer_t operator ->() { return &(*this->m_it); }

			friend class json_array_t;
		private:
			std::vector<value_t>::iterator m_it;
		};

		class const_iterator
		{
		private:
			const_iterator() = default;
		public:
			typedef std::ptrdiff_t difference_type;

			const_iterator(std::vector<value_t>::const_iterator it) : m_it(it) {}
			bool operator == (const const_iterator& it) const { return (this->m_it == it.m_it); }
			bool operator != (const const_iterator& it) const { return !operator == (it); }
			const_iterator& operator ++() { ++this->m_it; return *this; }
			const_iterator operator ++(int) { const_iterator tmp = *this; ++(*this); return tmp; }
			const_reference_t operator *() const { return (*this->m_it); }
			const_pointer_t operator ->() const { return &(*this->m_it); }

			friend class json_array_t;
		private:
			std::vector<value_t>::const_iterator m_it;
		};

		class reverse_iterator
		{
		private:
			reverse_iterator() = default;
		public:
			typedef std::ptrdiff_t difference_type;

			reverse_iterator(std::vector<value_t>::reverse_iterator it) : m_it(it) {}
			bool operator == (const reverse_iterator& it) const { return (this->m_it == it.m_it); }
			bool operator != (const reverse_iterator& it) const { return !operator == (it); }
			reverse_iterator& operator --() { --this->m_it; return *this; }
			reverse_iterator operator --(int) { reverse_iterator tmp = *this; --(*this); return tmp; }
			reference_t operator *() { return (*this->m_it); }
			pointer_t operator ->() { return &(*this->m_it); }

			friend class json_array_t;
		private:
			std::vector<value_t>::reverse_iterator m_it;
		};

		class const_reverse_iterator
		{
		private:
			const_reverse_iterator() = default;
		public:
			typedef std::ptrdiff_t difference_type;

			const_reverse_iterator(std::vector<value_t>::const_reverse_iterator it) : m_it(it) {}
			bool operator == (const const_reverse_iterator& it) const { return (this->m_it == it.m_it); }
			bool operator != (const const_reverse_iterator& it) const { return !operator == (it); }
			const_reverse_iterator& operator --() { --this->m_it; return *this; }
			const_reverse_iterator operator --(int) { const_reverse_iterator tmp = *this; --(*this); return tmp; }
			const_reference_t operator *() const { return (*this->m_it); }
			const_pointer_t operator ->() const { return &(*this->m_it); }

			friend class json_array_t;
		private:
			std::vector<value_t>::const_reverse_iterator m_it;
		};

		iterator insert(const_iterator position, const value_t& val);
		iterator insert(const_iterator position, size_t n, const value_t& val);
		iterator insert(const_iterator position, std::initializer_list<value_t> il);
		template <class InputIterator> iterator insert(const_iterator position, InputIterator first, InputIterator last)
		{
			return iterator(this->m_data.insert(position, first, last));
		}

		iterator erase(const_iterator position);
		iterator erase(const_iterator first, const_iterator last);

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			this->m_data.assign(first, last);
		}

		void assign(size_t n, const value_t& val);
		void assign(std::initializer_list<value_t> il);

		iterator begin();
		iterator end();
		const_iterator cbegin() const;
		const_iterator cend() const;
		reverse_iterator rbegin();
		reverse_iterator rend();
		const_reverse_iterator crbegin() const;
		const_reverse_iterator crend() const;

	private:
		std::vector<value_t> m_data;
	};
}
