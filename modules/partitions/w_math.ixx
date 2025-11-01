export module wind:math;

export import <cmath>;
import :base;

namespace wind::math
{
	export template <typename T> constexpr auto epsilon() -> T requires std::is_arithmetic_v<T>
	{
		return static_cast<T>(0);
	}

	export template <> constexpr auto epsilon<double>() -> double
	{
		return 2.2204460492503131e-016;
	}

	export template <> constexpr auto epsilon<float>() -> float
	{
		return 1.192092896e-07f;
	}

	export template <typename T> auto absolute(T value) -> T requires std::is_arithmetic_v<T>
	{
		if (value < static_cast<T>(0))
		{
			return -value;
		}
		return value;
	}

	export template <typename T> constexpr auto are_equal(T a, T b) -> bool requires std::is_arithmetic_v<T>
	{
		return absolute(a - b) < epsilon<T>();
	}

	export template <typename T> constexpr auto is_zero(T a) -> bool requires std::is_arithmetic_v<T>
	{
		return absolute(a) < epsilon<T>();
	}

	export template <typename T> constexpr auto sqrt(T val) -> T requires std::is_floating_point_v<T>
	{
		if (val < static_cast<T>(0.0) || val == std::numeric_limits<T>::infinity())
		{
			throw std::domain_error("Cannot compute square root of negative number or infinity.");
		}

		T result{ val };
		T last{ static_cast<T>(0.0) };

		// Refactored loop to be less error-prone and avoid float/double as loop counter
		while (result != last)
		{
			last = result;
			result = static_cast<T>(0.5) * (result + val / result);
		}

		return result;
	}

	export template <typename T> auto clamp(T value, T min, T max) -> T requires std::is_floating_point_v<T>
	{
		if (value < min)
		{
			return min;
		}
		if (value > max)
		{
			return max;
		}
		return value;
	}

	export template <typename T> auto negate(T& value) -> T requires std::is_arithmetic_v<T>
	{
		return -value;
	}

	export template <typename T> auto subtract(T& a, T& b) -> T requires std::is_arithmetic_v<T>
	{
		return (a - b);
	}

	export template <typename T> auto add(T& a, T& b) -> T requires std::is_arithmetic_v<T>
	{
		return (a + b);
	}

	export template<typename T, typename Q> auto multiply(T& value, Q factor) -> T requires std::is_arithmetic_v<T>
	{
		return (value * factor);
	}

	export template<typename T, typename Q> auto divide(T& value, Q factor) -> T requires std::is_arithmetic_v<T>
	{
		if (is_zero(factor))
		{
			return std::numeric_limits<T>::infinity();
		}
		return (value / factor);
	}

	export template<typename T, typename Q> auto lerp(T& a, T& b, Q factor) -> T requires std::is_floating_point_v<T>
	{
		return (a + (b - a) * factor);
	}
}

export template <typename T> auto operator + (T& a, T& b) -> T requires std::is_arithmetic_v<T>
{
	return wind::math::add(a, b);
}

export template <typename T> auto operator - (T& a, T& b) -> T requires std::is_arithmetic_v<T>
{
	return wind::math::subtract(a, b);
}

export template<typename T, typename Q> auto operator * (T& value, Q factor) -> T requires std::is_arithmetic_v<T>
{
	return wind::math::multiply(value, factor);
}

export template<typename T, typename Q> auto operator / (T& value, Q factor) -> T requires std::is_arithmetic_v<T>
{
	return wind::math::divide(value, factor);
}

export template <typename T> auto operator - (T& value) -> T requires std::is_arithmetic_v<T>
{
	return wind::math::negate(value);
}
