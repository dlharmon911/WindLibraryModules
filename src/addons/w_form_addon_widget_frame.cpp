module wind.form_addon;

import <cassert>;
import <memory>;
import <vector>;
import <string>;
import <cstdint>;
import <any>;
import <functional>;
import <unordered_map>;
import allegro;
import wind;
import :base;
import :widget;
import :widget.frame;

namespace wind
{
	namespace form
	{
		namespace widget
		{
			auto frame_t::on_event(const ALLEGRO::EVENT& event) -> bool
			{
				return false;
			}

			auto frame_t::get_title() const -> const string_t&
			{
				return this->m_title;
			}

			auto frame_t::set_title(const string_t& title) -> void
			{
				this->m_title = title;
			}
		}
	}
}
