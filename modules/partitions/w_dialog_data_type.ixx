export module wind:dialog.data.type;

import :base;
import :string;
import :log;
import :dialog.constants;
import :timestamp;
import :input;

namespace wind::dialog
{
	using namespace WIND::DIALOG::CONSTANTS;

	namespace display
	{
		export using option_t = struct option_tag_t
		{
			int32_t m_value{ 0 };
			int32_t m_importance{ 0 };
		};

		using data_t = struct data_tag_t
		{
			std::map<int32_t, option_t> m_options{};
			ALLEGRO::DISPLAY m_object{ nullptr };
			int32_t m_flags{ DISPLAY::DEFAULT_FLAGS };
			int32_t m_width{ DISPLAY::DEFAULT_WIDTH };
			int32_t m_height{ DISPLAY::DEFAULT_HEIGHT };
		};
	}

	namespace timer
	{
		using data_t = struct data_tag_t
		{
			ALLEGRO::TIMER m_object{ nullptr };
			double m_interval{ TIMER::DEFAULT_FPS };
			bool m_paused{ false };
			uint64_t m_tick_count{ 0 };
		};
	}

	namespace event_queue
	{
		using data_t = struct data_tag_t
		{
			ALLEGRO::EVENT_QUEUE m_object{ nullptr };
		};
	}

	export using data_t = struct data_tag_t
	{
		timer::data_t m_timer{ nullptr };
		display::data_t m_display{};
		event_queue::data_t m_event_queue{};
		input_t m_input{};
		bool m_kill{ false };
	};
}
