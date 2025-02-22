export module wind:bitmap;

import <memory>;
import <string>;
import <cstdint>;
import allegro;
import :base;

namespace wind
{
	namespace bitmap
	{
		export auto is_empty(const ALLEGRO::BITMAP& bitmap) -> bool;
		export auto flood_fill(const ALLEGRO::BITMAP& bitmap, const ALLEGRO::RECTANGLE<int32_t>& region) -> void;
	}
}
