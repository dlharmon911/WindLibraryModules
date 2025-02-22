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
		export auto create(const font_t& font, ALLEGRO::SIZE<int32_t> size = { 40, 25 }) -> console_t;
		export auto get_width(const console_t& console) -> int32_t;
		export auto get_height(const console_t& console) -> int32_t;
		export auto get_size(const console_t& console) -> ALLEGRO::SIZE<int32_t>&;
		export auto clear(console_t& console) -> void;

		namespace gfx
		{
			export auto draw(const console_t& console, const ALLEGRO::POINT<int32_t>& point) -> void;
		}

		namespace cursor
		{
			export auto get(const console_t& console) -> const cursor_t&;
			export auto set(console_t& console, const cursor_t& cursor) -> void;
		}

		namespace bitmap
		{
			export auto get(console_t& console) -> ALLEGRO::BITMAP&;
		}

		namespace font
		{
			export auto set(console_t& console, font_t& font) -> void;
			export auto get(const console_t& console) -> const font_t&;
			export auto get(console_t& console) -> font_t&;
		}

		namespace palette
		{
			export auto set(console_t& console, size_t index, uint32_t rgba) -> void;
			export auto set(console_t& console, const palette_t& palette) -> void;
			export auto get(const console_t& console, size_t index) -> uint32_t;
			export auto get(const console_t& console) -> const palette_t&;
			export auto get(console_t& console) -> palette_t&;

			namespace background
			{
				export auto set(console_t& console, size_t index) -> void;
				export auto get(const console_t& console) -> size_t;
			}

			namespace foreground
			{
				export auto set(console_t& console, size_t index) -> void;
				export auto get(const console_t& console) -> size_t;
			}
		}

		namespace text
		{
			namespace gfx
			{
				export auto draw(console_t& console, uint8_t c) -> void;
			}
		}

		namespace sprite
		{
			namespace gfx
			{
				export auto draw(console_t& console, const sprite_t& sprite, const ALLEGRO::POINT<int32_t>& point, int32_t flags = WIND::CONSOLE::SPRITE::DRAW_FLAGS::FLIP_NONE) -> void;
				export auto draw(console_t& console, const layer_t& layers, int32_t begin, int32_t end, const ALLEGRO::POINT<int32_t>& point, int32_t flags = WIND::CONSOLE::SPRITE::DRAW_FLAGS::FLIP_NONE) -> void;
			}
		}
	}
}
