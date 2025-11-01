export module wind:uuid.functions;

import :base;
import :uuid.base;
import :string;
import :json;	

namespace wind::json::parser
{
	template <> inline auto parse<uuid_t>(const json::object_t& obj, const string_t& name, uuid_t& value) -> int32_t
	{
		auto it = obj.find(name);
		if (it == obj.cend())
		{
			wind::lout << "Missing key in JSON object: " << name << "\n";
			return -1;
		}

		if (it->second.get_type() != WIND::JSON::TYPE::STRING)
		{
			wind::lout << "Invalid JSON format: Key '" << name << "' is not a string\n";
			return -1;
		}

		if (!value.from_string(it->second.get_as_string()))
		{
			wind::lout << "Invalid UUID format: Key '" << name << "' is not a valid UUID\n";
			return -1;
		}

		return 0;
	}
}

