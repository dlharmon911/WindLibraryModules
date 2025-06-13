export module wind:console.base;

import <string>;
import <cstdint>;
import <vector>;
import <array>;
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
	export using console_t = typename std::shared_ptr<console_data_t>;

	namespace console
	{
		export using font_data_t = struct font_data_tag_t;
		export using font_t = typename std::shared_ptr<font_data_t>;
		export using cursor_t = typename ALLEGRO::VECTOR_2D<int32_t>;
		export using rgba_t = typename uint32_t;
		export using palette_t = typename std::array<rgba_t, WIND::CONSOLE::PALETTE::SIZE>;

		namespace sprite
		{
			export using layer_data_t = struct layer_data_tag_t
			{
				int8_t m_color;
				std::array<uint8_t, WIND::CONSOLE::SPRITE::CHARACTER_COUNT> m_character{};
			};
			export using layer_t = typename std::shared_ptr<layer_data_t>;
		}

		export using sprite_data_t = struct sprite_data_tag_t
		{
			sprite::layer_t m_layers{ nullptr };
			int32_t m_begin{ 0 };
			int32_t m_end{ 0 };
		};
		export using sprite_t = typename std::shared_ptr<sprite_data_t>;
	}
}
