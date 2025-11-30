export module wind:nbt.types;

import :base;
import :u8string;
import :nbt.constants;

namespace wind::nbt
{
	export using type_t = WIND::NBT::TAG_TYPE;
	export using payload_t = std::any;

	export using tag_t = struct tag_tag_t
	{
		type_t m_type{ WIND::NBT::TAG_TYPE::INVALID };
		payload_t m_payload{};
	};

	export using node_t = struct node_tag_t
	{
		u8string_t m_name{};
		tag_t m_tag{};
	};

	namespace payload
	{
		export using byte_t = int8_t;
		export using short_t = int16_t;
		export using int_t = int32_t;
		export using long_t = int64_t;
		export using float_t = float;
		export using double_t = double;
		export using string_t = u8string_t;
		export using list_t = struct list_tag_t
		{
			type_t m_type{ WIND::NBT::TAG_TYPE::INVALID };
			std::vector<payload_t> m_data{};
		};
		export using compound_t = typename std::unordered_map<u8string_t, tag_t>;
		export using byte_array_t = typename std::vector<byte_t>;
		export using int_array_t = typename std::vector<int_t>;
		export using long_array_t = typename std::vector<long_t>;
	}
}
