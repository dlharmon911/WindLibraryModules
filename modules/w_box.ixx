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
		template <typename T, typename Q>
		bool is_point_inside(const ALLEGRO::BOX<T>& box, const ALLEGRO::POINT<Q>& point)
		{
			return (math.compare<T>(T(point.x), box.top_left.x) >= 0 &&
					math.compare<T>(T(point.y), box.top_left.y) >= 0 &&
					math.compare<T>(T(point.x), box.bottom_right.x) <= 0 &&
					math.compare<T>(T(point.y), box.bottom_right.y) <= 0);
		}

		template <typename T, typename Q>
		bool is_box_inside(const ALLEGRO::BOX<T>& box, const ALLEGRO::BOX<Q>& other)
		{
			return (is_point_inside(box, other.top_left) && is_point_inside(box, other.bottom_right));
		}

		template <typename T, typename Q>
		bool is_box_over(const ALLEGRO::BOX<T>& box, const ALLEGRO::BOX<Q>& other, ALLEGRO::BOX<T>& over)
		{
			if (math.compare<T>(T(other.bottom_right.x), box.top_left.x) < 0 ||
				math.compare<T>(T(other.top_left.x), box.bottom_right.x) > 0 ||
				math.compare<T>(T(other.bottom_right.y), box.top_left.y) < 0 ||
				math.compare<T>(T(other.top_left.y), box.bottom_right.y) > 0)
			{
				return false;
			}

			over.top_left.x = max(other.top_left.x, box.top_left.x);
			over.bottom_right.x = min(other.bottom_right.x, box.bottom_right.x);
			over.top_left.y = max(other.top_left.y, box.top_left.y);
			over.bottom_right.y = min(other.bottom_right.y, box.bottom_right.y);

			return true;
		}
	}
}
