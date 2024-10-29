export module wind:math;

import <cstdint>;
import <cmath>;
import <limits>;

namespace wind
{
	namespace math
	{
		export template <typename T> T abs(const T& a, const T& b)
		{
			if (a > b)
			{
				return (a - b);
			}

			return (b - a);
		}

		template <> float abs(const float& a, const float& b)
		{
			return fabsf(a - b);
		}

		template <> double abs(const double& a, const double& b)
		{
			return fabs(a - b);
		}

		export template <typename T> inline int32_t compare(const T& a, const T& b)
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

		export template <typename T> inline bool is_equal(const T& a, const T& b)
		{
			return (compare<T>(a, b) == 0);
		}

		export template <typename T> inline bool is_between(const T& a, const T& b, const T& c)
		{
			return (compare<T>(a, b) >= 0 && compare<T>(a, c) <= 0);
		}
	}
}
