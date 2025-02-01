module wind;

import <cstdint>;
import <array>;
import allegro;
import allegro.primitives_addon;
import :base;
import :frame;
import :color;

namespace wind
{
	namespace theme
	{
		std::array<uint32_t, std::to_underlying(WIND::THEME::COLOR::COUNT)> colors
		{
			0xd6d3ceff,
			0xffffffff,
			0xffffffff,
			0x828182ff,
			0xffffffff,
			0x424142ff,
			0x000000ff,
			0x828182ff
		};
	}

	namespace frame
	{
		namespace border
		{
			static auto draw(const ALLEGRO::POINT<float>& point, const ALLEGRO::SIZE<float>& dim, WIND::FRAME::BORDER::TYPE type) -> void
			{
				static ALLEGRO::POINT<float> point1 = { 0.0f, 0.0f };
				static ALLEGRO::POINT<float> point2 = { 0.0f, 0.0f };
				static ALLEGRO::COLOR border_light = map_rgba_i(theme::colors[std::to_underlying(WIND::THEME::COLOR::BORDER_LIGHT)]);
				static ALLEGRO::COLOR border_normal = map_rgba_i(theme::colors[std::to_underlying(WIND::THEME::COLOR::BORDER)]);
				static ALLEGRO::COLOR border_dark = map_rgba_i(theme::colors[std::to_underlying(WIND::THEME::COLOR::BORDER_DARK)]);

				point1 = { point.x + 0.5f, point.y + 0.5f };
				point2 = { point.x + dim.width + 0.5f, point.y + dim.height + 0.5f };

				switch (type)
				{
				case WIND::FRAME::BORDER::TYPE::RAISED:
				{
					al::draw_line({ point1.x, point1.y }, { point1.x, point2.y - 0.5f }, border_light, 1.0f);
					al::draw_line({ point1.x, point1.y }, { point2.x - 0.5f, point1.y }, border_light, 1.0f);
					al::draw_line({ point1.x + 1.0f, point2.y - 2.0f }, { point2.x - 2.0f, point2.y - 2.0f }, border_normal, 1.0f);
					al::draw_line({ point2.x - 2.0f, point1.y + 1.0f }, { point2.x - 2.0f, point2.y - 1.0f }, border_normal, 1.0f);
					al::draw_line({ point1.x, point2.y - 1.0f }, { point2.x - 1.0f, point2.y - 1.0f }, border_dark, 1.0f);
					al::draw_line({ point2.x - 1.0f, point1.y }, { point2.x - 1.0f, point2.y }, border_dark, 1.0f);
				} break;

				case WIND::FRAME::BORDER::TYPE::WORKSPACE:
				{
					al::draw_rectangle({ point1.x, point1.y }, { point2.x, point2.y }, border_normal, 1.0f);
					al::draw_rectangle({ point1.x + 1.0f, point1.y + 1.0f }, { point2.x - 1.0f, point2.y - 1.0f }, border_dark, 1.0f);
				} break;

				case WIND::FRAME::BORDER::TYPE::SUNKEN:
				{
					al::draw_line({ point1.x, point1.y }, { point1.x, point2.y - 0.5f }, border_dark, 1.0f);
					al::draw_line({ point1.x, point1.y }, { point2.x - 0.5f, point1.y }, border_dark, 1.0f);
					al::draw_line({ point1.x + 1.0f, point1.y + 1.0f }, { point2.x - 2.0f, point1.y + 1.0f }, border_normal, 1.0f);
					al::draw_line({ point1.x + 1.0f, point1.y + 1.0f }, { point1.x + 1.0f, point2.y - 2.0f }, border_normal, 1.0f);
					al::draw_line({ point1.x, point2.y - 1.0f }, { point2.x - 1.0f, point2.y - 1.0f }, border_light, 1.0f);
					al::draw_line({ point2.x - 1.0f, point1.y }, { point2.x - 1.0f, point2.y }, border_light, 1.0f);
				} break;

				case WIND::FRAME::BORDER::TYPE::RIDGE:
				{
					al::draw_line({ point1.x, point2.y - 1.0f }, { point2.x - 1.0f, point2.y - 1.0f }, border_normal, 1.0f);
					al::draw_line({ point2.x - 1.0f, point1.y }, { point2.x - 1.0f, point2.y }, border_normal, 1.0f);
					al::draw_line({ point1.x + 1.0f, point1.y + 1.0f }, { point2.x - 2.0f, point1.y + 1.0f }, border_normal, 1.0f);
					al::draw_line({ point1.x + 1.0f, point1.y + 1.0f }, { point1.x + 1.0f, point2.y - 2.0f }, border_normal, 1.0f);
					al::draw_rectangle({ point1.x, point1.y }, { point2.x - 2.0f, point2.y - 2.0f }, border_light, 1.0f);
				} break;

				case WIND::FRAME::BORDER::TYPE::GROOVE:
				{
					al::draw_line({ point1.x, point2.y - 1.0f }, { point2.x - 1.0f, point2.y - 1.0f }, border_light, 1.0f);
					al::draw_line({ point2.x - 1.0f, point1.y }, { point2.x - 1.0f, point2.y }, border_light, 1.0f);
					al::draw_line({ point1.x + 1.0f, point1.y + 1.0f }, { point2.x - 2.0f, point1.y + 1.0f }, border_light, 1.0f);
					al::draw_line({ point1.x + 1.0f, point1.y + 1.0f, }, { point1.x + 1.0f, point2.y - 2.0f }, border_light, 1.0f);
					al::draw_rectangle({ point1.x, point1.y }, { point2.x - 2.0f, point2.y - 2.0f }, border_normal, 1.0f);
				} break;

				case WIND::FRAME::BORDER::TYPE::SOLID:
				{
					al::draw_rectangle({ point1.x, point1.y }, { point2.x - 1.0f, point2.y - 1.0f }, border_dark, 1.0f);
					al::draw_rectangle({ point1.x + 1.0f, point1.y + 1.0f }, { point2.x - 2.0f, point2.y - 2.0f }, border_dark, 1.0f);
				} break;
				}
			}
		}

		auto draw(const ALLEGRO::POINT<float>& point, const ALLEGRO::SIZE<float>& dim, WIND::FRAME::TYPE type, WIND::FRAME::BORDER::TYPE border) -> void
		{
			static ALLEGRO::POINT<float> point1 = { 0.0f, 0.0f };
			static ALLEGRO::POINT<float> point2 = { 0.0f, 0.0f };
			static uint32_t background = theme::colors[std::to_underlying(WIND::THEME::COLOR::BACKGROUND)];

			background = theme::colors[std::to_underlying(WIND::THEME::COLOR::BACKGROUND)];
			point1 = { point.x + 0.5f, point.y + 0.5f };
			point2 = { point.x + dim.width + 0.5f, point.y + dim.height + 0.5f };

			if (type == WIND::FRAME::TYPE::WORKSPACE)
			{
				background = theme::colors[std::to_underlying(WIND::THEME::COLOR::WORKSPACE)];
			}

			al::draw_filled_rectangle(point1, point2, map_rgba_i(background));

			if (border != WIND::FRAME::BORDER::TYPE::NONE)
			{
				border::draw(point, dim, border);
			}
		}
	}
}