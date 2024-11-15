export module wind:memory;

import <vector>;
import <string>;
import <cstdint>;
import <memory>;
import allegro;
import :base;

namespace wind
{
	export template<typename T> struct array_deleter { auto operator ()(T const* p) -> void { delete[] p; } };

	export template<typename Type>
	auto make_shared(Type* object) -> std::shared_ptr<void>
	{
		return std::shared_ptr<void>(object);
	}

	export template<typename Type>
	auto make_shared(Type* object, void (*Deleter)(Type*)) -> std::shared_ptr<void>
	{
		return std::shared_ptr<void>((void*)object, Deleter);
	}
}
