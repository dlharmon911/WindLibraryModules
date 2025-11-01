export module wind:log;

import <cstdarg>;
import :base;
import :string;

namespace WIND::LOG
{
	static const wind::string_t TRUE_STRING{ "true" };
	static const wind::string_t FALSE_STRING{ "false" };
	static const char ENDL_CHAR{ '\n' };
}

namespace wind
{
	export class log_t
	{
	public:
		log_t() = default;
		log_t(const log_t& log) = default;
		~log_t() = default;
		auto operator = (const log_t& log)->log_t & = default;

		auto open(const string_t& filename) -> void
		{
			this->m_file = al::fopen(filename.c_str(), "wb");
		}

		auto is_open() const -> bool
		{
			return static_cast<bool>(this->m_file);
		}

		auto close()
		{
			if (this->m_file)
			{
				this->m_file.reset();
			}
		}

		auto flush() -> void
		{
			if (!this->m_file)
			{
				return;
			}

			al::fflush(this->m_file);
		}

		auto eof() const -> bool
		{
			if (!this->m_file)
			{
				return true;
			}

			return al::feof(this->m_file);
		}

		auto putc(int32_t c) -> int32_t
		{
			if (!this->m_file)
			{
				return ALLEGRO::FILE_EOF;
			}

			return al::fputc(this->m_file, c);
		}

		auto write(const char* data, size_t length) -> int32_t
		{
			if (!this->m_file)
			{
				return ALLEGRO::FILE_EOF;
			}

			if (!data)
			{
				return 0;
			}

			if (!length)
			{
				return 0;
			}

			if (length != al::fwrite(this->m_file, data, length))
			{
				return ALLEGRO::FILE_EOF;
			}

			return static_cast<int32_t>(length);
		}

		template <typename iterator> auto write(iterator begin, iterator end) -> int32_t
		{
			iterator temp{ begin };
			size_t size{ 0 };
			while (temp != end)
			{
				++temp;
				++size;
			}

			return this->write(&(*begin), size);
		}

		auto writeln(const string_t& string) -> int32_t
		{
			if (string.size() == 0)
			{
				return 0;
			}

			int32_t size = this->write(string.cbegin(), string.cend());

			if (size < 0)
			{
				return size;
			}

			if (this->putc(WIND::LOG::ENDL_CHAR) < 0)
			{
				return ALLEGRO::FILE_EOF;
			}

			return 1 + size;
		}

		auto writef(const char* const format, va_list args) -> int32_t
		{
			int32_t rv{ ALLEGRO::FILE_EOF };

			if (!format)
			{
				return 0;
			}

			ALLEGRO::USTRING ustr{ al::ustr_dup(al::ustr_empty_string()) };

			if (!ustr)
			{
				return 0;
			}

			bool success{ al::ustr_vappendf(ustr, format, args) };

			if (success)
			{
				size_t size = al::ustr_size(ustr);

				if (size > 0)
				{
					rv = this->write(al::c_str(ustr), size);

					if (rv != static_cast<int32_t>(size))
					{
						rv = ALLEGRO::FILE_EOF;
					}
				}
			}

			ustr.reset();

			return rv;
		}

		// Remove the ellipsis notation and provide a type-safe variadic alternative using variadic templates.
		template <typename... Args> auto writef(const char* const format, Args&&... args) -> int32_t
		{
			if (!format)
			{
				return 0;
			}

			int32_t rv{ -1 };

			// Use std::snprintf to format the string into a buffer
			constexpr size_t BUFFER_SIZE{ 1024 };
			std::array<char, BUFFER_SIZE> buffer{};

			int written = std::snprintf(buffer.data(), buffer.size(), format, std::forward<Args>(args)...);
			if (written < 0)
			{
				return rv;
			}

			// Clamp to buffer size
			auto size{ static_cast<size_t>(written) };
			if (size >= BUFFER_SIZE)
			{
				size = BUFFER_SIZE - 1;
			}

			rv = this->write(buffer.data(), size);

			if (rv != static_cast<int32_t>(size))
			{
				rv = -1;
			}

			return rv;
		}

		auto write(const string_t& value) -> int32_t
		{
			if (value.size() == 0)
			{
				return 0;
			}

			return this->write(value.cbegin(), value.cend());
		}

		auto write(const char* string) -> int32_t
		{
			if (!string)
			{
				return 0;
			}

			size_t size = std::strlen(string);
			return this->write(string, size);
		}

		friend auto operator << (wind::log_t& log, const std::function<auto (wind::log_t& log)->wind::log_t&>& manipulator)->wind::log_t&
		{
			return manipulator(log);
		}

		template <typename T> friend auto operator<< (wind::log_t& log, const T& value)->wind::log_t& requires std::is_arithmetic_v<T>
		{
			log.write(std::to_string(value));
			return log;
		}

		friend auto operator << (wind::log_t& log, const wind::string_t& value)->wind::log_t&
		{
			log.write(value);
			return log;
		}

		friend auto operator << (wind::log_t& log, const bool& value)->wind::log_t&
		{
			if (value)
			{
				log.write(WIND::LOG::TRUE_STRING);
			}
			else
			{
				log.write(WIND::LOG::FALSE_STRING);
			}

			return log;
		}

		friend auto operator << (wind::log_t& log, const char* value)->wind::log_t&
		{
			log.write(value);
			return log;
		}

	private:
		ALLEGRO::FILE m_file{};
	};

	export auto endl(log_t& log) -> log_t&
	{
		log.putc(WIND::LOG::ENDL_CHAR);
		log.flush();
		return log;
	}

	export inline log_t lout{};
}






