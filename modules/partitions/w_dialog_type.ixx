export module wind:dialog.type;

import :base;
import :string;
import :dialog.data.type;

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
		virtual auto on_initialize() -> int32_t = 0;
		virtual auto on_shutdown() -> int32_t = 0;
		virtual auto on_start() -> int32_t = 0;
		virtual auto on_stop() -> int32_t = 0;
		virtual auto on_update() -> int32_t = 0;
		virtual auto on_render() -> int32_t = 0;
		virtual auto on_event(const ALLEGRO::EVENT& event) -> bool 
		{
			return false;
		}

		auto data() -> dialog::data_t&
		{
			if (!this->m_data)
			{
				throw std::exception{ "Dialog data is not initialized." };
			}

			return *this->m_data;
		}

		auto data() const -> const dialog::data_t&
		{
			if (!this->m_data)
			{
				throw std::exception{ "Dialog data is not initialized." };
			}

			return *this->m_data;
		}

	private:
		friend class dialog::system_t;

		dialog::data_t* m_data{};
	};
}
