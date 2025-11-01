export module wind:timestamp;

import :base;
import :string;

namespace wind::timestamp
{
	export auto get() -> string_t
	{
		struct tm local;
		__time64_t long_time;

		_time64(&long_time);

		errno_t err = _localtime64_s(&local, &long_time);
		if (err)
		{
			throw std::runtime_error("Failed to get local time.");
		}

		auto hour12 = (local.tm_hour % 12 == 0 ? 12 : local.tm_hour % 12);
		auto ampm = (local.tm_hour > 11 ? "p.m." : "a.m.");

		auto formatted = std::format("{:2}:{:02}:{:02} {} {:2}/{:02}/{:04}",
			hour12,
			local.tm_min,
			local.tm_sec,
			ampm,
			local.tm_mon + 1,
			local.tm_mday,
			1900 + local.tm_year);

		return string_t(formatted);
	}
}
