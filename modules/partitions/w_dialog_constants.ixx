export module wind:dialog.constants;

import :base;
import :string;

namespace ALLEGRO
{
	export constexpr int32_t EVENT_TYPE_MOUSE_BUTTON_CLICK{ 1024 };
}

namespace WIND::DIALOG::CONSTANTS
{
	export const wind::string_t DEFAULT_TITLE{ "Wind Dialog Application" };
	export constexpr uint32_t DEFAULT_VERSION_INT{ 0x00010000 };

	namespace TIMER
	{
		export constexpr double DEFAULT_FPS{ 60.0 };
	}

	namespace DISPLAY
	{
		export constexpr int32_t DEFAULT_WIDTH{ 800 };
		export constexpr int32_t DEFAULT_HEIGHT{ 600 };
		export constexpr int32_t DEFAULT_FLAGS{ ALLEGRO::DISPLAY_FLAG_WINDOWED | ALLEGRO::DISPLAY_FLAG_RESIZABLE };
	}
}

