module wind;

import <string>;
import <array>;
import <cstdint>;
import <memory>;
import allegro;
import :base;
import :bitmap;
import :tilemap;
import :error;
import :map;

namespace wind
{
	auto shared = std::make_shared<int[]>(10);

	template <typename type>
	std::shared_ptr<type> create_array(size_t size)
	{
		return std::static_pointer_cast<type>(std::make_shared<type[]>(size));
	}

	map_t::map_t() : m_data(), m_size({ 0, 0 }) {}

	map_t::map_t(size_t width, size_t height) : m_data(std::make_shared<map_t::value_type[]>(width* height)), m_size(width, height) {}
	
	map_t::map_t(ALLEGRO::SIZE<size_t> size) : m_data(std::make_shared<map_t::value_type[]>(size.width * size.height)), m_size(size) {}

	map_t::map_t(const map_t& map) : m_data(map.m_data), m_size(map.m_size) {}
	
	map_t::~map_t() {}
	
	map_t& map_t::operator = (const map_t& map)
	{
		this->m_data = map.m_data;

		return *this;
	}

	map_t::operator bool() const
	{
		return (bool)this->m_data;
	}

	void map_t::clear()
	{
		this->m_data.reset();
		this->m_size = { 0,0 };
	}

	bool map_t::reset(size_t width, size_t height)
	{
		this->m_size = { 0, 0 };

		this->m_data = std::make_shared<map_t::value_type[]>(width * height);
		if (this->m_data)
		{
			this->m_size = ALLEGRO::SIZE(width, height);
		}

		return (bool)this->m_data;
	}

	bool map_t::reset(ALLEGRO::SIZE<size_t> size)
	{
		return this->reset(size.width, size.height);
	}

	void* map_t::data()
	{
		return this->m_data.get();
	}

	const void* map_t::data() const
	{
		return this->m_data.get();
	}

	const ALLEGRO::SIZE<size_t>& map_t::size() const
	{
		return this->m_size;
	}
	
	map_t::reference_type map_t::at(size_t index)
	{
		ALLEGRO::ASSERT(index < (this->m_size.width * this->m_size.height));
		return this->m_data.get()[index];
	}
	
	map_t::const_reference_type map_t::at(size_t index) const
	{
		ALLEGRO::ASSERT(index < (this->m_size.width * this->m_size.height));
		return this->m_data.get()[index];
	}
	
	map_t::reference_type map_t::operator [](size_t index)
	{
		ALLEGRO::ASSERT(index < (this->m_size.width * this->m_size.height));
		return this->m_data.get()[index];
	}
	
	map_t::const_reference_type map_t::operator [](size_t index) const
	{
		ALLEGRO::ASSERT(index < (this->m_size.width * this->m_size.height));
		return this->m_data.get()[index];
	}
	
	map_t::iterator map_t::begin()
	{
		return iterator(this->m_data, 0);
	}
	
	map_t::iterator map_t::end()
	{
		return iterator(this->m_data, this->m_size.width * this->m_size.height);
	}

	map_t::const_iterator map_t::cbegin()
	{
		return const_iterator(this->m_data, 0);
	}

	map_t::const_iterator map_t::cend()
	{
		return const_iterator(this->m_data, this->m_size.width * this->m_size.height);
	}
}
