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

		auto cell_t::at(size_t index) -> cell_t::reference_element_type
		{
			ALLEGRO::ASSERT(index < WIND::MAP::CELL::LAYER_COUNT);

			return this->m_data[index];
		}

		auto cell_t::at(size_t index) const -> cell_t::const_reference_element_type
		{
			ALLEGRO::ASSERT(index < WIND::MAP::CELL::LAYER_COUNT);

			return this->m_data[index];
		}

		auto cell_t::operator [](size_t index) -> cell_t::reference_element_type
		{
			ALLEGRO::ASSERT(index < WIND::MAP::CELL::LAYER_COUNT);

			return this->m_data[index];
		}

		auto cell_t::operator [](size_t index) const -> cell_t::const_reference_element_type
		{
			ALLEGRO::ASSERT(index < WIND::MAP::CELL::LAYER_COUNT);

			return this->m_data[index];
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