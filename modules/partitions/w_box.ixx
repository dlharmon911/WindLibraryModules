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
			auto is_point_inside(const ALLEGRO::BOX<T>& box, const ALLEGRO::VECTOR_2D<Q>& point) -> bool
		{
			return (math.compare<T>(T(point.get_x()), box.top_left.get_x()) >= 0 &&
				math.compare<T>(T(point.get_y()), box.top_left.get_y()) >= 0 &&
				math.compare<T>(T(point.get_x()), box.bottom_right.get_x()) <= 0 &&
				math.compare<T>(T(point.get_y()), box.bottom_right.get_y()) <= 0);
		}

		export template <typename T, typename Q>
			auto is_box_inside(const ALLEGRO::BOX<T>& box, const ALLEGRO::BOX<Q>& other) -> bool
		{
			return (is_point_inside(box, other.top_left) && is_point_inside(box, other.bottom_right));
		}

		export template <typename T, typename Q>
			auto is_box_over(const ALLEGRO::BOX<T>& box, const ALLEGRO::BOX<Q>& other, ALLEGRO::BOX<T>& over) -> bool
		{
			if (wind::math::compare<T>(T(other.bottom_right.get_x()), box.top_left.get_x()) < 0 ||
				wind::math::compare<T>(T(other.top_left.get_x()), box.bottom_right.get_x()) > 0 ||
				wind::math::compare<T>(T(other.bottom_right.get_y()), box.top_left.get_y()) < 0 ||
				wind::math::compare<T>(T(other.top_left.get_y()), box.bottom_right.get_y()) > 0)
			{
				return false;
			}

			over.top_left.get_x() = std::max(other.top_left.get_x(), box.top_left.get_x());
			over.bottom_right.get_x() = std::min(other.bottom_right.get_x(), box.bottom_right.get_x());
			over.top_left.get_y() = std::max(other.top_left.get_y(), box.top_left.get_y());
			over.bottom_right.get_y() = std::min(other.bottom_right.get_y(), box.bottom_right.get_y());

			return true;
		}
	}
}
