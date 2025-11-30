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

	export struct color_t
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

		auto operator = (const ALLEGRO::COLOR& al_color) -> color_t&
		{
			*this = *reinterpret_cast<const color_t*>(&al_color);
			return *this;
		}

		auto operator = (const color_t& other) -> color_t&
		{
			this->m_r = other.m_r;
			this->m_g = other.m_g;
			this->m_b = other.m_b;
			this->m_a = other.m_a;
			return *this;
		}
	};
}
