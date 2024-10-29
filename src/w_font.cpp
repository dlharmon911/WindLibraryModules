module wind;

import <cstdint>;
import :bitmap;
import :base;
import :string;
import allegro;
import allegro.font_addon;
import allegro.ttf_addon;
import wind.datafile_addon;

namespace wind
{
	namespace datafile
	{
		namespace object
		{
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


		}
	}
}
