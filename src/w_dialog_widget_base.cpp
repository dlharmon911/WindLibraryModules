module wind;

import :dialog.widget;
import :dialog.widget.base;

namespace wind
{
	namespace dialog
	{
		namespace widget
		{
			base_t::base_t() : m_position(), m_dimensions() {}

			base_t::~base_t() {}

			const ALLEGRO::POINT<int32_t>& base_t::get_position() const
			{
				return this->m_position;
			}

			const ALLEGRO::SIZE<size_t>& base_t::get_dimensions() const
			{
				return this->m_dimensions;
			}

			void base_t::push_back(wind::add_const_reference_t<base_t::element_type> widget)
			{
				this->m_widgets.push_back(widget);
			}

			void base_t::pop_back()
			{
				this->m_widgets.pop_back();
			}

			auto base_t::begin() -> base_t::iterator
			{
				return iterator(this->m_widgets.begin());
			}

			auto base_t::end() -> base_t::iterator
			{
				return iterator(this->m_widgets.end());
			}

			auto base_t::cbegin() const -> base_t::const_iterator
			{
				return const_iterator(this->m_widgets.cbegin());
			}

			auto base_t::cend() const -> base_t::const_iterator
			{
				return const_iterator(this->m_widgets.cend());
			}
		}
	}
}