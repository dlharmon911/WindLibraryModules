module wind;

import <cstdint>;
import :base;
import :hex;
import :string;
import :value;

namespace wind
{
	value_t::value_t() : m_value() {}
	value_t::value_t(const value_t& value) : m_value(value.m_value) {}
	value_t::value_t(const bool& value) : m_value(string::to_string<bool>(value)) {}
	value_t::value_t(const int32_t& value) : m_value(string::to_string<int32_t>(value)) {}
	value_t::value_t(const uint32_t& value) : m_value(string::to_string<uint32_t>(value)) {}
	value_t::value_t(const int64_t& value) : m_value(string::to_string<int64_t>(value)) {}
	value_t::value_t(const uint64_t& value) : m_value(string::to_string<uint64_t>(value)) {}
	value_t::value_t(const float& value) : m_value(string::to_string<float>(value)) {}
	value_t::value_t(const double& value) : m_value(string::to_string<double>(value)) {}
	value_t::value_t(const string_t& value) : m_value(value) {}
	value_t::value_t(const char* value) : m_value(value) {}
	value_t::~value_t() {}

	auto value_t::clear() -> void
	{
		this->m_value.clear();
	}

	auto value_t::operator = (const value_t& value) -> value_t&
	{
		this->m_value = value.m_value;
		return *this;
	}

	auto value_t::operator = (bool value) -> value_t&
	{
		this->m_value = string::to_string<>(value);
		return *this;
	}

	auto value_t::operator = (int32_t value) -> value_t&
	{
		this->m_value = string::to_string<>(value);
		return *this;
	}

	auto value_t::operator = (uint32_t value) -> value_t&
	{
		this->m_value = string::to_string<>(value);
		return *this;
	}

	auto value_t::operator = (int64_t value) -> value_t&
	{
		this->m_value = string::to_string<>(value);
		return *this;
	}

	auto value_t::operator = (uint64_t value) -> value_t&
	{
		this->m_value = string::to_string<>(value);
		return *this;
	}

	auto value_t::operator = (float value) -> value_t&
	{
		this->m_value = string::to_string<>(value);
		return *this;
	}

	auto value_t::operator = (double value) -> value_t&
	{
		this->m_value = string::to_string<>(value);
		return *this;
	}

	auto value_t::operator = (const char* value) -> value_t&
	{
		this->m_value = value;
		return *this;
	}

	auto value_t::operator = (const string_t& value) -> value_t&
	{
		this->m_value = value;
		return *this;
	}

	auto value_t::operator == (const value_t& value) const -> bool
	{
		return this->m_value == value.m_value;
	}

	auto value_t::operator == (bool value) const -> bool
	{
		return string::from_string<bool>(this->m_value);
	}

	auto value_t::operator == (int32_t value) const -> bool
	{
		return (value == (decltype(value)(*this)));
	}

	auto value_t::operator == (uint32_t value) const -> bool
	{
		return (value == (decltype(value)(*this)));
	}

	auto value_t::operator == (int64_t value) const -> bool
	{
		return (value == (decltype(value)(*this)));
	}

	auto value_t::operator == (uint64_t value) const -> bool
	{
		return (value == (decltype(value)(*this)));
	}

	auto value_t::operator == (float value) const -> bool
	{
		return (value == (decltype(value)(*this)));
	}

	auto value_t::operator == (double value) const -> bool
	{
		return (value == (decltype(value)(*this)));
	}

	auto value_t::operator == (const char* value) const -> bool
	{
		return this->m_value == value;
	}

	auto value_t::operator == (const string_t& value) const -> bool
	{
		return this->m_value == value;
	}

	value_t::operator bool() const
	{
		return string::from_string<bool>(this->m_value);
	}

	value_t::operator int32_t() const
	{
		return string::from_string<int32_t>(this->m_value);
	}

	value_t::operator uint32_t() const
	{
		return string::from_string<uint32_t>(this->m_value);
	}

	value_t::operator int64_t() const
	{
		return string::from_string<int64_t>(this->m_value);
	}

	value_t::operator uint64_t() const
	{
		return string::from_string<uint64_t>(this->m_value);
	}

	value_t::operator float() const
	{
		return string::from_string<float>(this->m_value);
	}

	value_t::operator double() const
	{
		return string::from_string<double>(this->m_value);
	}

	value_t::operator const char* () const
	{
		return this->m_value.c_str();
	}

	value_t::operator const string_t& () const
	{
		return this->m_value;
	}
}

auto operator == (bool lhs, const wind::value_t& rhs) -> bool
{
	return (rhs == lhs);
}

auto operator == (int32_t lhs, const wind::value_t& rhs) -> bool
{
	return (rhs == lhs);
}

auto operator == (uint32_t lhs, const wind::value_t& rhs) -> bool
{
	return (rhs == lhs);
}

auto operator == (int64_t lhs, const wind::value_t& rhs) -> bool
{
	return (rhs == lhs);
}

auto operator == (uint64_t lhs, const wind::value_t& rhs) -> bool
{
	return (rhs == lhs);
}

auto operator == (float lhs, const wind::value_t& rhs) -> bool
{
	return (rhs == lhs);
}

auto operator == (double lhs, const wind::value_t& rhs) -> bool
{
	return (rhs == lhs);
}

auto operator == (const char* lhs, const wind::value_t& rhs) -> bool
{
	return (rhs == lhs);
}

auto operator == (const wind::string_t& lhs, const wind::value_t& rhs) -> bool
{
	return (rhs == lhs);
}