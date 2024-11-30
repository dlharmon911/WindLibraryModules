module wind;

import <vector>;
import <cstdint>;
import :base;
import :error;
import :string;

namespace wind
{
	error_t::error_t() : m_message(), m_filename(), m_line(0), m_function() {}

	error_t::error_t(const string_t& message, const string_t& filename, int32_t line, const string_t& function) : m_message(message), m_filename(filename), m_line(line), m_function(function) {}

	error_t::error_t(const error_t& error) : m_message(error.m_message), m_filename(error.m_filename), m_line(error.m_line), m_function(error.m_function) {}

	error_t::~error_t() {}

	auto error_t::operator = (const error_t& error) -> error_t&
	{
		this->m_message = error.m_message;
		this->m_filename = error.m_filename;
		this->m_line = error.m_line;
		this->m_function = error.m_function;

		return *this;
	}

	auto error_t::get_message() const -> const string_t&
	{
		return this->m_message;
	}

	auto error_t::set_message(const string_t& message) -> void
	{
		this->m_message = message;
	}

	auto error_t::get_filename() const -> const string_t&
	{
		return this->m_filename;
	}

	auto error_t::set_filename(const string_t& filename) -> void
	{
		this->m_filename = filename;
	}

	auto error_t::get_line() const -> int32_t
	{
		return this->m_line;
	}

	auto error_t::set_line(int32_t line) -> void
	{
		this->m_line = line;
	}

	auto error_t::get_function() const -> const string_t&
	{
		return this->m_function;
	}

	auto error_t::set_function(const string_t& function) -> void
	{
		this->m_function = function;
	}

	namespace error
	{
		std::vector<error_t> error_list;

		auto clear() -> void
		{
			error_list.clear();
		}

		auto push(const string_t& message, const string_t& filename, int32_t line, const string_t& function) -> void
		{
			error_list.push_back(error_t(message, filename, line, function));
		}

		auto push(const error_t& error) -> void
		{
			error_list.push_back(error);
		}

		auto peek() -> const error_t
		{
			return error_list.back();
		}

		auto pop() -> void
		{
			error_list.pop_back();
		}

		auto count() -> size_t
		{
			return error_list.size();
		}
	}
}