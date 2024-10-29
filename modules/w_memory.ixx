export module wind:memory;

import <vector>;
import <string>;
import <cstdint>;
import allegro;
import :base;

namespace wind
{
	template<typename Type>
	std::shared_ptr<void> make_shared(Type* object)
	{
		return std::shared_ptr<void>(object);
	}

	template<typename Type>
	std::shared_ptr<void> make_shared(Type* object, void (*Deleter)(Type*))
	{
		return std::shared_ptr<void>((void*)object, Deleter);
	}
}
