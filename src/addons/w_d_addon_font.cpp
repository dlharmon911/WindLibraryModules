module wind.d_addon;

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

		static auto load_data(const data_t& data, element_type& object) -> int32_t
		{
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

			return 0;
		}
	}

	namespace json
	{
		namespace initializer
		{
			static auto get_flag(const string_t& string) -> int32_t
			{
				std::unordered_map<string_t, int32_t> map
				{ {
					{ "no_kerning", ALLEGRO::FLAG_TTF_NO_KERNING },
					{ "monochrome", ALLEGRO::FLAG_TTF_MONOCHROME },
					{ "no_premultified_alpha", ALLEGRO::FLAG_NO_PREMULTIPLIED_ALPHA }
				} };

				auto it = map.find(string);
				if (it == map.cend())
				{
					return -1;
				}

				return it->second;
			}

			template <> auto parse(const json_t& json, datafile::object::font::data_t& value) -> int32_t
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

				if (parse<string_t>(*it, value.m_file) < 0)
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
					if (parse<bool>(*it, value.m_truetype) < 0)
					{
						return -1;
					}
				}

				it = object.find("size");
				if (it == object.cend())
				{
					return -1;
				}

				if (parse<int32_t>(*it, value.m_size) < 0)
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
					std::vector<string_t> flags{};
					string_t flag_s{};

					if (parse<string_t>(*it, flag_s) < 0)
					{
						return -1;
					}

					if (string::separate(flag_s, flags, '|') == 0)
					{
						return -1;
					}

					for (auto& a : flags)
					{
						int32_t flag = get_flag(a);
						
						if (flag < 0)
						{
							return -1;
						}

						value.m_flags |= flag;
					}
				}

				return 0;
			}
		}
	}

	namespace datafile::object::font
	{
		auto parse(const json_t& json, std::any& any) -> int32_t
		{
			element_type object{};
			data_t data{};

			if (json::initializer::parse<data_t>(json, data) < 0)
			{
				return -1;
			}

			if (load_data(data, object) < 0)
			{
				return -1;
			}

			any = object;

			return 0;
		}
	}
}
