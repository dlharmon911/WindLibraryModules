export module wind:json.object;

import std;
import allegro;
import :hex;
import :file;
import :base;
import :string;

namespace WIND
{
	namespace JSON
	{
		export enum class TYPE : int32_t
		{
			EMPTY,
			BOOLEAN,
			NUMBER,
			STRING,
			OBJECT,
			ARRAY
		};
	}
}

namespace wind
{
	export class json_object_t;
	export class json_array_t;

	export class json_t
	{
	public:
		json_t();
		json_t(const json_t& value);
		template <typename T> explicit json_t(const T& value) = delete;
		template <> explicit json_t(const bool& value);
		template <> explicit json_t(const string_t& value);
		template <> explicit json_t(const int8_t& value);
		template <> explicit json_t(const int16_t& value);
		template <> explicit json_t(const int32_t& value);
		template <> explicit json_t(const int64_t& value);
		template <> explicit json_t(const uint8_t& value);
		template <> explicit json_t(const uint16_t& value);
		template <> explicit json_t(const uint32_t& value);
		template <> explicit json_t(const uint64_t& value);
		template <> explicit json_t(const float& value);
		template <> explicit json_t(const double& value);
		template <> explicit json_t(const json_object_t& value);
		template <> explicit json_t(const json_array_t& value);
		~json_t();

		auto operator = (const json_t& json)->json_t&;

		auto is_defined() const -> bool;

		auto clear() -> void;

		auto get_type() const->WIND::JSON::TYPE;

		template <typename T> auto set_as(const T& value) -> bool = delete;
		template <> auto set_as(const bool& value) -> bool;
		template <> auto set_as(const string_t& value) -> bool;
		template <> auto set_as(const int8_t& value) -> bool;
		template <> auto set_as(const int16_t& value) -> bool;
		template <> auto set_as(const int32_t& value) -> bool;
		template <> auto set_as(const int64_t& value) -> bool;
		template <> auto set_as(const uint8_t& value) -> bool;
		template <> auto set_as(const uint16_t& value) -> bool;
		template <> auto set_as(const uint32_t& value) -> bool;
		template <> auto set_as(const uint64_t& value) -> bool;
		template <> auto set_as(const float& value) -> bool;
		template <> auto set_as(const double& value) -> bool;
		template <> auto set_as(const json_object_t& value) -> bool;
		template <> auto set_as(const json_array_t& value) -> bool;

		template <typename T> auto get_as() const -> T = delete;
		template <> auto get_as<bool>() const -> bool;
		template <> auto get_as<int8_t>() const -> int8_t;
		template <> auto get_as<int16_t>() const -> int16_t;
		template <> auto get_as<int32_t>() const -> int32_t;
		template <> auto get_as<int64_t>() const -> int64_t;
		template <> auto get_as<uint8_t>() const -> uint8_t;
		template <> auto get_as<uint16_t>() const -> uint16_t;
		template <> auto get_as<uint32_t>() const -> uint32_t;
		template <> auto get_as<uint64_t>() const -> uint64_t;
		template <> auto get_as<float>() const -> float;
		template <> auto get_as<double>() const -> double;
		template <> auto get_as<string_t>() const -> string_t;
		template <> auto get_as<json_object_t>() const -> json_object_t;
		template <> auto get_as<json_array_t>() const -> json_array_t;

		template <typename T> auto get_as() -> T& = delete;
		template <> auto get_as<json_object_t&>() -> json_object_t&;
		template <> auto get_as<json_array_t&>() -> json_array_t&;


		auto get_data() -> std::shared_ptr<void>&;
		auto get_data() const -> const std::shared_ptr<void>&;

	private:
		WIND::JSON::TYPE m_type{ WIND::JSON::TYPE::EMPTY };
		std::shared_ptr<void> m_data{};
	};

	using json_key_t = string_t;

	export using json_pair_t = std::pair<json_key_t, json_t>;

	export class json_object_t
	{
	private:
		using array_t = std::map<json_key_t, json_t>;
		using allocator_t = array_t::allocator_type;

	public:
		using element_type = json_t;
		using pointer_element_type = wind::add_pointer<element_type>::type;
		using const_pointer_element_type = wind::add_pointer<wind::add_const<element_type>::type>::type;
		using reference_element_type = wind::add_reference<element_type>::type;
		using const_reference_element_type = wind::add_reference<wind::add_const<element_type>::type>::type;

		json_object_t();
		json_object_t(const json_t& json);
		json_object_t(const json_object_t& object);
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
			explicit iterator(array_t::iterator it) : m_it(it) {}
			auto key() -> const json_key_t& { return this->m_it->first; }
			auto operator == (const iterator& it) const -> bool { return (this->m_it == it.m_it); }
			auto operator != (const iterator& it) const -> bool { return !operator == (it); }
			auto operator ++ () -> iterator& { ++this->m_it; return *this; }
			auto operator ++ (int32_t) -> iterator { iterator tmp = *this; ++(*this); return tmp; }
			auto operator * () -> reference_element_type { return this->m_it->second; }
			auto operator -> () -> pointer_element_type { return &this->m_it->second; }

			friend class json_object_t;
		private:
			array_t::iterator m_it;
		};

		class const_iterator
		{
		private:
			const_iterator() = default;
		public:
			explicit const_iterator(array_t::const_iterator it) : m_it(it) {}

			auto key() const -> const json_key_t& { return this->m_it->first; }
			auto operator == (const const_iterator& it) const -> bool { return (this->m_it == it.m_it); }
			auto operator != (const const_iterator& it) const -> bool { return !operator == (it); }
			auto operator ++ () -> const_iterator& { ++this->m_it; return *this; }
			auto operator ++ (int32_t) -> const_iterator { const_iterator tmp = *this; ++(*this); return tmp; }
			auto operator * () const -> const_reference_element_type { return this->m_it->second; }
			auto operator -> () const -> const_pointer_element_type { return &this->m_it->second; }

			friend class json_object_t;
		private:
			array_t::const_iterator m_it;
		};

		auto find(const json_key_t& key) -> iterator;
		auto find(const json_key_t& key) const->const_iterator;

		auto begin() -> iterator;
		auto end() -> iterator;
		auto cbegin() const->const_iterator;
		auto cend() const->const_iterator;

	private:

		array_t m_data;
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
		json_array_t(const json_t& json);
		explicit json_array_t(size_t n);
		json_array_t(size_t n, const element_type& val);
		template <class InputIterator> json_array_t(InputIterator first, InputIterator last) : m_data(array_t(first, last)) {}
		json_array_t(const json_array_t& array);
		explicit json_array_t(std::initializer_list<element_type> il);
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
			explicit iterator(std::vector<element_type>::iterator it) : m_it(it) {}
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
			explicit const_iterator(std::vector<element_type>::const_iterator it) : m_it(it) {}
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

	private:
		std::vector<element_type> m_data;
	};
}
