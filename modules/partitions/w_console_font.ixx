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

namespace WIND::CONSOLE::FONT
{
	export enum class ALIGNMENT : int32_t
	{
		LEFT,
		RIGHT,
		CENTRE
	};
}

namespace wind
{
	namespace console
	{
		export auto create_font_default() -> font_t;
		export auto save_font(const font_t& font, const wind::string_t& filename) -> bool;
		export auto save_font_f(ALLEGRO::FILE& file, const font_t& font) -> bool;
		export auto get_font_bitmap(font_t& font) -> ALLEGRO::BITMAP&;
		export auto get_font_bitmap(const font_t& font) -> const ALLEGRO::BITMAP&;
		export auto get_font_glyph(font_t& font, size_t index) -> ALLEGRO::BITMAP&;
		export auto get_font_glyph(const font_t& font, size_t index) -> const ALLEGRO::BITMAP&;
		export auto set_font_glyph(font_t& font, size_t index, const uint8_t* data) -> bool;
		export auto set_font_glyph(font_t& font, size_t index, const wind::string_t& string) -> bool;
		export auto draw_font_glyph(const font_t& font, ALLEGRO::COLOR color, const ALLEGRO::VECTOR_2D<int32_t>& point, uint8_t c) -> void;
		export auto draw_font(const font_t& font, ALLEGRO::COLOR color, const ALLEGRO::VECTOR_2D<int32_t>& point, WIND::CONSOLE::FONT::ALIGNMENT alignment, const wind::string_t& text) -> void;
		export auto draw_font(const font_t& font, ALLEGRO::COLOR color, const ALLEGRO::VECTOR_2D<int32_t>& point, WIND::CONSOLE::FONT::ALIGNMENT alignment, const char* format, ...) -> void;
	}
}
