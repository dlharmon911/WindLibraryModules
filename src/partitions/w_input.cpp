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
			ALLEGRO::VECTOR_2D<int32_t> m_position;
			ALLEGRO::VECTOR_2D<int32_t> m_wheel;
			button_state_t m_state[WIND::MOUSE::BUTTON_COUNT];

			auto is_pressed(int32_t index) -> bool
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::MOUSE::BUTTON_COUNT);
				return m_state[index].m_is_pressed;
			}

			auto was_pressed(int32_t index) -> bool
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::MOUSE::BUTTON_COUNT);
				return m_state[index].m_is_pressed && !m_state[index].m_last_pressed;
			}

			auto was_released(int32_t index) -> bool
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::MOUSE::BUTTON_COUNT);
				return !m_state[index].m_is_pressed && m_state[index].m_last_pressed;
			}

			auto set_pressed(int32_t index) -> void
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::MOUSE::BUTTON_COUNT);
				m_state[index].m_is_pressed = true;
			}

			auto set_released(int32_t index) -> void
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::MOUSE::BUTTON_COUNT);
				m_state[index].m_is_pressed = false;
			}

			auto get_state(int32_t index) -> const button_state_t&
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::MOUSE::BUTTON_COUNT);
				return m_state[index];
			}

			auto acknowledge(int32_t index) -> void
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::MOUSE::BUTTON_COUNT);
				m_state[index].m_last_pressed = m_state[index].m_is_pressed;
			}

			auto set_position(const ALLEGRO::VECTOR_2D<int32_t>& position) -> void
			{
				m_position = position;
			}

			auto set_wheel(const ALLEGRO::VECTOR_2D<int32_t>& position) -> void
			{
				m_wheel = position;
			}

			auto get_position() -> const ALLEGRO::VECTOR_2D<int32_t>&
			{
				return m_position;
			}

			auto get_wheel() -> const ALLEGRO::VECTOR_2D<int32_t>&
			{
				return m_wheel;
			}
		}

		namespace keyboard
		{
			button_state_t m_state[WIND::KEYBOARD::BUTTON_COUNT];

			auto is_pressed(int32_t index) -> bool
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::KEYBOARD::BUTTON_COUNT);
				return m_state[index].m_is_pressed;
			}

			auto was_pressed(int32_t index) -> bool
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::KEYBOARD::BUTTON_COUNT);
				return m_state[index].m_is_pressed && !m_state[index].m_last_pressed;
			}

			auto was_released(int32_t index) -> bool
			{
				return !m_state[index].m_is_pressed && m_state[index].m_last_pressed;
			}

			auto set_pressed(int32_t index) -> void
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::KEYBOARD::BUTTON_COUNT);
				m_state[index].m_is_pressed = true;
			}

			auto set_released(int32_t index) -> void
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::KEYBOARD::BUTTON_COUNT);
				m_state[index].m_is_pressed = false;
			}

			auto get_state(int32_t index) -> const button_state_t&
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::KEYBOARD::BUTTON_COUNT);
				return m_state[index];
			}

			auto acknowledge(int32_t index) -> void
			{
				ALLEGRO::ASSERT(index >= 0 && index < WIND::KEYBOARD::BUTTON_COUNT);
				m_state[index].m_last_pressed = m_state[index].m_is_pressed;
			}
		}

		auto acknowledge() -> void
		{
			for (int32_t index = 0; index < WIND::MOUSE::BUTTON_COUNT; ++index)
			{
				mouse::m_state[index].m_last_pressed = mouse::m_state[index].m_is_pressed;
			}

			for (int32_t index = 0; index < WIND::KEYBOARD::BUTTON_COUNT; ++index)
			{
				keyboard::m_state[index].m_last_pressed = keyboard::m_state[index].m_is_pressed;
			}
		}
	}
}
