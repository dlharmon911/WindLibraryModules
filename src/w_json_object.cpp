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

	bool json_t::is_defined() const
	{
		return (this->m_type >= 0);
	}

	void json_t::clear()
	{
		this->m_type = WIND::JSON::TYPE_NULL;
		this->m_data.reset();
	}

	json_t& json_t::operator = (const json_t& json)
	{
		this->m_type = json.m_type;
		this->m_data = json.m_data;

		return *this;
	}

	int32_t json_t::type() const
	{
		return this->m_type;
	}

	bool json_t::set_as_boolean(bool value)
	{
		this->m_type = WIND::JSON::TYPE_BOOLEAN;
		this->m_data = al::ustr_new(value ? "true" : "false");
		return true;
	}

	bool json_t::set_as_number(double value)
	{
		this->m_type = WIND::JSON::TYPE_NUMBER;
		this->m_data = al::ustr_new(std::to_string(value).c_str());

		return true;
	}

	bool json_t::set_as_string(const string_t& value)
	{
		this->m_type = WIND::JSON::TYPE_STRING;
		this->m_data = value.u_str();

		return true;
	}

	bool json_t::set_as_object(const json_object_t& value)
	{
		this->m_type = WIND::JSON::TYPE_OBJECT;
		ALLEGRO::ASSERT(this->m_data = std::make_shared<json_object_t>(value));

		return true;
	}

	bool json_t::set_as_array(const json_array_t& value)
	{
		this->m_type = WIND::JSON::TYPE_ARRAY;
		ALLEGRO::ASSERT(this->m_data = std::make_shared<json_array_t>(value));

		return true;
	}

	bool json_t::get_as_boolean() const
	{
		ALLEGRO::ASSERT(this->m_type == WIND::JSON::TYPE_BOOLEAN);
		return this->get_as_string() == "true";
	}

	double json_t::get_as_number() const
	{
		ALLEGRO::ASSERT(this->m_type == WIND::JSON::TYPE_NUMBER);
		return std::atof(al::c_str((ALLEGRO::USTRING&)this->m_data));
	}

	string_t json_t::get_as_string()
	{
		ALLEGRO::ASSERT(this->m_type == WIND::JSON::TYPE_STRING);

		string_t rv;

		if (this->m_data)
		{
			rv = ((string_t&)this->m_data);
		}

		return rv;
	}

	const string_t json_t::get_as_string() const
	{
		string_t rv;

		if (this->m_type == WIND::JSON::TYPE_STRING)
		{
			if (this->m_data)
			{
				rv = std::static_pointer_cast<ALLEGRO::USTRING_DATA>(this->m_data);
			}
		}

		return rv;
	}

	json_object_t& json_t::get_as_object()
	{
		ALLEGRO::ASSERT(this->m_type == WIND::JSON::TYPE_OBJECT);
		return (*((json_object_t*)this->m_data.get()));
	}

	const json_object_t& json_t::get_as_object() const
	{
		ALLEGRO::ASSERT(this->m_type == WIND::JSON::TYPE_OBJECT);
		return (*((json_object_t*)this->m_data.get()));
	}

	json_array_t& json_t::get_as_array()
	{
		ALLEGRO::ASSERT(this->m_type == WIND::JSON::TYPE_ARRAY);
		return (*((json_array_t*)this->m_data.get()));
	}

	const json_array_t& json_t::get_as_array() const
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

	json_object_t& json_object_t::operator = (const json_object_t& object)
	{
		this->m_data = object.m_data;
		return *this;
	}

	json_object_t& json_object_t::operator = (json_object_t& object)
	{
		this->m_data = object.m_data;
		return *this;
	}

	void json_object_t::clear() noexcept
	{
		return this->m_data.clear();
	}

	size_t json_object_t::size() const noexcept
	{
		return this->m_data.size();
	}

	bool json_object_t::is_empty() const noexcept
	{
		return this->m_data.empty();
	}

	json_object_t::reference_t json_object_t::at(const json_key_t& key)
	{
		return this->m_data.at(key);
	}

	json_object_t::const_reference_t json_object_t::at(const json_key_t& key) const
	{
		return this->m_data.at(key);
	}

	json_object_t::reference_t json_object_t::operator [](const json_key_t& key)
	{
		return this->m_data[key];
	}

	void json_object_t::add(const json_key_t& key, const value_t& val)
	{
		this->m_data[key] = val;
	}

	void json_object_t::add(const json_pair_t& pair)
	{
		this->m_data[pair.first] = pair.second;
	}

	void json_object_t::remove(const json_key_t& key)
	{
		this->m_data.erase(key);
	}

	json_object_t::iterator json_object_t::find(const json_key_t& key)
	{
		return iterator(this->m_data.find(key));
	}

	json_object_t::const_iterator json_object_t::find(const json_key_t& key) const
	{
		return const_iterator(this->m_data.find(key));
	}

	json_object_t::iterator json_object_t::begin()
	{
		return iterator(this->m_data.begin());
	}

	json_object_t::iterator json_object_t::end()
	{
		return iterator(this->m_data.end());
	}

	json_object_t::const_iterator json_object_t::cbegin() const
	{
		return const_iterator(this->m_data.cbegin());
	}

	json_object_t::const_iterator json_object_t::cend() const
	{
		return const_iterator(this->m_data.cend());
	}

	/****************************************************************************************/

	json_array_t::json_array_t() : m_data() {}
	json_array_t::json_array_t(size_t n) : m_data(n) {}
	json_array_t::json_array_t(size_t n, const value_t& val) : m_data(n, val) {}
	json_array_t::json_array_t(const json_array_t& array) : m_data(array.m_data) {}
	json_array_t::json_array_t(json_array_t& array) : m_data(array.m_data) {}
	json_array_t::json_array_t(std::initializer_list<value_t> il) : m_data(il) {}
	json_array_t::~json_array_t() {}

	json_array_t& json_array_t::operator = (const json_array_t& array)
	{
		this->m_data = array.m_data;
		return *this;
	}

	json_array_t& json_array_t::operator = (json_array_t& array)
	{
		this->m_data = array.m_data;
		return *this;
	}

	json_array_t& json_array_t::operator = (std::initializer_list<value_t> il)
	{
		this->m_data = il;
		return *this;
	}

	void json_array_t::clear() noexcept
	{
		return this->m_data.clear();
	}

	size_t json_array_t::size() const noexcept
	{
		return this->m_data.size();
	}

	bool json_array_t::is_empty() const noexcept
	{
		return this->m_data.empty();
	}

	json_array_t::reference_t json_array_t::at(size_t index)
	{
		ALLEGRO::ASSERT(index < this->m_data.size());
		return this->m_data[index];
	}

	json_array_t::const_reference_t json_array_t::at(size_t index) const
	{
		ALLEGRO::ASSERT(index < this->m_data.size());
		return this->m_data[index];
	}

	json_array_t::reference_t json_array_t::operator [](size_t index)
	{
		ALLEGRO::ASSERT(index < this->m_data.size());
		return this->m_data[index];
	}

	json_array_t::const_reference_t json_array_t::operator [](size_t index) const
	{
		ALLEGRO::ASSERT(index < this->m_data.size());
		return this->m_data[index];
	}

	void json_array_t::push_back(const value_t& val)
	{
		this->m_data.push_back(val);
	}

	void json_array_t::pop_back()
	{
		this->m_data.pop_back();
	}

	json_array_t::iterator json_array_t::insert(const_iterator position, const value_t& val)
	{
		return iterator(this->m_data.insert(position.m_it, val));
	}

	json_array_t::iterator json_array_t::insert(const_iterator position, size_t n, const value_t& val)
	{
		return iterator(this->m_data.insert(position.m_it, n, val));
	}

	json_array_t::iterator json_array_t::insert(const_iterator position, std::initializer_list<value_t> il)
	{
		return iterator(this->m_data.insert(position.m_it, il));
	}

	json_array_t::iterator json_array_t::erase(const_iterator position)
	{
		return iterator(this->m_data.erase(position.m_it));
	}

	json_array_t::iterator json_array_t::erase(const_iterator first, const_iterator last)
	{
		return iterator(this->m_data.erase(first.m_it, last.m_it));
	}

	void json_array_t::assign(size_t n, const value_t& val)
	{
		this->m_data.assign(n, val);
	}

	void json_array_t::assign(std::initializer_list<value_t> il)
	{
		this->m_data.assign(il);
	}

	json_array_t::iterator json_array_t::begin()
	{
		return iterator(this->m_data.begin());
	}

	json_array_t::iterator json_array_t::end()
	{
		return iterator(this->m_data.end());
	}

	json_array_t::const_iterator json_array_t::cbegin() const
	{
		return const_iterator(this->m_data.cbegin());
	}

	json_array_t::const_iterator json_array_t::cend() const
	{
		return const_iterator(this->m_data.cend());
	}

	json_array_t::reverse_iterator json_array_t::rbegin()
	{
		return reverse_iterator(this->m_data.rbegin());
	}

	json_array_t::reverse_iterator json_array_t::rend()
	{
		return reverse_iterator(this->m_data.rend());
	}

	json_array_t::const_reverse_iterator json_array_t::crbegin() const
	{
		return const_reverse_iterator(this->m_data.crbegin());
	}

	json_array_t::const_reverse_iterator json_array_t::crend() const
	{
		return const_reverse_iterator(this->m_data.crend());
	}
}

