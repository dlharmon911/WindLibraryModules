export module wind.form_addon:widget.frame;

import <cassert>;
import <memory>;
import <vector>;
import <string>;
import <cstdint>;
import <any>;
import <functional>;
import allegro;
import wind;
import :base;

namespace wind
{	
	namespace form
	{
		namespace widget
		{
			export class frame_t
			{
			public:
				frame_t() = default;
				virtual ~frame_t() = default;
				virtual auto on_initialize() -> int32_t = 0;
				virtual auto on_shutdown() -> int32_t = 0;
				virtual auto on_start() -> int32_t = 0;
				virtual auto on_stop() -> int32_t = 0;
				virtual auto on_update() -> int32_t = 0;
				virtual auto on_render() -> int32_t = 0;
				virtual auto on_event(const ALLEGRO::EVENT& event) -> bool;

				auto get_title() const -> const string_t&;
				auto set_title(const string_t& title) -> void;

			private:
				string_t m_title{};
			};
		}
	}
}
