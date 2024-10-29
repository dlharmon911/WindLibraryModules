module wind;

import <string>;
import <cstdint>;
import allegro;
import :json.tokenizer;
import :string;

/****************************************************************************************/

namespace wind
{
	json_token_t::json_token_t() : m_type(WIND::JSON::TOKEN::TYPE_UNDEFINED), m_ustring()
	{
	}

	json_token_t::json_token_t(int32_t type, const string_t& str) : m_type(type), m_ustring(str) {}
	json_token_t::json_token_t(const json_token_t& token) : m_type(token.m_type), m_ustring(token.m_ustring) {}
	json_token_t::~json_token_t() {}

	void json_token_t::clear()
	{
		this->m_type = WIND::JSON::TOKEN::TYPE_UNDEFINED;
		this->m_ustring.clear();
	}

	json_token_t& json_token_t::operator = (const json_token_t& token)
	{
		this->m_type = token.m_type;
		this->m_ustring = token.m_ustring;

		return *this;
	}

	void json_token_t::set_type(int32_t type)
	{
		this->m_type = type;
	}

	int32_t json_token_t::get_type() const
	{
		return this->m_type;
	}

	void json_token_t::set_string(const string_t& ustring)
	{
		this->m_ustring = ustring;
	}

	string_t& json_token_t::get_string()
	{
		return this->m_ustring;
	}

	const string_t& json_token_t::get_string() const
	{
		return this->m_ustring;
	}
}
