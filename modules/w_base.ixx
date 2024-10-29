export module wind:base;

import <string>;
import <cstdint>;
import <memory>;
import <type_traits>;
import allegro;
import allegro.font_addon;

namespace wind
{
	template< typename T >
	struct array_deleter
	{
		void operator ()(T const* p)
		{
			delete[] p;
		}
	};
}

