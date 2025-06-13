module wind;

import <string>;
import <cstdint>;
import allegro;
import :tilemap;
import :base;
import :bitmap;

namespace wind
{
	tilemap_t::tilemap_t() : m_sheets(), m_tilesize()
	{
	}

	tilemap_t::tilemap_t(ALLEGRO::VECTOR_2D<int32_t> tilesize) : m_sheets(), m_tilesize(tilesize)
	{
	}

	tilemap_t::tilemap_t(const tilemap_t& tilemap) : m_sheets(tilemap.m_sheets), m_tilesize(tilemap.m_tilesize)
	{
	}

	tilemap_t::~tilemap_t()
	{
	}

	auto tilemap_t::operator = (const tilemap_t& tilemap) -> tilemap_t&
	{
		this->m_sheets = tilemap.m_sheets;
		return *this;
	}

	auto tilemap_t::data() -> void*
	{
		return this->m_sheets.data();
	}

	auto tilemap_t::data() const -> const void*
	{
		return this->m_sheets.data();
	}

	auto tilemap_t::push_back(reference_element_type tilemap) -> void
	{
		this->m_sheets.push_back(tilemap);
	}

	auto tilemap_t::pop_back() -> void
	{
		this->m_sheets.pop_back();
	}

	auto tilemap_t::clear() -> void
	{
		this->m_sheets.clear();
	}

	auto tilemap_t::size() const -> size_t
	{
		return this->m_sheets.size();
	}

	auto tilemap_t::is_empty() const -> bool
	{
		return this->m_sheets.empty();
	}

	auto tilemap_t::get_tile_size() const -> const ALLEGRO::VECTOR_2D<int32_t>&
	{
		return this->m_tilesize;
	}

	auto tilemap_t::set_tile_size(ALLEGRO::VECTOR_2D<int32_t> tilesize) -> void
	{
		this->m_tilesize = tilesize;
	}

	auto tilemap_t::at(size_t index) -> tilemap_t::reference_element_type
	{
		return this->m_sheets[index];
	}

	auto tilemap_t::at(size_t index) const -> tilemap_t::const_reference_element_type
	{
		return this->m_sheets[index];
	}

	auto tilemap_t::operator [](size_t index) -> tilemap_t::reference_element_type
	{
		return this->m_sheets[index];
	}

	auto tilemap_t::operator [](size_t index) const -> tilemap_t::const_reference_element_type
	{
		return this->m_sheets[index];
	}

	auto tilemap_t::begin() -> tilemap_t::iterator
	{
		return iterator(this->m_sheets.begin());
	}

	auto tilemap_t::end() -> tilemap_t::iterator
	{
		return iterator(this->m_sheets.end());
	}

	auto tilemap_t::cbegin() const -> tilemap_t::const_iterator
	{
		return const_iterator(this->m_sheets.cbegin());
	}

	auto tilemap_t::cend() const -> tilemap_t::const_iterator
	{
		return const_iterator(this->m_sheets.cend());
	}
}
