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
		system_t(wind::add_const_reference_t<std::shared_ptr<dialog_t>> dialog);
		~system_t();
		auto run(wind::add_const_reference_t<vector_t<wind::string_t>> args) -> int32_t;

	private:
		auto init(wind::add_const_reference_t<vector_t<wind::string_t>> args)->int32_t;
		auto shutdown() -> void;
		auto loop() -> void;

		std::shared_ptr<dialog_t> m_dialog{};
		ALLEGRO::TIMER m_timer{nullptr};
		time_info_t m_time_info{ 0.0, 0.0 };
		bool m_kill{ false };
	};

	namespace system
	{
		export auto get_bitmap_buffer() -> wind::add_const_reference<ALLEGRO::BITMAP>::type;
		export auto get_display() -> wind::add_const_reference<ALLEGRO::DISPLAY>::type;
		export auto get_event_queue() -> wind::add_const_reference<ALLEGRO::EVENT_QUEUE>::type;
		export auto timestamp() -> wind::string_t;
	}
}

