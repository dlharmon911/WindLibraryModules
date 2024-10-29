export module wind:console;

import <string>;
import <cstdint>;
import allegro;
import allegro.font_addon;
export import :console.base;
export import :console.font;

namespace wind
{
	namespace console
	{
		export console_t create(const font_t& font, ALLEGRO::SIZE<size_t> size = { 40, 25 });
		export size_t get_width(const console_t& console);
		export size_t get_height(const console_t& console);
		export ALLEGRO::SIZE<size_t>& get_size(const console_t& console);
		export void clear(console_t& console);

		namespace gfx
		{
			export void draw(const console_t& console, const ALLEGRO::POINT<int32_t>& point);
		}

		namespace cursor
		{
			export const cursor_t& get(const console_t& console);
			export void set(console_t& console, const cursor_t& cursor);
		}

		namespace bitmap
		{
			export ALLEGRO::BITMAP& get(console_t& console);
		}

		namespace font
		{
			export void set(console_t& console, font_t& font);
			export const font_t& get(const console_t& console);
			export font_t& get(console_t& console);
		}

		namespace palette
		{
			export void set(console_t& console, size_t index, uint32_t rgba);
			export void set(console_t& console, const palette_t& palette);
			export uint32_t get(const console_t& console, size_t index);
			export const palette_t& get(const console_t& console);
			export palette_t& get(console_t& console);

			namespace background
			{
				export void set(console_t& console, size_t index);
				export size_t get(const console_t& console);
			}

			namespace foreground
			{
				export void set(console_t& console, size_t index);
				export size_t get(const console_t& console);
			}
		}

		namespace text
		{
			namespace gfx
			{
				export void draw(console_t& console, uint8_t c);
			}
		}

		namespace sprite
		{
			namespace gfx
			{
				export void draw(console_t& console, const sprite_t& sprite, const ALLEGRO::POINT<int32_t>& point, int32_t flags = WIND::CONSOLE::SPRITE::DRAW_FLAGS::FLIP_NONE);
				export void draw(console_t& console, const layer_t& layers, int32_t begin, int32_t end, const ALLEGRO::POINT<int32_t>& point, int32_t flags = WIND::CONSOLE::SPRITE::DRAW_FLAGS::FLIP_NONE);
			}
		}
	}
}
