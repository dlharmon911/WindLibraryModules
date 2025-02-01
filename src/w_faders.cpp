module wind;

import <cstdint>;
import allegro;
import :base;
import :faders;

namespace wind
{
	namespace faders
	{
		auto in(const ALLEGRO::BITMAP& bitmap, double speed) -> void
		{
			double segment(wind::math::abs<double>(speed) / (double)WIND::FADERS::DIVISIONS);
			ALLEGRO::SIZE<int32_t> bsize{ al::get_bitmap_dimensions(bitmap) };
			ALLEGRO::SIZE<int32_t> dsize{ al::get_display_dimensions(wind::system::display::get()) };
			ALLEGRO::COLOR tint{ 0.0f, 0.0f, 0.0f, 0.0f };

			wind::system::timer::pause();

			for (size_t i = 0; i < 100; ++i)
			{
				tint.red = tint.green = tint.blue = tint.alpha = (float)(i) / (double)WIND::FADERS::DIVISIONS;
				al::clear_to_color(al::map_rgb(0, 0, 0));
				al::draw_tinted_scaled_bitmap(bitmap, tint, { {0, 0}, bsize }, { { 0, 0 }, dsize });

				al::flip_display();
				al::rest(segment);
			}

			wind::system::timer::unpause();
		}

		auto out(const ALLEGRO::BITMAP& bitmap, double speed) -> void
		{
			double segment(wind::math::abs<double>(speed) / (double)WIND::FADERS::DIVISIONS);
			ALLEGRO::SIZE<int32_t> bsize{ al::get_bitmap_dimensions(bitmap) };
			ALLEGRO::SIZE<int32_t> dsize{ al::get_display_dimensions(wind::system::display::get()) };
			ALLEGRO::COLOR tint{ 0.0f, 0.0f, 0.0f, 0.0f };

			wind::system::timer::pause();

			for (size_t i = (WIND::FADERS::DIVISIONS - 1); i > 0; --i)
			{
				tint.red = tint.green = tint.blue = tint.alpha = (float)(i) / (double)WIND::FADERS::DIVISIONS;
				al::clear_to_color(al::map_rgb(0, 0, 0));
				al::draw_tinted_scaled_bitmap(bitmap, tint, { {0, 0}, bsize }, { { 0, 0 }, dsize });

				al::flip_display();
				al::rest(segment);
			}

			wind::system::timer::unpause();
		}

		auto out(double speed) -> void
		{
			const ALLEGRO::DISPLAY& display = wind::system::display::get();
			ALLEGRO::BITMAP buffer = al::get_backbuffer(display);
			ALLEGRO::BITMAP clone = al::clone_bitmap(buffer);
			faders::out(clone, speed);
		}

		auto in(double speed) -> void
		{
			const ALLEGRO::DISPLAY& display = wind::system::display::get();
			ALLEGRO::BITMAP buffer = al::get_backbuffer(display);
			ALLEGRO::BITMAP clone = al::clone_bitmap(buffer);
			faders::in(clone, speed);
		}

		auto across(const ALLEGRO::BITMAP& bitmap_a, const ALLEGRO::BITMAP& bitmap_b, double speed) -> void
		{
			faders::out(bitmap_a, speed * 0.5);
			faders::in(bitmap_b, speed * 0.5);
		}
	}
}