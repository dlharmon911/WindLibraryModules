module;

#ifdef _MSC_VER
#include <windows.h>
#endif

export module wind:dialog.system.type;

import :base;
import :string;
import :log;
import :color;
import :timestamp;
import :random;
import :dialog.constants;
import :dialog.type;
import :dialog.data.type;

namespace wind::dialog
{
	static data_t g_data{};

	namespace data
	{
		export inline auto get() -> data_t&
		{
			return g_data;
		}

		static auto clear() -> void
		{
			g_data.m_timer.m_object.reset();
			g_data.m_display.m_object.reset();
			g_data.m_event_queue.m_object.reset();
			g_data.m_input.acknowledge();
			g_data.m_kill = false;
		}
	}

	export class system_t
	{
	public:
		~system_t() = default;

		explicit system_t(const std::shared_ptr<dialog_t>& dialog) : m_dialog(dialog) {}
		
		auto run(std::span<const char* const>& span) -> int32_t
		{
			int32_t rv = 0;

			if (!al::init())
			{
				return -1;
			}

			lout.open("logs\\output.txt");

			lout << "----------------------------------------\n" <<
				" Log opened: " << wind::timestamp::get() << "\n" <<
				"----------------------------------------" << wind::endl;

			if (this->m_dialog)
			{
				this->m_dialog->m_data = &g_data;

				if ((rv = this->init(span)) == 0)
				{
					this->loop();
				}

				this->m_dialog->m_data = nullptr;

				this->shutdown();
			}

			lout << "---------------------------------------\n" <<
				" Log closed: " << wind::timestamp::get() << "\n" <<
				"---------------------------------------" << wind::endl;
			lout.close();

			al::uninstall_system();

			return rv;
		}

	private:
		system_t() = default;

		auto init(std::span<const char* const>& span) -> int32_t
		{
			wind::lout << "Initialization Phase Begin" << "\n----------------------------------------\n";

			if (!al::image_addon::is_initialized())
			{
				wind::lout << "Initializing Image Addon: ";
				if (!al::image_addon::init())
				{
					wind::lout << "failed\n";
					return -1;
				}
				wind::lout << "pass\n";
			}

			if (!al::ttf_addon::is_initialized())
			{
				wind::lout << "Initializing TTF Addon: ";
				if (!al::ttf_addon::init())
				{
					wind::lout << "failed\n";
					return -1;
				}
				wind::lout << "pass\n";
			}

			if (!al::font_addon::is_initialized())
			{
				wind::lout << "Initializing Font Addon: ";
				if (!al::font_addon::init())
				{
					wind::lout << "failed\n";
					return -1;
				}
				wind::lout << "pass\n";
			}

			if (!al::primitives_addon::is_initialized())
			{
				wind::lout << "Initializing Primitives Addon: ";
				if (!al::primitives_addon::init())
				{
					wind::lout << "failed\n";
					return -1;
				}
				wind::lout << "pass\n";
			}

			if (!al::physfs_addon::is_initialized())
			{
				wind::lout << "Initializing PhysFS Addon: ";
				if (!al::physfs_addon::init(span[0]))
				{
					wind::lout << "failed\n";
					return -1;
				}
				wind::lout << "pass\n";
			}

			if (!al::is_mouse_installed())
			{
				wind::lout << "Initializing Mouse: ";
				if (!al::install_mouse())
				{
					wind::lout << "failed\n";
					return -1;
				}
				wind::lout << "pass\n";
			}

			if (!al::is_keyboard_installed())
			{
				wind::lout << "Initializing Keyboard: ";
				if (!al::install_keyboard())
				{
					wind::lout << "failed\n";
					return -1;
				}
				wind::lout << "pass\n";
			}

			wind::lout << "Creating Display: ";
			al::set_new_display_flags(g_data.m_display.m_flags);

			for (auto i = g_data.m_display.m_options.cbegin(); i != g_data.m_display.m_options.cend(); ++i)
			{
				al::set_new_display_option(i->first, i->second.m_value, i->second.m_importance);
			}

			al::set_new_window_title(this->m_dialog->title().c_str());
			g_data.m_display.m_object = al::create_display(g_data.m_display.m_width, g_data.m_display.m_height);
			if (!g_data.m_display.m_object)
			{
				wind::lout << "failed\n";
				return -1;
			}
			wind::lout << "pass\n";
			al::clear_to_color(WIND::COLOR::EIGENGRAU);

#ifdef _MSC_VER
			HICON icon = LoadIcon(GetModuleHandle(nullptr), L"IDI_ICON1");
			if (icon)
			{
				HWND winhandle = al::windows::get_window_handle(g_data.m_display.m_object);
				SetClassLongPtr(winhandle, GCLP_HICON, (LONG_PTR)icon);
				SetClassLongPtr(winhandle, GCLP_HICONSM, (LONG_PTR)icon);
			}
#else
			ALLEGRO::BITMAP icon = al::load_bitmap("assets\\icon\\icon.png");
			if (icon)
			{
				al::convert_mask_to_alpha(icon, wind::map_rgb_i(0xff00ff));
				al::set_display_icon(g_data.m_display.m_object, icon);
				icon.reset();
			}
#endif

			wind::lout << "Creating Event Queue: ";
			g_data.m_event_queue.m_object = al::create_event_queue();
			if (!g_data.m_event_queue.m_object)
			{
				wind::lout << "failed\n";
				return -1;
			}
			wind::lout << "pass\n";

			wind::lout << "Creating Logic Timer: ";
			g_data.m_timer.m_object = al::create_timer(1.0 / g_data.m_timer.m_interval);
			if (!g_data.m_timer.m_object)
			{
				wind::lout << "failed\n";
				return -1;
			}
			wind::lout << "pass\n";

			al::register_event_source(g_data.m_event_queue.m_object, al::get_display_event_source(g_data.m_display.m_object));
			al::register_event_source(g_data.m_event_queue.m_object, al::get_timer_event_source(g_data.m_timer.m_object));
			al::register_event_source(g_data.m_event_queue.m_object, al::get_keyboard_event_source());
			al::register_event_source(g_data.m_event_queue.m_object, al::get_mouse_event_source());

			const auto now = std::chrono::system_clock::now();
			const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
			wind::random::set_seed((uint32_t)t_c);

			wind::lout << "Initializing Dialog: \n";
			if (this->m_dialog->on_initialize() < 0)
			{
				wind::lout << "failed\n";
				return -1;
			}
			wind::lout << "pass\n";

			wind::lout << "----------------------------------------\n"
				<< "Initialization Phase Complete\n"
				<< "----------------------------------------" << wind::endl;

			return 0;

		}

		auto shutdown() -> void
		{
			data::clear();
		}

		auto input() -> void
		{
			ALLEGRO::EVENT event{};

			while (!al::is_event_queue_empty(g_data.m_event_queue.m_object))
			{
				al::get_next_event(g_data.m_event_queue.m_object, event);

				this->m_dialog->on_event(event);

				switch (event.type)
				{
				case ALLEGRO::EVENT_TYPE_KEY_UP:
				{
					auto& button = g_data.m_input.key().button(event.keyboard.keycode);
					button.value(WIND::INPUT::BUTTON::CHANGED);
				} break;

				case ALLEGRO::EVENT_TYPE_KEY_DOWN:
				{
					auto& button = g_data.m_input.key().button(event.keyboard.keycode);
					button.value(WIND::INPUT::BUTTON::PRESSED | WIND::INPUT::BUTTON::CHANGED);
				} break;

				case ALLEGRO::EVENT_TYPE_MOUSE_AXES:
				{
					auto& axis{ g_data.m_input.mouse().axis() };
					axis.first = static_cast<float>(event.mouse.x);
					axis.second = static_cast<float>(event.mouse.y);
				} break;

				case ALLEGRO::EVENT_TYPE_MOUSE_BUTTON_DOWN:
				{
					auto& button = g_data.m_input.mouse().button(static_cast<int32_t>(event.mouse.button - 1));
					button.value(WIND::INPUT::BUTTON::PRESSED | WIND::INPUT::BUTTON::CHANGED);
				} break;

				case ALLEGRO::EVENT_TYPE_MOUSE_BUTTON_UP:
				{
					auto& button = g_data.m_input.mouse().button(static_cast<int32_t>(event.mouse.button - 1));
					button.value(WIND::INPUT::BUTTON::CHANGED);
				} break;

				case ALLEGRO::EVENT_TYPE_TIMER:
				{
					if (!g_data.m_timer.m_paused)
					{
						++g_data.m_timer.m_tick_count;
					}
				} break;

				case ALLEGRO::EVENT_TYPE_DISPLAY_RESIZE:
				{
					al::acknowledge_resize(g_data.m_display.m_object);
				} break;

				case ALLEGRO::EVENT_TYPE_DISPLAY_CLOSE:
				{
					g_data.m_kill = true;
				} break;

#ifdef PICKLE_BALL
				case ALLEGRO::EVENT_TYPE_MENU_CLICK:
				{
					if (this->m_dialog->on_display_menu_click(event))
					{
					}
				} break;
#endif
				}
			}
		}

		auto update() -> void
		{
			while (g_data.m_timer.m_tick_count > 0)
			{
				if (this->m_dialog->on_update() < 0)
				{
					g_data.m_kill = true;
				}
				--g_data.m_timer.m_tick_count;
			}
		}

		auto render() -> void
		{
			this->m_dialog->on_render();
		}

		auto loop() -> void
		{
			this->m_dialog->on_start();

			al::start_timer(g_data.m_timer.m_object);
			al::pause_event_queue(g_data.m_event_queue.m_object, false);

			while (!g_data.m_kill)
			{
				input();
				update();

				if (g_data.m_kill)
				{
					break;
				}
					
				render();
				al::rest(0.1);				
			}

			al::pause_event_queue(g_data.m_event_queue.m_object, true);
			al::stop_timer(g_data.m_timer.m_object);

			this->m_dialog->on_stop();
		}

		std::shared_ptr<dialog_t> m_dialog{};
	};
}