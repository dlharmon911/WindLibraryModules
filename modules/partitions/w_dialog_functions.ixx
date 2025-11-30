export module wind:dialog.functions;

import :base;
import :string;
import :dialog.type;
import :dialog.system.type;

namespace wind::dialog
{
	export template <typename T> int32_t run(std::span<const char* const>& span) requires std::is_base_of_v<wind::dialog_t, T>
	{
		int32_t rv = -1;

		std::shared_ptr<dialog_t> dialog = std::static_pointer_cast<dialog_t>(std::make_shared<T>());

		if (dialog)
		{
			rv = system_t::run(dialog, span);
		}

		return rv;
	}
}