export module wind:dialog.base;

import <string>;
import <memory>;
import std;
import allegro;
import :base;
import :array;
import :string;
import :math;

namespace WIND
{
	namespace DIALOG
	{
		export namespace STATUS_FLAGS
		{
			constexpr int32_t ENABLED = wind::math::power_2(0);
			constexpr int32_t VISIBLE = wind::math::power_2(1);
			constexpr int32_t GRABBABLE = wind::math::power_2(2);
		}
	}
}

namespace wind
{
	class system_t;

	namespace dialog
	{
		export template <typename T> class base_t
		{
		public:
			using element_type = std::shared_ptr<T>;
			using pointer_element_type = wind::add_pointer_t<element_type>;
			using const_pointer_element_type = wind::add_const_pointer_t<element_type>;
			using reference_element_type = wind::add_reference_t<element_type>;
			using const_reference_element_type = wind::add_const_reference_t<element_type>;

			base_t() : m_dimensions({ 0, 0 }), m_grabbable({ { 0, 0 }, { 0, 0 } }), m_position({ 0, 0 }), m_flags(0), m_widgets() {}
			virtual ~base_t() = default;

			virtual auto on_initialize() -> int32_t { return 0; };
			virtual auto on_shutdown() -> int32_t { return 0; };
			virtual auto on_start() -> int32_t { return 0; };
			virtual auto on_stop() -> int32_t { return 0; };
			virtual auto on_update() -> int32_t { return 0; };
			virtual auto on_render() -> int32_t { return 0; };

			virtual auto on_joystick_axis(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_joystick_button_down(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_joystick_button_up(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_key_down(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_key_up(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_key_char(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_mouse_click(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_mouse_axes(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_mouse_button_down(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_mouse_button_up(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_mouse_grab(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_mouse_drag(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_mouse_enter(const ALLEGRO::EVENT& event) -> bool { return false; }
			virtual auto on_mouse_leave(const ALLEGRO::EVENT& event) -> bool { return false; }

			auto get_position() const -> const ALLEGRO::POINT<int32_t>&
			{
				return this->m_position;
			}

			auto set_position(const ALLEGRO::POINT<int32_t>& position) -> void
			{
				this->m_position = position;
			}

			auto get_dimensions() const -> const ALLEGRO::SIZE<size_t>&
			{
				return this->m_dimensions;
			}

			auto set_dimensions(const ALLEGRO::SIZE<int32_t>& dimensions) -> void
			{
				this->m_dimensions = dimensions;
			}

			auto add_child(wind::add_const_reference_t<element_type> widget) -> void
			{
				this->m_widgets.push_back(widget);
			}

			auto get_grabbable() const -> const ALLEGRO::RECTANGLE<int32_t>&
			{
				return this->m_grabbable;
			}

			auto set_grabbable(const ALLEGRO::RECTANGLE<int32_t>& grabbable) -> void
			{
				this->m_grabbable = grabbable;
			}

			auto get_flags() const -> int32_t
			{
				return this->m_flags;
			}

			auto set_flags(int32_t flags) -> void
			{
				this->m_flags = flags;
			}

			auto get_widgets() const -> const std::vector<element_type>&
			{
				return this->m_widgets;
			}

			auto get_widgets() -> std::vector<element_type>&
			{
				return this->m_widgets;
			}

			auto set_widgets(const std::vector<element_type>& widgets) -> void
			{
				this->m_widgets = widgets;
			}

			class iterator
			{
			private:
				iterator() = default;
			public:
				explicit iterator(std::vector<element_type>::iterator it) : m_it(it) {}
				auto operator == (wind::add_const_reference_t<iterator> it) const -> bool { return (this->m_it == it.m_it); }
				auto operator != (wind::add_const_reference_t<iterator> it) const -> bool { return !operator == (it); }
				auto operator ++ () -> wind::add_reference_t<iterator> { ++this->m_it; return *this; }
				auto operator ++ (int32_t) -> iterator { iterator tmp = *this; ++(*this); return tmp; }
				auto operator * () -> reference_element_type { return (*this->m_it); }
				auto operator -> () -> pointer_element_type { return &(*this->m_it); }

			private:
				std::vector<element_type>::iterator m_it;
			};

			class const_iterator
			{
			private:
				const_iterator() = default;
			public:
				explicit const_iterator(std::vector<element_type>::const_iterator it) : m_it(it) {}
				auto operator == (wind::add_const_reference_t<const_iterator> it) const -> bool { return (this->m_it == it.m_it); }
				auto operator != (wind::add_const_reference_t<const_iterator> it) const -> bool { return !operator == (it); }
				auto operator ++ () -> wind::add_reference_t<const_iterator> { ++this->m_it; return *this; }
				auto operator ++ (int32_t) -> const_iterator { const_iterator tmp = *this; ++(*this); return tmp; }
				auto operator * () -> const_reference_element_type { return (*this->m_it); }
				auto operator -> () -> const_pointer_element_type { return &(*this->m_it); }

			private:
				std::vector<element_type>::const_iterator m_it;
			};

			auto begin() -> iterator
			{
				return iterator(this->m_widgets.begin());
			}

			auto end() -> iterator
			{
				return iterator(this->m_widgets.end());
			}

			auto cbegin() const -> const_iterator
			{
				return const_iterator(this->m_widgets.cbegin());
			}

			auto cend() const -> const_iterator
			{
				return const_iterator(this->m_widgets.cend());
			}

			friend class wind::system_t;

		private:
			ALLEGRO::SIZE<size_t> m_dimensions{ 0, 0 };
			ALLEGRO::RECTANGLE<int32_t> m_grabbable{ { 0, 0 }, { 0, 0 } };
			ALLEGRO::POINT<int32_t> m_position{ 0, 0 };
			int32_t m_flags{ 0 };
			std::vector<element_type> m_widgets{};
		};
	}
}
