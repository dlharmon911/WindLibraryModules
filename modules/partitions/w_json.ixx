export module wind:json;

import allegro;
export import :json.object;
export import :json.io;
export import :json.initializer;

namespace wind
{
	namespace json
	{
		export 	template <typename T>
			auto parse_size(const wind::json_object_t& object, ALLEGRO::VECTOR_2D<T>& size) -> int32_t
		{
			auto width_it = object.find("width");
			if (width_it == object.cend())
			{
				return -1;
			}

			if (width_it->get_type() != WIND::JSON::TYPE::NUMBER)
			{
				return -1;
			}
			size.get_x() = width_it->get_as<T>();

			auto height_it = object.find("height");
			if (height_it == object.cend())
			{
				return -1;
			}

			if (height_it->get_type() != WIND::JSON::TYPE::NUMBER)
			{
				return -1;
			}
			size.get_y() = height_it->get_as<T>();
			return 0;
		}

		export 	template <typename T>
			auto parse_point(const wind::json_object_t& object, ALLEGRO::VECTOR_2D<T>& point) -> int32_t
		{
			auto x_it = object.find("x");
			if (x_it == object.cend())
			{
				return -1;
			}

			if (x_it->get_type() != WIND::JSON::TYPE::NUMBER)
			{
				return -1;
			}
			point.get_x() = x_it->get_as<T>();

			auto y_it = object.find("y");
			if (y_it == object.cend())
			{
				return -1;
			}

			if (y_it->get_type() != WIND::JSON::TYPE::NUMBER)
			{
				return -1;
			}
			point.get_y() = y_it->get_as<T>();
			return 0;
		}
	}
}
