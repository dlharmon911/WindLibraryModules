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

	void set_mouse_pressed(int32_t button)
	{
		ALLEGRO::ASSERT(button >= 0 && button < WIND::MOUSE_BUTTON_COUNT);
		mouse_state[button].m_is_pressed =
		mouse_state[button].m_was_pressed = true;
	}

	void set_mouse_released(int32_t button)
	{
		ALLEGRO::ASSERT(button >= 0 && button < WIND::MOUSE_BUTTON_COUNT);
		mouse_state[button].m_is_pressed = true;
	}

	const button_state_t& get_mouse_state(int32_t button)
	{
		ALLEGRO::ASSERT(button >= 0 && button < WIND::MOUSE_BUTTON_COUNT);
		return mouse_state[button];
	}

	void set_mouse_position(const ALLEGRO::POINT<int32_t>& pos)
	{
		mouse_pos = pos;
	}

	void set_mouse_wheel(const ALLEGRO::POINT<int32_t>& wheel)
	{
		mouse_wheel = wheel;
	}

	const ALLEGRO::POINT<int32_t>& get_mouse_position()
	{
		return mouse_pos;
	}

	const ALLEGRO::POINT<int32_t>& get_mouse_wheel()
	{
		return mouse_wheel;
	}

	void set_keyboard_pressed(int32_t key)
	{
		ALLEGRO::ASSERT(key >= 0 && key < WIND::KEYBOARD_BUTTON_COUNT);
		keyboard_state[key].m_is_pressed =
		keyboard_state[key].m_was_pressed = true;
	}

	void set_keyboard_released(int32_t key)
	{
		ALLEGRO::ASSERT(key >= 0 && key < WIND::KEYBOARD_BUTTON_COUNT);
		keyboard_state[key].m_is_pressed = true;
	}

	const button_state_t& get_keyboard_state(int32_t key)
	{
		ALLEGRO::ASSERT(key >= 0 && key < WIND::KEYBOARD_BUTTON_COUNT);
		return keyboard_state[key];
	}

	void input_acknowledge()
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
