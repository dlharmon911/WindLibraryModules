export module wind:dialog;

import <cstdint>;
import <vector>;
import <memory>;
import allegro;
import :base;
import :string;
import :vector;

namespace wind
{
	export class dialog_t : public class_t<dialog_t>
	{
	public:
		dialog_t() {}
		virtual ~dialog_t() {}

		virtual auto get_version() const -> int32_t = 0;
		virtual auto get_title() const -> const wind::string_t& = 0;

		virtual auto on_initialize(const wind::vector_t<wind::string_t>& args) -> int32_t = 0;
		virtual auto on_shutdown() -> int32_t = 0;
		virtual auto on_start() -> int32_t = 0;
		virtual auto on_stop() -> int32_t = 0;
		virtual auto on_update(int32_t tick_count) -> int32_t = 0;
		virtual auto on_render(ALLEGRO::DISPLAY& display) -> int32_t = 0;

		virtual auto on_joystick_axis(const ALLEGRO::EVENT& event) -> bool { return false; }
		virtual auto on_joystick_button_down(const ALLEGRO::EVENT& event) -> bool { return false; }
		virtual auto on_joystick_button_up(const ALLEGRO::EVENT& event) -> bool { return false; }
		virtual auto on_joystick_configuration(const ALLEGRO::EVENT& event) -> bool { return false; }
		virtual auto on_key_down(const ALLEGRO::EVENT& event) -> bool { return false; }
		virtual auto on_key_up(const ALLEGRO::EVENT& event) -> bool { return false; }
		virtual auto on_key_char(const ALLEGRO::EVENT& event) -> bool { return false; }
		virtual auto on_mouse_click(const ALLEGRO::EVENT& event) -> bool { return false; }
		virtual auto on_mouse_axes(const ALLEGRO::EVENT& event) -> bool { return false; }
		virtual auto on_mouse_button_down(const ALLEGRO::EVENT& event) -> bool { return false; }
		virtual auto on_mouse_button_up(const ALLEGRO::EVENT& event) -> bool { return false; }
		virtual auto on_mouse_grab(const ALLEGRO::EVENT& event) -> bool { return false; }
		virtual auto on_mouse_drag(const ALLEGRO::EVENT& event) -> bool { return false; }
		virtual auto on_mouse_enter_display(const ALLEGRO::EVENT& event) -> bool { return false; }
		virtual auto on_mouse_leave_display(const ALLEGRO::EVENT& event) -> bool { return false; }
		virtual auto on_mouse_warped(const ALLEGRO::EVENT& event) -> bool { return false; }
		virtual auto on_display_resize(const ALLEGRO::EVENT& event) -> bool { return false; }
		virtual auto on_display_close(const ALLEGRO::EVENT& event) -> bool { return false; }
		virtual auto on_display_lost(const ALLEGRO::EVENT& event) -> bool { return false; }
		virtual auto on_display_found(const ALLEGRO::EVENT& event) -> bool { return false; }
		virtual auto on_display_switch_in(const ALLEGRO::EVENT& event) -> bool { return false; }
		virtual auto on_display_switch_out(const ALLEGRO::EVENT& event) -> bool { return false; }
	};
}

