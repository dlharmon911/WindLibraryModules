export module wind:input;

import <cstdint>;
import allegro;
import :base;

namespace WIND
{
	export inline constexpr int32_t MOUSE_BUTTON_COUNT = 8;
	export inline constexpr int32_t KEYBOARD_BUTTON_COUNT = ALLEGRO::KEY_MAX;
}

namespace wind
{
	export typedef struct button_state_t
	{
		bool m_is_pressed;
		bool m_was_pressed;
	} button_state_t;

	export void set_mouse_pressed(int32_t button);
	export void set_mouse_released(int32_t button);
	export void set_mouse_position(ALLEGRO::POINT<int32_t> pos);
	export void set_mouse_wheel(ALLEGRO::POINT<int32_t> pos);

	export const button_state_t& get_mouse_state(int32_t button);
	export const ALLEGRO::POINT<int32_t>& get_mouse_position();
	export const ALLEGRO::POINT<int32_t>& get_mouse_wheel();


	export void set_keyboard_pressed(int32_t key);
	export void set_keyboard_released(int32_t key);
	export const button_state_t& get_keyboard_state(int32_t key);

	export void input_acknowledge();
}

