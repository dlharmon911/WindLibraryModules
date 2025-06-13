export module wind:theme;

import <string>;
import <cstdint>;
import <array>;
import allegro;
import :base;
import :math;

namespace WIND
{
	namespace THEME
	{
		export enum class COLOR : int32_t
		{
			BACKGROUND,
			FOREGROUND,
			MENU,
			WORKSPACE,
			BORDER,
			BORDER_LIGHT,
			BORDER_DARK,
			TEXT,
			TEXT_SHADOW,
			COUNT
		};
	}
}

namespace wind
{
	namespace theme
	{
		using data_t = std::array<uint32_t, std::to_underlying(WIND::THEME::COLOR::COUNT)>;
	}

	export class theme_t
	{
	public:
		theme_t() = delete;
		theme_t(const theme_t& font) = delete;
		~theme_t() = default;

		static auto get_theme() -> const theme::data_t&;
		static auto set_theme(const theme::data_t& theme) -> void;
		static auto set_color(WIND::THEME::COLOR color, uint32_t value) -> void;
		static auto get_color(WIND::THEME::COLOR color) -> ALLEGRO::COLOR;


	private:
		static theme::data_t m_theme;
	};
}
