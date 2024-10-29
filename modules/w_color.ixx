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

	export inline ALLEGRO::COLOR map_rgba_i(uint32_t color)
	{
		_color c = { 0 };
		c.i = color;
		return al::map_rgba(c.r, c.g, c.b, c.a);
	}

	export inline ALLEGRO::COLOR map_rgb_i(uint32_t color)
	{
		return map_rgba_i(0xff | (color << 8));
	}

	export inline uint32_t unmap_rgb_i(ALLEGRO::COLOR color)
	{
		_color c = { 0 };
		al::unmap_rgba(color, c.r, c.g, c.b, c.a);

		return (c.i >> 8);
	}

	export inline uint32_t unmap_rgba_i(ALLEGRO::COLOR color)
	{
		_color c = { 0 };
		al::unmap_rgba(color, c.r, c.g, c.b, c.a);

		return c.i;
	}
}
