module wind.datafile_addon;

import <cassert>;
import <memory>;
import <vector>;
import <string>;
import <cstdint>;
import <any>;
import <functional>;
import <unordered_map>;
import allegro;
import allegro.font_addon;
import allegro.ttf_addon;
import wind;
import :base;
import :object;

namespace wind
{
	namespace datafile::object::font
	{
		using element_type = typename ALLEGRO::FONT;

		using data_t = struct data_tag_t
		{
			string_t m_file{};
			bool m_truetype{ false };
			int32_t m_size{ -1 };
			int32_t m_flags{ 0 };
		};

		static auto generate_object(const data_t& data, std::any& any) -> int32_t
		{
			element_type object{};

			if (data.m_truetype)
			{
				object = al::load_ttf_font(data.m_file.c_str(), data.m_size, data.m_flags);
			}
			else
			{
				object = al::load_font(data.m_file.c_str(), data.m_size, data.m_flags);
			}

			if (!object)
			{
				return -1;
			}

			any = object;

			return 0;
		}

		static auto parse_data(const json_t& json, data_t& value) -> int32_t
		{
			if (json.get_type() != WIND::JSON::TYPE::OBJECT)
			{
				return -1;
			}

			const json_object_t& object = json.get_as_object();

			auto it = object.find("file");
			if (it == object.cend())
			{
				return -1;
			}

			if (wind::json::initializer::parse<string_t>(*it, value.m_file) < 0)
			{
				return -1;
			}

			it = object.find("truetype");
			if (it == object.cend())
			{
				value.m_truetype = false;
			}
			else
			{
				if (wind::json::initializer::parse<bool>(*it, value.m_truetype) < 0)
				{
					return -1;
				}
			}

			it = object.find("size");
			if (it == object.cend())
			{
				return -1;
			}

			if (wind::json::initializer::parse<int32_t>(*it, value.m_size) < 0)
			{
				return -1;
			}

			it = object.find("flags");
			if (it == object.cend())
			{
				value.m_flags = 0;
			}
			else
			{
				const std::unordered_map<string_t, int32_t> map
				{ {
					{ "no_kerning", ALLEGRO::FLAG_TTF_NO_KERNING },
					{ "monochrome", ALLEGRO::FLAG_TTF_MONOCHROME },
					{ "no_premultified_alpha", ALLEGRO::FLAG_NO_PREMULTIPLIED_ALPHA }
				} };
				string_t string{};

				if (wind::json::initializer::parse<string_t>(*it, string) < 0)
				{
					return -1;
				}

				int32_t flags = wind::flag::parse_map(map, string, '|');
				if (flags < 0)
				{
					return -1;
				}

				value.m_flags = flags;
			}

			return 0;
		}

		auto parse(const json_t& json, std::any& any) -> int32_t
		{
			data_t data{};

			if (parse_data(json, data) < 0)
			{
				return -1;
			}

			if (generate_object(data, any) < 0)
			{
				return -1;
			}

			return 0;
		}
	}
}
