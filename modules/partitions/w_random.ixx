export module wind:random;

import <cstdlib>;
import <cstdint>;
import :base;

namespace wind::random
{
	namespace internal
	{
		static auto get_seed() -> uint32_t&
		{
			static uint32_t seed{ 0 };
			return seed;
		}
	}

	export auto set_seed(uint32_t seed) -> void
	{
		internal::get_seed() = seed;
		srand(seed);
	}

	export auto get_seed() -> uint32_t
	{
		return internal::get_seed();
	}

	export template <typename T> auto generate(T max_value) -> T
	{
		return static_cast<T>(std::rand()) / (static_cast<T>(RAND_MAX) / max_value);
	}

	export template <typename T> auto generate(T min_value, T max_value) -> T
	{
		return min_value + generate<T>(max_value - min_value);
	}
}
