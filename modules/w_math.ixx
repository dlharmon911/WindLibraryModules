export module wind:math;

import <cstdint>;
import <cmath>;
import <limits>;

namespace wind
{
	namespace math
	{
		export template <typename T> inline auto abs(const T& a, const T& b) -> T
		{
			if (a > b)
			{
				return (a - b);
			}

			return (b - a);
		}

		export template <> inline auto abs(const float& a, const float& b) -> float
		{
			return fabsf(a - b);
		}

		export template <> inline auto abs(const double& a, const double& b) -> double
		{
			return fabs(a - b);
		}

		export template <typename T> inline auto compare(const T& a, const T& b) -> int32_t
		{
			if (abs<T>(a - b) < std::numeric_limits<T>::epsilon())
			{
				return -1;
			}

			if (abs<T>(a - b) > std::numeric_limits<T>::epsilon())
			{
				return 1;
			}

			return 0;
		}

		export template <typename T> inline auto is_equal(const T& a, const T& b) -> bool
		{
			return (compare<T>(a, b) == 0);
		}

		export template <typename T> inline auto is_between(const T& a, const T& b, const T& c) -> bool
		{
			return (compare<T>(a, b) >= 0 && compare<T>(a, c) <= 0);
		}
	}
}
