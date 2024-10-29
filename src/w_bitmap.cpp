module wind;

import <cstdint>;
import :bitmap;
import :base;
import :string;
import allegro;
import allegro.image_addon;
import wind.datafile_addon;


namespace wind
{
	namespace bitmap
	{
		bool is_empty(ALLEGRO::BITMAP& bitmap)
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

	namespace datafile
	{
		namespace object
		{
			bool bitmap_parser(data_t& data, object_t& object)
			{
				string_t file;
				string_t working = path::get_working_directory();
				string_t filepath;
				string_t base;
				string_t ext;
				string_t path;
				bool masked = false;

				if (!data.find_data("file", file))
				{
					return false;
				}

				filepath = path::make_canonical(file);

				path::split_filepath(filepath, path, base, ext);

				if (base.size() == 0)
				{
					wind::error::push("Invalid \"file\" attribute", __FILE__, __LINE__, __FUNCTION__);
					return false;
				}

				if (!al::filename_exists(filepath.c_str()))
				{
					wind::error::push(string::to_string("File \"%s\" not found", file.c_str()), __FILE__, __LINE__, __FUNCTION__);
					return false;
				}

				object.m_object = al::load_bitmap(filepath.c_str());
				if (!object.m_object)
				{
					wind::error::push(string::to_string("Could not load bitmap from \"%s\" attribute", file.c_str()), __FILE__, __LINE__, __FUNCTION__);
					return false;
				}

				data.find_data("masked", masked);

				if (masked)
				{
					ALLEGRO::BITMAP bitmap = std::static_pointer_cast<ALLEGRO::BITMAP_DATA>(object.m_object);
					al::convert_mask_to_alpha(bitmap, al::map_rgb(255, 0, 255));
				}

				return (bool)object.m_object;
			}
		}
	}
}