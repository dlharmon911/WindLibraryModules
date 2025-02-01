export module wind:math;

import <cstdint>;
import <cmath>;
import <limits>;

namespace WIND
{
	namespace MATH
	{
		export constexpr double CONSTANT_1DIVPI = 0.3183098861837906715377675267450287240689192914809129;
		export constexpr double CONSTANT_2DIVPI = 0.6366197723675813430755350534900574481378385829618258;
		export constexpr double CONSTANT_2DIVSQRTPI = 1.1283791670955125738961589031215451716881012586579977;
		export constexpr double CONSTANT_2PI = 6.2831853071795864769252867665590057683943387987502116;
		export constexpr double CONSTANT_4DIVPI = 1.2732395447351626861510701069801148962756771659236516;
		export constexpr double CONSTANT_DEGTORAD = 0.0174532925199432957692369076848861271344287188854173;
		export constexpr double CONSTANT_E = 2.7182818284590452353602874713526624977572470936999595;
		export constexpr double CONSTANT_FWHMTOSIG = 2.3548200450309493820231386529193992754947713787716411;
		export constexpr double CONSTANT_LN10 = 2.3025850929940456840179914546843642076011014886287730;
		export constexpr double CONSTANT_LN2 = 0.6931471805599453094172321214581765680755001343602553;
		export constexpr double CONSTANT_LOG10E = 0.4342944819032518276511289189166050822943970058036666;
		export constexpr double CONSTANT_LOG2E = 1.4426950408889634073599246810018921374266459541529859;
		export constexpr double CONSTANT_PI = 3.1415926535897932384626433832795028841971693993751058;
		export constexpr double CONSTANT_PIDIV2 = 1.5707963267948966192313216916397514420985846996875529;
		export constexpr double CONSTANT_PIDIV4 = 0.7853981633974483096156608458198757210492923498437765;
		export constexpr double CONSTANT_RADTODEG = 57.295779513082320876798154814105170332405472466564322;
		export constexpr double CONSTANT_SIGTOFWHM = 0.4246609001440095213607514170514448098575705468921770;
		export constexpr double CONSTANT_SQRT1DIV2 = 0.7071067811865475244008443621048490392848359376884740;
		export constexpr double CONSTANT_SQRT2 = 1.4142135623730950488016887242096980785696718753769481;
		export constexpr double CONSTANT_SQRT2PI = 2.5066282746310005024157652848110452530069867406099383;
		export constexpr double CONSTANT_SQRT3 = 1.7320508075688772935274463415058723669428052538103806;
	}
}

namespace wind
{
	namespace math
	{
		export constexpr int32_t power_2(int32_t value)
		{
			return (1 << value);
		}

		export template <typename T> inline auto sin(const T& a) -> T { return std::sin(a); }
		export template <typename T> inline auto cos(const T& a) -> T { return std::cos(a); }
		export template <typename T> inline auto tan(const T& a) -> T { return std::tan(a); }
		export template <typename T> inline auto asin(const T& a) -> T { return std::asin(a); }
		export template <typename T> inline auto acos(const T& a) -> T { return std::acos(a); }
		export template <typename T> inline auto atan(const T& a) -> T { return std::atan(a); }
		export template <typename T> inline auto sinh(const T& a) -> T { return std::sinh(a); }
		export template <typename T> inline auto cosh(const T& a) -> T { return std::cosh(a); }
		export template <typename T> inline auto tanh(const T& a) -> T { return std::tanh(a); }
		export template <typename T> inline auto exp(const T& a) -> T { return std::exp(a); }
		export template <typename T> inline auto log(const T& a) -> T { return std::log(a); }
		export template <typename T> inline auto log10(const T& a) -> T { return std::log10(a); }
		export template <typename T> inline auto sqrt(const T& a) -> T { return std::sqrt(a); }
		export template <typename T> inline auto ceil(const T& a) -> T { return std::ceil(a); }
		export template <typename T> inline auto floor(const T& a) -> T { return std::floor(a); }
		export template <typename T> inline auto abs(const T& a) -> T { return std::abs(a); }

		export template <typename T> inline auto to_radians(const T& angle) -> T
		{
			return (angle * WIND::MATH::CONSTANT_DEGTORAD);
		}

		export template <typename T> inline auto to_degrees(const T& angle) -> T
		{
			return (angle * WIND::MATH::CONSTANT_RADTODEG);
		}

		export template <typename T> inline auto atan2(const T& a, const T& b) -> T
		{
			return std::atan2(a, b);
		}

		export template <typename T> inline auto pow(const T& a, const T& b) -> T
		{
			return std::pow(a, b);
		}

		export template <typename T> inline auto logb(const T& base, const T& d) -> T
		{
			return (math::log(d) / math::log(base));
		}

		export template <typename T> inline auto hypot(const T& a, const T& b) -> T
		{
			return (math::sqrt((a * a) + (b * b)));
		}

		export template <typename T> inline auto compare(const T& a, const T& b) -> int32_t
		{
			return (a - b);
		}

		export template <typename T> inline auto is_zero(const T& a) -> bool
		{
			return (a <= std::numeric_limits<T>::epsilon());
		}

		export template <typename T> inline auto is_equal(const T& a, const T& b) -> bool
		{
			return (is_zero(compare<T>(a, b)));
		}

		export template <typename T> inline auto is_between(const T& a, const T& b, const T& c) -> bool
		{
			return (compare<T>(a, b) >= 0 && compare<T>(a, c) <= 0);
		}

		export template<class T> inline auto sign(const T d) -> T
		{
			return ((d >= T(0)) ? T(1) : -T(1));
		}
	}
}