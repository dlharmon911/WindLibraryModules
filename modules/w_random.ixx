export module wind:random;

import <cstdlib>;
import <cstdint>;
import :base;

namespace WIND::RANDOM
{
	export constexpr int32_t MAXIMUM = RAND_MAX;
}

namespace wind
{
	namespace random
	{
		export auto set_seed(int32_t seed) -> void;
		export auto get_seed() -> int32_t;
		export auto generate(int32_t max_value = WIND::RANDOM::MAXIMUM) -> int32_t;
		export auto generate(int32_t min_value, int32_t max_value) -> int32_t;
	}
}