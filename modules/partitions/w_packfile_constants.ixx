export module wind:packfile.constants;

import :base;

namespace WIND::PACKFILE
{
	namespace MODE
	{
		export constexpr int32_t READ = 0x0001;
		export constexpr int32_t WRITE = 0x0002;
		export constexpr int32_t BINARY = 0x0004;
		export constexpr int32_t APPEND = 0x0008;
		export constexpr int32_t TRANSPARENT = 0x0010;
	}

	namespace COMPRESSION
	{
		export enum class TYPE : int32_t
		{
			DEFAULT,
			FILTERED,
			HUFFMAN_ONLY,
			RLE
		};

		export constexpr int32_t DEFAULT_LEVEL{ 6 };
	}
}
