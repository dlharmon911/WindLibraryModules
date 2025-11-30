export module wind:nbt.file.read.payload;

import :base;
import :file;
import :nbt.constants;
import :nbt.types;
import :nbt.file.read.string;

namespace wind::nbt::payload
{
	namespace list
	{
		auto read(ALLEGRO::FILE& file, list_t& list) -> int32_t;
	}

	namespace compound
	{
		auto read(ALLEGRO::FILE& file, compound_t& compound) -> int32_t;
	}

	export auto read(ALLEGRO::FILE& file, type_t type, payload_t& payload) -> int32_t
	{
		int32_t result{ 0 };

		switch (type)
		{
			using enum WIND::NBT::TAG_TYPE;
		case BYTE:
		{
			payload::byte_t value{};
			if (file::read_integral_type<payload::byte_t>(file, value, sizeof(payload::byte_t)) != sizeof(payload::byte_t))
			{
				return file::error(__FILE__, __LINE__);
			}
			payload = value;
			result = static_cast<int32_t>(sizeof(payload::byte_t));
		} break;
		case SHORT:
		{
			payload::short_t value{};
			if (file::read_integral_type<payload::short_t>(file, value, sizeof(payload::short_t)) != sizeof(payload::short_t))
			{
				return file::error(__FILE__, __LINE__);
			}
			payload = value;
			result = static_cast<int32_t>(sizeof(payload::short_t));
		} break;
		case INT:
		{
			payload::int_t value{};
			if (file::read_integral_type<payload::int_t>(file, value, sizeof(payload::int_t)) != sizeof(payload::int_t))
			{
				return file::error(__FILE__, __LINE__);
			}
			payload = value;
			result = static_cast<int32_t>(sizeof(payload::int_t));
		} break;
		case LONG:
		{
			payload::long_t value{};
			if (file::read_integral_type<payload::long_t>(file, value, sizeof(payload::long_t)) != sizeof(payload::long_t))
			{
				return file::error(__FILE__, __LINE__);
			}
			payload = value;
			result = static_cast<int32_t>(sizeof(payload::long_t));
		} break;
		case FLOAT:
		{
			payload::float_t value{};
			if (file::read_floating_point_type<payload::float_t>(file, value, sizeof(payload::float_t)) != sizeof(payload::float_t))
			{
				return file::error(__FILE__, __LINE__);
			}
			payload = value;
			result = static_cast<int32_t>(sizeof(payload::float_t));
		} break;
		case DOUBLE:
		{
			payload::double_t value{};
			if (file::read_floating_point_type<payload::double_t>(file, value, sizeof(payload::double_t)) != sizeof(payload::double_t))
			{
				return file::error(__FILE__, __LINE__);
			}
			payload = value;
			result = static_cast<int32_t>(sizeof(payload::double_t));
		} break;
		case BYTE_ARRAY:
		{
			payload::byte_array_t value{};
			payload::int_t size{ 0 };
			auto result = file::read_array_type<payload::byte_t>(file, value, size);
			if (result == ALLEGRO::FILE_EOF)
			{
				return file::error(__FILE__, __LINE__);
			}
			payload = value;
			result = result;
		} break;
		case STRING:
		{
			payload::string_t value{};
			auto result = string::read(file, value);
			if (result == ALLEGRO::FILE_EOF)
			{
				return file::error(__FILE__, __LINE__);
			}
			payload = value;
		} break;
		case LIST:
		{
			payload::list_t list_payload{};
			auto result = list::read(file, list_payload);
			if (result == ALLEGRO::FILE_EOF)
			{
				return file::error(__FILE__, __LINE__);
			}
			payload = list_payload;
			
		} break;
		case COMPOUND:
		{
			payload::compound_t compound_payload{};
			auto result = compound::read(file, compound_payload);
			if (result == ALLEGRO::FILE_EOF)
			{
				return file::error(__FILE__, __LINE__);
			}
			payload = compound_payload;
		} break;
		case INT_ARRAY:
		{
			payload::int_array_t value{};
			payload::int_t size{ 0 };
			auto result = file::read_array_type<payload::int_t>(file, value, size);
			if (result == ALLEGRO::FILE_EOF)
			{
				return file::error(__FILE__, __LINE__);
			}
			payload = value;
		} break;
		case LONG_ARRAY:
		{
			payload::long_array_t value{};
			payload::int_t size{ 0 };
			auto result = file::read_array_type<payload::long_t>(file, value, size);
			if (result == ALLEGRO::FILE_EOF)
			{
				return file::error(__FILE__, __LINE__);
			}
			payload = value;
		} break;
		default:
			return file::error(__FILE__, __LINE__);
		}

		return result;
	}
}

