module wind;

import <memory>;
import <string>;
import <cstdint>;
import allegro;
import :base;
import :string;
import :log;
import :file;

namespace wind
{
	namespace log
	{
		void destroy(shared_data_t* log_struct)
		{
			if (log_struct)
			{
				if (log_struct->m_file)
				{
					if (log_struct->m_type == WIND::LOG::TYPE::HTML)
					{
						log_struct->m_file << "</span></pre>\n"
							<< "</body>\n"
							<< "</html>\n";
					}
					log_struct->m_file.reset();
				}

				delete log_struct;
			}
		}

		std::shared_ptr<shared_data_t> create(const wind::string_t& filename, int32_t type)
		{
			std::shared_ptr<shared_data_t> rv(new shared_data_t, destroy);

			if (rv)
			{
				rv->m_file = al::fopen(filename.c_str(), "wb");
				rv->m_type = type;
				if (rv->m_file)
				{
					if (type == WIND::LOG::TYPE::HTML)
					{
						rv->m_file << "<html>\n"
							<< "<head>\n"
							<< "<title>LogFile</title>\n"
							<< "<meta name=\"generator\" content=\"log 1.0\" />\n"
							<< "<meta name=\"author\" content=\"Daniel Harmon\" />\n"
							<< "<meta name=\"keywords\" content=\"?\" />\n"
							<< "<meta name=\"description\" content=\"Wind log file\" />\n"
							<< "</head>\n"
							<< "<body>\n"
							<< "<pre style=\"font-size:120%\"><span style=\"color:#000000\">\n";
					}
				}
				else
				{
					rv.reset();
				}
			}

			return rv;
		}

		template<typename T> auto write(const ALLEGRO::FILE &file, const T& value) -> void
		{
			if (file)
			{
				al::fputs(file, string_t(std::to_string(value)).c_str());
			}
		}

		template<> auto write(const ALLEGRO::FILE& file, const bool& value) -> void
		{
			if (file)
			{
				al::fputs(file, (value ? "true" : "false"));
			}
		}
	}

	log_t::log_t() : m_data()
	{
	}

	log_t::log_t(const wind::string_t& filename, int32_t type) : m_data(log::create(filename, type))
	{
	}

	log_t::log_t(const log_t& log) : m_data(log.m_data)
	{
	}

	log_t::~log_t()
	{
	}

	auto log_t::operator = (const log_t& log)->log_t&
	{
		this->m_data = log.m_data;

		return *this;
	}

	auto log_t::open(const wind::string_t& filename, int32_t type) -> void
	{
		this->m_data = log::create(filename, type);
	}

	auto log_t::reset() -> void
	{
		this->m_data.reset();
	}

	auto log_t::is_open() const -> bool
	{
		return (this->m_data && this->m_data->m_file);
	}

	auto log_t::operator<< (auto (*manipulator)(log_t& log)->log_t&)->log_t&
	{
		return manipulator(*this);
	}

	auto log_t::operator<< (bool value)->log_t&
	{
		if (this->m_data)
		{
			log::write<bool>(this->m_data->m_file, value);
		}
		return *this;
	}

	auto log_t::operator<< (short value)->log_t&
	{
		if (this->m_data)
		{
			log::write<short>(this->m_data->m_file, value);
		}
		return *this;
	}

	auto log_t::operator<< (unsigned short value)->log_t&
	{
		if (this->m_data)
		{
			log::write<unsigned short>(this->m_data->m_file, value);
		}
		return *this;
	}

	auto log_t::operator<< (int value)->log_t&
	{
		if (this->m_data)
		{
			log::write<int>(this->m_data->m_file, value);
		}
		return *this;
	}

	auto log_t::operator<< (unsigned int value)->log_t&
	{
		if (this->m_data)
		{
			log::write<unsigned int>(this->m_data->m_file, value);
		}
		return *this;
	}

	auto log_t::operator<< (long value)->log_t&
	{
		if (this->m_data)
		{
			log::write<long>(this->m_data->m_file, value);
		}
		return *this;
	}

	auto log_t::operator<< (unsigned long value)->log_t&
	{
		if (this->m_data)
		{
			log::write<unsigned long>(this->m_data->m_file, value);
		}
		return *this;
	}

	auto log_t::operator<< (float value)->log_t&
	{
		if (this->m_data)
		{
			log::write<float>(this->m_data->m_file, value);
		}
		return *this;
	}

	auto log_t::operator<< (double value)->log_t&
	{
		if (this->m_data)
		{
			log::write<double>(this->m_data->m_file, value);
		}
		return *this;
	}

	auto log_t::operator<< (const char* string)->log_t&
	{
		return this->puts(string);
	}

	auto log_t::operator<< (const wind::string_t& string)->log_t&
	{
		return this->puts(string);
	}

	auto log_t::operator<< (long double value)->log_t&
	{
		log::write(this->m_data->m_file, value);
		return *this;
	}

	auto log_t::putc(int32_t c) -> log_t&
	{
		if (this->m_data && this->m_data->m_file)
		{
			al::fputc(this->m_data->m_file, c);
		}
		return *this;
	}

	auto log_t::puts(const char* string) -> log_t&
	{
		if (this->m_data && this->m_data->m_file)
		{
			if (string)
			{
				const char* c = string;
				while (*c)
				{
					al::fputc(this->m_data->m_file, *c);
					++c;
				}
			}
			else
			{
				al::fputs(this->m_data->m_file, "<null>");
			}
		}

		return *this;
	}

	auto log_t::puts(const wind::string_t& string) -> log_t&
	{
		if (this->m_data && this->m_data->m_file)
		{
			al::fputs(this->m_data->m_file, string.c_str());
		}
		return *this;
	}

	auto log_t::write(const char* s, size_t n) -> log_t&
	{
		if (this->m_data && this->m_data->m_file)
		{
			al::fwrite(this->m_data->m_file, s, n);
		}
		return *this;
	}

	auto log_t::flush() -> log_t&
	{
		if (this->m_data && this->m_data->m_file)
		{
			al::fflush(this->m_data->m_file);
		}
		return *this;
	}

	auto endl(log_t& log) -> log_t&
	{
		log.putc('\n');
		log.flush();
		return log;
	}
}