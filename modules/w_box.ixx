export module wind:box;

import <string>;
import <cstdint>;
import allegro;
import :base;
import :math;

namespace wind
{
	namespace box
	{
		export template <typename T, typename Q>
			auto is_point_inside(const ALLEGRO::BOX<T>& box, const ALLEGRO::POINT<Q>& point) -> bool
		{
			return (math.compare<T>(T(point.x), box.top_left.x) >= 0 &&
				math.compare<T>(T(point.y), box.top_left.y) >= 0 &&
				math.compare<T>(T(point.x), box.bottom_right.x) <= 0 &&
				math.compare<T>(T(point.y), box.bottom_right.y) <= 0);
		}

		export template <typename T, typename Q>
			auto is_box_inside(const ALLEGRO::BOX<T>& box, const ALLEGRO::BOX<Q>& other) -> bool
		{
			return (is_point_inside(box, other.top_left) && is_point_inside(box, other.bottom_right));
		}

		export template <typename T, typename Q>
			auto is_box_over(const ALLEGRO::BOX<T>& box, const ALLEGRO::BOX<Q>& other, ALLEGRO::BOX<T>& over) -> bool
		{
			if (wind::math::compare<T>(T(other.bottom_right.x), box.top_left.x) < 0 ||
				wind::math::compare<T>(T(other.top_left.x), box.bottom_right.x) > 0 ||
				wind::math::compare<T>(T(other.bottom_right.y), box.top_left.y) < 0 ||
				wind::math::compare<T>(T(other.top_left.y), box.bottom_right.y) > 0)
			{
				return false;
			}

			over.top_left.x = std::max(other.top_left.x, box.top_left.x);
			over.bottom_right.x = std::min(other.bottom_right.x, box.bottom_right.x);
			over.top_left.y = std::max(other.top_left.y, box.top_left.y);
			over.bottom_right.y = std::min(other.bottom_right.y, box.bottom_right.y);

			return true;
		}
	}
}
