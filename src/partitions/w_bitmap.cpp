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
				ALLEGRO::VECTOR_2D<size_t> b_size(al::get_bitmap_width(bitmap), al::get_bitmap_height(bitmap));
				ALLEGRO::VECTOR_2D<float> point{};

				for (size_t j = 0; j < b_size.get_y(); ++j)
				{
					for (size_t i = 0; i < b_size.get_x(); ++i)
					{
						point.set_values(static_cast<float>(i), static_cast<float>(j));
						color = al::get_pixel(bitmap, point);

						if (std::abs<float>(color.a - 0.0f) > std::numeric_limits<float>::epsilon())
						{
							i = b_size.get_x();
							j = b_size.get_y();
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
			ALLEGRO::VECTOR_2D<int32_t> bgsize = al::get_bitmap_dimensions(bitmap);

			const ALLEGRO::RECTANGLE<int32_t> clip = al::get_clipping_rectangle();
			al::set_clipping_rectangle(region);

			for (int32_t y = region.get_y(); y < (region.get_y() + region.get_height()); y += bgsize.get_y())
			{
				for (int32_t x = region.get_x(); x < (region.get_x() + region.get_width()); x += bgsize.get_x())
				{
					al::draw_bitmap(bitmap, { static_cast<float>(x), static_cast<float>(y) });
				}
			}
			al::set_clipping_rectangle(clip);
		}
	}
}
