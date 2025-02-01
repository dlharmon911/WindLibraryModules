export module wind:dialog;

import <cstdint>;
import <vector>;
import <memory>;
import allegro;
import :base;
import :string;
import :array;
import :dialog.widget;
import :dialog.base;

namespace wind
{
	export class dialog_t : public dialog::base_t<wind::dialog::widget_t>
	{
	public:
		dialog_t() = default;
		virtual ~dialog_t() = default;

		virtual auto get_version() const->int32_t = 0;
		virtual auto get_title() const->wind::add_const_reference_t<wind::string_t> = 0;

		virtual auto on_initialize(const wind::array_t<wind::string_t>& args) -> int32_t = 0;
		virtual auto on_shutdown() -> int32_t = 0;
		virtual auto on_start() -> int32_t = 0;
		virtual auto on_stop() -> int32_t = 0;
		virtual auto on_update() -> int32_t = 0;
		virtual auto on_render() -> int32_t = 0;

		virtual auto on_joystick_axis(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_joystick_button_down(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_joystick_button_up(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_joystick_configuration(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_key_down(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_key_up(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_key_char(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_mouse_click(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_mouse_axes(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_mouse_button_down(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_mouse_button_up(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_mouse_grab(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_mouse_drag(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_mouse_enter(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_mouse_leave(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_mouse_warped(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_display_resize(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_display_close(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_display_lost(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_display_found(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_display_switch_in(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_display_switch_out(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }

	protected:
	};
}