export module wind:tilesheet;

import <vector>;
import <cstdint>;
import <string>;
import allegro;
import :base;
import :file;
import :bitmap;
import :string;

namespace wind
{
	export class tilesheet_t
	{
	public:
		using element_type = ALLEGRO::BITMAP;
		using pointer_element_type = wind::add_pointer<element_type>::type;
		using const_pointer_element_type = wind::add_pointer<wind::add_const<element_type>::type>::type;
		using reference_element_type = wind::add_reference<element_type>::type;
		using const_reference_element_type = wind::add_reference<wind::add_const<element_type>::type>::type;

		tilesheet_t();
		tilesheet_t(const std::vector<ALLEGRO::BITMAP>& bitmaps, const ALLEGRO::SIZE<size_t>& tile_size);
		tilesheet_t(const tilesheet_t& tilesheet);
		~tilesheet_t();
		auto operator = (const tilesheet_t& tilesheet)->wind::add_reference_t<tilesheet_t>;
		auto clear() -> void;
		auto count() const->size_t;
		auto is_empty() const -> bool;
		auto tile_size() const->wind::add_reference_t <const ALLEGRO::SIZE<size_t>>;
		auto at(size_t index) -> reference_element_type;
		auto at(size_t index) const->const_reference_element_type;
		auto operator [](size_t index)->reference_element_type;
		auto operator [](size_t index) const->const_reference_element_type;

		class iterator
		{
		private:
			iterator() = default;
		public:
			iterator(std::vector<element_type>::iterator it) : m_it(it) {}
			auto operator == (const iterator& it) const -> bool { return (this->m_it == it.m_it); }
			auto operator != (const iterator& it) const -> bool { return !operator == (it); }
			auto operator ++() -> iterator& { ++this->m_it; return *this; }
			auto operator ++ (int32_t) -> iterator { iterator tmp = *this; ++(*this); return tmp; }
			auto operator * () -> reference_element_type { return (*this->m_it); }
			auto operator -> () -> pointer_element_type { return &(*this->m_it); }

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
			auto operator ++() -> const_iterator& { ++this->m_it; return *this; }
			auto operator ++ (int32_t) -> const_iterator { const_iterator tmp = *this; ++(*this); return tmp; }
			auto operator * () -> const_reference_element_type { return (*this->m_it); }
			auto operator -> () -> const_pointer_element_type { return &(*this->m_it); }

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
			auto operator --() -> reverse_iterator& { --this->m_it; return *this; }
			auto operator -- (int32_t) -> reverse_iterator { reverse_iterator tmp = *this; --(*this); return tmp; }
			auto operator * () -> const_reference_element_type { return (*this->m_it); }
			auto operator -> () -> const_pointer_element_type { return &(*this->m_it); }

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
			auto operator --() -> const_reverse_iterator& { --this->m_it; return *this; }
			auto operator -- (int32_t) -> const_reverse_iterator { const_reverse_iterator tmp = *this; --(*this); return tmp; }
			auto operator * () -> const_reference_element_type { return (*this->m_it); }
			auto operator -> () -> const_pointer_element_type { return &(*this->m_it); }

		private:
			std::vector<element_type>::const_reverse_iterator m_it;
		};

		auto begin() -> iterator;
		auto end() -> iterator;
		auto cbegin() const->const_iterator;
		auto cend() const->const_iterator;
		auto rbegin() -> reverse_iterator;
		auto rend() -> reverse_iterator;
		auto crbegin() const->const_reverse_iterator;
		auto crend() const->const_reverse_iterator;

	private:
		std::vector<element_type> m_bitmaps{};
		ALLEGRO::SIZE<size_t> m_tile_size{ 0, 0 };
	};
}