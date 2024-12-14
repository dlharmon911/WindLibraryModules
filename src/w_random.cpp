module wind;

import std;
import <cstdlib>;
import <cstdint>;
import :base;
import :random;

namespace wind
{
	namespace random
	{
		namespace internal
		{
			int32_t m_seed{ 0 };
		}

		auto set_seed(int32_t seed) -> void
		{
			internal::m_seed = seed;
			srand(internal::m_seed);
		}

		auto get_seed() -> int32_t
		{
			return internal::m_seed;
		}

		auto generate(int32_t max_value) -> int32_t
		{
			return (int32_t)rand() % max_value;
		}

		auto generate(int32_t min_value, int32_t max_value) -> int32_t
		{
			if (min_value == max_value)
			{
				return (int32_t)min_value;
			}

			if (min_value > max_value)
			{
				return generate(max_value, min_value);
			}

			return (min_value + (generate(max_value - min_value + 1)));
		}
	}
}