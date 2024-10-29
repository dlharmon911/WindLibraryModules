export module wind:tilemap;

import <vector>;
import <cstdint>;
import <memory>;
import allegro;
import :base;
import :tilesheet;

namespace wind
{
	export class tilemap_t
	{
	public:
		using value_type = tilesheet_t;
		using pointer_type = value_type*;
		using const_pointer_type = const value_type*;
		using reference_type = value_type&;
		using const_reference_type = const value_type&;

	private:
		using vector_type = std::vector<value_type>;

	public:
		tilemap_t();
		tilemap_t(ALLEGRO::SIZE<int32_t> tilesize);
		tilemap_t(const tilemap_t& tilemap);
		~tilemap_t();
		tilemap_t& operator = (const tilemap_t& tilemap);

		void* data();
		const void* data() const;

		void clear();

		size_t get_count() const;
		bool is_empty() const;

		void push_back(reference_type tilemap);
		void pop_back();

		const ALLEGRO::SIZE<int32_t>& get_tile_size() const;
		void set_tile_size(ALLEGRO::SIZE<int32_t> tilesize);

		reference_type at(size_t index);
		const_reference_type at(size_t index) const;
		reference_type operator [](size_t index);
		const_reference_type operator [](size_t index) const;

		class iterator
		{
		private:
			iterator() = default;
		public:
			typedef std::ptrdiff_t difference_type;

			iterator(vector_type::iterator it) : m_it(it) {}
			bool operator == (const iterator& it) const { return (this->m_it == it.m_it); }
			bool operator != (const iterator& it) const { return !operator == (it); }
			iterator& operator ++() { ++this->m_it; return *this; }
			iterator operator ++(int) { iterator tmp = *this; ++(*this); return tmp; }
			reference_type operator *() { return (*this->m_it); }
			pointer_type operator ->() { return &(*this->m_it); }

		private:
			vector_type::iterator m_it;
		};

		class const_iterator
		{
		private:
			const_iterator() = default;
		public:
			typedef std::ptrdiff_t difference_type;

			const_iterator(const vector_type::const_iterator it) : m_it(it) {}
			bool operator == (const const_iterator& it) const { return (this->m_it == it.m_it); }
			bool operator != (const const_iterator& it) const { return !operator == (it); }
			const_iterator& operator ++() { ++this->m_it; return *this; }
			const_iterator operator ++(int) { const_iterator tmp = *this; ++(*this); return tmp; }
			const_reference_type operator *() const { return (*this->m_it); }
			const_pointer_type operator ->() const { return &(*this->m_it); }

		private:
			vector_type::const_iterator m_it;
		};

		iterator begin();
		iterator end();
		const_iterator cbegin();
		const_iterator cend();

	private:
		vector_type m_sheets;
		ALLEGRO::SIZE<int32_t> m_tilesize;
	};

	namespace tilemap
	{
		export class tile_t
		{
		public:
			tile_t();
			tile_t(const tile_t& tile);
			tile_t(uint32_t tilesheet, uint32_t index);
			tile_t(uint32_t tile);
			~tile_t();
			tile_t& operator = (const tile_t& tile);
			tile_t& operator = (uint32_t tile);
			bool operator == (const tile_t& tile);
			bool operator == (uint32_t tile);
			bool operator != (const tile_t& tile);
			bool operator != (uint32_t tile);
			void set_data(uint32_t tile);
			uint32_t get_data() const;
			void set_tilesheet(uint32_t tilesheet);
			uint32_t get_tilesheet() const;
			void set_index(uint32_t index);
			uint32_t get_index() const;

		private:
			union _tile
			{
				uint32_t m_data{ 0 };
				struct
				{
					uint32_t m_tilesheet : 6;
					uint32_t m_index : 10;
					uint32_t m_reserved : 16;
				};
			} m_tile;
		};
	}
}
