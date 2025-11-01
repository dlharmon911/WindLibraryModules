export module wind:input.constants;

import :base;

namespace WIND::INPUT
{
	namespace BUTTON
	{
		export constexpr uint8_t DEFAULT{ 0 };
		export constexpr uint8_t PRESSED{ 0x01 };
		export constexpr uint8_t CHANGED{ 0x02 };
	}

	namespace KEY
	{
		export constexpr int32_t MAX{ ALLEGRO::KEY_MAX };
	}

	namespace MOUSE
	{
		export constexpr int32_t MAX{ ALLEGRO::MOUSE_BUTTON_MIDDLE };
	}
}
