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
		file_iterator_t() : m_data(), m_c(EOF) {}
		
		file_iterator_t(const ALLEGRO::FILE& file) : m_data(file), m_c(EOF) {}
		
		file_iterator_t(const file_iterator_t& it) : m_data(it.m_data), m_c(it.m_c) {}

		~file_iterator_t() {}

		file_iterator_t& operator = (const file_iterator_t& it)
		{
			this->m_data = it.m_data;
			this->m_c = it.m_c;
			return *this;
		}

		bool operator == (const file_iterator_t& it)
		{
			return ((!this->m_data && !it.m_data) ||
				(this->m_data == it.m_data && al::ftell(this->m_data) == al::ftell(it.m_data)));
		}

		bool operator != (const file_iterator_t& it)
		{
			return !(this->operator==(it));
		}

		int32_t get()
		{
			return this->m_c;
		}

		void pop()
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

		int32_t operator *() const
		{
			return this->m_c;
		}

		file_iterator_t& operator ++() { this->pop(); return *this; }

		file_iterator_t operator ++(int) { file_iterator_t tmp = *this; ++(*this); return tmp; }

		static file_iterator_t begin(ALLEGRO::FILE& file)
		{
			if (file)
			{
				al::fseek(file, 0, ALLEGRO::FILE_SEEK_SET);
				
			}

			file_iterator_t it{ file };

			it.pop();

			return it;
		}

		static file_iterator_t end()
		{
			return file_iterator_t();
		}

	private:
		ALLEGRO::FILE m_data;
		int32_t m_c;
	};
}

export ALLEGRO::FILE& operator << (ALLEGRO::FILE& stream, const wind::string_t& value);
export ALLEGRO::FILE& operator << (ALLEGRO::FILE& stream, const char* value);
export ALLEGRO::FILE& operator << (ALLEGRO::FILE& stream, int8_t value);
export ALLEGRO::FILE& operator << (ALLEGRO::FILE& stream, uint8_t value);
export ALLEGRO::FILE& operator << (ALLEGRO::FILE& stream, int16_t value);
export ALLEGRO::FILE& operator << (ALLEGRO::FILE& stream, uint16_t value);
export ALLEGRO::FILE& operator << (ALLEGRO::FILE& stream, int32_t value);
export ALLEGRO::FILE& operator << (ALLEGRO::FILE& stream, uint32_t value);
export ALLEGRO::FILE& operator << (ALLEGRO::FILE& stream, float value);
export ALLEGRO::FILE& operator << (ALLEGRO::FILE& stream, double value);


export ALLEGRO::FILE& operator >> (ALLEGRO::FILE& stream, wind::string_t& value);
export ALLEGRO::FILE& operator >> (ALLEGRO::FILE& stream, int8_t& value);
export ALLEGRO::FILE& operator >> (ALLEGRO::FILE& stream, uint8_t& value);
export ALLEGRO::FILE& operator >> (ALLEGRO::FILE& stream, int16_t& value);
export ALLEGRO::FILE& operator >> (ALLEGRO::FILE& stream, uint16_t& value);
export ALLEGRO::FILE& operator >> (ALLEGRO::FILE& stream, int32_t& value);
export ALLEGRO::FILE& operator >> (ALLEGRO::FILE& stream, uint32_t& value);
export ALLEGRO::FILE& operator >> (ALLEGRO::FILE& stream, float& value);
export ALLEGRO::FILE& operator >> (ALLEGRO::FILE& stream, double& value);
