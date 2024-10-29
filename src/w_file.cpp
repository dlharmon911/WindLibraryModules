module wind;

import <cstdint>;
import :base;
import :file;
import :string;

namespace wind
{
    template<typename T>
    T swap_bytes(const T& v)
    {
        T n;
        size_t s = sizeof(T);
        char* pn = (char*)(&n);
        char* pv = (char*)(&v);

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

    template <typename T>
    ALLEGRO::FILE& write_to_file(ALLEGRO::FILE& stream, const T& value)
    {
        bool big_endian = al::get_platform_endianness() == ALLEGRO::BIG_ENDIAN;
        size_t size = sizeof(T);

        for (size_t i = 0; i < size; ++i)
        {
            if (al::fputc(stream, *((char*)(&value) + (big_endian ? size - (i + 1) : i))) == EOF)
            {
                break;
            }
        }

        return stream;
    }

    template <typename T>
    ALLEGRO::FILE& read_from_file(ALLEGRO::FILE& stream, T& value)
    {
        bool big_endian = al::get_platform_endianness() == ALLEGRO::BIG_ENDIAN;
        size_t size = sizeof(T);

        for (size_t i = 0; i < size; ++i)
        {
            int32_t c = al::fgetc(stream);
            if (c == EOF)
            {
                break;
            }

            *((char*)(&value) + (big_endian ? size - (i + 1) : i)) = c;
        }

        return stream;
    }
}

ALLEGRO::FILE& operator << (ALLEGRO::FILE& stream, const wind::string_t& value)
{
    al::fwrite(stream, value.c_str(), value.size());
    return stream;
}

ALLEGRO::FILE& operator << (ALLEGRO::FILE& stream, const char* val)
{
    if (val)
    {
        size_t size = strlen(val);
        al::fwrite(stream, val, size);
    }

    return stream;
}

ALLEGRO::FILE& operator << (ALLEGRO::FILE& stream, int8_t value)
{
    return wind::write_to_file(stream, value);
}

ALLEGRO::FILE& operator << (ALLEGRO::FILE& stream, uint8_t value)
{
    return wind::write_to_file(stream, value);
}

ALLEGRO::FILE& operator << (ALLEGRO::FILE& stream, int16_t value)
{
    return wind::write_to_file(stream, value);
}

ALLEGRO::FILE& operator << (ALLEGRO::FILE& stream, uint16_t value)
{
    return wind::write_to_file(stream, value);
}

ALLEGRO::FILE& operator << (ALLEGRO::FILE& stream, int32_t value)
{
    return wind::write_to_file(stream, value);
}

ALLEGRO::FILE& operator << (ALLEGRO::FILE& stream, uint32_t value)
{
    return wind::write_to_file(stream, value);
}

ALLEGRO::FILE& operator << (ALLEGRO::FILE& stream, float value)
{
    return wind::write_to_file(stream, value);
}

ALLEGRO::FILE& operator << (ALLEGRO::FILE& stream, double value)
{
    return wind::write_to_file(stream, value);
}

ALLEGRO::FILE& operator >> (ALLEGRO::FILE& stream, wind::string_t& value)
{
    value.clear();
    value.append(al::fget_ustr(stream));
    return stream;
}

ALLEGRO::FILE& operator >> (ALLEGRO::FILE& stream, int8_t& value)
{
	return wind::read_from_file(stream, value);
}

ALLEGRO::FILE& operator >> (ALLEGRO::FILE& stream, uint8_t& value)
{
    return wind::read_from_file(stream, value);
}

ALLEGRO::FILE& operator >> (ALLEGRO::FILE& stream, int16_t& value)
{
    return wind::read_from_file(stream, value);
}

ALLEGRO::FILE& operator >> (ALLEGRO::FILE& stream, uint16_t& value)
{
    return wind::read_from_file(stream, value);
}

ALLEGRO::FILE& operator >> (ALLEGRO::FILE& stream, int32_t& value)
{
    return wind::read_from_file(stream, value);
}

ALLEGRO::FILE& operator >> (ALLEGRO::FILE& stream, uint32_t& value)
{
    return wind::read_from_file(stream, value);
}

ALLEGRO::FILE& operator >> (ALLEGRO::FILE& stream, float& value)
{
    return wind::read_from_file(stream, value);
}

ALLEGRO::FILE& operator >> (ALLEGRO::FILE& stream, double& value)
{
    return wind::read_from_file(stream, value);
}
