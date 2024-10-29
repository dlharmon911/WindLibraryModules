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
	export class dialog_t
	{
	public:
		dialog_t() {}
		virtual ~dialog_t() {}

		virtual int32_t get_version() const = 0;
		virtual const wind::string_t& get_title() const = 0;

		virtual int32_t on_initialize(const wind::vector_t<wind::string_t>& args) = 0;
		virtual int32_t on_shutdown() = 0;
		virtual int32_t on_start() = 0;
		virtual int32_t on_stop() = 0;
		virtual int32_t on_update(int32_t tick_count) = 0;
		virtual int32_t on_render(ALLEGRO::DISPLAY& display) = 0;

		virtual bool on_joystick_axis(const ALLEGRO::EVENT& event) { return false; }
		virtual bool on_joystick_button_down(const ALLEGRO::EVENT& event) { return false; }
		virtual bool on_joystick_button_up(const ALLEGRO::EVENT& event) { return false; }
		virtual bool on_joystick_configuration(const ALLEGRO::EVENT& event) { return false; }
		virtual bool on_key_down(const ALLEGRO::EVENT& event) { return false; }
		virtual bool on_key_up(const ALLEGRO::EVENT& event) { return false; }
		virtual bool on_key_char(const ALLEGRO::EVENT& event) { return false; }
		virtual bool on_mouse_click(const ALLEGRO::EVENT& event) { return false; }
		virtual bool on_mouse_axes(const ALLEGRO::EVENT& event) { return false; }
		virtual bool on_mouse_button_down(const ALLEGRO::EVENT& event) { return false; }
		virtual bool on_mouse_button_up(const ALLEGRO::EVENT& event) { return false; }
		virtual bool on_mouse_grab(const ALLEGRO::EVENT& event) { return false; }
		virtual bool on_mouse_drag(const ALLEGRO::EVENT& event) { return false; }
		virtual bool on_mouse_enter_display(const ALLEGRO::EVENT& event) { return false; }
		virtual bool on_mouse_leave_display(const ALLEGRO::EVENT& event) { return false; }
		virtual bool on_mouse_warped(const ALLEGRO::EVENT& event) { return false; }
		virtual bool on_display_resize(const ALLEGRO::EVENT& event) { return false; }
		virtual bool on_display_close(const ALLEGRO::EVENT& event) { return false; }
		virtual bool on_display_lost(const ALLEGRO::EVENT& event) { return false; }
		virtual bool on_display_found(const ALLEGRO::EVENT& event) { return false; }
		virtual bool on_display_switch_in(const ALLEGRO::EVENT& event) { return false; }
		virtual bool on_display_switch_out(const ALLEGRO::EVENT& event) { return false; }
	};
}

