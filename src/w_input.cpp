module wind;

import <cassert>;
import <string>;
import <cstdint>;
import allegro;
import :input;
import :base;

namespace wind
{
	namespace input
	{
		namespace mouse
		{
			ALLEGRO::POINT<int32_t> m_position;
			ALLEGRO::POINT<int32_t> m_wheel;
			button_state_t m_state[WIND::MOUSE_BUTTON_COUNT];

			auto is_pressed(int32_t index) -> bool
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::MOUSE_BUTTON_COUNT);
				return m_state[index].m_is_pressed;
			}

			auto was_pressed(int32_t index) -> bool
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::MOUSE_BUTTON_COUNT);
				return m_state[index].m_was_pressed;
			}

			auto set_pressed(int32_t index) -> void
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::MOUSE_BUTTON_COUNT);
				m_state[index].m_is_pressed = true;
				m_state[index].m_was_pressed = true;
			}

			auto set_released(int32_t index) -> void
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::MOUSE_BUTTON_COUNT);
				m_state[index].m_is_pressed = false;
			}

			auto get_state(int32_t index) -> const button_state_t&
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::MOUSE_BUTTON_COUNT);
				return m_state[index];
			}

			auto set_position(const ALLEGRO::POINT<int32_t>& position) -> void
			{
				m_position = position;
			}

			auto set_wheel(const ALLEGRO::POINT<int32_t>& position) -> void
			{
				m_wheel = position;
			}

			auto get_position() -> const ALLEGRO::POINT<int32_t>&
			{
				return m_position;
			}

			auto get_wheel() -> const ALLEGRO::POINT<int32_t>&
			{
				return m_wheel;
			}

			auto acknowledge(int32_t index) -> void
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::MOUSE_BUTTON_COUNT);
				m_state[index].m_was_pressed = false;
			}
		}

		namespace keyboard
		{
			button_state_t m_state[WIND::KEYBOARD_BUTTON_COUNT];

			auto is_pressed(int32_t index) -> bool
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::KEYBOARD_BUTTON_COUNT);
				return m_state[index].m_is_pressed;
			}
			
			auto was_pressed(int32_t index) -> bool
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::KEYBOARD_BUTTON_COUNT);
				return m_state[index].m_was_pressed;
			}

			auto set_pressed(int32_t index) -> void
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::KEYBOARD_BUTTON_COUNT);
				m_state[index].m_is_pressed = true;
				m_state[index].m_was_pressed = true;
			}

			auto set_released(int32_t index) -> void
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::KEYBOARD_BUTTON_COUNT);
				m_state[index].m_is_pressed = false;
			}

			auto get_state(int32_t index) -> const button_state_t&
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::KEYBOARD_BUTTON_COUNT);
				return m_state[index];
			}

			auto acknowledge(int32_t index) -> void
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::KEYBOARD_BUTTON_COUNT);
				m_state[index].m_was_pressed = false;
			}
		}

		auto acknowledge() -> void
		{
			for (int32_t i = 0; i < WIND::MOUSE_BUTTON_COUNT; ++i)
			{
				mouse::m_state[i].m_was_pressed = false;
			}

			for (int32_t i = 0; i < WIND::KEYBOARD_BUTTON_COUNT; ++i)
			{
				keyboard::m_state[i].m_was_pressed = false;
			}
		}

	}
}