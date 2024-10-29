module wind;

import <cstdint>;
import :base;
import :map;

namespace wind
{
	namespace map
	{
		camera_t::camera_t() : m_camera(), m_tile(), m_map_tl(), m_map_br() {}
		
		camera_t::camera_t(ALLEGRO::SIZE<size_t> camera_size, ALLEGRO::POINT<size_t> tile_shift) : m_camera({ {0,0}, camera_size }), m_tile({ tile_shift, {(1 << tile_shift.x), (1 << tile_shift.y)} }), m_map_tl(), m_map_br() {}
		
		camera_t::camera_t(const camera_t& camera) : m_camera(camera.m_camera), m_tile(camera.m_tile), m_map_tl(camera.m_map_tl), m_map_br(camera.m_map_br) {}
		
		camera_t::~camera_t() {}
		
		camera_t& camera_t::operator = (const camera_t& camera)
		{
			this->m_camera = camera.m_camera;
			this->m_tile = camera.m_tile;
			this->m_map_tl = camera.m_map_tl;
			this->m_map_br = camera.m_map_br;

			return *this;
		}

		void camera_t::set_map(ALLEGRO::RECTANGLE<size_t> map)
		{
			this->m_map_tl = { (map.position.x << this->m_tile.position.x), (map.position.y << this->m_tile.position.y) };
			this->m_map_br = { this->m_map_tl.x + ((map.size.width - 1) << this->m_tile.position.x), this->m_map_tl.y + ((map.size.height - 1) << this->m_tile.position.y) };
		}

		void camera_t::set_tile(ALLEGRO::POINT<size_t> shift)
		{
			this->m_tile = { shift, {(1 << shift.x), (1 << shift.y)} };
		}

		const ALLEGRO::SIZE<size_t>& camera_t::get_size() const
		{
			return this->m_camera.size;
		}

		void camera_t::set_size(ALLEGRO::SIZE<size_t> size)
		{
			this->m_camera.size = size;
		}

		ALLEGRO::POINT<size_t> camera_t::get_position() const
		{
			return { (this->m_camera.position.x >> this->m_tile.position.x), (this->m_camera.position.y >> this->m_tile.position.y) };
		}

		void camera_t::set_position(ALLEGRO::POINT<size_t> position)
		{
			this->m_camera.position.x = (position.x << this->m_tile.position.x);
			this->m_camera.position.y = (position.y << this->m_tile.position.y);
		}

		ALLEGRO::POINT<size_t> camera_t::get_shift() const
		{
			return { this->m_camera.position.x % this->m_tile.size.width, this->m_camera.position.y % this->m_tile.size.height };
		}

		ALLEGRO::POINT<int32_t> camera_t::move(const ALLEGRO::POINT<int32_t> delta)
		{
			const ALLEGRO::POINT<int32_t> br = { this->m_map_br.x - (this->m_camera.size.width << this->m_tile.position.x), this->m_map_br.y - (this->m_camera.size.height << this->m_tile.position.y) };
			const ALLEGRO::POINT<int32_t> start = this->m_camera.position;

			if (delta.x)
			{
				if (delta.x < 0)
				{
					this->m_camera.position.x = start.x - std::min(-delta.x, start.x - this->m_map_tl.x);
				}
				else
				{
					this->m_camera.position.x = start.x + std::min(delta.x, br.x - start.x);
				}
			}

			if (delta.y)
			{
				if (delta.y < 0)
				{
					this->m_camera.position.y = start.y - std::min(-delta.y, start.y - this->m_map_tl.y);
				}
				else
				{
					this->m_camera.position.y = start.y + std::min(delta.y, br.y - start.y);
				}
			}












			return { this->m_camera.position.x - start.x, this->m_camera.position.y - start.y};
		}
	}
}
