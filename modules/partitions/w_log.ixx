export module wind:log;

import <memory>;
import <string>;
import <cstdint>;
import allegro;
import :base;
import :string;

namespace WIND::LOG
{
	export enum class TYPE : int32_t
	{
		TEXT,
		HTML
	};
}

namespace wind
{
	export class log_t
	{
	public:
		log_t() = default;
		log_t(const wind::string_t& filename, WIND::LOG::TYPE type = WIND::LOG::TYPE::TEXT);
		log_t(const log_t& log) = default;
		~log_t() = default;
		auto operator = (const log_t& log)->log_t & = default;
		auto open(const wind::string_t& filename, WIND::LOG::TYPE type = WIND::LOG::TYPE::TEXT) -> void;
		auto reset() -> void;
		auto is_open() const -> bool;
		auto operator<< (auto (*manipulator)(log_t& log)->log_t&)->log_t&;
		auto operator<< (bool value)->log_t&;
		auto operator<< (short value)->log_t&;
		auto operator<< (unsigned short value)->log_t&;
		auto operator<< (int value)->log_t&;
		auto operator<< (unsigned int value)->log_t&;
		auto operator<< (long value)->log_t&;
		auto operator<< (unsigned long value)->log_t&;
		auto operator<< (float value)->log_t&;
		auto operator<< (double value)->log_t&;
		auto operator<< (long double value)->log_t&;
		auto operator<< (const char* string)->log_t&;
		auto operator<< (const wind::string_t& string)->log_t&;
		auto putc(int32_t c) -> log_t&;
		auto puts(const char* string) -> log_t&;
		auto puts(const wind::string_t& string) -> log_t&;
		auto write(const char* s, size_t n) -> log_t&;
		auto flush() -> log_t&;

	private:
		ALLEGRO::FILE m_file{};
		WIND::LOG::TYPE m_type{ WIND::LOG::TYPE::TEXT };
	};

	export auto endl(log_t& log) -> log_t&;

	export extern log_t lout;
}
