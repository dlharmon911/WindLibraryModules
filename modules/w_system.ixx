export module wind:system;

import <cstdint>;
import <vector>;
import <string>;
import <memory>;
import <ctime>;
import allegro;
import :dialog;
import :base;
import :string;
import :vector;

namespace WIND
{
	static constexpr double TICK_RATE = 0.001;
}

namespace wind
{
	export typedef struct time_info_t
	{
		double m_elapsed = 0.0;
		double m_last_updated = 0.0;
	} time_info_t;

	export class system_t : public class_t<system_t>
	{
	public:
		system_t(const std::shared_ptr<dialog_t>& dialog);
		~system_t();
		auto run(const vector_t<wind::string_t>& args) -> int32_t;

	private:
		auto init(const vector_t<wind::string_t>& args)->int32_t;
		auto shutdown() -> void;
		auto loop() -> void;

		std::shared_ptr<dialog_t> m_dialog{};
		ALLEGRO::DISPLAY m_display{nullptr};
		ALLEGRO::EVENT_QUEUE m_event_queue{ nullptr };
		ALLEGRO::TIMER m_timer{nullptr};
		time_info_t m_time_info{ 0.0, 0.0 };
		bool m_kill{ false };
	};

	namespace system
	{
		export inline auto timestamp() -> wind::string_t
		{
			char buffer[1024];
			struct tm local;
			__time64_t long_time;

			_time64(&long_time);

			errno_t err = _localtime64_s(&local, &long_time);
			if (err)
			{
				printf("Invalid argument to _localtime64_s.");
				exit(1);
			}

			sprintf_s<1024>(buffer,
				"%2d:%02d:%02d %s %2d/%02d/%4d",
				(local.tm_hour % 12 == 0 ? 12 : local.tm_hour % 12),
				local.tm_min,
				local.tm_sec,
				(local.tm_hour > 11 ? "p.m." : "a.m."),
				local.tm_mon + 1,
				local.tm_mday,
				1900 + local.tm_year);

			return string_t(buffer);
		}
	}
}

