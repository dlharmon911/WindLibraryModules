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

	error_t& error_t::operator = (const error_t& error)
	{
		this->m_message = error.m_message;
		this->m_filename = error.m_filename;
		this->m_line = error.m_line;
		this->m_function = error.m_function;

		return *this;

	}

	const string_t& error_t::get_message() const
	{
		return this->m_message;
	}

	void error_t::set_message(const string_t& message)
	{
		this->m_message = message;
	}

	const string_t& error_t::get_filename() const
	{
		return this->m_filename;
	}

	void error_t::set_filename(const string_t& filename)
	{
		this->m_filename = filename;
	}

	int32_t error_t::get_line() const
	{
		return this->m_line;
	}

	void error_t::set_line(int32_t line)
	{
		this->m_line = line;
	}

	const string_t& error_t::get_function() const
	{
		return this->m_function;
	}

	void error_t::set_function(const string_t& function)
	{
		this->m_function = function;
	}

	namespace error
	{
		std::vector<error_t> error_list;

		void clear()
		{
			error_list.clear();
		}

		void push(const string_t& message, const string_t& filename, int32_t line, const string_t& function)
		{
			error_list.push_back(error_t(message, filename, line, function));
		}

		void push(const error_t& error)
		{
			error_list.push_back(error);
		}

		const error_t peek()
		{
			return error_list.back();
		}

		void pop()
		{
			error_list.pop_back();
		}

		size_t count()
		{
			return error_list.size();
		}
	}
}
