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
	export using button_state_t = struct button_state_tag_t
	{
		bool m_is_pressed{ false };
		bool m_was_pressed{ false };
	};

	export auto set_mouse_pressed(int32_t button) -> void;
	export auto set_mouse_released(int32_t button) -> void;
	export auto set_mouse_position(const ALLEGRO::POINT<int32_t>& pos) -> void;
	export auto set_mouse_wheel(const ALLEGRO::POINT<int32_t>& pos) -> void;

	export auto get_mouse_state(int32_t button) -> const button_state_t&;
	export auto get_mouse_position() -> const ALLEGRO::POINT<int32_t>&;
	export auto get_mouse_wheel() -> const ALLEGRO::POINT<int32_t>&;

	export auto set_keyboard_pressed(int32_t key) -> void;
	export auto set_keyboard_released(int32_t key) -> void;
	export auto get_keyboard_state(int32_t key) -> const button_state_t&;

	export auto input_acknowledge() -> void;
}