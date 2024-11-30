export module wind:console.base;

import <string>;
import <cstdint>;
import <vector>;
import <memory>;
import allegro;
import allegro.font_addon;
import :base;

namespace WIND
{
	namespace CONSOLE
	{
		export inline constexpr int32_t FONT_GLYPH_SHIFT = 3;
		export inline constexpr int32_t FONT_GLYPH_SIZE = (1 << FONT_GLYPH_SHIFT);

		namespace CELL
		{
			export inline constexpr int32_t WIDTH = 8;
			export inline constexpr int32_t HEIGHT = 8;
		}

		namespace PALETTE
		{
			export inline constexpr size_t SIZE = 16;
		}

		namespace SPRITE
		{
			export inline constexpr size_t CHARACTER_COUNT = 4;

			namespace DRAW_FLAGS
			{
				export inline constexpr int32_t FLIP_NONE = 0;
				export inline constexpr int32_t FLIP_HORIZONTAL = 1;
				export inline constexpr int32_t FLIP_VERTICAL = 2;
			};
		}
	}
}

namespace wind
{
	export using console_data_t = struct console_data_tag_t;
	export using console_t = std::shared_ptr<console_data_t>;

	namespace console
	{
		export using font_data_t = struct font_data_tag_t;
		export using font_t = std::shared_ptr<font_data_t>;
		export using cursor_t = ALLEGRO::POINT<int32_t>;
		export using rgba_t = uint32_t;
		export using palette_t = rgba_t[WIND::CONSOLE::PALETTE::SIZE];

		namespace sprite
		{
			export using layer_data_t = struct layer_data_tag_t
			{
				int8_t m_color;
				uint8_t m_character[WIND::CONSOLE::SPRITE::CHARACTER_COUNT];
			};
			export using layer_t = std::shared_ptr<layer_data_t>;
		}

		export using sprite_data_t = struct sprite_data_tag_t
		{
			sprite::layer_t m_layers{ nullptr };
			int32_t m_begin{ 0 };
			int32_t m_end{ 0 };
		};
		export using sprite_t = std::shared_ptr<sprite_data_t>;
	}
}