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
	auto shared = std::make_shared<int32_t[]>(10);

	template <typename type>
	std::shared_ptr<type> create_array(size_t size)
	{
		return std::static_pointer_cast<type>(std::make_shared<type[]>(size));
	}

	map_t::map_t() : m_data(), m_size({ 0, 0 }) {}

	map_t::map_t(size_t width, size_t height) : m_data(std::make_shared<map_t::element_type[]>(width* height)), m_size(width, height) {}

	map_t::map_t(ALLEGRO::SIZE<size_t> size) : m_data(std::make_shared<map_t::element_type[]>(size.width* size.height)), m_size(size) {}

	map_t::map_t(const map_t& map) : m_data(map.m_data), m_size(map.m_size) {}

	map_t::~map_t() {}

	auto map_t::operator = (const map_t& map) -> map_t&
	{
		this->m_data = map.m_data;

		return *this;
	}

	map_t::operator bool() const
	{
		return (bool)this->m_data;
	}

	auto map_t::clear() -> void
	{
		this->m_data.reset();
		this->m_size = { 0,0 };
	}

	auto map_t::reset(size_t width, size_t height) -> bool
	{
		this->m_size = { 0, 0 };

		this->m_data = std::make_shared<map_t::element_type[]>(width * height);
		if (this->m_data)
		{
			this->m_size = ALLEGRO::SIZE(width, height);
		}

		return (bool)this->m_data;
	}

	auto map_t::reset(const ALLEGRO::SIZE<size_t>& size) -> bool
	{
		return this->reset(size.width, size.height);
	}

	auto map_t::data() -> void*
	{
		return this->m_data.get();
	}

	auto map_t::data() const -> const void*
	{
		return this->m_data.get();
	}

	auto map_t::size() const -> const ALLEGRO::SIZE<size_t>&
	{
		return this->m_size;
	}

	auto map_t::at(size_t index) -> map_t::reference_element_type
	{
		ALLEGRO::ASSERT(index < (this->m_size.width * this->m_size.height));
		return this->m_data.get()[index];
	}

	auto map_t::at(size_t index) const -> map_t::const_reference_element_type
	{
		ALLEGRO::ASSERT(index < (this->m_size.width * this->m_size.height));
		return this->m_data.get()[index];
	}

	auto map_t::operator [](size_t index) -> map_t::reference_element_type
	{
		ALLEGRO::ASSERT(index < (this->m_size.width * this->m_size.height));
		return this->m_data.get()[index];
	}

	auto map_t::operator [](size_t index) const -> map_t::const_reference_element_type
	{
		ALLEGRO::ASSERT(index < (this->m_size.width * this->m_size.height));
		return this->m_data.get()[index];
	}

	auto map_t::begin() -> map_t::iterator
	{
		return iterator(this->m_data, 0);
	}

	auto map_t::end() -> map_t::iterator
	{
		return iterator(this->m_data, this->m_size.width * this->m_size.height);
	}

	auto map_t::cbegin() const -> map_t::const_iterator
	{
		return const_iterator(this->m_data, 0);
	}

	auto map_t::cend() const -> map_t::const_iterator
	{
		return const_iterator(this->m_data, this->m_size.width * this->m_size.height);
	}
}
