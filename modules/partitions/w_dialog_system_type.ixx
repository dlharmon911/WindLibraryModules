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
import :input;
import :dialog.constants;
import :dialog.type;
import :dialog.system.data;

namespace wind::dialog
{
	export class system_t
	{
	public:
		~system_t() = default;
		
		static auto run(std::shared_ptr<dialog_t>& dialog, std::span<const char* const>& span) -> int32_t
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

			if (dialog)
			{
				system_t system{ dialog };

				if ((rv = system.init(span)) == 0)
				{
					system.loop();
				}
				system.shutdown();
			}

			dialog.reset();


			lout << "---------------------------------------\n" <<
				" Log closed: " << wind::timestamp::get() << "\n" <<
				"---------------------------------------" << wind::endl;
			lout.close();


			return rv;
		}

	private:
		system_t() = default;

		explicit system_t(const std::shared_ptr<dialog_t>& dialog) : m_dialog(dialog), m_data() {}

		auto init_addons(std::span<const char* const>& span) -> int32_t
		{
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

			return 0;
		}

		auto init(std::span<const char* const>& span) -> int32_t
		{
			wind::lout << "Initialization Phase Begin" << "\n----------------------------------------\n";

			if (init_addons(span) < 0)
			{
				return -1;
			}

			if (this->m_dialog->on_pre_initialize(this->m_data.m_settings_data) < 0)
			{
				return -1;
			}

			wind::lout << "Creating Display: ";
			al::set_new_display_flags(this->m_data.m_settings_data.m_display_data.m_flags);

			for (auto i = this->m_data.m_settings_data.m_display_data.m_options.cbegin(); i != this->m_data.m_settings_data.m_display_data.m_options.cend(); ++i)
			{
				al::set_new_display_option(i->first, i->second.m_value, i->second.m_importance);
			}

			al::set_new_window_title(this->m_dialog->title().c_str());
			this->m_data.m_display_object = al::create_display(this->m_data.m_settings_data.m_display_data.m_width, this->m_data.m_settings_data.m_display_data.m_height);
			if (!this->m_data.m_display_object)
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
				HWND winhandle = al::windows::get_window_handle(this->m_data.m_display_object);
				SetClassLongPtr(winhandle, GCLP_HICON, (LONG_PTR)icon);
				SetClassLongPtr(winhandle, GCLP_HICONSM, (LONG_PTR)icon);
			}
#else
			ALLEGRO::BITMAP icon = al::load_bitmap("assets\\icon\\icon.png");
			if (icon)
			{
				al::convert_mask_to_alpha(icon, wind::map_rgb_i(0xff00ff));
				al::set_display_icon(this->m_data.m_display, icon);
				icon.reset();
			}
#endif

			wind::lout << "Creating Event Queue: ";
			this->m_data.m_event_queue_object = al::create_event_queue();
			if (!this->m_data.m_event_queue_object)
			{
				wind::lout << "failed\n";
				return -1;
			}
			wind::lout << "pass\n";

			wind::lout << "Creating Logic Timer: ";
			this->m_data.m_timer_object = al::create_timer(1.0 / this->m_data.m_settings_data.m_timer_data.m_interval);
			if (!this->m_data.m_timer_object)
			{
				wind::lout << "failed\n";
				return -1;
			}
			wind::lout << "pass\n";

			al::register_event_source(this->m_data.m_event_queue_object, al::get_display_event_source(this->m_data.m_display_object));
			al::register_event_source(this->m_data.m_event_queue_object, al::get_timer_event_source(this->m_data.m_timer_object));
			al::register_event_source(this->m_data.m_event_queue_object, al::get_keyboard_event_source());
			al::register_event_source(this->m_data.m_event_queue_object, al::get_mouse_event_source());

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
			this->m_dialog->on_shutdown();

			this->m_data.m_timer_object.reset();
			this->m_data.m_display_object.reset();
			this->m_data.m_event_queue_object.reset();
			this->m_data.m_input_data.acknowledge();
			this->m_data.m_kill = false;
		}

		auto input() -> void
		{
			ALLEGRO::EVENT event{};

			while (!al::is_event_queue_empty(this->m_data.m_event_queue_object))
			{
				al::get_next_event(this->m_data.m_event_queue_object, event);

				this->m_dialog->on_event(event);

				switch (event.type)
				{
				case ALLEGRO::EVENT_TYPE_KEY_UP:
				{
					auto& button = this->m_data.m_input_data.key().button(event.keyboard.keycode);
					button.value(WIND::INPUT::BUTTON::CHANGED);
				} break;

				case ALLEGRO::EVENT_TYPE_KEY_DOWN:
				{
					auto& button = this->m_data.m_input_data.key().button(event.keyboard.keycode);
					button.value(WIND::INPUT::BUTTON::PRESSED | WIND::INPUT::BUTTON::CHANGED);
				} break;

				case ALLEGRO::EVENT_TYPE_MOUSE_AXES:
				{
					auto& axis{ this->m_data.m_input_data.mouse().axis() };
					axis.first = static_cast<float>(event.mouse.x);
					axis.second = static_cast<float>(event.mouse.y);
				} break;

				case ALLEGRO::EVENT_TYPE_MOUSE_BUTTON_DOWN:
				{
					auto& button = this->m_data.m_input_data.mouse().button(static_cast<int32_t>(event.mouse.button - 1));
					button.value(WIND::INPUT::BUTTON::PRESSED | WIND::INPUT::BUTTON::CHANGED);
				} break;

				case ALLEGRO::EVENT_TYPE_MOUSE_BUTTON_UP:
				{
					auto& button = this->m_data.m_input_data.mouse().button(static_cast<int32_t>(event.mouse.button - 1));
					button.value(WIND::INPUT::BUTTON::CHANGED);
				} break;

				case ALLEGRO::EVENT_TYPE_TIMER:
				{
					if (!this->m_data.m_timer_data.m_paused)
					{
						++this->m_data.m_timer_data.m_tick_count;
					}
				} break;

				case ALLEGRO::EVENT_TYPE_DISPLAY_RESIZE:
				{
					al::acknowledge_resize(this->m_data.m_display_object);
				} break;

				case ALLEGRO::EVENT_TYPE_DISPLAY_CLOSE:
				{
					this->m_data.m_kill = true;
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
			while (this->m_data.m_timer_data.m_tick_count > 0)
			{
				if (this->m_dialog->on_update(this->m_data.m_input_data) < 0)
				{
					this->m_data.m_kill = true;
				}
				--this->m_data.m_timer_data.m_tick_count;
			}

			al::rest(0.01);
		}

		auto render() -> void
		{
			this->m_dialog->on_render(this->m_data.m_display_object);
		}

		auto loop() -> void
		{
			this->m_dialog->on_start();

			al::start_timer(this->m_data.m_timer_object);
			al::pause_event_queue(this->m_data.m_event_queue_object, false);

			while (!this->m_data.m_kill)
			{
				input();
				update();

				if (this->m_data.m_kill)
				{
					break;
				}
					
				render();
				al::rest(0.1);				
			}

			al::pause_event_queue(this->m_data.m_event_queue_object, true);
			al::stop_timer(this->m_data.m_timer_object);

			this->m_dialog->on_stop();
		}

		std::shared_ptr<dialog_t> m_dialog{};
		system::data_t m_data{};
	};
}