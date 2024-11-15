module;

#include <windows.h>

module wind;

import <string>;
import <cstdint>;
import allegro;
import allegro.image_addon;
import allegro.font_addon;
import allegro.ttf_addon;
import allegro.primitives_addon;
import allegro.physfs_addon;
import :color;
import :input;
import :dialog;
import :system;
import :base;
import :string;
import :vector;

namespace WIND
{
	static constexpr float DISPLAY_SCALE = 1.25f;
	static constexpr ALLEGRO::SIZE<float> DISPLAY_SIZE = { 800.0f, 600.0f };
	static constexpr double LOGIC_TIMING = 60.0;
	static constexpr double TICK_SIZE = 0.02;
	static constexpr uint32_t BACKGROUND_DEFAULT = 0x101030;
}

namespace wind
{
	namespace system
	{
		ALLEGRO::DISPLAY m_display{ nullptr };
		ALLEGRO::EVENT_QUEUE m_event_queue{ nullptr };
		ALLEGRO::BITMAP m_bitmap_buffer{ nullptr };

		auto get_bitmap_buffer() -> wind::add_const_reference<ALLEGRO::BITMAP>::type
		{
			return system::m_bitmap_buffer;
		}

		auto get_display() -> wind::add_const_reference<ALLEGRO::DISPLAY>::type
		{
			return system::m_display;
		}

		auto get_event_queue() -> wind::add_const_reference<ALLEGRO::EVENT_QUEUE>::type
		{
			return system::m_event_queue;
		}

		auto timestamp() -> wind::string_t
		{
			char buffer[1024];
			struct tm local;
			__time64_t long_time;

			_time64(&long_time);

			errno_t err = _localtime64_s(&local, &long_time);
			if (err)
			{
				printf("Invalid argument to _localtime64_s.");
				exit(1);
			}

			sprintf_s<1024>(buffer,
				"%2d:%02d:%02d %s %2d/%02d/%4d",
				(local.tm_hour % 12 == 0 ? 12 : local.tm_hour % 12),
				local.tm_min,
				local.tm_sec,
				(local.tm_hour > 11 ? "p.m." : "a.m."),
				local.tm_mon + 1,
				local.tm_mday,
				1900 + local.tm_year);

			return string_t(buffer);
		}

		namespace widget
		{
			auto update(wind::add_const_reference_t<std::shared_ptr<wind::dialog::widget_t>> widget) -> void
			{
				widget->on_update();

				for (auto it = widget->cbegin(); it != widget->cend(); ++it)
				{
					widget::update(*it);
				}
			}

			auto render(wind::add_const_reference_t<std::shared_ptr<wind::dialog::widget_t>> widget) -> void
			{
				widget->on_render();

				for (auto it = widget->cbegin(); it != widget->cend(); ++it)
				{
					widget::render(*it);
				}
			}
		}

		namespace dialog
		{
			auto update(wind::add_const_reference_t<std::shared_ptr<wind::dialog_t>> dialog) -> void
			{
				dialog->on_update();

				for (auto it = dialog->cbegin(); it != dialog->cend(); ++it)
				{
					widget::update(*it);
				}
			}

			auto render(wind::add_const_reference_t<std::shared_ptr<wind::dialog_t>> dialog) -> void
			{
				dialog->on_render();

				for (auto it = dialog->cbegin(); it != dialog->cend(); ++it)
				{
					widget::render(*it);
				}
			}
		}
	}

	system_t::system_t(wind::add_const_reference_t<std::shared_ptr<dialog_t>> dialog) :
		m_dialog(dialog),
		m_timer(),
		m_time_info({ 0.0, 0.0 }),
		m_kill(false)
	{}

	system_t::~system_t()
	{}

	int32_t system_t::run(wind::add_const_reference_t<vector_t<wind::string_t>> args)
	{
		int32_t rv = 0;

		if (this->m_dialog)
		{
			if ((rv = this->init(args)) == 0)
			{
				this->loop();
			}
			this->shutdown();
		}

		return rv;
	}

	int32_t system_t::init(wind::add_const_reference_t<vector_t<wind::string_t>> args)
	{
		std::cout << "Initialization Begin" << std::endl;

		if (!al::is_system_installed())
		{
			std::cout << "Initializing Allegro Library: ";
			if (!al::init())
			{
				std::cout << "failed" << std::endl;
				return -1;
			}
			std::cout << "pass" << std::endl;
		}
	
		if (!al::image_addon::is_initialized())
		{
			std::cout << "Initializing Image Addon: ";
			if (!al::image_addon::init())
			{
				std::cout << "failed" << std::endl;
				return -1;
			}
			std::cout << "pass" << std::endl;
		}

		if (!al::ttf_addon::is_initialized())
		{
			std::cout << "Initializing TTF Addon: ";
			if (!al::ttf_addon::init())
			{
				std::cout << "failed" << std::endl;
				return -1;
			}
			std::cout << "pass" << std::endl;
		}

		if (!al::font_addon::is_initialized())
		{
			std::cout << "Initializing Font Addon: ";
			if (!al::font_addon::init())
			{
				std::cout << "failed" << std::endl;
				return -1;
			}
			std::cout << "pass" << std::endl;
		}

		if (!al::primitives_addon::is_initialized())
		{
			std::cout << "Initializing Primitives Addon: ";
			if (!al::primitives_addon::init())
			{
				std::cout << "failed" << std::endl;
				return -1;
			}
			std::cout << "pass" << std::endl;
		}

		std::cout << "Initializing PhysFS Addon: ";
		if (!PHYSFS_init(args[0].c_str()))
		{
			std::cout << "failed" << std::endl;
			return -1;
		}
		std::cout << "pass" << std::endl;

#ifndef _DEBUG
		// set the directory to the path of the exe
		ALLEGRO::PATH base_path = al::get_standard_path(ALLEGRO::RESOURCES_PATH);

		if (base_path)
		{
			al::make_path_canonical(base_path);
			al::change_directory(al::path_cstr(base_path, ALLEGRO::NATIVE_PATH_SEP));
			base_path.reset();
		}
#endif // !_DEBUG

		if (!al::is_mouse_installed())
		{
			std::cout << "Initializing Mouse: ";
			if (!al::install_mouse())
			{
				std::cout << "failed" << std::endl;
				return -1;
			}
			std::cout << "pass" << std::endl;
		}

		if (!al::is_keyboard_installed())
		{
			std::cout << "Initializing Keyboard: ";
			if (!al::install_keyboard())
			{
				std::cout << "failed" << std::endl;
				return -1;
			}
			std::cout << "pass" << std::endl;
		}

		std::cout << "Creating Display: ";
		al::set_new_display_flags(ALLEGRO::DISPLAY_FLAG_WINDOWED | ALLEGRO::DISPLAY_FLAG_RESIZABLE | ALLEGRO::DISPLAY_FLAG_PROGRAMMABLE_PIPELINE);
		al::set_new_display_option(ALLEGRO::DISPLAY_OPTION_VSYNC, 2, ALLEGRO::DISPLAY_OPTION_IMPORTANCE_SUGGEST);
		al::set_new_window_title(this->m_dialog->get_title().c_str());
		system::m_display = al::create_display(WIND::DISPLAY_SIZE);
		if (!system::m_display)
		{
			std::cout << "failed" << std::endl;
			return -1;
		}
		std::cout << "pass" << std::endl;
		al::clear_to_color(wind::map_rgb_i(0xffffff));

#ifdef _MSC_VER
		HICON icon1 = LoadIcon(GetModuleHandle(NULL), L"IDI_ICON1");
		if (icon1)
		{
			HWND winhandle = al::windows::get_window_handle(system::m_display);
			SetClassLongPtr(winhandle, GCLP_HICON, (LONG_PTR)icon1);
			SetClassLongPtr(winhandle, GCLP_HICONSM, (LONG_PTR)icon1);
		}
#endif

		ALLEGRO::BITMAP icon2 = al::load_bitmap("assets\\icon\\icon.png");
		if (icon2)
		{
			al::convert_mask_to_alpha(icon2, wind::map_rgb_i(0xff00ff));
			al::set_display_icon(system::m_display, icon2);
			icon2.reset();
		}

		std::cout << "Creating Doubld Buffer Bitmap: ";
		system::m_bitmap_buffer = al::create_bitmap(al::get_display_dimensions(system::m_display));
		if (!system::m_bitmap_buffer)
		{
			std::cout << "failed" << std::endl;
			return -1;
		}
		std::cout << "pass" << std::endl;

		std::cout << "Creating Event Queue: ";
		system::m_event_queue = al::create_event_queue();
		if (!system::m_event_queue)
		{
			std::cout << "failed" << std::endl;
			return -1;
		}
		std::cout << "pass" << std::endl;

		std::cout << "Creating Logic Timer: ";
		this->m_timer = al::create_timer(1.0 / WIND::LOGIC_TIMING);
		if (!this->m_timer)
		{
			std::cout << "failed" << std::endl;
			return -1;
		}
		std::cout << "pass" << std::endl;

		al::register_event_source(system::m_event_queue, al::get_display_event_source(system::m_display));
		al::register_event_source(system::m_event_queue, al::get_timer_event_source(this->m_timer));
		al::register_event_source(system::m_event_queue, al::get_keyboard_event_source());
		al::register_event_source(system::m_event_queue, al::get_mouse_event_source());

		const auto now = std::chrono::system_clock::now();
		const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
		srand(t_c);

		this->m_time_info.m_elapsed = 0.0;
		this->m_time_info.m_last_updated = al::get_time();

		std::cout << "Initializing Application: \n";
		if (this->m_dialog->on_initialize(args) < 0)
		{
			std::cout << "Initialization failed" << std::endl;
			return -1;
		}
		std::cout << "Initialization Complete" << std::endl << std::endl;

		return 0;
	}

	void system_t::shutdown()
	{
		std::cout << std::endl << "Shutdown Begin" << std::endl;

		std::cout << "Closing Application: ";
		this->m_dialog->on_shutdown();

		if (this->m_timer)
		{
			al::stop_timer(m_timer);
			this->m_timer.reset();
			std::cout << "Timer Destroyed" << std::endl;
		}

		if (system::m_event_queue)
		{
			system::m_event_queue.reset();
			std::cout << "Event Queue Destroyed" << std::endl;
		}

		if (system::m_bitmap_buffer)
		{
			system::m_bitmap_buffer.reset();
			std::cout << "Double Buffer Destroyed" << std::endl;
		}

		if (system::m_display)
		{
			system::m_display.reset();
			std::cout << "Display Destroyed" << std::endl;
		}

		PHYSFS_deinit();

		std::cout << "Shutdown Complete" << std::endl << std::endl;
	}

	void system_t::loop()
	{
		int32_t tick_count{ 0 };
		double elapsed{ 0.0 };
		double timepoint{ 0.0 };
		ALLEGRO::BITMAP target{};
		ALLEGRO::EVENT event{};

		this->m_dialog->on_start();

		al::start_timer(this->m_timer);
		al::pause_event_queue(system::m_event_queue, false);

		timepoint = al::get_time();

		while (!this->m_kill)
		{
			while (!al::is_event_queue_empty(system::m_event_queue))
			{
				al::get_next_event(system::m_event_queue, event);

				switch (event.type)
				{
				case ALLEGRO::EVENT_TYPE_JOYSTICK_AXIS:
				{
					if (this->m_dialog->on_joystick_axis(event))
					{
					}
					else
					{
					}
				} break;

				case ALLEGRO::EVENT_TYPE_JOYSTICK_BUTTON_DOWN:
				{
					if (this->m_dialog->on_joystick_button_down(event))
					{
					}
					else
					{
					}
				} break;

				case ALLEGRO::EVENT_TYPE_JOYSTICK_BUTTON_UP:
				{
					if (this->m_dialog->on_joystick_button_up(event))
					{
					}
					else
					{
					}
				} break;

				case ALLEGRO::EVENT_TYPE_JOYSTICK_CONFIGURATION:
				{
					if (this->m_dialog->on_joystick_configuration(event))
					{
					}
					else
					{
					}
				} break;

				case ALLEGRO::EVENT_TYPE_KEY_UP:
				{
					wind::set_keyboard_released(event.keyboard.keycode);

					if (this->m_dialog->on_key_up(event))
					{
					}
					else
					{
					}
				} break;

				case ALLEGRO::EVENT_TYPE_KEY_DOWN:
				{
					wind::set_keyboard_pressed(event.keyboard.keycode);

					if (this->m_dialog->on_key_down(event))
					{
					}
					else
					{
					}
				} break;

				case ALLEGRO::EVENT_TYPE_KEY_CHAR:
				{
					if (this->m_dialog->on_key_char(event))
					{
					}
					else
					{
					}
				} break;

				case ALLEGRO::EVENT_TYPE_MOUSE_AXES:
				{
					wind::set_mouse_position({ event.mouse.x, event.mouse.y });
					wind::set_mouse_wheel({ event.mouse.w, event.mouse.z });

					if (this->m_dialog->on_mouse_axes(event))
					{
					}
					else
					{
					}
				} break;

				case ALLEGRO::EVENT_TYPE_MOUSE_BUTTON_DOWN:
				{
					wind::set_mouse_pressed(event.mouse.button);

					if (this->m_dialog->on_mouse_button_down(event))
					{
					}
					else
					{
					}
				} break;

				case ALLEGRO::EVENT_TYPE_MOUSE_BUTTON_UP:
				{
					wind::set_mouse_released(event.mouse.button);

					if (this->m_dialog->on_mouse_button_up(event))
					{
					}
					else
					{
					}
				} break;

				case ALLEGRO::EVENT_TYPE_MOUSE_ENTER_DISPLAY:
				{
					if (this->m_dialog->on_mouse_enter(event))
					{
					}
					else
					{
					}
				} break;

				case ALLEGRO::EVENT_TYPE_MOUSE_LEAVE_DISPLAY:
				{
					if (this->m_dialog->on_mouse_leave(event))
					{
					}
					else
					{
					}
				} break;

				case ALLEGRO::EVENT_TYPE_MOUSE_WARPED:
				{
					if (this->m_dialog->on_mouse_warped(event))
					{
					}
					else
					{
					}
				} break;

				case ALLEGRO::EVENT_TYPE_TIMER:
				{
					double current = al::get_time();
					elapsed += current - timepoint;
					timepoint = current;

					tick_count += static_cast<int32_t>(elapsed / WIND::TICK_SIZE);
					elapsed -= static_cast<float>(tick_count * WIND::TICK_SIZE);

					if (this->m_dialog->on_update())
					{
					}
					else
					{
					}
				} break;

				case ALLEGRO::EVENT_TYPE_DISPLAY_RESIZE:
				{
					if (this->m_dialog->on_display_resize(event))
					{
					}
					else
					{
					}                
					
					al::acknowledge_resize(system::m_display);
				} break;

				case ALLEGRO::EVENT_TYPE_DISPLAY_CLOSE:
				{
					if (this->m_dialog->on_display_close(event))
					{
					}
					else
					{
						this->m_kill = true;
					}
				} break;

				case ALLEGRO::EVENT_TYPE_DISPLAY_LOST:
				{
					if (this->m_dialog->on_display_lost(event))
					{
					}
					else
					{
					}
				} break;

				case ALLEGRO::EVENT_TYPE_DISPLAY_FOUND:
				{
					if (this->m_dialog->on_display_found(event))
					{
					}
					else
					{
					}
				} break;

				case ALLEGRO::EVENT_TYPE_DISPLAY_SWITCH_IN:
				{
					if (this->m_dialog->on_display_switch_in(event))
					{
					}
					else
					{
					}
				} break;

				case ALLEGRO::EVENT_TYPE_DISPLAY_SWITCH_OUT:
				{
					if (this->m_dialog->on_display_switch_out(event))
					{
					}
					else
					{
					}
				} break;

				//case ALLEGRO::EVENT_TYPE_MENU_CLICK:
				//{
				//	if (this->m_dialog->on_display_menu_click(event))
				//	{
				//	}
				//} break;
				}
			}

			while (tick_count > 0)
			{
				system::dialog::update(this->m_dialog);
				--tick_count;
			}

			if (this->m_kill)
			{
				break;
			}

			target = al::get_target_bitmap();
			al::set_target_bitmap(system::m_bitmap_buffer);

			system::dialog::render(this->m_dialog);

			al::set_target_bitmap(target);

			al::draw_scaled_bitmap(system::m_bitmap_buffer,
				{ {0, 0}, al::get_bitmap_dimensions(system::m_bitmap_buffer) },
				{ { 0, 0}, al::get_display_dimensions(system::m_display) });

			al::flip_display();
			al::rest(0.1);
		}

		al::pause_event_queue(system::m_event_queue, true);
		al::stop_timer(this->m_timer);

		this->m_dialog->on_stop();
	}


}

