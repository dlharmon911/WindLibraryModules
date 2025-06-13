module;

#include <windows.h>

module wind;

import std;
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
import :widget;
import :system;
import :base;
import :string;
import :array;
import :log;

namespace WIND
{
	static constexpr float DISPLAY_SCALE = 1.25f;
	static constexpr ALLEGRO::VECTOR_2D<float> DISPLAY_SIZE = { 800.0f, 600.0f };
	static constexpr double LOGIC_TIMING = 60.0;
	static constexpr uint32_t BACKGROUND_DEFAULT = 0x101030;
}

namespace wind
{
	log_t lout{};

	namespace system
	{
		namespace timer
		{
			int32_t m_tick_count{ 0 };
			bool m_paused{ false };

			auto pause() -> void
			{
				m_paused = true;
			}

			auto unpause() -> void
			{
				m_paused = false;
			}

			auto reset() -> void
			{
				m_tick_count = 0;
			}
		}

		ALLEGRO::DISPLAY m_display{ nullptr };
		namespace display
		{
			std::map<int32_t, display::option_t> m_options{};
			int32_t m_flags{ ALLEGRO::DISPLAY_FLAG_WINDOWED | ALLEGRO::DISPLAY_FLAG_RESIZABLE };
			display::option_t m_null_option{ -1, 0 };
			ALLEGRO::VECTOR_2D<int32_t> m_start_size{ WIND::DISPLAY_SIZE };

			auto set_start_size(const ALLEGRO::VECTOR_2D<int32_t>& size) -> void
			{
				m_start_size = size;
			}

			auto get_new_option(int32_t id) -> display::option_t&
			{
				auto i = m_options.find(id);

				if (i == m_options.end())
				{
					return m_null_option;
				}

				return m_options[id];
			}

			auto set_new_option(int32_t id, const display::option_t& option) -> void
			{
				m_options[id] = { option.m_value, option.m_importance };
			}

			auto get_new_flags() -> int32_t
			{
				return m_flags;
			}

			auto set_new_flags(int32_t flags) -> void
			{
				m_flags = flags;
			}

			auto get() -> wind::add_const_reference<ALLEGRO::DISPLAY>::type
			{
				return m_display;
			}
		}

		ALLEGRO::EVENT_QUEUE m_event_queue{ nullptr };
		namespace event_queue
		{
			auto get() -> wind::add_const_reference<ALLEGRO::EVENT_QUEUE>::type
			{
				return m_event_queue;
			}
		}

		auto timestamp() -> string_t
		{
			std::array<char, 1024> buffer{""};
			struct tm local;
			__time64_t long_time;

			_time64(&long_time);

			errno_t err = _localtime64_s(&local, &long_time);
			if (err)
			{
				printf("Invalid argument to _localtime64_s.");
				exit(1);
			}

			sprintf_s(buffer.data(), buffer.size(),
				"%2d:%02d:%02d %s %2d/%02d/%4d",
				(local.tm_hour % 12 == 0 ? 12 : local.tm_hour % 12),
				local.tm_min,
				local.tm_sec,
				(local.tm_hour > 11 ? "p.m." : "a.m."),
				local.tm_mon + 1,
				local.tm_mday,
				1900 + local.tm_year);

			return string_t(buffer.data());
		}
	}

	system_t::system_t(wind::add_const_reference_t<std::shared_ptr<dialog_t>> dialog) :
		m_dialog(dialog),
		m_timer(),
		m_kill(false)
	{
	}

	system_t::~system_t()
	{
	}

	int32_t system_t::run(wind::add_const_reference_t<array_t<wind::string_t>> args)
	{
		int32_t rv = 0;

		if (!al::init())
		{
			return -1;
		}

		lout.open("logs\\output.txt");

		lout << "----------------------------------------\n" <<
			" Log opened: " << wind::system::timestamp() << "\n" <<
			"----------------------------------------" << wind::endl;

		if (this->m_dialog)
		{
			if ((rv = this->init(args)) == 0)
			{
				this->loop();
			}

			this->shutdown();
		}

		lout << "---------------------------------------\n" <<
			" Log closed: " << wind::system::timestamp() << "\n" <<
			"---------------------------------------" << wind::endl;
		lout.reset();

		return rv;
	}

	int32_t system_t::init(wind::add_const_reference_t<array_t<wind::string_t>> args)
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
			if (!al::physfs_addon::init(args[0].c_str()))
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
		al::set_new_display_flags(system::display::m_flags);

		for (auto i = system::display::m_options.cbegin(); i != system::display::m_options.cend(); ++i)
		{
			al::set_new_display_option(i->first, i->second.m_value, i->second.m_importance);
		}

		al::set_new_window_title(this->m_dialog->get_title().c_str());
		system::m_display = al::create_display(static_cast<ALLEGRO::VECTOR_2D<int32_t>>(system::display::m_start_size));
		if (!system::m_display)
		{
			wind::lout << "failed\n";
			return -1;
		}
		wind::lout << "pass\n";
		al::clear_to_color(wind::map_rgb_i(0x00000));

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

		wind::lout << "Creating Event Queue: ";
		system::m_event_queue = al::create_event_queue();
		if (!system::m_event_queue)
		{
			wind::lout << "failed\n";
			return -1;
		}
		wind::lout << "pass\n";

		wind::lout << "Creating Logic Timer: ";
		this->m_timer = al::create_timer(1.0 / WIND::LOGIC_TIMING);
		if (!this->m_timer)
		{
			wind::lout << "failed\n";
			return -1;
		}
		wind::lout << "pass\n";

		al::register_event_source(system::m_event_queue, al::get_display_event_source(system::m_display));
		al::register_event_source(system::m_event_queue, al::get_timer_event_source(this->m_timer));
		al::register_event_source(system::m_event_queue, al::get_keyboard_event_source());
		al::register_event_source(system::m_event_queue, al::get_mouse_event_source());

		const auto now = std::chrono::system_clock::now();
		const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
		wind::random::set_seed((uint32_t)t_c);

		wind::json::initializer::register_defaults();

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

	void system_t::shutdown()
	{
		wind::lout << "\n----------------------------------------\n"
			<< "Termination Phase Begin\n"
			<< "----------------------------------------" << wind::endl;

		this->m_dialog->on_shutdown();
		wind::lout << "Dialog Terminated\n";

		wind::json::initializer::register_defaults(false);
		wind::lout << "Wind Uninitialized\n";

		if (this->m_timer)
		{
			al::stop_timer(m_timer);
			this->m_timer.reset();
			wind::lout << "Timer Destroyed\n";
		}

		if (system::m_event_queue)
		{
			system::m_event_queue.reset();
			wind::lout << "Event Queue Destroyed\n";
		}

		if (system::m_display)
		{
			system::m_display.reset();
			wind::lout << "Display Destroyed\n";
		}

		al::physfs_addon::shutdown();

		wind::lout << "----------------------------------------\nTermination Phase Complete\n";
	}

	void system_t::loop()
	{
		ALLEGRO::EVENT event{};
		std::shared_ptr<widget_t> selected{};

		this->m_dialog->on_start();

		al::start_timer(this->m_timer);
		al::pause_event_queue(system::m_event_queue, false);

		while (!this->m_kill)
		{
			while (!al::is_event_queue_empty(system::m_event_queue))
			{
				al::get_next_event(system::m_event_queue, event);

				this->m_dialog->on_event(event);

				switch (event.type)
				{
				case ALLEGRO::EVENT_TYPE_KEY_UP:
				{
					wind::input::keyboard::set_released(event.keyboard.keycode);
				} break;

				case ALLEGRO::EVENT_TYPE_KEY_DOWN:
				{
					wind::input::keyboard::set_pressed(event.keyboard.keycode);
				} break;

				case ALLEGRO::EVENT_TYPE_MOUSE_AXES:
				{
					wind::input::mouse::set_position({ event.mouse.x, event.mouse.y });
					wind::input::mouse::set_wheel({ event.mouse.w, event.mouse.z });
				} break;

				case ALLEGRO::EVENT_TYPE_MOUSE_BUTTON_DOWN:
				{
					wind::input::mouse::set_pressed(event.mouse.button);
					selected = this->m_dialog->get_mouse_over(wind::input::mouse::get_position());
					if (!selected)
					{
						selected = this->m_dialog;
					}
				} break;

				case ALLEGRO::EVENT_TYPE_MOUSE_BUTTON_UP:
				{
					wind::input::mouse::set_released(event.mouse.button);

					std::shared_ptr<widget_t> temp = this->m_dialog->get_mouse_over(wind::input::mouse::get_position());
					if (!temp)
					{
						temp = std::static_pointer_cast<widget_t>(this->m_dialog);
					}

					if (selected == temp)
					{
						event.type = ALLEGRO::EVENT_TYPE_MOUSE_BUTTON_CLICK;
						selected->on_event(event);
					}
					selected.reset();
				} break;

				case ALLEGRO::EVENT_TYPE_TIMER:
				{
					if (!system::timer::m_paused)
					{
						++system::timer::m_tick_count;
					}
				} break;

				case ALLEGRO::EVENT_TYPE_DISPLAY_RESIZE:
				{
					al::acknowledge_resize(system::m_display);
				} break;

				case ALLEGRO::EVENT_TYPE_DISPLAY_CLOSE:
				{
					this->m_kill = true;
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

			while (system::timer::m_tick_count > 0)
			{
				if (this->m_dialog->on_update() < 0)
				{
					this->m_kill = true;
				}
				--system::timer::m_tick_count;
			}

			if (this->m_kill)
			{
				break;
			}

			this->m_dialog->on_render();
			al::flip_display();
			al::rest(0.1);
		}

		al::pause_event_queue(system::m_event_queue, true);
		al::stop_timer(this->m_timer);

		this->m_dialog->on_stop();
	}
}
