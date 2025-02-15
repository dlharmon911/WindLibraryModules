export module wind.d_addon;

import <cassert>;
import <memory>;
import <vector>;
import <string>;
import <cstdint>;
import <any>;
import <functional>;
import allegro;
import wind;
export import :base;
export import :object;

namespace wind
{	
	export auto load_datafile(const string_t& filename, d_t& datafile) -> int32_t;
}