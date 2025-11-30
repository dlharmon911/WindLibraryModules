export module wind:packfile.types;

import :base;
import <zlib.h>;

namespace wind
{
	namespace packfile::internal
	{
		export using data_t = typename gzFile_s;
		export using data_ptr_t = std::add_pointer<data_t>::type;
	}

	export using packfile_t = typename std::shared_ptr<packfile::internal::data_t>;
}
