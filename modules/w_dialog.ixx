export module wind:dialog;

import <cstdint>;
import <vector>;
import <memory>;
import allegro;
import :base;
import :string;
import :vector;
import :dialog.widget;

namespace wind
{
	export class dialog_t : public class_t<dialog_t>
	{
	public:
		using element_type = std::shared_ptr<dialog::widget_t>;
		using pointer_element_type = wind::add_pointer_t<element_type>;
		using const_pointer_element_type = wind::add_const_pointer_t<element_type>;
		using reference_element_type = wind::add_reference_t<element_type>;
		using const_reference_element_type = wind::add_const_reference_t<element_type>;


		dialog_t();
		virtual ~dialog_t();

		virtual auto get_version() const -> int32_t = 0;
		virtual auto get_title() const -> wind::add_const_reference_t<wind::string_t> = 0;

		virtual auto on_initialize(wind::add_const_reference_t<vector_t<wind::string_t>> args) -> int32_t = 0;
		virtual auto on_shutdown() -> int32_t = 0;
		virtual auto on_start() -> int32_t = 0;
		virtual auto on_stop() -> int32_t = 0;
		virtual auto on_update() -> int32_t = 0;
		virtual auto on_render() -> int32_t = 0;

		virtual auto on_joystick_axis(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_joystick_button_down(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_joystick_button_up(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_joystick_configuration(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_key_down(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_key_up(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_key_char(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_mouse_click(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_mouse_axes(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_mouse_button_down(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_mouse_button_up(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_mouse_grab(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_mouse_drag(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_mouse_enter(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_mouse_leave(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_mouse_warped(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_display_resize(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_display_close(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_display_lost(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_display_found(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_display_switch_in(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }
		virtual auto on_display_switch_out(wind::add_const_reference_t<ALLEGRO::EVENT> event) -> bool { return false; }

		auto push_back(wind::add_const_reference_t<dialog_t::element_type> widget) -> void;
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
		auto cbegin() const -> const_iterator;
		auto cend() const -> const_iterator;

	protected:
		std::vector<element_type> m_widgets;
	};
}

