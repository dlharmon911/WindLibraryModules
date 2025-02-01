export module wind:input;

import <cstdint>;
import allegro;
import :base;

namespace WIND
{
	namespace MOUSE
	{
		export inline constexpr int32_t BUTTON_COUNT = 4;
	}

	namespace KEYBOARD
	{
		export inline constexpr int32_t BUTTON_COUNT = ALLEGRO::KEY_MAX;
	}
}

namespace wind
{
	namespace input
	{
		export using button_state_t = struct button_state_tag_t
		{
			bool m_is_pressed{ false };
			bool m_last_pressed{ false };
		};

		namespace mouse
		{
			export auto is_pressed(int32_t index) -> bool;
			export auto was_pressed(int32_t index) -> bool;
			export auto set_pressed(int32_t index) -> void;
			export auto was_released(int32_t index) -> bool;
			export auto set_released(int32_t index) -> void;
			export auto set_position(const ALLEGRO::POINT<int32_t>& position) -> void;
			export auto set_wheel(const ALLEGRO::POINT<int32_t>& position) -> void;
			export auto acknowledge(int32_t index) -> void;

			export auto get_state(int32_t index) -> const button_state_t&;
			export auto get_position() -> const ALLEGRO::POINT<int32_t>&;
			export auto get_wheel() -> const ALLEGRO::POINT<int32_t>&;
		}

		namespace keyboard
		{
			export auto is_pressed(int32_t index) -> bool;
			export auto was_pressed(int32_t index) -> bool;
			export auto set_pressed(int32_t index) -> void;
			export auto was_released(int32_t index) -> bool;
			export auto set_released(int32_t index) -> void;
			export auto get_state(int32_t index) -> const button_state_t&;
			export auto acknowledge(int32_t index) -> void;
		}

		export auto acknowledge() -> void;
	}
}