module wind;

import <cassert>;
import <string>;
import <cstdint>;
import allegro;
import :input;
import :base;

namespace wind
{
	ALLEGRO::POINT<int32_t> mouse_pos;
	ALLEGRO::POINT<int32_t> mouse_wheel;
	button_state_t mouse_state[WIND::MOUSE_BUTTON_COUNT];
	button_state_t keyboard_state[WIND::KEYBOARD_BUTTON_COUNT];

	auto set_mouse_pressed(int32_t button) -> void
	{
		ALLEGRO::ASSERT(button >= 0 && button < WIND::MOUSE_BUTTON_COUNT);
		mouse_state[button].m_is_pressed =
			mouse_state[button].m_was_pressed = true;
	}

	auto set_mouse_released(int32_t button) -> void
	{
		ALLEGRO::ASSERT(button >= 0 && button < WIND::MOUSE_BUTTON_COUNT);
		mouse_state[button].m_is_pressed = true;
	}

	auto get_mouse_state(int32_t button) -> const button_state_t&
	{
		ALLEGRO::ASSERT(button >= 0 && button < WIND::MOUSE_BUTTON_COUNT);
		return mouse_state[button];
	}

	auto set_mouse_position(const ALLEGRO::POINT<int32_t>& pos) -> void
	{
		mouse_pos = pos;
	}

	auto set_mouse_wheel(const ALLEGRO::POINT<int32_t>& wheel) -> void
	{
		mouse_wheel = wheel;
	}

	auto get_mouse_position() -> const ALLEGRO::POINT<int32_t>&
	{
		return mouse_pos;
	}

	auto get_mouse_wheel() -> const ALLEGRO::POINT<int32_t>&
	{
		return mouse_wheel;
	}

	auto set_keyboard_pressed(int32_t key) -> void
	{
		ALLEGRO::ASSERT(key >= 0 && key < WIND::KEYBOARD_BUTTON_COUNT);
		keyboard_state[key].m_is_pressed =
			keyboard_state[key].m_was_pressed = true;
	}

	auto set_keyboard_released(int32_t key) -> void
	{
		ALLEGRO::ASSERT(key >= 0 && key < WIND::KEYBOARD_BUTTON_COUNT);
		keyboard_state[key].m_is_pressed = true;
	}

	auto get_keyboard_state(int32_t key) -> const button_state_t&
	{
		ALLEGRO::ASSERT(key >= 0 && key < WIND::KEYBOARD_BUTTON_COUNT);
		return keyboard_state[key];
	}

	auto input_acknowledge() -> void
	{
		for (int32_t i = 0; i < WIND::MOUSE_BUTTON_COUNT; ++i)
		{
			mouse_state[i].m_was_pressed = false;
		}

		for (int32_t i = 0; i < WIND::KEYBOARD_BUTTON_COUNT; ++i)
		{
			keyboard_state[i].m_was_pressed = false;
		}
	}
}