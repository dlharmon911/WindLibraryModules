export module wind:color;

import <cstdint>;
import allegro;
import :base;
import :math;

namespace wind
{
	union _color
	{
		uint32_t i;
		struct
		{
			uint8_t a;
			uint8_t b;
			uint8_t g;
			uint8_t r;
		};
	};

	export inline auto map_rgba_i(uint32_t color) -> ALLEGRO::COLOR
	{
		_color c = { 0 };
		c.i = color;
		return al::map_rgba(c.r, c.g, c.b, c.a);
	}

	export inline auto map_rgb_i(uint32_t color) -> ALLEGRO::COLOR
	{
		return map_rgba_i(0xff | (color << 8));
	}

	export inline auto unmap_rgb_i(const ALLEGRO::COLOR& color) -> uint32_t
	{
		_color c = { 0 };
		al::unmap_rgba(color, c.r, c.g, c.b, c.a);

		return (c.i >> 8);
	}

	export inline auto unmap_rgba_i(const ALLEGRO::COLOR& color) -> uint32_t
	{
		_color c = { 0 };
		al::unmap_rgba(color, c.r, c.g, c.b, c.a);

		return c.i;
	}
}
