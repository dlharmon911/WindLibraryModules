export module dialog.widget.button;

import <string>;
import <memory>;
import std;
import allegro;
import wind;

namespace wind
{
	export class button_t : public dialog::widget_t
	{
	public:
		button_t();
		~button_t();

		int32_t on_initialize() override;
		int32_t on_shutdown() override;
		int32_t on_start() override;
		int32_t on_stop() override;
		int32_t on_update() override;
		int32_t on_render() override;

	private:
	};
}

