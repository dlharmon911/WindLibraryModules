module wind;

import <cstdint>;
import :bitmap;
import :base;
import :string;
import allegro;
import allegro.image_addon;

namespace wind
{
	namespace bitmap
	{
		auto is_empty(const ALLEGRO::BITMAP& bitmap) -> bool
		{
			bool rv = true;

			ALLEGRO::BITMAP_LOCKED_REGION region = al::lock_bitmap(bitmap, ALLEGRO::PIXEL_FORMAT_ANY, ALLEGRO::BITMAP_LOCK_READ_ONLY);

			if (region)
			{
				ALLEGRO::COLOR color;
				ALLEGRO::SIZE<size_t> b_size = { al::get_bitmap_width(bitmap), al::get_bitmap_height(bitmap) };
				ALLEGRO::POINT<float> point;

				for (size_t j = 0; j < b_size.height; ++j)
				{
					for (size_t i = 0; i < b_size.width; ++i)
					{
						point = { (float)i, (float)j };
						color = al::get_pixel(bitmap, point);

						if (fabs(color.alpha - 0.0f) > std::numeric_limits<float>::epsilon())
						{
							i = b_size.width;
							j = b_size.height;
							rv = false;
						}
					}
				}

				al::unlock_bitmap(bitmap);
			}

			return rv;
		}

		auto flood_fill(const ALLEGRO::BITMAP& bitmap, const ALLEGRO::RECTANGLE<int32_t>& region) -> void
		{
			ALLEGRO::SIZE<int32_t> bgsize = al::get_bitmap_dimensions(bitmap);

			const ALLEGRO::RECTANGLE<int32_t> clip = al::get_clipping_rectangle();
			al::set_clipping_rectangle(region);

			for (int32_t y = region.position.y; y < (region.position.y + region.size.height); y += bgsize.height)
			{
				for (int32_t x = region.position.x; x < (region.position.x + region.size.width); x += bgsize.width)
				{
					al::draw_bitmap(bitmap, { x, y });
				}
			}
			al::set_clipping_rectangle(clip);
		}
	}
}
