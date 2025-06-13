module wind;

import <cassert>;
import <memory>;
import <vector>;
import <string>;
import <cstdint>;
import <any>;
import <functional>;
import <unordered_map>;
import allegro;
import :base;
import :widget;

namespace wind
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

	auto widget_t::get_mouse_over(const ALLEGRO::POINT<int32_t>& mouse) const -> const std::shared_ptr<widget_t>
	{
		for (auto& widget : this->m_widgets)
		{
			const ALLEGRO::RECTANGLE<int32_t>& dimensions = widget->get_dimensions();

			if (mouse.x >= dimensions.position.x &&
				mouse.x < (dimensions.position.x + dimensions.size.width) &&
				mouse.y >= dimensions.position.y &&
				mouse.y < (dimensions.position.y + dimensions.size.height))
			{
				const std::shared_ptr<widget_t> result = widget->get_mouse_over(mouse);
				if (result)
				{
					return result;
				}
				return widget;
			}
		}

		return nullptr;
	}

	auto widget_t::get_mouse_over(const ALLEGRO::POINT<int32_t>& mouse) -> std::shared_ptr<widget_t>
	{
		for (auto& widget : this->m_widgets)
		{
			const ALLEGRO::RECTANGLE<int32_t>& dimensions = widget->get_dimensions();

			if (mouse.x >= dimensions.position.x &&
				mouse.x < (dimensions.position.x + dimensions.size.width) &&
				mouse.y >= dimensions.position.y &&
				mouse.y < (dimensions.position.y + dimensions.size.height))
			{
				std::shared_ptr<widget_t> result = widget->get_mouse_over(mouse);
				if (result)
				{
					return result;
				}
				return widget;
			}
		}

		return nullptr;
	}

	auto widget_t::add_widget(const std::shared_ptr<widget_t>& widget) -> void
	{
		ALLEGRO::ASSERT(widget);
		this->m_widgets.push_back(widget);
	}
}
