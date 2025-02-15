export module wind:faders;

import <cstdint>;
import allegro;
import :base;

namespace WIND::FADERS
{
	export constexpr double DEFAULT_SPEED{ 1.0 };
	constexpr size_t DIVISIONS{ 50 };
}

namespace wind
{
	namespace faders
	{
		export auto in(const ALLEGRO::BITMAP& bitmap, double speed = WIND::FADERS::DEFAULT_SPEED) -> void;
		export auto out(const ALLEGRO::BITMAP& bitmap, double speed = WIND::FADERS::DEFAULT_SPEED) -> void;
		export auto out(double speed = WIND::FADERS::DEFAULT_SPEED) -> void;
		export auto in(double speed = WIND::FADERS::DEFAULT_SPEED) -> void;
		export auto across(const ALLEGRO::BITMAP& bitmap_a, const ALLEGRO::BITMAP& bitmap_b, double speed = WIND::FADERS::DEFAULT_SPEED) -> void;
	}
}
