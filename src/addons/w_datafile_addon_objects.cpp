module wind.datafile_addon;

import <cstdint>;
import allegro;
import allegro.image_addon;
import allegro.font_addon;
import allegro.ttf_addon;
import wind;

namespace wind
{
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

			bool font_parser(data_t& data, object_t& object)
			{
				string_t file{};
				string_t working{ path::get_working_directory() };
				string_t filepath{};
				string_t base{};
				string_t ext{};
				string_t path{};
				int32_t size{ 0 };
				bool truetype{ false };
				string_t flag_string{};
				int32_t flags{ 0 };
				std::vector<string_t> flag_vector{};
				size_t sz{ 0 };

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

				if (!data.find_data("size", size))
				{
					return false;
				}

				data.find_data("truetype", truetype, false);

				if (!data.find_data("flags", flag_string))
				{
					return false;
				}

				sz = string::separate(flag_string, flag_vector, '|');

				for (auto a : flag_vector)
				{
					if (truetype)
					{
						if (a == "no_kerning") flags |= ALLEGRO::FLAG_TTF_NO_KERNING;
						if (a == "monochrome") flags |= ALLEGRO::FLAG_TTF_MONOCHROME;
					}
					else
					{
						if (a == "no_premultified_alpha") flags |= ALLEGRO::FLAG_NO_PREMULTIPLIED_ALPHA;
					}
				}

				if (truetype)
				{
					object.m_object = al::load_ttf_font(filepath.c_str(), size, flags);
				}
				else
				{
					object.m_object = al::load_font(filepath.c_str(), size, flags);
				}

				if (!object.m_object)
				{
					wind::error::push(string::to_string("Could not load font from \"%s\" attribute", file.c_str()), __FILE__, __LINE__, __FUNCTION__);
				}

				return (bool)object.m_object;
			}

			bool text_parser(data_t& data, object_t& object)
			{
				if (data.has_content())
				{
					object.m_object = al::ustr_dup(data.get_string().u_str());
					ALLEGRO::ASSERT(object.m_object);
				}

				return (bool)object.m_object;
			}
		}
	}
}