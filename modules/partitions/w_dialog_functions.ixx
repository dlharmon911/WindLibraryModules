export module wind:dialog.functions;

import :base;
import :string;
import :dialog.type;
import :dialog.system.type;

namespace wind::dialog
{
	export template <typename T> int32_t run(std::span<const char* const>& span) requires(std::is_base_of_v<wind::dialog_t, T>)
	{
		int32_t rv = 0;

		std::shared_ptr<T> dialog = std::make_shared<T>();

		if (dialog)
		{
			system_t system(dialog);

			rv = system.run(span);

			dialog.reset();
		}
		else
		{
			rv = -1;
		}

		return rv;
	}
}