export module wind:json;

import allegro;
export import :json.object;
export import :json.io;

namespace wind
{
	namespace json
	{
		export 	template <typename T>
			auto parse_size(const wind::json_object_t& object, ALLEGRO::SIZE<T>& size) -> int32_t
		{
			auto width_it = object.find("width");
			if (width_it == object.cend())
			{
				return -1;
			}

			if (width_it->get_type() != WIND::JSON::TYPE_NUMBER)
			{
				return -1;
			}
			size.width = (T)width_it->get_as_number();

			auto height_it = object.find("height");
			if (height_it == object.cend())
			{
				return -1;
			}

			if (height_it->get_type() != WIND::JSON::TYPE_NUMBER)
			{
				return -1;
			}
			size.height = (T)height_it->get_as_number();
			return 0;
		}

		export 	template <typename T>
			auto parse_point(const wind::json_object_t& object, ALLEGRO::POINT<T>& point) -> int32_t
		{
			auto x_it = object.find("x");
			if (x_it == object.cend())
			{
				return -1;
			}

			if (x_it->get_type() != WIND::JSON::TYPE_NUMBER)
			{
				return -1;
			}
			point.x = (T)x_it->get_as_number();

			auto y_it = object.find("y");
			if (y_it == object.cend())
			{
				return -1;
			}

			if (y_it->get_type() != WIND::JSON::TYPE_NUMBER)
			{
				return -1;
			}
			point.y = (T)y_it->get_as_number();
			return 0;
		}
	}
}
