export module wind:error;

import <cstdint>;
import <source_location>;
import <string_view>;
import :base;
import :log;
import :string;

namespace wind
{
	namespace error
	{
		export auto report_error(const string_t& message, std::source_location location = std::source_location::current()) -> void;
	}

	export class error_t
	{
	public:
		error_t();
		error_t(const string_t& message, const string_t& filename = string_t(), int32_t line = 0, const string_t& function = string_t());
		error_t(const error_t& error);
		~error_t();
		auto operator = (const error_t& error)->error_t&;

		auto get_message() const -> const string_t&;
		auto set_message(const string_t& message) -> void;
		auto get_filename() const -> const string_t&;
		auto set_filename(const string_t& filename) -> void;
		auto get_line() const->int32_t;
		auto set_line(int32_t line) -> void;
		auto get_function() const -> const string_t&;
		auto set_function(const string_t& function) -> void;

	private:
		string_t m_message{};
		string_t m_filename{};
		int32_t m_line{ 0 };
		string_t m_function{};
	};

	namespace error
	{
		export auto clear() -> void;
		export auto push(const string_t& message, const string_t& filename = string_t(), int32_t line = 0, const string_t& function = string_t()) -> void;
		export auto push(const error_t& error) -> void;
		export auto peek() -> const error_t;
		export auto pop() -> void;
		export auto count() -> size_t;
	}
}