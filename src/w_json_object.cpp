module wind;

import <string>;
import <cstdint>;
import allegro;
import :base;
import :json.object;
import :string;

namespace wind
{
	json_t::json_t() : m_type(WIND::JSON::TYPE_NULL), m_data() {}

	json_t::json_t(bool value) : m_type(WIND::JSON::TYPE_BOOLEAN), m_data(al::ustr_new(value ? "true" : "false"))
	{
		ALLEGRO::ASSERT(this->m_data);
	}

	json_t::json_t(double value) : m_type(WIND::JSON::TYPE_NUMBER), m_data(al::ustr_new(std::to_string(value).c_str()))
	{
		ALLEGRO::ASSERT(this->m_data);
	}

	json_t::json_t(const string_t& value) : m_type(WIND::JSON::TYPE_STRING), m_data(value.u_str())
	{
		ALLEGRO::ASSERT(this->m_data);
	}

	json_t::json_t(const json_object_t& value) : m_type(WIND::JSON::TYPE_OBJECT), m_data(std::make_shared<json_object_t>(value))
	{
		ALLEGRO::ASSERT(this->m_data);
	}

	json_t::json_t(const json_array_t& value) : m_type(WIND::JSON::TYPE_ARRAY), m_data(std::make_shared<json_array_t>(value))
	{
		ALLEGRO::ASSERT(this->m_data);
	}

	json_t::json_t(const json_t& json) : m_type(json.m_type)
	{
		switch (json.m_type)
		{
		case WIND::JSON::TYPE_NULL:
		case WIND::JSON::TYPE_BOOLEAN:
		case WIND::JSON::TYPE_NUMBER:
		case WIND::JSON::TYPE_STRING:
		{
			this->m_data = json.m_data;
		} break;
		case WIND::JSON::TYPE_OBJECT:
		{
			this->m_data = json.m_data;
		} break;
		case WIND::JSON::TYPE_ARRAY:
		{
			this->m_data = json.m_data;
		} break;
		}
	}

	json_t::~json_t() {}

	auto json_t::is_defined() const -> bool
	{
		return (this->m_type >= 0);
	}

	auto json_t::clear() -> void
	{
		this->m_type = WIND::JSON::TYPE_NULL;
		this->m_data.reset();
	}

	auto json_t::operator = (const json_t& json) -> json_t&
	{
		this->m_type = json.m_type;
		this->m_data = json.m_data;

		return *this;
	}

	auto json_t::get_type() const -> int32_t
	{
		return this->m_type;
	}

	auto json_t::set_as_boolean(bool value) -> bool
	{
		this->m_type = WIND::JSON::TYPE_BOOLEAN;
		this->m_data = al::ustr_new(value ? "true" : "false");
		return true;
	}

	auto json_t::set_as_number(double value) -> bool
	{
		this->m_type = WIND::JSON::TYPE_NUMBER;
		this->m_data = al::ustr_new(std::to_string(value).c_str());

		return true;
	}

	auto json_t::set_as_string(const string_t& value) -> bool
	{
		this->m_type = WIND::JSON::TYPE_STRING;
		this->m_data = value.u_str();

		return true;
	}

	auto json_t::set_as_object(const json_object_t& value) -> bool
	{
		this->m_type = WIND::JSON::TYPE_OBJECT;
		ALLEGRO::ASSERT(this->m_data = std::make_shared<json_object_t>(value));

		return true;
	}

	auto json_t::set_as_array(const json_array_t& value) -> bool
	{
		this->m_type = WIND::JSON::TYPE_ARRAY;
		ALLEGRO::ASSERT(this->m_data = std::make_shared<json_array_t>(value));

		return true;
	}

	auto json_t::get_as_boolean() const -> bool
	{
		ALLEGRO::ASSERT(this->m_type == WIND::JSON::TYPE_BOOLEAN);
		return this->get_as_string() == "true";
	}

	auto json_t::get_as_number() const -> double
	{
		ALLEGRO::ASSERT(this->m_type == WIND::JSON::TYPE_NUMBER);
		return std::atof(al::c_str((ALLEGRO::USTRING&)this->m_data));
	}

	auto json_t::get_as_string() const -> string_t
	{
		ALLEGRO::ASSERT(this->m_type == WIND::JSON::TYPE_STRING);

		string_t rv;

		if (this->m_data)
		{
			rv = ((ALLEGRO::USTRING&)this->m_data);
		}

		return rv;
	}

	auto json_t::get_as_object() -> json_object_t&
	{
		ALLEGRO::ASSERT(this->m_type == WIND::JSON::TYPE_OBJECT);
		return (*((json_object_t*)this->m_data.get()));
	}

	auto json_t::get_as_object() const -> const json_object_t&
	{
		ALLEGRO::ASSERT(this->m_type == WIND::JSON::TYPE_OBJECT);
		return (*((json_object_t*)this->m_data.get()));
	}

	auto json_t::get_as_array() -> json_array_t&
	{
		ALLEGRO::ASSERT(this->m_type == WIND::JSON::TYPE_ARRAY);
		return (*((json_array_t*)this->m_data.get()));
	}

	auto json_t::get_as_array() const -> const json_array_t&
	{
		ALLEGRO::ASSERT(this->m_type == WIND::JSON::TYPE_ARRAY);
		return (*((json_array_t*)this->m_data.get()));
	}

	json_t::operator bool() const
	{
		return this->get_as_boolean();
	}

	json_t::operator double() const
	{
		return this->get_as_number();
	}

	json_t::operator string_t()
	{
		return this->get_as_string();
	}

	json_t::operator const string_t() const
	{
		return this->get_as_string();
	}

	json_t::operator json_object_t& ()
	{
		return this->get_as_object();
	}

	json_t::operator const json_object_t& () const
	{
		return this->get_as_object();
	}

	json_t::operator json_array_t& ()
	{
		return this->get_as_array();
	}
	json_t::operator const json_array_t& () const
	{
		return this->get_as_array();
	}

	json_object_t::json_object_t() : m_data() {}
	json_object_t::json_object_t(const json_object_t& object) : m_data(object.m_data) {}
	json_object_t::json_object_t(json_object_t& object) : m_data(object.m_data) {}
	json_object_t::~json_object_t() {}

	auto json_object_t::operator = (const json_object_t& object) -> json_object_t&
	{
		this->m_data = object.m_data;
		return *this;
	}

	auto json_object_t::operator = (json_object_t& object) -> json_object_t&
	{
		this->m_data = object.m_data;
		return *this;
	}

	auto json_object_t::clear() noexcept -> void
	{
		return this->m_data.clear();
	}

	auto json_object_t::size() const noexcept -> size_t
	{
		return this->m_data.size();
	}

	auto json_object_t::is_empty() const noexcept -> bool
	{
		return this->m_data.empty();
	}

	auto json_object_t::at(const json_key_t& key) -> json_object_t::reference_element_type
	{
		return this->m_data.at(key);
	}

	auto json_object_t::at(const json_key_t& key) const -> json_object_t::const_reference_element_type
	{
		return this->m_data.at(key);
	}

	auto json_object_t::operator [](const json_key_t& key) -> json_object_t::reference_element_type
	{
		return this->m_data[key];
	}

	auto json_object_t::add(const json_key_t& key, const element_type& val) -> void
	{
		this->m_data[key] = val;
	}

	auto json_object_t::add(const json_pair_t& pair) -> void
	{
		this->m_data[pair.first] = pair.second;
	}

	auto json_object_t::remove(const json_key_t& key) -> void
	{
		this->m_data.erase(key);
	}

	auto json_object_t::find(const json_key_t& key) -> json_object_t::iterator
	{
		return iterator(this->m_data.find(key));
	}

	auto json_object_t::find(const json_key_t& key) const -> json_object_t::const_iterator
	{
		return const_iterator(this->m_data.find(key));
	}

	auto json_object_t::begin() -> json_object_t::iterator
	{
		return iterator(this->m_data.begin());
	}

	auto json_object_t::end() -> json_object_t::iterator
	{
		return iterator(this->m_data.end());
	}

	auto json_object_t::cbegin() const -> json_object_t::const_iterator
	{
		return const_iterator(this->m_data.cbegin());
	}

	auto json_object_t::cend() const -> json_object_t::const_iterator
	{
		return const_iterator(this->m_data.cend());
	}

	/****************************************************************************************/

	json_array_t::json_array_t() : m_data() {}
	json_array_t::json_array_t(size_t n) : m_data(n) {}
	json_array_t::json_array_t(size_t n, const element_type& val) : m_data(n, val) {}
	json_array_t::json_array_t(const json_array_t& array) : m_data(array.m_data) {}
	json_array_t::json_array_t(json_array_t& array) : m_data(array.m_data) {}
	json_array_t::json_array_t(std::initializer_list<element_type> il) : m_data(il) {}
	json_array_t::~json_array_t() {}

	auto json_array_t::operator = (const json_array_t& array) -> json_array_t&
	{
		this->m_data = array.m_data;
		return *this;
	}

	auto json_array_t::operator = (json_array_t& array) -> json_array_t&
	{
		this->m_data = array.m_data;
		return *this;
	}

	auto json_array_t::operator = (std::initializer_list<element_type> il) -> json_array_t&
	{
		this->m_data = il;
		return *this;
	}

	auto json_array_t::clear() noexcept -> void
	{
		return this->m_data.clear();
	}

	auto json_array_t::size() const noexcept -> size_t
	{
		return this->m_data.size();
	}

	auto json_array_t::is_empty() const noexcept -> bool
	{
		return this->m_data.empty();
	}

	auto json_array_t::at(size_t index) -> json_array_t::reference_element_type
	{
		ALLEGRO::ASSERT(index < this->m_data.size());
		return this->m_data[index];
	}

	auto json_array_t::at(size_t index) const -> json_array_t::const_reference_element_type
	{
		ALLEGRO::ASSERT(index < this->m_data.size());
		return this->m_data[index];
	}

	auto json_array_t::operator [](size_t index) -> json_array_t::reference_element_type
	{
		ALLEGRO::ASSERT(index < this->m_data.size());
		return this->m_data[index];
	}

	auto json_array_t::operator [](size_t index) const -> json_array_t::const_reference_element_type
	{
		ALLEGRO::ASSERT(index < this->m_data.size());
		return this->m_data[index];
	}

	auto json_array_t::push_back(const element_type& val) -> void
	{
		this->m_data.push_back(val);
	}

	auto json_array_t::pop_back() -> void
	{
		this->m_data.pop_back();
	}

	auto json_array_t::insert(const_iterator position, const element_type& val) -> json_array_t::iterator
	{
		return iterator(this->m_data.insert(position.m_it, val));
	}

	auto json_array_t::insert(const_iterator position, size_t n, const element_type& val) -> json_array_t::iterator
	{
		return iterator(this->m_data.insert(position.m_it, n, val));
	}

	auto json_array_t::insert(const_iterator position, std::initializer_list<element_type> il) -> json_array_t::iterator
	{
		return iterator(this->m_data.insert(position.m_it, il));
	}

	auto json_array_t::erase(const_iterator position) -> json_array_t::iterator
	{
		return iterator(this->m_data.erase(position.m_it));
	}

	auto json_array_t::erase(const_iterator first, const_iterator last) -> json_array_t::iterator
	{
		return iterator(this->m_data.erase(first.m_it, last.m_it));
	}

	auto json_array_t::assign(size_t n, const element_type& val) -> void
	{
		this->m_data.assign(n, val);
	}

	auto json_array_t::assign(std::initializer_list<element_type> il) -> void
	{
		this->m_data.assign(il);
	}

	auto json_array_t::begin() -> json_array_t::iterator
	{
		return iterator(this->m_data.begin());
	}

	auto json_array_t::end() -> json_array_t::iterator
	{
		return iterator(this->m_data.end());
	}

	auto json_array_t::cbegin() const -> json_array_t::const_iterator
	{
		return const_iterator(this->m_data.cbegin());
	}

	auto json_array_t::cend() const -> json_array_t::const_iterator
	{
		return const_iterator(this->m_data.cend());
	}

	auto json_array_t::rbegin() -> json_array_t::reverse_iterator
	{
		return reverse_iterator(this->m_data.rbegin());
	}

	auto json_array_t::rend() -> json_array_t::reverse_iterator
	{
		return reverse_iterator(this->m_data.rend());
	}

	auto json_array_t::crbegin() const -> json_array_t::const_reverse_iterator
	{
		return const_reverse_iterator(this->m_data.crbegin());
	}

	auto json_array_t::crend() const -> json_array_t::const_reverse_iterator
	{
		return const_reverse_iterator(this->m_data.crend());
	}
}