module wind;

import <cstdarg>;
import <cstdint>;
import <vector>;
import <memory>;
import allegro;
import allegro.font_addon;
import :base;
import :hex;
import :console.base;
import :console.font;
import :string;
import :bitmap;
import :file;
import :color;

namespace wind
{
	typedef struct console_data_t
	{
		console::cursor_t m_cursor = { 0.0f, 0.0f };
		size_t m_background{ 0 };
		size_t m_foreground{ 15 };
		ALLEGRO::SIZE<size_t> m_size = { 0,0 };
		ALLEGRO::BITMAP m_bitmap{ nullptr };
		std::shared_ptr<uint8_t> m_data{ nullptr };
		console::palette_t m_palette{};
		console::font_t m_font{ nullptr };
	} console_data_t;

	namespace console
	{
		console_t create(const font_t& font, ALLEGRO::SIZE<size_t> size)
		{
			console_t console = std::make_shared<console_data_t>();

			if (console)
			{
				palette_t default_palette =
				{
					0x000000ff,
					0x0000aaff,
					0x00aa00ff,
					0x00aaaaff,
					0xaa0000ff,
					0xaa00aaff,
					0xaa5500ff,
					0xaaaaaaff,
					0x555555ff,
					0x5555ffff,
					0x55ff55ff,
					0x55ffffff,
					0xff5555ff,
					0xff55ffff,
					0xffff55ff,
					0xffffffff
				};

				console->m_cursor = { 0.0f, 0.0f };
				console->m_background = 0;
				console->m_foreground = 15;
				console->m_size = size;
				console->m_bitmap = al::create_bitmap(size);
				console->m_data = std::shared_ptr<uint8_t>(new uint8_t[size.width * size.height], array_deleter<uint8_t>());
				console->m_font = font;

				if (!console->m_bitmap || !console->m_data || !console->m_font)
				{
					return nullptr;
				}

				for (size_t j = 0; j < console->m_size.height; ++j)
				{
					for (size_t i = 0; i < console->m_size.width; ++i)
					{
						console->m_data.get()[i + j * console->m_size.width] = 0;
					}
				}

				for (int32_t i = 0; i < WIND::CONSOLE::PALETTE::SIZE; ++i)
				{
					console->m_palette[i] = default_palette[i];
				}

				console::clear(console);
			}

			return console;
		}

		size_t get_width(const console_t& console)
		{
			return console->m_size.width;
		}

		size_t get_height(const console_t& console)
		{
			return console->m_size.height;
		}

		ALLEGRO::SIZE<size_t>& get_size(const console_t& console)
		{
			return console->m_size;
		}

		void clear(console_t& console)
		{
			static ALLEGRO::BITMAP target{ nullptr };

			target = al::get_target_bitmap();
			al::set_target_bitmap(console->m_bitmap);

			al::clear_to_color(wind::map_rgb_i(console->m_palette[console->m_background]));

			al::set_target_bitmap(target);

			console->m_cursor = { 0.0f, 0.0f };

			for (size_t j = 0; j < console->m_size.height; ++j)
			{
				for (size_t i = 0; i < console->m_size.width; ++i)
				{
					console->m_data.get()[i + j * console->m_size.width] = 0;
				}
			}
		}

		namespace gfx
		{
			void draw(const console_t& console, const ALLEGRO::POINT<int32_t>& point)
			{
				al::draw_bitmap(console->m_bitmap, point);
			}
		}

		namespace cursor
		{
			const cursor_t& get(const console_t& console)
			{
				return console->m_cursor;
			}

			void set(console_t& console, const cursor_t& cursor)
			{
				console->m_cursor = cursor;
			}
		}

		namespace bitmap
		{
			ALLEGRO::BITMAP& get(console_t& console)
			{
				return console->m_bitmap;
			}
		}

		namespace font
		{
			void set(console_t& console, font_t& font)
			{
				console->m_font = font;
			}

			const font_t& get(const console_t& console)
			{
				return console->m_font;
			}

			font_t& get(console_t& console)
			{
				return console->m_font;
			}
		}

		namespace palette
		{
			void set(console_t& console, size_t index, uint32_t rgba)
			{
				if (index >= 0 && index < WIND::CONSOLE::PALETTE::SIZE)
				{
					console->m_palette[index] = rgba;
				}
			}

			void set(console_t& console, const palette_t& palette)
			{
				for (size_t index = 0; index < WIND::CONSOLE::PALETTE::SIZE; ++index)
				{
					console->m_palette[index] = palette[index];
				}
			}

			uint32_t get(const console_t& console, size_t index)
			{
				if (index >= 0 && index < WIND::CONSOLE::PALETTE::SIZE)
				{
					return console->m_palette[index];
				}
				return -1;
			}

			const palette_t& get(const console_t& console)
			{
				return console->m_palette;
			}

			palette_t& get(console_t& console)
			{
				return console->m_palette;
			}

			namespace background
			{
				void set(console_t& console, size_t index)
				{
					if (index >= 0 && index < WIND::CONSOLE::PALETTE::SIZE)
					{
						console->m_background = index;
					}
				}

				size_t get(const console_t& console)
				{
					return console->m_background;
				}
			}

			namespace foreground
			{
				void set(console_t& console, size_t index)
				{
					if (index >= 0 && index < WIND::CONSOLE::PALETTE::SIZE)
					{
						console->m_foreground = index;
					}
				}

				size_t get(const console_t& console)
				{
					return console->m_foreground;
				}
			}
		}

		namespace text
		{
			namespace gfx
			{
				void draw(console_t& console, uint8_t c)
				{
					static ALLEGRO::BITMAP target{ nullptr };
					static ALLEGRO::POINT<float> point{ 0.0f, 0.0f };
					static ALLEGRO::COLOR background = { 0.0f, 0.0f, 0.0f, 0.0f };
					static ALLEGRO::COLOR  foreground = { 0.0f, 0.0f, 0.0f, 0.0f };

					point = { float(console->m_cursor.x * WIND::CONSOLE::CELL::WIDTH), float(console->m_cursor.y * WIND::CONSOLE::CELL::HEIGHT) };
					background = wind::map_rgba_i(console->m_palette[console->m_background]);
					foreground = wind::map_rgba_i(console->m_palette[console->m_foreground]);

					target = al::get_target_bitmap();
					al::set_target_bitmap(console::bitmap::get(console));
					draw_font_glyph(console->m_font, background, point, 255);
					draw_font_glyph(console->m_font, foreground, point, c);
					al::set_target_bitmap(target);

					console->m_data.get()[console->m_cursor.x + console->m_cursor.y * console->m_size.width] = c;

					++console->m_cursor.x;
					if (console->m_cursor.x == console->m_size.width)
					{
						console->m_cursor.x = 0;
						++console->m_cursor.y;
						if (console->m_cursor.y == console->m_size.height)
						{
							console->m_cursor.y = 0;
						}
					}
				}
			}
		}

		namespace sprite
		{
			namespace gfx
			{
				void draw(console_t& console, const sprite_t& sprite, const ALLEGRO::POINT<int32_t>& point, int32_t flags)
				{
					draw(console, sprite->m_layers, sprite->m_begin, sprite->m_end, point, flags);
				}

				void draw(console_t& console, const layer_t& layers, int32_t begin, int32_t end, const ALLEGRO::POINT<int32_t>& point, int32_t flags)
				{
					static ALLEGRO::BITMAP target{ nullptr };
					static ALLEGRO::TRANSFORM backup{};
					static ALLEGRO::TRANSFORM t{};
					static font_t font{ nullptr };
					static palette_t* palette{ nullptr };

					palette = &console::palette::get(console);
					font = console::font::get(console);

					target = al::get_target_bitmap();
					al::set_target_bitmap(console::bitmap::get(console));

					al::copy_transform(backup, al::get_current_transform());
					al::identity_transform(t);
					al::translate_transform(t, { -point.x, -point.y });

					if (flags & WIND::CONSOLE::SPRITE::DRAW_FLAGS::FLIP_HORIZONTAL)
					{
						al::scale_transform(t, { -1.0f, 1.0f });
						al::translate_transform(t, { (float)WIND::CONSOLE::CELL::WIDTH * 2.0f, 0.0f });
					}

					if (flags & WIND::CONSOLE::SPRITE::DRAW_FLAGS::FLIP_VERTICAL)
					{
						al::scale_transform(t, { 1.0f, -1.0f });
						al::translate_transform(t, { 0.0f, (float)WIND::CONSOLE::CELL::WIDTH * 2.0f });
					}

					al::translate_transform(t, point);
					al::use_transform(t);

					for (int32_t layer = 0; layer < (1 + (end - begin)); ++layer)
					{
						int index = 0;
						for (int32_t j = 0; j < 2; ++j)
						{
							for (int32_t i = 0; i < 2; ++i)
							{
								ALLEGRO::POINT<float> p = point;
								p.x += i * (float)WIND::CONSOLE::CELL::WIDTH;
								p.y += j * (float)WIND::CONSOLE::CELL::HEIGHT;

								ALLEGRO::COLOR color = wind::map_rgba_i((*palette)[layers.get()[layer + begin].m_color]);
								uint8_t c = layers.get()[layer + begin].m_character[index];
								draw_font_glyph(font, color, p, layers.get()[layer + begin].m_character[index]);
								++index;
							}
						}
					}

					al::use_transform(backup);
					al::set_target_bitmap(target);
				}
			}
		}
	}
}
