module wind;

import :dialog.widget;

namespace wind
{
	namespace dialog
	{
		widget_t::widget_t() : m_position(), m_dimensions() {}

		widget_t::~widget_t() {}

		const ALLEGRO::POINT<int32_t>& widget_t::get_position() const
		{
			return this->m_position;
		}

		const ALLEGRO::SIZE<size_t>& widget_t::get_dimensions() const
		{
			return this->m_dimensions;
		}

		void widget_t::push_back(wind::add_const_reference_t<widget_t::element_type> widget)
		{
			this->m_widgets.push_back(widget);
		}

		void widget_t::pop_back()
		{
			this->m_widgets.pop_back();
		}

		auto widget_t::begin() -> widget_t::iterator
		{
			return iterator(this->m_widgets.begin());
		}

		auto widget_t::end() -> widget_t::iterator
		{
			return iterator(this->m_widgets.end());
		}

		auto widget_t::cbegin() const -> widget_t::const_iterator
		{
			return const_iterator(this->m_widgets.cbegin());
		}

		auto widget_t::cend() const -> widget_t::const_iterator
		{
			return const_iterator(this->m_widgets.cend());
		}
	}
}
