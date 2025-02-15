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
			static auto draw(const map::cell_t& cell, const tilemap_t& tilemap, const ALLEGRO::POINT<size_t>& position) -> void
			{
				for (size_t layer = 0; layer < std::to_underlying(WIND::MAP::CELL::LAYER::COUNT); ++layer)
				{
					const tilemap::tile_t& tile = cell[(WIND::MAP::CELL::LAYER)layer];
					const tilesheet_t& tilesheet = tilemap.at(tile.get_tilesheet());
					const ALLEGRO::BITMAP& bitmap = tilesheet.at(tile.get_index());

					al::draw_bitmap(bitmap, static_cast<ALLEGRO::POINT<float>>(position));
				}
			}
		}

		auto draw(const map_t& map, const tilemap_t& tilemap, const map::camera_t& camera, const ALLEGRO::POINT<size_t>& position) -> void
		{
			const ALLEGRO::SIZE<size_t>& map_size{ map.size() };
			const ALLEGRO::SIZE<size_t>& camera_size{ camera.get_size() };
			const ALLEGRO::SIZE<size_t>& tile_size{ static_cast<ALLEGRO::SIZE<size_t>>(tilemap.get_tile_size()) };
			const ALLEGRO::SIZE<size_t>& tile_shift{ static_cast<ALLEGRO::SIZE<size_t>>(tilemap.get_tile_size()) };
			ALLEGRO::POINT<size_t> point{ position.x - camera.get_shift().x, position.y - camera.get_shift().y };
			ALLEGRO::POINT<size_t> actual_position{};
			size_t map_index{ 0 };
			ALLEGRO::RECTANGLE<int32_t> clip{ al::get_clipping_rectangle() };

			al::set_clipping_rectangle({ position.x, position.y, camera.get_size().width * tile_size.width, camera.get_size().height * tile_size.height });

			for (size_t j = 0; j < (camera_size.height + (camera.get_shift().x ? 1 : 0)); ++j)
			{
				for (size_t i = 0; i < (camera_size.width + (camera.get_shift().y ? 1 : 0)); ++i)
				{
					map_index = (camera.get_position().x + i) + (camera.get_position().y + j) * map_size.width;

					cell::draw(map[map_index], tilemap, point);

					point.x += tile_size.width;
				}

				point.x = position.x;
				point.y += tile_size.height;
			}

			al::set_clipping_rectangle(clip);
		}
	}
}
