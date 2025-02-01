export module wind:file;

import <cstdint>;
import allegro;
import :base;
import :string;

#ifndef EOF
export constexpr int32_t EOF = -1;
#endif

namespace wind
{
	export class file_iterator_t
	{
	public:
		file_iterator_t() = default;

		explicit file_iterator_t(const ALLEGRO::FILE& file) : m_data(file), m_c(EOF) {}

		file_iterator_t(const file_iterator_t& it) = default;

		~file_iterator_t() = default;

		auto operator = (const file_iterator_t& it) -> file_iterator_t&
		{
			this->m_data = it.m_data;
			this->m_c = it.m_c;
			return *this;
		}

		auto operator == (const file_iterator_t& it) -> bool
		{
			return ((!this->m_data && !it.m_data) ||
				(this->m_data == it.m_data && al::ftell(this->m_data) == al::ftell(it.m_data)));
		}

		auto operator != (const file_iterator_t& it) -> bool
		{
			return !(this->operator==(it));
		}

		auto get() -> int32_t
		{
			return this->m_c;
		}

		auto pop() -> void
		{
			if (this->m_data)
			{
				this->m_c = al::fgetc(this->m_data);
			}

			if (this->m_c == EOF)
			{
				this->m_data.reset();
			}
		}

		auto operator *() const -> int32_t
		{
			return this->m_c;
		}

		auto operator ++() -> file_iterator_t& { this->pop(); return *this; }

		auto operator ++(int32_t) -> file_iterator_t { file_iterator_t tmp = *this; ++(*this); return tmp; }

		static auto begin(ALLEGRO::FILE& file) -> file_iterator_t
		{
			if (file)
			{
				al::fseek(file, 0, ALLEGRO::FILE_SEEK_SET);
			}

			file_iterator_t it{ file };

			it.pop();

			return it;
		}

		static auto end() -> file_iterator_t
		{
			return file_iterator_t();
		}

	private:
		ALLEGRO::FILE m_data{};
		int32_t m_c{ EOF };
	};
}

export auto operator << (ALLEGRO::FILE& stream, const wind::string_t& value)->ALLEGRO::FILE&;
export auto operator << (ALLEGRO::FILE& stream, const char* value)->ALLEGRO::FILE&;
export auto operator << (ALLEGRO::FILE& stream, int8_t value)->ALLEGRO::FILE&;
export auto operator << (ALLEGRO::FILE& stream, uint8_t value)->ALLEGRO::FILE&;
export auto operator << (ALLEGRO::FILE& stream, int16_t value)->ALLEGRO::FILE&;
export auto operator << (ALLEGRO::FILE& stream, uint16_t value)->ALLEGRO::FILE&;
export auto operator << (ALLEGRO::FILE& stream, int32_t value)->ALLEGRO::FILE&;
export auto operator << (ALLEGRO::FILE& stream, uint32_t value)->ALLEGRO::FILE&;
export auto operator << (ALLEGRO::FILE& stream, float value)->ALLEGRO::FILE&;
export auto operator << (ALLEGRO::FILE& stream, double value)->ALLEGRO::FILE&;

export auto operator >> (ALLEGRO::FILE& stream, wind::string_t& value)->ALLEGRO::FILE&;
export auto operator >> (ALLEGRO::FILE& stream, int8_t& value)->ALLEGRO::FILE&;
export auto operator >> (ALLEGRO::FILE& stream, uint8_t& value)->ALLEGRO::FILE&;
export auto operator >> (ALLEGRO::FILE& stream, int16_t& value)->ALLEGRO::FILE&;
export auto operator >> (ALLEGRO::FILE& stream, uint16_t& value)->ALLEGRO::FILE&;
export auto operator >> (ALLEGRO::FILE& stream, int32_t& value)->ALLEGRO::FILE&;
export auto operator >> (ALLEGRO::FILE& stream, uint32_t& value)->ALLEGRO::FILE&;
export auto operator >> (ALLEGRO::FILE& stream, float& value)->ALLEGRO::FILE&;
export auto operator >> (ALLEGRO::FILE& stream, double& value)->ALLEGRO::FILE&;