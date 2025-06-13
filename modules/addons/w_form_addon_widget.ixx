export module wind.form_addon:widget;

import <cassert>;
import <memory>;
import <vector>;
import <string>;
import <cstdint>;
import <any>;
import <functional>;
import allegro;
import wind;
import :base;

namespace wind
{	
	namespace form
	{
		export class widget_t
		{
		public:
			widget_t() = default;
			virtual ~widget_t() = default;
			virtual auto on_initialize() -> int32_t = 0;
			virtual auto on_shutdown() -> int32_t = 0;
			virtual auto on_start() -> int32_t = 0;
			virtual auto on_stop() -> int32_t = 0;
			virtual auto on_update() -> int32_t = 0;
			virtual auto on_render() -> int32_t = 0;
			virtual auto on_event(const ALLEGRO::EVENT& event) -> bool;

			auto get_position() const -> const ALLEGRO::POINT<int32_t>&;
			auto set_position(const ALLEGRO::POINT<int32_t>& position) -> void;
			auto get_size() const -> const ALLEGRO::SIZE<int32_t>&;
			auto set_size(const ALLEGRO::SIZE<int32_t>& size) -> void;
			auto get_dimensions() const -> const ALLEGRO::RECTANGLE<int32_t>&;
			auto set_dimensions(const ALLEGRO::RECTANGLE<int32_t>& dimensions) -> void;
			auto get_state() const->int32_t;
			auto set_state(int32_t state) -> void;

			auto get_mouse_over() const -> const widget_t*;
			auto get_mouse_over() -> widget_t*;

		private:
			std::vector<widget_t*> m_widgets{};
			ALLEGRO::RECTANGLE<int32_t> m_dimensions{};
			int32_t m_state{ 0 };
		};
	}
}
