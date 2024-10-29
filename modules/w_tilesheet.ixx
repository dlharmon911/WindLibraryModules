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
		using value_t = ALLEGRO::BITMAP;
		using pointer_t = value_t*;
		using reference_t = value_t&;
		using const_pointer_t = const value_t*;
		using const_reference_t = const value_t&;

		tilesheet_t();
		tilesheet_t(const std::vector<ALLEGRO::BITMAP>& bitmaps, const ALLEGRO::SIZE<size_t>& tile_size);
		tilesheet_t(const tilesheet_t& tilesheet);
		~tilesheet_t();
		tilesheet_t& operator = (const tilesheet_t& tilesheet);
		void clear();
		size_t count() const;
		bool is_empty() const;
		const ALLEGRO::SIZE<size_t>& tile_size() const;
		reference_t at(size_t index);
		const_reference_t at(size_t index) const;
		reference_t operator [](size_t index);
		const_reference_t operator [](size_t index) const;

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
			reference_t operator ->() { return (*this->m_it); }

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
			const_reference_t operator ->() const { return (*this->m_it); }

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
			reference_t operator ->() { return (*this->m_it); }

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
			const_reference_t operator ->() const { return (*this->m_it); }

		private:
			std::vector<value_t>::const_reverse_iterator m_it;
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
		std::vector<value_t> m_bitmaps{};
		ALLEGRO::SIZE<size_t> m_tile_size{ 0, 0 };
	};
}
