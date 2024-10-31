export module wind:base;

import <string>;
import <cstdint>;
import <memory>;
import <type_traits>;
import allegro;
import allegro.font_addon;

namespace wind
{
	export template<typename T> struct add_pointer { using type = typename T*; };
	export template<typename T> struct add_reference { using type = typename T&; };
	export template<typename T> struct add_const { using type = typename const T; };

	export template<typename T> using add_pointer_t = typename add_pointer<T>::type;
	export template<typename T> using add_reference_t = typename add_reference<T>::type;
	export template<typename T> using add_const_t = typename add_const<T>::type;


	export template<typename T> struct array_deleter { auto operator ()(T const* p) -> void { delete[] p; } };


	export template <typename T>
	class class_t
	{
	public:
		using type = T;
		using pointer_type = add_pointer_t<type>;
		using const_pointer_type = add_pointer_t<add_const_t<type>>;
		using reference_type = add_reference_t<type>;
		using const_reference_type = add_reference_t<add_const_t<type>>;

		class_t() {}
		virtual ~class_t() {}
	};
}

