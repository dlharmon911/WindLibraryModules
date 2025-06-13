module wind.form_addon;

import <cassert>;
import <memory>;
import <vector>;
import <string>;
import <cstdint>;
import <any>;
import <functional>;
import <unordered_map>;
import allegro;
import wind;
import :base;
import :widget;

namespace wind
{
	namespace form
	{
		auto widget_t::on_event(const ALLEGRO::EVENT& event) -> bool
		{
			return false;
		}

		auto widget_t::get_position() const -> const ALLEGRO::POINT<int32_t>&
		{
			return this->m_dimensions.position;
		}

		auto widget_t::set_position(const ALLEGRO::POINT<int32_t>& position) -> void
		{
			this->m_dimensions.position = position;
		}

		auto widget_t::get_size() const -> const ALLEGRO::SIZE<int32_t>&
		{
			return this->m_dimensions.size;
		}

		auto widget_t::set_size(const ALLEGRO::SIZE<int32_t>& size) -> void
		{
			this->m_dimensions.size = size;
		}

		auto widget_t::get_dimensions() const -> const ALLEGRO::RECTANGLE<int32_t>&
		{
			return this->m_dimensions;
		}

		auto widget_t::set_dimensions(const ALLEGRO::RECTANGLE<int32_t>& dimensions) -> void
		{
			this->m_dimensions = dimensions;
		}

		auto widget_t::get_state() const->int32_t
		{
			return this->m_state;
		}

		auto widget_t::set_state(int32_t state) -> void
		{
			this->m_state = state;
		}

		auto widget_t::get_mouse_over() const -> const form::widget_t*
		{
			return nullptr;
		}

		auto widget_t::get_mouse_over() -> form::widget_t*
		{
			return nullptr;
		}
	}
}
