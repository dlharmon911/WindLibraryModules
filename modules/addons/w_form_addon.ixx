export module wind.form_addon;

import <cassert>;
import <memory>;
import <vector>;
import <string>;
import <cstdint>;
import <any>;
import <functional>;
import allegro;
import wind;
export import :base;
export import :widget;


namespace wind
{
	export class form_t : public wind::dialog_t
	{
	public:
		form_t() = default;
		virtual ~form_t() = default;
		virtual auto on_initialize() -> int32_t = 0;
		virtual auto on_shutdown() -> int32_t = 0;
		virtual auto on_start() -> int32_t = 0;
		virtual auto on_stop() -> int32_t = 0;
		virtual auto on_update() -> int32_t = 0;
		virtual auto on_render() -> int32_t = 0;
		auto on_event(const ALLEGRO::EVENT& event) -> bool final;
		auto get_position() const -> const ALLEGRO::POINT<int32_t>&;
		auto set_position(const ALLEGRO::POINT<int32_t>& position) -> void;
		auto get_size() const -> const ALLEGRO::SIZE<int32_t>&;
		auto set_size(const ALLEGRO::SIZE<int32_t>& size) -> void;
		auto get_dimensions() const -> const ALLEGRO::RECTANGLE<int32_t>&;
		auto set_dimensions(const ALLEGRO::RECTANGLE<int32_t>& dimensions) -> void;
		auto get_state() const->int32_t;
		auto set_state(int32_t state) -> void;
		auto get_mouse_over() const -> const form::widget_t*;
		auto get_mouse_over() -> form::widget_t*;
		auto add_widget(form::widget_t* widget) -> void;

	private:
		std::vector<form::widget_t*> m_widgets{};
		ALLEGRO::RECTANGLE<int32_t> m_dimensions{};
		int32_t m_state{ 0 };
	};
}

