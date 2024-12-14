export module wind:base;

import <string>;
import <cstdint>;
import <memory>;
import <type_traits>;
import allegro;
import allegro.font_addon;

export using word_t = uint16_t;
export using byte_t = uint8_t;

namespace wind
{
	export template<typename T> struct add_pointer { using type = typename T*; };
	export template<typename T> struct add_reference { using type = typename T&; };
	export template<typename T> struct add_const { using type = typename const T; };
	export template<typename T> struct add_const_pointer { using type = typename const T*; };
	export template<typename T> struct add_const_reference { using type = typename const T&; };
	export template<typename T> using add_pointer_t = typename add_pointer<T>::type;
	export template<typename T> using add_reference_t = typename add_reference<T>::type;
	export template<typename T> using add_const_pointer_t = typename add_const_pointer<T>::type;
	export template<typename T> using add_const_reference_t = typename add_const_reference<T>::type;
	export template<typename T> using add_const_t = typename add_const<T>::type;
}