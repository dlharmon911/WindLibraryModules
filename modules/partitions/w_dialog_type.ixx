export module wind:dialog.type;

import :base;
import :string;
import :dialog.settings;
import :input;

namespace wind
{
	namespace dialog
	{
		class system_t;
	}

	export class dialog_t
	{
	public:
		dialog_t() = default;
		virtual ~dialog_t() = default;
		virtual auto version() const -> uint32_t = 0;
		virtual auto title() const -> const wind::string_t & = 0;
		virtual auto on_pre_initialize(dialog::settings_t& settings) -> int32_t
		{
			return 0;
		}
		virtual auto on_initialize() -> int32_t = 0;
		virtual auto on_shutdown() -> int32_t = 0;
		virtual auto on_start() -> int32_t = 0;
		virtual auto on_stop() -> int32_t = 0;
		virtual auto on_update(input_t& input) -> int32_t = 0;
		virtual auto on_render(const ALLEGRO::DISPLAY& display) -> int32_t = 0;
		virtual auto on_event(const ALLEGRO::EVENT& event) -> bool 
		{
			return false;
		}

	private:
		friend class dialog::system_t;
	};
}
