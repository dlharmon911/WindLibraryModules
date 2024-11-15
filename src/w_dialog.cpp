module wind;

namespace wind
{
	dialog_t::dialog_t() : m_widgets()
	{
	}

	dialog_t::~dialog_t()
	{
	}

	void dialog_t::push_back(wind::add_const_reference_t<dialog_t::element_type> widget)
	{
		this->m_widgets.push_back(widget);
	}

	void dialog_t::pop_back()
	{
		this->m_widgets.pop_back();
	}

	auto dialog_t::begin() -> dialog_t::iterator
	{
		return iterator(this->m_widgets.begin());
	}

	auto dialog_t::end() -> dialog_t::iterator
	{
		return iterator(this->m_widgets.end());
	}

	auto dialog_t::cbegin() const -> dialog_t::const_iterator
	{
		return const_iterator(this->m_widgets.cbegin());
	}

	auto dialog_t::cend() const -> dialog_t::const_iterator
	{
		return const_iterator(this->m_widgets.cend());
	}
}
