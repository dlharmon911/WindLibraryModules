export module wind:frame;

import <string>;
import <cstdint>;
import allegro;
import :base;
import :math;

namespace WIND
{
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
			WORKSPACE,
			MENU
		};
	}
}

namespace wind::frame
{
	export auto draw(const ALLEGRO::RECTANGLE<float>& rectangle, WIND::FRAME::TYPE type = WIND::FRAME::TYPE::NORMAL, WIND::FRAME::BORDER::TYPE border = WIND::FRAME::BORDER::TYPE::RAISED) -> void;
	export auto draw(const ALLEGRO::VECTOR_2D<float>& point, const ALLEGRO::VECTOR_2D<float>& size, WIND::FRAME::TYPE type = WIND::FRAME::TYPE::NORMAL, WIND::FRAME::BORDER::TYPE border = WIND::FRAME::BORDER::TYPE::RAISED) -> void;
}
