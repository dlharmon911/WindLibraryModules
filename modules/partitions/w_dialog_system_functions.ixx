export module wind:dialog.system.functions;

import :base;
import :string;
import :dialog.constants;
import :dialog.data.type;
import :dialog.type;
import :dialog.system.type;

namespace wind::dialog::system
{
	namespace display
	{
		export auto get() -> ALLEGRO::DISPLAY
		{
			auto& g_data{ data::get() };
			return g_data.m_display.m_object;
		}

		namespace option
		{
			export auto set(int32_t p_option, int32_t p_value, int32_t p_importance = 0) -> void
			{
				auto& g_data{ data::get() };
				g_data.m_display.m_options[p_option] = wind::dialog::display::option_t{ p_value, p_importance };
			}

			export auto get(int32_t p_option) -> std::optional<wind::dialog::display::option_t>
			{
				auto& g_data{ data::get() };
				auto it = g_data.m_display.m_options.find(p_option);
				if (it != g_data.m_display.m_options.end())
				{
					return it->second;
				}
				return std::nullopt;
			}
		}

		namespace flags
		{
			export auto set(int32_t p_flags) -> void
			{
				auto& g_data{ data::get() };
				g_data.m_display.m_flags = p_flags;
			}

			export auto add(int32_t p_flags) -> void
			{
				auto& g_data{ data::get() };
				g_data.m_display.m_flags |= p_flags;
			}

			export auto get() -> int32_t
			{
				auto& g_data{ data::get() };
				return g_data.m_display.m_flags;
			}

			export auto clear(int32_t p_flags) -> void
			{
				auto& g_data{ data::get() };
				g_data.m_display.m_flags &= ~p_flags;
			}
		}
	}

	namespace timer
	{
		export auto get() -> ALLEGRO::TIMER
		{
			auto& g_data{ data::get() };
			return g_data.m_timer.m_object;
		}

		namespace interval
		{
			export auto set(double p_interval) -> void
			{
				auto& g_data{ data::get() };
				g_data.m_timer.m_interval = p_interval;
			}

			export auto get() -> double
			{
				auto& g_data{ data::get() };
				return g_data.m_timer.m_interval;
			}
		}
	}

	namespace event_queue
	{
		export auto get() -> ALLEGRO::EVENT_QUEUE
		{
			auto& g_data{ data::get() };
			return g_data.m_event_queue.m_object;
		}
	}

	namespace input
	{
		export auto get() -> wind::input_t&
		{
			auto& g_data{ data::get() };
			return g_data.m_input;
		}
	}
}

