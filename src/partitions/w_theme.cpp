module wind;

import <cstdint>;
import :base;
import :hex;
import :string;
import :color;
import :theme;

namespace wind
{
	namespace theme
	{
		static const theme::data_t default_theme
		{
			0x5d6b99ff,
			0xe9efffff,
			0xccd5f0ff,
			0xf7f9feff,
			0x828182ff,
			0xe0e0e0ff,
			0x424142ff,
			0x121218ff,
			0x828182ff
		};
	}

	theme::data_t theme_t::m_theme = theme::default_theme;

	auto theme_t::get_theme() -> const theme::data_t&
	{
		return m_theme;
	}

	auto theme_t::set_theme(const theme::data_t& theme) -> void
	{
		theme_t::m_theme = theme;
	}

	auto theme_t::set_color(WIND::THEME::COLOR color, uint32_t value) -> void
	{
		theme_t::m_theme[std::to_underlying(color)] = value;
	}

	auto theme_t::get_color(WIND::THEME::COLOR color) -> ALLEGRO::COLOR
	{
		return map_rgba_i(theme_t::m_theme[std::to_underlying(color)]);
	}
}
