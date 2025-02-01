export module wind:system;

import <cstdint>;
import <vector>;
import <string>;
import <memory>;
import <ctime>;
import allegro;
import :dialog;
import :base;
import :string;
import :array;

namespace wind
{
	export class system_t
	{
	public:
		explicit system_t(wind::add_const_reference_t<std::shared_ptr<dialog_t>> dialog);
		~system_t();
		auto run(wind::add_const_reference_t<array_t<wind::string_t>> args) -> int32_t;

	private:
		auto init(wind::add_const_reference_t<array_t<wind::string_t>> args) -> int32_t;
		auto shutdown() -> void;
		auto loop() -> void;

		std::shared_ptr<dialog_t> m_dialog{};
		ALLEGRO::TIMER m_timer{ nullptr };
		bool m_kill{ false };
	};

	namespace system
	{
		namespace timer
		{
			export auto pause() -> void;
			export auto unpause() -> void;
			export auto reset() -> void;
		}

		namespace display
		{
			export using option_t = struct option_tag_t
			{
				int32_t m_value{ 0 };
				int32_t m_importance{ 0 };
			};
			export auto get_new_option(int32_t id) -> display::option_t&;
			export auto set_new_option(int32_t id, const display::option_t& option) -> void;
			export auto get_new_flags() -> int32_t;
			export auto set_new_flags(int32_t flags) -> void;
			export auto get() -> wind::add_const_reference<ALLEGRO::DISPLAY>::type;
		}

		namespace event_queue
		{
			export auto get() -> wind::add_const_reference<ALLEGRO::EVENT_QUEUE>::type;
		}

		export auto timestamp() -> wind::string_t;
	}
}