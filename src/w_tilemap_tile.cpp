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

		tile_t::tile_t(const tile_t& tile) : m_tile(tile.m_tile) {}

		tile_t::tile_t(uint32_t tilesheet, uint32_t index) : m_tile({ 0 })
		{
			this->m_tile.m_tilesheet = tilesheet;
			this->m_tile.m_index = index;
			this->m_tile.m_reserved = 0;
		}

		tile_t::tile_t(uint32_t tile) : m_tile({ tile }) {}

		tile_t::~tile_t() {}

		auto tile_t::operator = (const tile_t& tile) -> tile_t&
		{
			this->m_tile = tile.m_tile;
			return*this;
		}

		auto tile_t::operator = (uint32_t tile) -> tile_t&
		{
			this->m_tile.m_data = tile;
			return*this;
		}

		auto tile_t::operator == (const tile_t& tile) -> bool
		{
			return this->m_tile.m_data == tile.m_tile.m_data;
		}

		auto tile_t::operator == (uint32_t tile) -> bool
		{
			return this->m_tile.m_data == tile;
		}

		auto tile_t::set_data(uint32_t tile) -> void
		{
			this->m_tile.m_data = tile;
		}

		auto tile_t::get_data() const -> uint32_t
		{
			return this->m_tile.m_data;
		}

		auto tile_t::set_tilesheet(uint32_t tilesheet) -> void
		{
			this->m_tile.m_tilesheet = tilesheet;
		}

		auto tile_t::get_tilesheet() const -> uint32_t
		{
			return this->m_tile.m_tilesheet;
		}

		auto tile_t::set_index(uint32_t index) -> void
		{
			this->m_tile.m_index = index;
		}

		auto tile_t::get_index() const -> uint32_t
		{
			return this->m_tile.m_index;
		}
	}
}