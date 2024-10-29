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
		export bool is_empty(ALLEGRO::BITMAP& bitmap);
	}
}
