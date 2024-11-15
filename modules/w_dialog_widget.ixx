export module wind:dialog.widget;

import <string>;
import <memory>;
import std;
import allegro;
import :base;
import :vector;
import :string;

namespace wind
{
	namespace dialog
	{
		export class widget_t : public class_t<widget_t>
		{
		public:
			using element_type = std::shared_ptr<widget_t>;
			using pointer_element_type = wind::add_pointer_t<element_type>;
			using const_pointer_element_type = wind::add_const_pointer_t<element_type>;
			using reference_element_type = wind::add_reference_t<element_type>;
			using const_reference_element_type = wind::add_const_reference_t<element_type>;

			widget_t();
			virtual ~widget_t();

			virtual auto on_initialize() -> int32_t = 0;
			virtual auto on_shutdown() -> int32_t = 0;
			virtual auto on_start() -> int32_t = 0;
			virtual auto on_stop() -> int32_t = 0;
			virtual auto on_update() -> int32_t = 0;
			virtual auto on_render() -> int32_t = 0;

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

			const ALLEGRO::POINT<int32_t>& get_position() const;
			const ALLEGRO::SIZE<size_t>& get_dimensions() const;		
			
			auto push_back(wind::add_const_reference_t<element_type> widget) -> void;
			auto pop_back() -> void;

			class iterator
			{
			private:
				iterator() = default;
			public:
				iterator(std::vector<element_type>::iterator it) : m_it(it) {}
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
				const_iterator(std::vector<element_type>::const_iterator it) : m_it(it) {}
				auto operator == (wind::add_const_reference_t<const_iterator> it) const -> bool { return (this->m_it == it.m_it); }
				auto operator != (wind::add_const_reference_t<const_iterator> it) const -> bool { return !operator == (it); }
				auto operator ++ () -> wind::add_reference_t<const_iterator> { ++this->m_it; return *this; }
				auto operator ++ (int32_t) -> const_iterator { const_iterator tmp = *this; ++(*this); return tmp; }
				auto operator * () -> const_reference_element_type { return (*this->m_it); }
				auto operator -> () -> const_pointer_element_type { return &(*this->m_it); }

			private:
				std::vector<element_type>::const_iterator m_it;
			};

			auto begin() -> iterator;
			auto end() -> iterator;
			auto cbegin() const->const_iterator;
			auto cend() const->const_iterator;

		protected:
			std::vector<element_type> m_widgets;
			ALLEGRO::POINT<int32_t> m_position;
			ALLEGRO::SIZE<size_t> m_dimensions;
		};
	}
}

