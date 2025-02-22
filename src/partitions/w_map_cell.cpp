module wind;

import <cstdint>;
import :base;
import :error;
import :map;

namespace wind
{
	namespace map
	{
		cell_t::cell_t() : m_data() {}

		cell_t::cell_t(const cell_t& cell) : m_data(cell.m_data) {}

		cell_t::~cell_t() {}

		auto cell_t::operator = (const cell_t& cell) -> cell_t&
		{
			this->m_data = cell.m_data;

			return *this;
		}

		auto cell_t::at(WIND::MAP::CELL::LAYER layer) -> cell_t::reference_element_type
		{
			ALLEGRO::ASSERT(layer < WIND::MAP::CELL::LAYER::COUNT);

			return this->m_data[std::to_underlying(layer)];
		}

		auto cell_t::at(WIND::MAP::CELL::LAYER layer) const -> cell_t::const_reference_element_type
		{
			ALLEGRO::ASSERT(layer < WIND::MAP::CELL::LAYER::COUNT);

			return this->m_data[std::to_underlying(layer)];
		}

		auto cell_t::operator [](WIND::MAP::CELL::LAYER layer) -> cell_t::reference_element_type
		{
			ALLEGRO::ASSERT(layer < WIND::MAP::CELL::LAYER::COUNT);

			return this->m_data[std::to_underlying(layer)];
		}

		auto cell_t::operator [](WIND::MAP::CELL::LAYER layer) const -> cell_t::const_reference_element_type
		{
			ALLEGRO::ASSERT(layer < WIND::MAP::CELL::LAYER::COUNT);

			return this->m_data[std::to_underlying(layer)];
		}

		auto cell_t::begin() -> cell_t::iterator
		{
			return iterator(this->m_data.begin());
		}

		auto cell_t::end() -> cell_t::iterator
		{
			return iterator(this->m_data.end());
		}

		auto cell_t::cbegin() -> cell_t::const_iterator
		{
			return const_iterator(this->m_data.cbegin());
		}

		auto cell_t::cend() -> cell_t::const_iterator
		{
			return const_iterator(this->m_data.cend());
		}
	}
}
