module wind.datafile_addon;

import <string>;
import <cstdint>;
import <any>;
import allegro;
import wind;
import :base;
import :object;

namespace wind
{
	namespace datafile::object::datafile
	{
		using element_type = typename wind::datafile_t;

		class data_t
		{
		public:
			~data_t() = default;
			explicit data_t(const json_array_t& array) : m_array(array) {}
			const json_array_t& m_array;

		private:
			data_t() = delete;
		};

		static auto get_type(const json_object_t& object) -> int32_t
		{
			auto it{ object.find("type") };
			if (it == object.cend())
			{
				return -1;
			}

			if (it->get_type() != WIND::JSON::TYPE::STRING)
			{
				return -1;
			}

			string_t name{ it->get_as<string_t>() };

			return get_object_type(name);
		}

		static auto parse_object(const json_t& json, object_t& dobject)->int32_t
		{
			std::function<auto(const json_t&, std::any&)->int32_t> function{};

			if (json.get_type() != WIND::JSON::TYPE::OBJECT)
			{
				return -1;
			}

			const json_object_t& object = static_cast<const json_object_t&>(json);

			dobject.m_type = get_type(object);

			if (dobject.m_type < 0)
			{
				return -1;
			}

			if (get_object_function(dobject.m_type, function) < 0)
			{
				return -1;
			}

			return function(json, dobject.m_any);
		}

		static auto generate_object(const data_t& data, std::any& any) -> int32_t
		{
			size_t size = data.m_array.size();
			datafile_t datafile{ size };

			for (size_t index = 0; index < size; ++index)
			{
				const json_t& json{ data.m_array[index] };

				if (parse_object(json, datafile[index]) < 0)
				{
					return -1;
				}
			}

			any = datafile;

			return 0;
		}

		auto parse(const json_t& json, std::any& any) -> int32_t
		{
			if (json.get_type() != WIND::JSON::TYPE::OBJECT)
			{
				return -1;
			}

			const json_object_t& object = static_cast<const json_object_t&>(json);

			auto it = object.find("objects");
			if (it == object.cend())
			{
				return -1;
			}

			if (it->get_type() != WIND::JSON::TYPE::ARRAY)
			{
				return -1;
			}

			data_t data(static_cast<const json_array_t&>(*it));

			if (generate_object(data, any) < 0)
			{
				return -1;
			}

			return 0;
		}
	}
}
