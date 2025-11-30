export module wind:dialog.system.data;

import :base;
import :string;
import :log;
import :dialog.constants;
import :dialog.settings;
import :timestamp;
import :input;

namespace wind::dialog::system
{
	namespace data
	{
		namespace timer
		{
			export using data_t = struct data_tag_t
			{
				bool m_paused{ false };
				uint64_t m_tick_count{ 0 };
			};
		}
	}

	export using data_t = struct data_tag_t
	{
		ALLEGRO::TIMER m_timer_object{ nullptr };
		ALLEGRO::DISPLAY m_display_object{ nullptr };
		ALLEGRO::EVENT_QUEUE m_event_queue_object{ nullptr };
		settings_t m_settings_data{};
		input_t m_input_data{};
		data::timer::data_t m_timer_data{};
		bool m_kill{ false };
	};
}
