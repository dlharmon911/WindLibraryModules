export module wind:input.base;

import :base;
import :input.constants;

namespace wind
{
	namespace input
	{
		export class button_t
		{
		public:
			button_t() = default;
			button_t(const button_t& button) = default;
			~button_t() = default;
			button_t& operator = (const button_t& button) = default;

			auto value() const -> uint8_t
			{
				return this->m_value;
			}

			auto value(uint8_t value) -> void
			{
				this->m_value = value;
			}

			auto acknowledge() -> void
			{
				if (this->m_value & WIND::INPUT::BUTTON::CHANGED)
				{
					this->m_value ^= WIND::INPUT::BUTTON::CHANGED;
				}
			}

			auto is_pressed() const -> bool
			{
				return (this->m_value & WIND::INPUT::BUTTON::PRESSED);
			}

			auto has_changed() const -> bool
			{
				return (this->m_value & WIND::INPUT::BUTTON::CHANGED);
			}

			auto was_pressed() const -> bool
			{
				return ((this->m_value & WIND::INPUT::BUTTON::PRESSED) && (this->m_value & WIND::INPUT::BUTTON::CHANGED));
			}
			auto was_released() const -> bool
			{
				return (!(this->m_value & WIND::INPUT::BUTTON::PRESSED) && (this->m_value & WIND::INPUT::BUTTON::CHANGED));
			}
		private:
			uint8_t m_value{ WIND::INPUT::BUTTON::DEFAULT };
		};

		export class mouse_t
		{
		public:
			mouse_t() = default;
			mouse_t(const mouse_t& mouse) = default;
			~mouse_t() = default;
			mouse_t& operator = (const mouse_t& mouse) = default;

			auto operator[](int32_t index) -> button_t&
			{
				ALLEGRO::ASSERT(index < this->m_buttons.size());
				return this->m_buttons[index];
			}

			auto operator[](int32_t index) const -> const button_t&
			{
				ALLEGRO::ASSERT(index < this->m_buttons.size());
				return this->m_buttons[index];
			}

			auto button(int32_t index) -> button_t&
			{
				ALLEGRO::ASSERT(index < this->m_buttons.size());
				return this->m_buttons[index];
			}

			auto button(int32_t index) const -> const button_t&
			{
				ALLEGRO::ASSERT(index < this->m_buttons.size());
				return this->m_buttons[index];
			}

			auto acknowledge() -> void
			{
				for (auto& button : this->m_buttons)
				{
					button.acknowledge();
				}
			}

			auto x() -> float&
			{
				return this->m_axis.first;
			}

			auto x() const -> const float&
			{
				return this->m_axis.first;
			}

			auto x(float value) -> void
			{
				this->m_axis.first = value;
			}

			auto y() -> float&
			{
				return this->m_axis.second;
			}

			auto y() const -> const float&
			{
				return this->m_axis.second;
			}

			auto y(float value) -> void
			{
				this->m_axis.second = value;
			}

			auto axis() -> std::pair<float, float>&
			{
				return this->m_axis;
			}

			auto axis() const -> const std::pair<float, float>&
			{
				return this->m_axis;
			}

			auto axis(const std::pair<float, float>& axis) -> void
			{
				this->m_axis = axis;
			}

		private:
			std::pair<float, float> m_axis;
			std::array<button_t, WIND::INPUT::KEY::MAX> m_buttons;
		};

		export class key_t
		{
		public:
			key_t() = default;
			key_t(const key_t& key) = default;
			~key_t() = default;
			key_t& operator = (const key_t& key) = default;

			auto operator[](int32_t index) -> button_t&
			{
				ALLEGRO::ASSERT(index < this->m_buttons.size());
				return this->m_buttons[index];
			}

			auto operator[](int32_t index) const -> const button_t&
			{
				ALLEGRO::ASSERT(index < this->m_buttons.size());
				return this->m_buttons[index];
			}

			auto button(int32_t index) -> button_t&
			{
				ALLEGRO::ASSERT(index < this->m_buttons.size());
				return this->m_buttons[index];
			}

			auto button(int32_t index) const -> const button_t&
			{
				ALLEGRO::ASSERT(index < this->m_buttons.size());
				return this->m_buttons[index];
			}

			auto acknowledge() -> void
			{
				for (auto& button : this->m_buttons)
				{
					button.acknowledge();
				}
			}

		private:
			std::array<button_t, WIND::INPUT::KEY::MAX> m_buttons;
		};
	}

	export class input_t
	{
	public:
		input_t() = default;
		input_t(const input_t& input) = default;
		~input_t() = default;
		input_t& operator = (const input_t& input) = default;

		auto key() -> input::key_t&
		{
			return this->m_key;
		}

		auto key() const -> const input::key_t&
		{
			return this->m_key;
		}

		auto mouse() -> input::mouse_t&
		{
			return this->m_mouse;
		}

		auto mouse() const -> const input::mouse_t&
		{
			return this->m_mouse;
		}

		auto acknowledge() -> void
		{
			this->m_key.acknowledge();
			this->m_mouse.acknowledge();
		}

	private:
		input::key_t m_key{};
		input::mouse_t m_mouse{};
	};
}
