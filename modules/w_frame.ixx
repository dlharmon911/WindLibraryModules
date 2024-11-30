export module wind:frame;

import <string>;
import <cstdint>;
import allegro;
import :base;
import :math;

namespace wind
{
	namespace theme
	{
		export enum colors
		{
			background,
			foreground,
			workspace,
			border,
			border_light,
			border_dark,
			text,
			text_shadow,
			_count
		};
	}

	namespace frame
	{
		namespace border
		{
			export enum class type
			{
				none,
				raised,
				sunken,
				ridge,
				groove,
				workspace,
				solid
			};
		}

		export enum class type
		{
			normal,
			workspace
		};

		export auto draw(const ALLEGRO::POINT<float> point, const ALLEGRO::SIZE<float> dim, frame::type type = type::normal, frame::border::type border = border::type::raised) -> void;
	}
}