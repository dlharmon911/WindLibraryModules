export module wind:file_iterator;

import :base;
import :string;

namespace wind
{
	export class file_iterator_t
	{
	public:
		file_iterator_t() = default;

		explicit file_iterator_t(const ALLEGRO::FILE& file) : m_data(file), m_c(ALLEGRO::FILE_EOF) {}

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
			return ((this->eof() && it.eof()) ||
				(this->m_data == it.m_data && al::ftell(this->m_data) == al::ftell(it.m_data)));
		}

		auto operator != (const file_iterator_t& it) -> bool
		{
			return !(this->operator==(it));
		}

		auto eof() const -> bool
		{
			return (!this->m_data || this->m_c == ALLEGRO::FILE_EOF);
		}

		auto get() const -> int32_t
		{
			return this->m_c;
		}

		auto pop() -> void
		{
			if (this->m_data && !al::feof(this->m_data))
			{
				this->m_c = al::fgetc(this->m_data);
			}
			else
			{
				this->m_c = ALLEGRO::FILE_EOF;
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
		int32_t m_c{ ALLEGRO::FILE_EOF };
	};

	template<typename T> auto swap_bytes(const T& v) -> T
	{
		T n{};
		size_t s{ sizeof(T) };
		const char* pn{ (char*)(&n) };
		const char* pv{ (char*)(&v) };

		if (s == 1)
		{
			return v;
		}

		for (auto i = 0; i < s; ++i)
		{
			*(pn + i) = *(pv + s - (i + 1));
		}

		return n;
	}

	template <typename T> auto write_to_file(ALLEGRO::FILE& stream, const T& value) -> ALLEGRO::FILE&
	{
		bool big_endian{ al::get_platform_endianness() == ALLEGRO::BIG_ENDIAN };
		size_t size{ sizeof(T) };

		for (size_t i = 0; i < size; ++i)
		{
			if (al::fputc(stream, *((char*)(&value) + (big_endian ? size - (i + 1) : i))) == ALLEGRO::FILE_EOF)
			{
				break;
			}
		}

		return stream;
	}

	template <typename T> auto read_from_file(ALLEGRO::FILE& stream, T& value) -> ALLEGRO::FILE&
	{
		bool big_endian{ al::get_platform_endianness() == ALLEGRO::BIG_ENDIAN };
		size_t size{ sizeof(T) };

		for (size_t i = 0; i < size; ++i)
		{
			int32_t c = al::fgetc(stream);

			if (c == ALLEGRO::FILE_EOF)
			{
				break;
			}

			*((char*)(&value) + (big_endian ? size - (i + 1) : i)) = c;
		}

		return stream;
	}
}

export auto operator << (ALLEGRO::FILE& stream, const wind::string_t& value) -> ALLEGRO::FILE&
{
	al::fwrite(stream, value.c_str(), value.size());
	return stream;
}

export auto operator << (ALLEGRO::FILE& stream, const char* val) -> ALLEGRO::FILE&
{
	if (val)
	{
		size_t size = strlen(val);
		al::fwrite(stream, val, size);
	}

	return stream;
}

export auto operator << (ALLEGRO::FILE& stream, int8_t value) -> ALLEGRO::FILE&
{
	return wind::write_to_file(stream, value);
}

export auto operator << (ALLEGRO::FILE& stream, uint8_t value) -> ALLEGRO::FILE&
{
	return wind::write_to_file(stream, value);
}

export auto operator << (ALLEGRO::FILE& stream, int16_t value) -> ALLEGRO::FILE&
{
	return wind::write_to_file(stream, value);
}

export auto operator << (ALLEGRO::FILE& stream, uint16_t value) -> ALLEGRO::FILE&
{
	return wind::write_to_file(stream, value);
}

export auto operator << (ALLEGRO::FILE& stream, int32_t value) -> ALLEGRO::FILE&
{
	return wind::write_to_file(stream, value);
}

export auto operator << (ALLEGRO::FILE& stream, uint32_t value) -> ALLEGRO::FILE&
{
	return wind::write_to_file(stream, value);
}

export auto operator << (ALLEGRO::FILE& stream, float value) -> ALLEGRO::FILE&
{
	return wind::write_to_file(stream, value);
}

export auto operator << (ALLEGRO::FILE& stream, double value) -> ALLEGRO::FILE&
{
	return wind::write_to_file(stream, value);
}

export auto operator >> (ALLEGRO::FILE& stream, wind::string_t& value) -> ALLEGRO::FILE&
{
	if (!stream)
	{
		value.clear();
		return stream;
	}

	ALLEGRO::USTRING string{ al::fget_ustr(stream) };

	value.clear();
	value.append(al::c_str(al::fget_ustr(stream)));
	return stream;
}

export auto operator >> (ALLEGRO::FILE& stream, int8_t& value) -> ALLEGRO::FILE&
{
	return wind::read_from_file(stream, value);
}

export auto operator >> (ALLEGRO::FILE& stream, uint8_t& value) -> ALLEGRO::FILE&
{
	return wind::read_from_file(stream, value);
}

export auto operator >> (ALLEGRO::FILE& stream, int16_t& value) -> ALLEGRO::FILE&
{
	return wind::read_from_file(stream, value);
}

export auto operator >> (ALLEGRO::FILE& stream, uint16_t& value) -> ALLEGRO::FILE&
{
	return wind::read_from_file(stream, value);
}

export auto operator >> (ALLEGRO::FILE& stream, int32_t& value) -> ALLEGRO::FILE&
{
	return wind::read_from_file(stream, value);
}

export auto operator >> (ALLEGRO::FILE& stream, uint32_t& value) -> ALLEGRO::FILE&
{
	return wind::read_from_file(stream, value);
}

export auto operator >> (ALLEGRO::FILE& stream, float& value) -> ALLEGRO::FILE&
{
	return wind::read_from_file(stream, value);
}

export auto operator >> (ALLEGRO::FILE& stream, double& value) -> ALLEGRO::FILE&
{
	return wind::read_from_file(stream, value);
}
