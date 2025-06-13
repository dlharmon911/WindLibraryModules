export module wind:dialog;

import <cstdint>;
import <vector>;
import <memory>;
import allegro;
import :base;
import :string;
import :array;
import :widget;

namespace ALLEGRO
{
	export constexpr int32_t EVENT_TYPE_MOUSE_BUTTON_CLICK{ 1024 };
}

namespace wind
{
	export class dialog_t : public widget_t
	{
	public:
		dialog_t() = default;
		virtual ~dialog_t() = default;
		virtual auto get_version() const->int32_t = 0;
		virtual auto get_title() const-> const wind::string_t& = 0;
		virtual auto on_initialize() -> int32_t = 0;
		virtual auto on_shutdown() -> int32_t = 0;
		virtual auto on_start() -> int32_t = 0;
		virtual auto on_stop() -> int32_t = 0;
		virtual auto on_update() -> int32_t = 0;
		virtual auto on_render() -> int32_t = 0;
		virtual auto on_event(const ALLEGRO::EVENT& event) -> bool;

	private:

	};
}
