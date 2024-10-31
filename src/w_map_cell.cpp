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

		cell_t& cell_t::operator = (const cell_t& cell)
		{
			this->m_data = cell.m_data;

			return *this;
		}

		cell_t::reference_element_type cell_t::at(size_t index)
		{
			ALLEGRO::ASSERT(index < WIND::MAP::CELL::LAYER_COUNT);

			return this->m_data[index];
		}

		cell_t::const_reference_element_type cell_t::at(size_t index) const
		{
			ALLEGRO::ASSERT(index < WIND::MAP::CELL::LAYER_COUNT);

			return this->m_data[index];
		}

		cell_t::reference_element_type cell_t::operator [](size_t index)
		{
			ALLEGRO::ASSERT(index < WIND::MAP::CELL::LAYER_COUNT);

			return this->m_data[index];
		}

		cell_t::const_reference_element_type cell_t::operator [](size_t index) const
		{
			ALLEGRO::ASSERT(index < WIND::MAP::CELL::LAYER_COUNT);

			return this->m_data[index];
		}

		cell_t::iterator cell_t::begin()
		{
			return iterator(this->m_data.begin());
		}

		cell_t::iterator cell_t::end()
		{
			return iterator(this->m_data.end());
		}

		cell_t::const_iterator cell_t::cbegin()
		{
			return const_iterator(this->m_data.cbegin());
		}

		cell_t::const_iterator cell_t::cend()
		{
			return const_iterator(this->m_data.cend());
		}

	}
}
