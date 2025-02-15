export module wind:frame;

import <string>;
import <cstdint>;
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
			WORKSPACE,
			BORDER,
			BORDER_LIGHT,
			BORDER_DARK,
			TEXT,
			TEXT_SHADOW,
			COUNT
		};
	}

	namespace FRAME
	{
		namespace BORDER
		{
			export enum class TYPE : int32_t
			{
				NONE,
				RAISED,
				SUNKEN,
				RIDGE,
				GROOVE,
				WORKSPACE,
				SOLID
			};
		}

		export enum class TYPE : int32_t
		{
			NORMAL,
			WORKSPACE
		};
	}
}

namespace wind::frame
{
	export auto draw(const ALLEGRO::POINT<float>& point, const ALLEGRO::SIZE<float>& dim, WIND::FRAME::TYPE type = WIND::FRAME::TYPE::NORMAL, WIND::FRAME::BORDER::TYPE border = WIND::FRAME::BORDER::TYPE::RAISED) -> void;
}
