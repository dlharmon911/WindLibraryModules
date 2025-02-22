export module wind.datafile_addon:base;

import <cassert>;
import <memory>;
import <vector>;
import <string>;
import <cstdint>;
import <any>;
import <functional>;
import allegro;
import wind;

namespace WIND::DATAFILE
{
	namespace OBJECT_TYPE
	{
		export constexpr int32_t INVALID{ -1 };
		export constexpr int32_t DATAFILE{ 0 };
		export constexpr int32_t BITMAP{ 1 };
		export constexpr int32_t FONT{ 2 };
		export constexpr int32_t TEXT{ 3 };
		export constexpr int32_t SAMPLE{ 4 };
		export constexpr int32_t TILESHEET{ 5 };
		export constexpr int32_t COUNT{ 6 };
		export constexpr int32_t USER_DEFINED{ 0X100 };
	}

	namespace OUTPUT_TYPE
	{
		export constexpr int32_t INVALID{ -1 };
		export constexpr int32_t HEADER{ 0 };
		export constexpr int32_t MODULE{ 1 };
		export constexpr int32_t COUNT{ 2 };
	}
}
