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
		std::array<uint32_t, theme::_count> colors
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
			auto draw(ALLEGRO::POINT <float>point, ALLEGRO::SIZE<float> dim, frame::border::type type) -> void
			{
				static ALLEGRO::POINT<float> point1 = { 0.0f, 0.0f };
				static ALLEGRO::POINT<float> point2 = { 0.0f, 0.0f };
				static ALLEGRO::COLOR border_light = map_rgba_i(theme::colors[theme::border_light]);
				static ALLEGRO::COLOR border_normal = map_rgba_i(theme::colors[theme::border]);
				static ALLEGRO::COLOR border_dark = map_rgba_i(theme::colors[theme::border_dark]);

				point1 = { point.x + 0.5f, point.y + 0.5f };
				point2 = { point.x + dim.width + 0.5f, point.y + dim.height + 0.5f };

				switch (type)
				{
				case type::raised:
				{
					al::draw_line({ point1.x, point1.y }, { point1.x, point2.y - 0.5f }, border_light, 1.0f);
					al::draw_line({ point1.x, point1.y }, { point2.x - 0.5f, point1.y }, border_light, 1.0f);
					al::draw_line({ point1.x + 1.0f, point2.y - 2.0f }, { point2.x - 2.0f, point2.y - 2.0f }, border_normal, 1.0f);
					al::draw_line({ point2.x - 2.0f, point1.y + 1.0f }, { point2.x - 2.0f, point2.y - 1.0f }, border_normal, 1.0f);
					al::draw_line({ point1.x, point2.y - 1.0f }, { point2.x - 1.0f, point2.y - 1.0f }, border_dark, 1.0f);
					al::draw_line({ point2.x - 1.0f, point1.y }, { point2.x - 1.0f, point2.y }, border_dark, 1.0f);
				} break;

				case type::workspace:
				{
					al::draw_rectangle({ point1.x, point1.y }, { point2.x, point2.y }, border_normal, 1.0f);
					al::draw_rectangle({ point1.x + 1.0f, point1.y + 1.0f }, { point2.x - 1.0f, point2.y - 1.0f }, border_dark, 1.0f);
				} break;

				case type::sunken:
				{
					al::draw_line({ point1.x, point1.y }, { point1.x, point2.y - 0.5f }, border_dark, 1.0f);
					al::draw_line({ point1.x, point1.y }, { point2.x - 0.5f, point1.y }, border_dark, 1.0f);
					al::draw_line({ point1.x + 1.0f, point1.y + 1.0f }, { point2.x - 2.0f, point1.y + 1.0f }, border_normal, 1.0f);
					al::draw_line({ point1.x + 1.0f, point1.y + 1.0f }, { point1.x + 1.0f, point2.y - 2.0f }, border_normal, 1.0f);
					al::draw_line({ point1.x, point2.y - 1.0f }, { point2.x - 1.0f, point2.y - 1.0f }, border_light, 1.0f);
					al::draw_line({ point2.x - 1.0f, point1.y }, { point2.x - 1.0f, point2.y }, border_light, 1.0f);
				} break;

				case type::ridge:
				{
					al::draw_line({ point1.x, point2.y - 1.0f }, { point2.x - 1.0f, point2.y - 1.0f }, border_normal, 1.0f);
					al::draw_line({ point2.x - 1.0f, point1.y }, { point2.x - 1.0f, point2.y }, border_normal, 1.0f);
					al::draw_line({ point1.x + 1.0f, point1.y + 1.0f }, { point2.x - 2.0f, point1.y + 1.0f }, border_normal, 1.0f);
					al::draw_line({ point1.x + 1.0f, point1.y + 1.0f }, { point1.x + 1.0f, point2.y - 2.0f }, border_normal, 1.0f);
					al::draw_rectangle({ point1.x, point1.y }, { point2.x - 2.0f, point2.y - 2.0f }, border_light, 1.0f);
				} break;

				case type::groove:
				{
					al::draw_line({ point1.x, point2.y - 1.0f }, { point2.x - 1.0f, point2.y - 1.0f }, border_light, 1.0f);
					al::draw_line({ point2.x - 1.0f, point1.y }, { point2.x - 1.0f, point2.y }, border_light, 1.0f);
					al::draw_line({ point1.x + 1.0f, point1.y + 1.0f }, { point2.x - 2.0f, point1.y + 1.0f }, border_light, 1.0f);
					al::draw_line({ point1.x + 1.0f, point1.y + 1.0f, }, { point1.x + 1.0f, point2.y - 2.0f }, border_light, 1.0f);
					al::draw_rectangle({ point1.x, point1.y }, { point2.x - 2.0f, point2.y - 2.0f }, border_normal, 1.0f);
				} break;

				case type::solid:
				{
					al::draw_rectangle({ point1.x, point1.y }, { point2.x - 1.0f, point2.y - 1.0f }, border_dark, 1.0f);
					al::draw_rectangle({ point1.x + 1.0f, point1.y + 1.0f }, { point2.x - 2.0f, point2.y - 2.0f }, border_dark, 1.0f);
				} break;
				}
			}
		}

		auto draw(ALLEGRO::POINT<float> point, ALLEGRO::SIZE<float> dim, frame::type type, frame::border::type border) -> void
		{
			static ALLEGRO::POINT<float> point1 = { 0.0f, 0.0f };
			static ALLEGRO::POINT<float> point2 = { 0.0f, 0.0f };
			static uint32_t background = theme::colors[theme::background];

			background = theme::colors[theme::background];
			point1 = { point.x + 0.5f, point.y + 0.5f };
			point2 = { point.x + dim.width + 0.5f, point.y + dim.height + 0.5f };

			if (type == frame::type::workspace)
			{
				background = theme::colors[theme::workspace];
			}

			al::draw_filled_rectangle(point1, point2, map_rgba_i(background));

			if (border != border::type::none)
			{
				border::draw(point, dim, border);
			}
		}
	}
}