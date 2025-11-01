export module wind:color.base;

import :base;
import :color.constants;

namespace wind
{
	namespace color
	{
		export using type_t = typename float;
		export using array_t = typename std::array<type_t, WIND::COLOR::ARRAY_SIZE>;
	}

	export using color_t = struct color_tag_t
	{
		union
		{
			struct
			{
				color::type_t m_r;
				color::type_t m_g;
				color::type_t m_b;
				color::type_t m_a;
			};
			color::array_t m_array{ 0.0f, 0.0f, 0.0f, 0.0f };
		};

		operator ALLEGRO::COLOR() const
		{
			return *reinterpret_cast<const ALLEGRO::COLOR*>(this);
		}
	};
}
