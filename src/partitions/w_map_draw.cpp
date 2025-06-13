module wind;

import <cstdint>;
import :base;
import :map;

namespace wind
{
	namespace map
	{
		namespace cell
		{
			static auto draw(const map::cell_t& cell, const tilemap_t& tilemap, const ALLEGRO::VECTOR_2D<size_t>& position) -> void
			{
				for (size_t layer = 0; layer < std::to_underlying(WIND::MAP::CELL::LAYER::COUNT); ++layer)
				{
					const tilemap::tile_t& tile = cell[(WIND::MAP::CELL::LAYER)layer];
					const tilesheet_t& tilesheet = tilemap.at(tile.get_tilesheet());
					const ALLEGRO::BITMAP& bitmap = tilesheet.at(tile.get_index());

					al::draw_bitmap(bitmap, static_cast<ALLEGRO::VECTOR_2D<float>>(position));
				}
			}
		}

		auto draw(const map_t& map, const tilemap_t& tilemap, const map::camera_t& camera, const ALLEGRO::VECTOR_2D<size_t>& position) -> void
		{
			const ALLEGRO::VECTOR_2D<size_t>& map_size{ map.size() };
			const ALLEGRO::VECTOR_2D<size_t>& camera_size{ camera.get_size() };
			const ALLEGRO::VECTOR_2D<size_t>& tile_size{ static_cast<ALLEGRO::VECTOR_2D<size_t>>(tilemap.get_tile_size()) };
			const ALLEGRO::VECTOR_2D<size_t>& tile_shift{ static_cast<ALLEGRO::VECTOR_2D<size_t>>(tilemap.get_tile_size()) };
			ALLEGRO::VECTOR_2D<size_t> point{ position.get_x() - camera.get_shift().get_x(), position.get_y() - camera.get_shift().get_y() };
			ALLEGRO::VECTOR_2D<size_t> actual_position{};
			size_t map_index{ 0 };
			ALLEGRO::RECTANGLE<int32_t> clip{ al::get_clipping_rectangle() };

			al::set_clipping_rectangle({ position.get_x(), position.get_y(), camera.get_size().get_x() * tile_size.get_x(), camera.get_size().get_y() * tile_size.get_y() });

			for (size_t j = 0; j < (camera_size.get_y() + (camera.get_shift().get_x() ? 1 : 0)); ++j)
			{
				for (size_t i = 0; i < (camera_size.get_x() + (camera.get_shift().get_y() ? 1 : 0)); ++i)
				{
					map_index = (camera.get_position().get_x() + i) + (camera.get_position().get_y() + j) * map_size.get_x();

					cell::draw(map[map_index], tilemap, point);

					point.get_x() += tile_size.get_x();
				}

				point.get_x() = position.get_x();
				point.get_y() += tile_size.get_y();
			}

			al::set_clipping_rectangle(clip);
		}
	}
}
