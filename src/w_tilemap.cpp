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

	tilemap_t::tilemap_t(ALLEGRO::SIZE<int32_t> tilesize) : m_sheets(), m_tilesize(tilesize)
	{
	}

	tilemap_t::tilemap_t(const tilemap_t& tilemap) : m_sheets(tilemap.m_sheets), m_tilesize(tilemap.m_tilesize)
	{
	}

	tilemap_t::~tilemap_t()
	{
	}

	tilemap_t& tilemap_t::operator = (const tilemap_t& tilemap)
	{
		this->m_sheets = tilemap.m_sheets;
		return *this;
	}

	void* tilemap_t::data()
	{
		return this->m_sheets.data();
	}

	const void* tilemap_t::data() const
	{
		return this->m_sheets.data();
	}

	auto tilemap_t::push_back(reference_element_type tilemap) -> void
	{
		this->m_sheets.push_back(tilemap);
	}

	void tilemap_t::pop_back()
	{
		this->m_sheets.pop_back();
	}

	void tilemap_t::clear()
	{
		this->m_sheets.clear();
	}

	size_t tilemap_t::get_count() const
	{
		return this->m_sheets.size();
	}

	bool tilemap_t::is_empty() const
	{
		return this->m_sheets.empty();
	}

	const ALLEGRO::SIZE<int32_t>& tilemap_t::get_tile_size() const
	{
		return this->m_tilesize;
	}

	void tilemap_t::set_tile_size(ALLEGRO::SIZE<int32_t> tilesize)
	{
		this->m_tilesize = tilesize;
	}

	tilemap_t::reference_element_type tilemap_t::at(size_t index)
	{
		return this->m_sheets[index];
	}

	tilemap_t::const_reference_element_type tilemap_t::at(size_t index) const
	{
		return this->m_sheets[index];
	}

	tilemap_t::reference_element_type tilemap_t::operator [](size_t index)
	{
		return this->m_sheets[index];
	}

	tilemap_t::const_reference_element_type tilemap_t::operator [](size_t index) const
	{
		return this->m_sheets[index];
	}

	tilemap_t::iterator tilemap_t::begin()
	{
		return iterator(this->m_sheets.begin());
	}

	tilemap_t::iterator tilemap_t::end()
	{
		return iterator(this->m_sheets.end());
	}

	tilemap_t::const_iterator tilemap_t::cbegin()
	{
		return const_iterator(this->m_sheets.cbegin());
	}

	tilemap_t::const_iterator tilemap_t::cend()
	{
		return const_iterator(this->m_sheets.cend());
	}
}
