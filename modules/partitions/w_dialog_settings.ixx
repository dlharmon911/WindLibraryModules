export module wind:dialog.settings;

import :base;
import :string;
import :log;
import :dialog.constants;
import :timestamp;

namespace wind::dialog
{
	namespace settings
	{
		using namespace WIND::DIALOG::CONSTANTS;

		namespace display
		{
			export using option_t = struct option_tag_t
			{
				int32_t m_value{ 0 };
				int32_t m_importance{ 0 };
			};

			export using data_t = struct data_tag_t
			{
				std::unordered_map<int32_t, option_t> m_options{};
				int32_t m_flags{ DISPLAY::DEFAULT_FLAGS };
				int32_t m_width{ DISPLAY::DEFAULT_WIDTH };
				int32_t m_height{ DISPLAY::DEFAULT_HEIGHT };
			};
		}

		namespace timer
		{
			export using data_t = struct data_tag_t
			{
				double m_interval{ TIMER::DEFAULT_FPS };
			};
		}
	}

	export using settings_t = struct settings_tag_t
	{
		settings::timer::data_t m_timer_data{};
		settings::display::data_t m_display_data{};
	};
}