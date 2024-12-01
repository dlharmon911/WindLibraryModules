export module wind:dialog.widget;

import <string>;
import <memory>;
import std;
import allegro;
import :base;
import :array;
import :string;
import :dialog.base;

namespace wind
{
	namespace dialog
	{
		export class widget_t : public dialog::base_t<wind::dialog::widget_t>
		{
		public:
			widget_t() {}
			virtual ~widget_t() {}

			virtual auto on_initialize() -> int32_t = 0;
			virtual auto on_shutdown() -> int32_t = 0;
			virtual auto on_start() -> int32_t = 0;
			virtual auto on_stop() -> int32_t = 0;
			virtual auto on_update() -> int32_t = 0;
			virtual auto on_render() -> int32_t = 0;

			virtual auto on_joystick_axis(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_joystick_button_down(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_joystick_button_up(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_key_down(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_key_up(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_key_char(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_mouse_click(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_mouse_axes(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_mouse_button_down(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_mouse_button_up(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_mouse_grab(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_mouse_drag(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_mouse_enter(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_mouse_leave(const ALLEGRO::EVENT& event) -> bool { return false; }

			friend class wind::system_t;

		protected:
		};
	}
}