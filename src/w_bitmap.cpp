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
		auto is_empty(ALLEGRO::BITMAP& bitmap) -> bool
		{
			bool rv = true;
			ALLEGRO::BITMAP_LOCKED_REGION region = al::lock_bitmap(bitmap, ALLEGRO::PIXEL_FORMAT_ANY, ALLEGRO::BITMAP_LOCK_READ_ONLY);

			if (region)// && al::is_bitmap_locked(bitmap))
			{
				ALLEGRO::COLOR color;
				ALLEGRO::SIZE<size_t> b_size = { al::get_bitmap_width(bitmap), al::get_bitmap_height(bitmap) };
				ALLEGRO::POINT<int32_t> point;

				for (size_t j = 0; j < b_size.height; ++j)
				{
					for (size_t i = 0; i < b_size.width; ++i)
					{
						point = { i, j };
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
	}
}