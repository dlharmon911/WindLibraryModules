module wind;

import std;
import allegro;
import :base;
import :json.object;
import :string;

namespace wind
{
	json_t::json_t() : m_type(WIND::JSON::TYPE::EMPTY), m_data() {}
	json_t::json_t(const json_t& value) : m_type(value.m_type), m_data(value.m_data) {}

	template <> json_t::json_t(const bool& value) : m_type(WIND::JSON::TYPE::BOOLEAN), m_data(al::ustr_new(value ? "true" : "false")) { ALLEGRO::ASSERT(this->m_data); }
	template <> json_t::json_t(const string_t& value) : m_type(WIND::JSON::TYPE::NUMBER), m_data(al::ustr_new(value.c_str())) { ALLEGRO::ASSERT(this->m_data); }
	template <> json_t::json_t(const int8_t& value) : m_type(WIND::JSON::TYPE::NUMBER), m_data(al::ustr_new(string::to_string<int32_t>(value).c_str())) { ALLEGRO::ASSERT(this->m_data); }
	template <> json_t::json_t(const int16_t& value) : m_type(WIND::JSON::TYPE::NUMBER), m_data(al::ustr_new(string::to_string<int32_t>(value).c_str())) { ALLEGRO::ASSERT(this->m_data); }
	template <> json_t::json_t(const int32_t& value) : m_type(WIND::JSON::TYPE::NUMBER), m_data(al::ustr_new(string::to_string<int32_t>(value).c_str())) { ALLEGRO::ASSERT(this->m_data); }
	template <> json_t::json_t(const int64_t& value) : m_type(WIND::JSON::TYPE::NUMBER), m_data(al::ustr_new(string::to_string<int64_t>(value).c_str())) { ALLEGRO::ASSERT(this->m_data); }
	template <> json_t::json_t(const uint8_t& value) : m_type(WIND::JSON::TYPE::NUMBER), m_data(al::ustr_new(string::to_string<uint32_t>(value).c_str())) { ALLEGRO::ASSERT(this->m_data); }
	template <> json_t::json_t(const uint16_t& value) : m_type(WIND::JSON::TYPE::NUMBER), m_data(al::ustr_new(string::to_string<uint32_t>(value).c_str())) { ALLEGRO::ASSERT(this->m_data); }
	template <> json_t::json_t(const uint32_t& value) : m_type(WIND::JSON::TYPE::NUMBER), m_data(al::ustr_new(string::to_string<uint32_t>(value).c_str())) { ALLEGRO::ASSERT(this->m_data); }
	template <> json_t::json_t(const uint64_t& value) : m_type(WIND::JSON::TYPE::NUMBER), m_data(al::ustr_new(string::to_string<uint64_t>(value).c_str())) { ALLEGRO::ASSERT(this->m_data); }
	template <> json_t::json_t(const float& value) : m_type(WIND::JSON::TYPE::NUMBER), m_data(al::ustr_new(string::to_string<float>(value).c_str())) { ALLEGRO::ASSERT(this->m_data); }
	template <> json_t::json_t(const double& value) : m_type(WIND::JSON::TYPE::NUMBER), m_data(al::ustr_new(string::to_string<double>(value).c_str())) { ALLEGRO::ASSERT(this->m_data); }
	template <> json_t::json_t(const json_object_t& value) : m_type(WIND::JSON::TYPE::OBJECT), m_data(std::make_shared<json_object_t>(value)) { ALLEGRO::ASSERT(this->m_data); }
	template <> json_t::json_t(const json_array_t& value) : m_type(WIND::JSON::TYPE::ARRAY), m_data(std::make_shared<json_array_t>(value)) { ALLEGRO::ASSERT(this->m_data); }

	json_t::~json_t() {}

	auto json_t::is_defined() const -> bool
	{
		return (this->m_type != WIND::JSON::TYPE::EMPTY);
	}

	auto json_t::clear() -> void
	{
		this->m_type = WIND::JSON::TYPE::EMPTY;
		this->m_data.reset();
	}

	auto json_t::operator = (const json_t& json) -> json_t&
	{
		this->m_type = json.m_type;
		this->m_data = json.m_data;

		return *this;
	}

	auto json_t::get_type() const -> WIND::JSON::TYPE
	{
		return this->m_type;
	}

	template <> auto json_t::set_as(const bool& value) -> bool
	{
		this->m_type = WIND::JSON::TYPE::BOOLEAN;
		this->m_data = al::ustr_new(value ? "true" : "false");
		return true;
	}

	template<> auto json_t::set_as(const string_t& value) -> bool
	{
		this->m_type = WIND::JSON::TYPE::STRING;
		this->m_data = value.u_str();

		return true;
	}

	template <> auto json_t::set_as(const int8_t& value) -> bool
	{
		this->m_type = WIND::JSON::TYPE::NUMBER;
		this->m_data = al::ustr_new(string::to_string<int32_t>(value).c_str());

		return true;
	}

	template <> auto json_t::set_as(const int16_t& value) -> bool
	{
		this->m_type = WIND::JSON::TYPE::NUMBER;
		this->m_data = al::ustr_new(string::to_string<int32_t>(value).c_str());

		return true;
	}

	template <> auto json_t::set_as(const int32_t& value) -> bool
	{
		this->m_type = WIND::JSON::TYPE::NUMBER;
		this->m_data = al::ustr_new(string::to_string<int32_t>(value).c_str());

		return true;
	}

	template <> auto json_t::set_as(const int64_t& value) -> bool
	{
		this->m_type = WIND::JSON::TYPE::NUMBER;
		this->m_data = al::ustr_new(string::to_string<int64_t>(value).c_str());

		return true;
	}

	template <> auto json_t::set_as(const uint8_t& value) -> bool
	{
		this->m_type = WIND::JSON::TYPE::NUMBER;
		this->m_data = al::ustr_new(string::to_string<uint32_t>(value).c_str());

		return true;
	}

	template <> auto json_t::set_as(const uint16_t& value) -> bool
	{
		this->m_type = WIND::JSON::TYPE::NUMBER;
		this->m_data = al::ustr_new(string::to_string<uint32_t>(value).c_str());

		return true;
	}

	template <> auto json_t::set_as(const uint32_t& value) -> bool
	{
		this->m_type = WIND::JSON::TYPE::NUMBER;
		this->m_data = al::ustr_new(string::to_string<uint32_t>(value).c_str());

		return true;
	}

	template <> auto json_t::set_as(const uint64_t& value) -> bool
	{
		this->m_type = WIND::JSON::TYPE::NUMBER;
		this->m_data = al::ustr_new(string::to_string<uint64_t>(value).c_str());

		return true;
	}

	template <> auto json_t::set_as(const float& value) -> bool
	{
		this->m_type = WIND::JSON::TYPE::NUMBER;
		this->m_data = al::ustr_new(string::to_string<float>(value).c_str());

		return true;
	}

	template <> auto json_t::set_as(const double& value) -> bool
	{
		this->m_type = WIND::JSON::TYPE::NUMBER;
		this->m_data = al::ustr_new(string::to_string<double>(value).c_str());

		return true;
	}

	template <> auto json_t::set_as(const json_object_t& value) -> bool
	{
		this->m_type = WIND::JSON::TYPE::OBJECT;
		ALLEGRO::ASSERT(this->m_data = std::make_shared<json_object_t>(value));

		return true;
	}

	template <> auto json_t::set_as(const json_array_t& value) -> bool
	{
		this->m_type = WIND::JSON::TYPE::ARRAY;
		ALLEGRO::ASSERT(this->m_data = std::make_shared<json_array_t>(value));

		return true;
	}


	template <> auto json_t::get_as<bool>() const -> bool
	{
		ALLEGRO::ASSERT(this->m_type == WIND::JSON::TYPE::BOOLEAN);
		return this->get_as<string_t>() == "true";
	}

	template <> auto json_t::get_as<string_t>() const -> string_t
	{
		ALLEGRO::ASSERT(this->m_type == WIND::JSON::TYPE::BOOLEAN ||
			this->m_type == WIND::JSON::TYPE::NUMBER ||
			this->m_type == WIND::JSON::TYPE::STRING);

		string_t rv;

		if (this->m_data)
		{
			rv = ((ALLEGRO::USTRING&)this->m_data);
		}

		return rv;
	}

	template <> auto json_t::get_as<int8_t>() const -> int8_t
	{
		return static_cast<int8_t>(json_t::get_as<int32_t>());
	}

	template <> auto json_t::get_as<int16_t>() const -> int16_t
	{
		return static_cast<int8_t>(json_t::get_as<int32_t>());
	}

	template <> auto json_t::get_as<int32_t>() const -> int32_t
	{
		ALLEGRO::ASSERT(this->m_type == WIND::JSON::TYPE::NUMBER);

		char* pEnd = nullptr;

		int32_t rv = std::strtol(al::c_str((ALLEGRO::USTRING&)this->m_data), &pEnd, 10);

		if (pEnd)
		{
			return 0;
		}

		return rv;
	}

	template <> auto json_t::get_as<int64_t>() const -> int64_t
	{
		ALLEGRO::ASSERT(this->m_type == WIND::JSON::TYPE::NUMBER);

		char* pEnd = nullptr;

		int64_t rv = std::strtoll(al::c_str((ALLEGRO::USTRING&)this->m_data), &pEnd, 10);

		if (pEnd)
		{
			return 0;
		}

		return rv;
	}

	template <> auto json_t::get_as<uint8_t>() const -> uint8_t
	{
		return static_cast<uint8_t>(json_t::get_as<uint32_t>());
	}

	template <> auto json_t::get_as<uint16_t>() const -> uint16_t
	{
		return static_cast<uint16_t>(json_t::get_as<uint32_t>());
	}

	template <> auto json_t::get_as<uint32_t>() const -> uint32_t
	{
		ALLEGRO::ASSERT(this->m_type == WIND::JSON::TYPE::NUMBER);

		char* pEnd = nullptr;

		uint32_t rv = std::strtoul(al::c_str((ALLEGRO::USTRING&)this->m_data), &pEnd, 10);

		if (pEnd)
		{
			return 0;
		}

		return rv;
	}

	template <> auto json_t::get_as<uint64_t>() const -> uint64_t
	{
		ALLEGRO::ASSERT(this->m_type == WIND::JSON::TYPE::NUMBER);

		char* pEnd = nullptr;

		uint64_t rv = std::strtoull(al::c_str((ALLEGRO::USTRING&)this->m_data), &pEnd, 10);

		if (pEnd)
		{
			return 0;
		}

		return rv;
	}

	template <> auto json_t::get_as<float>() const -> float
	{
		ALLEGRO::ASSERT(this->m_type == WIND::JSON::TYPE::NUMBER);

		char* pEnd = nullptr;

		float rv = std::strtof(al::c_str((ALLEGRO::USTRING&)this->m_data), &pEnd);

		if (pEnd)
		{
			return 0.0f;
		}

		return rv;
	}

	template <> auto json_t::get_as<double>() const -> double
	{
		ALLEGRO::ASSERT(this->m_type == WIND::JSON::TYPE::NUMBER);

		char* pEnd = nullptr;

		double rv = std::strtod(al::c_str((ALLEGRO::USTRING&)this->m_data), &pEnd);

		if (pEnd)
		{
			return 0;
		}

		return rv;
	}



	template <> auto json_t::get_as<json_object_t>() const->json_object_t
	{
		return static_cast<json_object_t>(*this);
	}

	template <> auto json_t::get_as<json_array_t>() const->json_array_t
	{
		return static_cast<json_array_t>(*this);
	}

	template <> auto json_t::get_as<json_object_t&>()->json_object_t&
	{
		return *reinterpret_cast<json_object_t*>(this->m_data.get());
	}

	template <> auto json_t::get_as<json_array_t&>()->json_array_t&
	{
		return *reinterpret_cast<json_array_t*>(this->m_data.get());
	}

	auto json_t::get_data() -> std::shared_ptr<void>&
	{
		return this->m_data;
	}

	auto json_t::get_data() const -> const std::shared_ptr<void>&
	{
		return this->m_data;
	}

	json_object_t::json_object_t() : m_data() {}
	json_object_t::json_object_t(const json_t& json) : m_data((reinterpret_cast<const json_object_t*>(&json))->m_data) {}
	json_object_t::json_object_t(const json_object_t& object) : m_data(object.m_data) {}
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
	json_array_t::json_array_t(const json_t& json) : m_data((reinterpret_cast<const json_array_t*>(&json))->m_data) {}
	json_array_t::json_array_t(size_t n) : m_data(n) {}
	json_array_t::json_array_t(size_t n, const element_type& val) : m_data(n, val) {}
	json_array_t::json_array_t(const json_array_t& array) : m_data(array.m_data) {}
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
}
