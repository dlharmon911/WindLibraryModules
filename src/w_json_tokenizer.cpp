module wind;

import <string>;
import <cstdint>;
import allegro;
import :json.tokenizer;
import :string;

/****************************************************************************************/

namespace wind
{
	json_token_t::json_token_t() : m_type(WIND::JSON::TOKEN::TYPE::UNDEFINED), m_ustring()
	{
	}

	json_token_t::json_token_t(WIND::JSON::TOKEN::TYPE type, const string_t& str) : m_type(type), m_ustring(str) {}
	json_token_t::json_token_t(const json_token_t& token) : m_type(token.m_type), m_ustring(token.m_ustring) {}
	json_token_t::~json_token_t() {}

	auto json_token_t::clear() -> void
	{
		this->m_type = WIND::JSON::TOKEN::TYPE::UNDEFINED;
		this->m_ustring.clear();
	}

	auto json_token_t::operator = (const json_token_t& token) -> json_token_t&
	{
		this->m_type = token.m_type;
		this->m_ustring = token.m_ustring;

		return *this;
	}

	auto json_token_t::set_type(WIND::JSON::TOKEN::TYPE type) -> void
	{
		this->m_type = type;
	}

	auto json_token_t::get_type() const -> WIND::JSON::TOKEN::TYPE
	{
		return this->m_type;
	}

	auto json_token_t::set_string(const string_t& ustring) -> void
	{
		this->m_ustring = ustring;
	}

	auto json_token_t::get_string() -> string_t&
	{
		return this->m_ustring;
	}

	auto json_token_t::get_string() const -> const string_t&
	{
		return this->m_ustring;
	}
}