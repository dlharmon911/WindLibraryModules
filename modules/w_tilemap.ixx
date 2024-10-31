export module wind:tilemap;

import <vector>;
import <cstdint>;
import <memory>;
import allegro;
import :base;
import :tilesheet;

namespace wind
{
	export class tilemap_t : public class_t<tilemap_t>
	{
	public:
		using element_type = tilesheet_t;
		using pointer_element_type = wind::add_pointer<element_type>::type;
		using const_pointer_element_type = wind::add_pointer<wind::add_const<element_type>::type>::type;
		using reference_element_type = wind::add_reference<element_type>::type;
		using const_reference_element_type = wind::add_reference<wind::add_const<element_type>::type>::type;

	private:
		using vector_type = std::vector<element_type>;

	public:
		tilemap_t();
		tilemap_t(ALLEGRO::SIZE<int32_t> tilesize);
		tilemap_t(const tilemap_t& tilemap);
		~tilemap_t();
		auto operator = (const tilemap_t& tilemap) ->tilemap_t&;

		auto data() -> void*;
		auto data() const -> const void*;

		auto clear() -> void;

		auto get_count() const ->size_t;
		auto is_empty() const -> bool;

		auto push_back(reference_element_type tilemap) -> void;
		auto pop_back() -> void;

		auto get_tile_size() const -> const ALLEGRO::SIZE<int32_t>&;
		auto set_tile_size(ALLEGRO::SIZE<int32_t> tilesize) -> void;

		auto at(size_t index) -> reference_element_type;
		auto at(size_t index) const ->const_reference_element_type;
		auto operator [](size_t index)->reference_element_type;
		auto operator [](size_t index) const ->const_reference_element_type;

		class iterator
		{
		private:
			iterator() = default;
		public:
			iterator(vector_type::iterator it) : m_it(it) {}
			auto operator == (const iterator& it) const -> bool { return (this->m_it == it.m_it); }
			auto operator != (const iterator& it) const -> bool { return !operator == (it); }
			auto operator ++() -> iterator& { ++this->m_it; return *this; }
			auto operator ++(int32_t) -> iterator { iterator tmp = *this; ++(*this); return tmp; }
			auto operator *() -> reference_element_type { return (*this->m_it); }
			auto operator ->() -> pointer_element_type { return &(*this->m_it); }

		private:
			vector_type::iterator m_it;
		};

		class const_iterator
		{
		private:
			const_iterator() = default;
		public:
			const_iterator(const vector_type::const_iterator it) : m_it(it) {}
			auto operator == (const const_iterator& it) const -> bool { return (this->m_it == it.m_it); }
			auto operator != (const const_iterator& it) const -> bool { return !operator == (it); }
			auto operator ++() -> const_iterator& { ++this->m_it; return *this; }
			auto operator ++(int32_t) -> const_iterator { const_iterator tmp = *this; ++(*this); return tmp; }
			auto operator *() const -> const_reference_element_type { return (*this->m_it); }
			auto operator ->() const -> const_pointer_element_type { return &(*this->m_it); }

		private:
			vector_type::const_iterator m_it;
		};

		auto begin()-> iterator;
		auto end()-> iterator;
		auto cbegin()->const_iterator;
		auto cend()->const_iterator;

	private:
		vector_type m_sheets;
		ALLEGRO::SIZE<int32_t> m_tilesize;
	};

	namespace tilemap
	{
		export class tile_t : public class_t<tile_t>
		{
		public:
			tile_t();
			tile_t(const tile_t& tile);
			tile_t(uint32_t tilesheet, uint32_t index);
			tile_t(uint32_t tile);
			~tile_t();
			auto operator = (const tile_t& tile)->tile_t&;
			auto operator = (uint32_t tile) -> tile_t&;
			auto operator == (const tile_t& tile) -> bool;
			auto operator == (uint32_t tile) -> bool;
			auto operator != (const tile_t& tile) -> bool;
			auto operator != (uint32_t tile) -> bool;
			auto set_data(uint32_t tile) -> void;
			auto get_data() const->uint32_t;
			auto set_tilesheet(uint32_t tilesheet) -> void;
			auto get_tilesheet() const->uint32_t;
			auto set_index(uint32_t index) -> void;
			auto get_index() const -> uint32_t;

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
