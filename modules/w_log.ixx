export module wind:log;

import <memory>;
import <string>;
import <cstdint>;
import allegro;
import :base;
import :string;

namespace WIND
{
	namespace LOG
	{
		namespace TYPE
		{
			enum
			{
				TEXT,
				HTML
			};
		}
	}
}

namespace wind
{
	namespace log
	{
		using data_t = struct data_tag_t
		{
			ALLEGRO::FILE m_file{};
			int32_t m_type{ WIND::LOG::TYPE::TEXT };
		};
	}

	export class log_t
	{
	public:
		log_t();
		log_t(const wind::string_t& filename, int32_t type = WIND::LOG::TYPE::TEXT);
		log_t(const log_t& log);
		~log_t();
		auto operator = (const log_t& log) -> log_t&;
		auto open(const wind::string_t& filename, int32_t type = WIND::LOG::TYPE::TEXT) -> void;
		auto close() -> void;
		auto is_open() const -> bool;
		auto operator<< (bool value) -> log_t&;
		auto operator<< (short value) -> log_t&;
		auto operator<< (unsigned short value) -> log_t&;
		auto operator<< (int value) -> log_t&;
		auto operator<< (unsigned int value) -> log_t&;
		auto operator<< (long value) -> log_t&;
		auto operator<< (unsigned long value) -> log_t&;
		auto operator<< (float value) -> log_t&;
		auto operator<< (double value) -> log_t&;
		auto operator<< (long double value) -> log_t&;
		auto putc(int32_t c) -> log_t&;
		auto puts(const wind::string_t& string) -> log_t&;
		auto write(const char* s, size_t n) -> log_t&;
		auto flush() -> log_t&;
	private:
		std::shared_ptr<log::data_t> m_data{};
	};

	auto endl(log_t& log)->log_t&;

}