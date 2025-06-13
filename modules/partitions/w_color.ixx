export module wind:color;

import <cstdint>;
import allegro;
import :base;
import :math;

namespace WIND
{
	export const ALLEGRO::COLOR EIGENGRAU{ 0.08627451f, 0.08627451f, 0.11372549f, 1.0f };
}

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

		rv.r = std::min<float>(1.0f, (color.r * 0.393f) + (color.g * 0.769f) + (color.b * 0.189f));
		rv.g = std::min<float>(1.0f, (color.r * 0.349f) + (color.g * 0.686f) + (color.b * 0.168f));
		rv.b = std::min<float>(1.0f, (color.r * 0.272f) + (color.g * 0.534f) + (color.b * 0.131f));

		return rv;
	}

	export inline auto map_grayscale(const ALLEGRO::COLOR& color) -> ALLEGRO::COLOR
	{
		ALLEGRO::COLOR rv{ 0.0f, 0.0f, 0.0f, 1.0f };

		rv.r = std::min<float>(1.0f, (rv.g = rv.b = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b));

		return rv;
	}
}
