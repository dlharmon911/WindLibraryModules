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
	export class tilesheet_t : public class_t<tilesheet_t>
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
		auto operator = (const tilesheet_t& tilesheet) -> reference_type;
		void clear();
		size_t count() const;
		bool is_empty() const;
		const ALLEGRO::SIZE<size_t>& tile_size() const;
		reference_element_type at(size_t index);
		const_reference_element_type at(size_t index) const;
		reference_element_type operator [](size_t index);
		const_reference_element_type operator [](size_t index) const;

		class iterator
		{
		private:
			iterator() = default;
		public:
			typedef std::ptrdiff_t difference_type;

			iterator(std::vector<element_type>::iterator it) : m_it(it) {}
			bool operator == (const iterator& it) const { return (this->m_it == it.m_it); }
			bool operator != (const iterator& it) const { return !operator == (it); }
			iterator& operator ++() { ++this->m_it; return *this; }
			iterator operator ++(int32_t) { iterator tmp = *this; ++(*this); return tmp; }
			reference_element_type operator *() { return (*this->m_it); }
			reference_element_type operator ->() { return (*this->m_it); }

		private:
			std::vector<element_type>::iterator m_it;
		};

		class const_iterator
		{
		private:
			const_iterator() = default;
		public:
			typedef std::ptrdiff_t difference_type;

			const_iterator(std::vector<element_type>::const_iterator it) : m_it(it) {}
			bool operator == (const const_iterator& it) const { return (this->m_it == it.m_it); }
			bool operator != (const const_iterator& it) const { return !operator == (it); }
			const_iterator& operator ++() { ++this->m_it; return *this; }
			const_iterator operator ++(int32_t) { const_iterator tmp = *this; ++(*this); return tmp; }
			const_reference_element_type operator *() const { return (*this->m_it); }
			const_reference_element_type operator ->() const { return (*this->m_it); }

		private:
			std::vector<element_type>::const_iterator m_it;
		};

		class reverse_iterator
		{
		private:
			reverse_iterator() = default;
		public:
			typedef std::ptrdiff_t difference_type;

			reverse_iterator(std::vector<element_type>::reverse_iterator it) : m_it(it) {}
			bool operator == (const reverse_iterator& it) const { return (this->m_it == it.m_it); }
			bool operator != (const reverse_iterator& it) const { return !operator == (it); }
			reverse_iterator& operator --() { --this->m_it; return *this; }
			reverse_iterator operator --(int32_t) { reverse_iterator tmp = *this; --(*this); return tmp; }
			reference_element_type operator *() { return (*this->m_it); }
			reference_element_type operator ->() { return (*this->m_it); }

		private:
			std::vector<element_type>::reverse_iterator m_it;
		};

		class const_reverse_iterator
		{
		private:
			const_reverse_iterator() = default;
		public:
			typedef std::ptrdiff_t difference_type;

			const_reverse_iterator(std::vector<element_type>::const_reverse_iterator it) : m_it(it) {}
			bool operator == (const const_reverse_iterator& it) const { return (this->m_it == it.m_it); }
			bool operator != (const const_reverse_iterator& it) const { return !operator == (it); }
			const_reverse_iterator& operator --() { --this->m_it; return *this; }
			const_reverse_iterator operator --(int32_t) { const_reverse_iterator tmp = *this; --(*this); return tmp; }
			const_reference_element_type operator *() const { return (*this->m_it); }
			const_reference_element_type operator ->() const { return (*this->m_it); }

		private:
			std::vector<element_type>::const_reverse_iterator m_it;
		};

		iterator begin();
		iterator end();
		const_iterator cbegin();
		const_iterator cend();
		reverse_iterator rbegin();
		reverse_iterator rend();
		const_reverse_iterator crbegin();
		const_reverse_iterator crend();

	private:
		std::vector<element_type> m_bitmaps{};
		ALLEGRO::SIZE<size_t> m_tile_size{ 0, 0 };
	};
}
