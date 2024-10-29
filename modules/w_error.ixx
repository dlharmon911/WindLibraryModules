export module wind:error;

import <cstdint>;
import :base;
import :string;

namespace wind
{
	export class error_t
	{
	public:
		error_t();
		error_t(const string_t& message, const string_t& filename = string_t(), int32_t line = 0, const string_t& function = string_t());
		error_t(const error_t& error);
		~error_t();
		error_t& operator = (const error_t& error);

		const string_t& get_message() const;
		void set_message(const string_t& message);
		const string_t& get_filename() const;
		void set_filename(const string_t& filename);
		int32_t get_line() const;
		void set_line(int32_t line);
		const string_t& get_function() const;
		void set_function(const string_t& function);

	private:
		string_t m_message{};
		string_t m_filename{};
		int32_t m_line{ 0 };
		string_t m_function{};
	};

	namespace error
	{
		export void clear();
		export void push(const string_t& message, const string_t& filename = string_t(), int32_t line = 0, const string_t& function = string_t());
		export void push(const error_t& error);
		export const error_t peek();
		export void pop();
		export size_t count();
	}
}
