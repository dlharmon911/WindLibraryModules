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

	export inline auto map_sepia(const ALLEGRO::COLOR& color) -> ALLEGRO::COLOR
	{
		ALLEGRO::COLOR rv{ 0.0f, 0.0f, 0.0f, 1.0f };

		rv.red = std::min(1.0f, (color.red * 0.393f) + (color.green * 0.769f) + (color.blue * 0.189f));
		rv.green = std::min(1.0f, (color.red * 0.349f) + (color.green * 0.686f) + (color.blue * 0.168f));
		rv.blue = std::min(1.0f, (color.red * 0.272f) + (color.green * 0.534f) + (color.blue * 0.131f));

		return rv;
	}

	export inline auto map_grayscale(const ALLEGRO::COLOR& color) -> ALLEGRO::COLOR
	{
		ALLEGRO::COLOR rv{ 0.0f, 0.0f, 0.0f, 1.0f };

		rv.red = std::min(1.0f, (rv.green = rv.blue = 0.299f * color.red + 0.587f * color.green + 0.114f * color.blue));

		return rv;
	}
}