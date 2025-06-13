module wind;

import <cstdint>;
import <array>;
import allegro;
import allegro.primitives_addon;
import :base;
import :frame;
import :color;
import :theme;

namespace wind
{
	namespace frame
	{
		namespace border
		{
			static auto draw(const ALLEGRO::VECTOR_2D<float>& point, const ALLEGRO::VECTOR_2D<float>& dim, WIND::FRAME::BORDER::TYPE type) -> void
			{
				static ALLEGRO::VECTOR_2D<float> point1 = { 0.0f, 0.0f };
				static ALLEGRO::VECTOR_2D<float> point2 = { 0.0f, 0.0f };
				static const ALLEGRO::COLOR border_light = theme_t::get_color(WIND::THEME::COLOR::BORDER_LIGHT);
				static const ALLEGRO::COLOR border_normal = theme_t::get_color(WIND::THEME::COLOR::BORDER);
				static const ALLEGRO::COLOR border_dark = theme_t::get_color(WIND::THEME::COLOR::BORDER_DARK);

				point1.set_values(point.get_x() + 0.5f, point.get_y() + 0.5f);
				point2.set_values(point.get_x() + dim.get_x() + 0.5f, point.get_y() + dim.get_y() + 0.5f);

				switch (type)
				{
				case WIND::FRAME::BORDER::TYPE::RAISED:
				{
					al::draw_line({ point1.get_x(), point1.get_y() }, { point1.get_x(), point2.get_y() - 0.5f }, border_light, 1.0f);
					al::draw_line({ point1.get_x(), point1.get_y() }, { point2.get_x() - 0.5f, point1.get_y() }, border_light, 1.0f);
					al::draw_line({ point1.get_x() + 1.0f, point2.get_y() - 2.0f }, { point2.get_x() - 2.0f, point2.get_y() - 2.0f }, border_normal, 1.0f);
					al::draw_line({ point2.get_x() - 2.0f, point1.get_y() + 1.0f }, { point2.get_x() - 2.0f, point2.get_y() - 1.0f }, border_normal, 1.0f);
					al::draw_line({ point1.get_x(), point2.get_y() - 1.0f }, { point2.get_x() - 1.0f, point2.get_y() - 1.0f }, border_dark, 1.0f);
					al::draw_line({ point2.get_x() - 1.0f, point1.get_y() }, { point2.get_x() - 1.0f, point2.get_y() }, border_dark, 1.0f);
				} break;

				case WIND::FRAME::BORDER::TYPE::WORKSPACE:
				{
					al::draw_rectangle({ point1.get_x(), point1.get_y() }, { point2.get_x(), point2.get_y() }, border_normal, 1.0f);
					al::draw_rectangle({ point1.get_x() + 1.0f, point1.get_y() + 1.0f }, { point2.get_x() - 1.0f, point2.get_y() - 1.0f }, border_dark, 1.0f);
				} break;

				case WIND::FRAME::BORDER::TYPE::SUNKEN:
				{
					al::draw_line({ point1.get_x(), point1.get_y() }, { point1.get_x(), point2.get_y() - 0.5f }, border_dark, 1.0f);
					al::draw_line({ point1.get_x(), point1.get_y() }, { point2.get_x() - 0.5f, point1.get_y() }, border_dark, 1.0f);
					al::draw_line({ point1.get_x() + 1.0f, point1.get_y() + 1.0f }, { point2.get_x() - 2.0f, point1.get_y() + 1.0f }, border_normal, 1.0f);
					al::draw_line({ point1.get_x() + 1.0f, point1.get_y() + 1.0f }, { point1.get_x() + 1.0f, point2.get_y() - 2.0f }, border_normal, 1.0f);
					al::draw_line({ point1.get_x(), point2.get_y() - 1.0f }, { point2.get_x() - 1.0f, point2.get_y() - 1.0f }, border_light, 1.0f);
					al::draw_line({ point2.get_x() - 1.0f, point1.get_y() }, { point2.get_x() - 1.0f, point2.get_y() }, border_light, 1.0f);
				} break;

				case WIND::FRAME::BORDER::TYPE::RIDGE:
				{
					al::draw_line({ point1.get_x(), point2.get_y() - 1.0f }, { point2.get_x() - 1.0f, point2.get_y() - 1.0f }, border_normal, 1.0f);
					al::draw_line({ point2.get_x() - 1.0f, point1.get_y() }, { point2.get_x() - 1.0f, point2.get_y() }, border_normal, 1.0f);
					al::draw_line({ point1.get_x() + 1.0f, point1.get_y() + 1.0f }, { point2.get_x() - 2.0f, point1.get_y() + 1.0f }, border_normal, 1.0f);
					al::draw_line({ point1.get_x() + 1.0f, point1.get_y() + 1.0f }, { point1.get_x() + 1.0f, point2.get_y() - 2.0f }, border_normal, 1.0f);
					al::draw_rectangle({ point1.get_x(), point1.get_y() }, { point2.get_x() - 2.0f, point2.get_y() - 2.0f }, border_light, 1.0f);
				} break;

				case WIND::FRAME::BORDER::TYPE::GROOVE:
				{
					al::draw_line({ point1.get_x(), point2.get_y() - 1.0f }, { point2.get_x() - 1.0f, point2.get_y() - 1.0f }, border_light, 1.0f);
					al::draw_line({ point2.get_x() - 1.0f, point1.get_y() }, { point2.get_x() - 1.0f, point2.get_y() }, border_light, 1.0f);
					al::draw_line({ point1.get_x() + 1.0f, point1.get_y() + 1.0f }, { point2.get_x() - 2.0f, point1.get_y() + 1.0f }, border_light, 1.0f);
					al::draw_line({ point1.get_x() + 1.0f, point1.get_y() + 1.0f, }, { point1.get_x() + 1.0f, point2.get_y() - 2.0f }, border_light, 1.0f);
					al::draw_rectangle({ point1.get_x(), point1.get_y() }, { point2.get_x() - 2.0f, point2.get_y() - 2.0f }, border_normal, 1.0f);
				} break;

				case WIND::FRAME::BORDER::TYPE::SOLID:
				{
					al::draw_rectangle({ point1.get_x(), point1.get_y() }, { point2.get_x() - 1.0f, point2.get_y() - 1.0f }, border_dark, 1.0f);
					al::draw_rectangle({ point1.get_x() + 1.0f, point1.get_y() + 1.0f }, { point2.get_x() - 2.0f, point2.get_y() - 2.0f }, border_dark, 1.0f);
				} break;
				}
			}
		}

		auto draw(const ALLEGRO::RECTANGLE<float>& rectangle, WIND::FRAME::TYPE type, WIND::FRAME::BORDER::TYPE border) -> void
		{
			draw(rectangle.get_position(), rectangle.get_size(), type, border);
		}

		auto draw(const ALLEGRO::VECTOR_2D<float>& point, const ALLEGRO::VECTOR_2D<float>& size, WIND::FRAME::TYPE type, WIND::FRAME::BORDER::TYPE border) -> void
		{
			static ALLEGRO::VECTOR_2D<float> point1 = { 0.0f, 0.0f };
			static ALLEGRO::VECTOR_2D<float> point2 = { 0.0f, 0.0f };
			static ALLEGRO::COLOR background = theme_t::get_color(WIND::THEME::COLOR::BACKGROUND);

			point1.set_values(point.get_x() + 0.5f, point.get_y() + 0.5f);
			point2.set_values(point.get_x() + size.get_x() + 0.5f, point.get_y() + size.get_y() + 0.5f);

			switch (type)
			{
			case WIND::FRAME::TYPE::MENU:
			{
				background = theme_t::get_color(WIND::THEME::COLOR::MENU);
			} break;
			case WIND::FRAME::TYPE::WORKSPACE:
			{
				background = theme_t::get_color(WIND::THEME::COLOR::WORKSPACE);
			} break;
			default:
			{
				background = theme_t::get_color(WIND::THEME::COLOR::BACKGROUND);
			} break;
			}

			al::draw_filled_rectangle(point1, point2, background);

			if (border != WIND::FRAME::BORDER::TYPE::NONE)
			{
				border::draw(point, size, border);
			}
		}
	}
}
