export module wind:nbt.file.write.payload;

import :base;
import :file;
import :nbt.constants;
import :nbt.types;
import :nbt.file.write.string;

namespace wind::nbt::payload
{
	namespace list
	{
		auto write(ALLEGRO::FILE& file, const list_t& list) -> int32_t;
	}

	namespace compound
	{
		auto write(ALLEGRO::FILE& file, const compound_t& compound) -> int32_t;
	}

	export auto write(ALLEGRO::FILE& file, type_t type, const payload_t& payload) -> int32_t
	{
		int32_t result{ 0 };
		switch (type)
		{
		case WIND::NBT::TAG_TYPE::BYTE:
		{
			byte_t value = std::any_cast<byte_t>(payload);
			result = file::write_integral_type<byte_t>(file, value, sizeof(byte_t));
		} break;
		case WIND::NBT::TAG_TYPE::SHORT:
		{
			short_t value = std::any_cast<short_t>(payload);
			result = file::write_integral_type<short_t>(file, value, sizeof(short_t));
		} break;
		case WIND::NBT::TAG_TYPE::INT:
		{
			int_t value = std::any_cast<int_t>(payload);
			result = file::write_integral_type<int_t>(file, value, sizeof(int_t));
		} break;
		case WIND::NBT::TAG_TYPE::LONG:
		{
			long_t value = std::any_cast<long_t>(payload);
			result = file::write_integral_type<long_t>(file, value, sizeof(long_t));
		} break;
		case WIND::NBT::TAG_TYPE::FLOAT:
		{
			float_t value = std::any_cast<float_t>(payload);
			result = file::write_floating_point_type<float_t>(file, value, sizeof(float_t));
		} break;
		case WIND::NBT::TAG_TYPE::DOUBLE:
		{
			double_t value = std::any_cast<double_t>(payload);
			result = file::write_floating_point_type<double_t>(file, value, sizeof(double_t));
		} break;
		case WIND::NBT::TAG_TYPE::BYTE_ARRAY:
		{
			byte_array_t value = std::any_cast<byte_array_t>(payload);
			result = file::write_array_type<byte_t>(file, value);
		} break;
		case WIND::NBT::TAG_TYPE::STRING:
		{
			string_t string = std::any_cast<string_t>(payload);
			result = string::write(file, string);
		} break;
		case WIND::NBT::TAG_TYPE::LIST:
		{
			list_t list = std::any_cast<list_t>(payload);
			result = list::write(file, list);
		} break;
		case WIND::NBT::TAG_TYPE::COMPOUND:
		{
			compound_t compound = std::any_cast<compound_t>(payload);
			result = compound::write(file, compound);
		} break;
		case WIND::NBT::TAG_TYPE::INT_ARRAY:
		{
			int_array_t value = std::any_cast<int_array_t>(payload);
			result = file::write_array_type<int_t>(file, value);
		} break;
		case WIND::NBT::TAG_TYPE::LONG_ARRAY:
		{
			long_array_t value = std::any_cast<long_array_t>(payload);
			result = file::write_array_type<long_t>(file, value);
		} break;
		default:
			result = ALLEGRO::FILE_EOF;
			break;
		}
		return result;
	}
}