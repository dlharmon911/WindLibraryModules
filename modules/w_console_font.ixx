export module wind:console.font;

import <array>;
import <cstdint>;
import <vector>;
import <memory>;
import allegro;
import allegro.font_addon;
import :base;
import :bitmap;
import :file;
import :console.base;
import :string;

namespace WIND
{
	namespace CONSOLE
	{
		export enum
		{
			FONT_ALIGNMENT_LEFT,
			FONT_ALIGNMENT_RIGHT,
			FONT_ALIGNMENT_CENTRE
		};
	}
}

namespace wind
{
	namespace console
	{
		export font_t create_font_default();
		export font_t create_font_from_array(const uint8_t* data, size_t count, int32_t start = 0x20);
		export bool save_font(const font_t& font, const wind::string_t& filename);
		export bool save_font_f(ALLEGRO::FILE& file, const font_t& font);
		export ALLEGRO::BITMAP& get_font_bitmap(font_t& font);
		export const ALLEGRO::BITMAP& get_font_bitmap(const font_t& font);
		export ALLEGRO::BITMAP& get_font_glyph(font_t& font, size_t index);
		export const ALLEGRO::BITMAP& get_font_glyph(const font_t& font, size_t index);
		export bool set_font_glyph(font_t& font, size_t index, const uint8_t* data);
		export bool set_font_glyph(font_t& font, size_t index, const wind::string_t& string);
		export void draw_font_glyph(const font_t& font, ALLEGRO::COLOR color, ALLEGRO::POINT<int32_t> point, uint8_t c);
		export void draw_font(const font_t& font, ALLEGRO::COLOR color, ALLEGRO::POINT<int32_t> point, int32_t alignment, const wind::string_t& text);
		export void draw_font(const font_t& font, ALLEGRO::COLOR color, ALLEGRO::POINT<int32_t> point, int32_t alignment, const char* format, ...);
	}
}
