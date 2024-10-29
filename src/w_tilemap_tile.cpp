module wind;

import <string>;
import <cstdint>;
import allegro;
import :tilemap;
import :base;

namespace wind
{
	namespace tilemap
	{
		tile_t::tile_t() : m_tile({ 0 }) {}

		tile_t::tile_t(const tile_t & tile) : m_tile(tile.m_tile) {}

		tile_t::tile_t(uint32_t tilesheet, uint32_t index) : m_tile({ 0 })
		{
			this->m_tile.m_tilesheet = tilesheet;
			this->m_tile.m_index = index;
			this->m_tile.m_reserved = 0;
		}

		tile_t::tile_t(uint32_t tile) : m_tile({ tile }) {}

		tile_t::~tile_t() {}

		tile_t& tile_t::operator = (const tile_t & tile)
		{
			this->m_tile = tile.m_tile;
			return*this;
		}

		tile_t& tile_t::operator = (uint32_t tile)
		{
			this->m_tile.m_data = tile;
			return*this;
		}

		bool tile_t::operator == (const tile_t & tile)
		{
			return this->m_tile.m_data == tile.m_tile.m_data;
		}

		bool tile_t::operator == (uint32_t tile)
		{
			return this->m_tile.m_data == tile;
		}

		bool tile_t::operator != (const tile_t & tile)
		{
			return !(this->operator == (tile));
		}

		bool tile_t::operator != (uint32_t tile)
		{
			return !(this->operator == (tile));
		}

		void tile_t::set_data(uint32_t tile)
		{
			this->m_tile.m_data = tile;
		}

		uint32_t tile_t::get_data() const
		{
			return this->m_tile.m_data;
		}

		void tile_t::set_tilesheet(uint32_t tilesheet)
		{
			this->m_tile.m_tilesheet = tilesheet;
		}

		uint32_t tile_t::get_tilesheet() const
		{
			return this->m_tile.m_tilesheet;
		}

		void tile_t::set_index(uint32_t index)
		{
			this->m_tile.m_index = index;
		}

		uint32_t tile_t::get_index() const
		{
			return this->m_tile.m_index;
		}
	}
}
