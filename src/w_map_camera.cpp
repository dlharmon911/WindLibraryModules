module wind;

import <cstdint>;
import :base;
import :map;
import std;

namespace wind
{
	namespace map
	{
		camera_t::camera_t() : m_camera(), m_tile(), m_map_tl(), m_map_br() {}

		camera_t::camera_t(const ALLEGRO::SIZE<size_t>& camera_size, const ALLEGRO::POINT<size_t>& tile_shift) : m_camera({ {0,0}, camera_size }), m_tile({ tile_shift, {(1 << tile_shift.x), (1 << tile_shift.y)} }), m_map_tl(), m_map_br() {}

		camera_t::camera_t(const camera_t& camera) : m_camera(camera.m_camera), m_tile(camera.m_tile), m_map_tl(camera.m_map_tl), m_map_br(camera.m_map_br) {}

		camera_t::~camera_t() {}

		auto camera_t::operator = (const camera_t& camera) -> camera_t&
		{
			this->m_camera = camera.m_camera;
			this->m_tile = camera.m_tile;
			this->m_map_tl = camera.m_map_tl;
			this->m_map_br = camera.m_map_br;

			return *this;
		}

		auto camera_t::set_map(const ALLEGRO::RECTANGLE<size_t>& map) -> void
		{
			this->m_map_tl = { (map.position.x << this->m_tile.position.x), (map.position.y << this->m_tile.position.y) };
			this->m_map_br = { this->m_map_tl.x + ((map.size.width - 1) << this->m_tile.position.x), this->m_map_tl.y + ((map.size.height - 1) << this->m_tile.position.y) };
		}

		auto camera_t::set_tile(const ALLEGRO::POINT<size_t>& shift) -> void
		{
			this->m_tile = { shift, {(1 << shift.x), (1 << shift.y)} };
		}

		auto camera_t::get_size() const -> const ALLEGRO::SIZE<size_t>&
		{
			return this->m_camera.size;
		}

		auto camera_t::set_size(const ALLEGRO::SIZE<size_t>& size) -> void
		{
			this->m_camera.size = size;
		}

		auto camera_t::get_position() const -> ALLEGRO::POINT<size_t>
		{
			return { (this->m_camera.position.x >> this->m_tile.position.x), (this->m_camera.position.y >> this->m_tile.position.y) };
		}

		auto camera_t::set_position(const ALLEGRO::POINT<size_t>& position) -> void
		{
			this->m_camera.position.x = (position.x << this->m_tile.position.x);
			this->m_camera.position.y = (position.y << this->m_tile.position.y);
		}

		auto camera_t::get_shift() const -> ALLEGRO::POINT<size_t>
		{
			return { this->m_camera.position.x % this->m_tile.size.width, this->m_camera.position.y % this->m_tile.size.height };
		}

		auto camera_t::move(const ALLEGRO::POINT<int32_t>& delta) -> ALLEGRO::POINT<int32_t>
		{
			const ALLEGRO::POINT<int32_t> br = { this->m_map_br.x - (this->m_camera.size.width << this->m_tile.position.x), this->m_map_br.y - (this->m_camera.size.height << this->m_tile.position.y) };
			const ALLEGRO::POINT<int32_t> start = static_cast<ALLEGRO::POINT<int32_t>>(this->m_camera.position);

			if (delta.x)
			{
				if (delta.x < 0)
				{
					this->m_camera.position.x = static_cast<size_t>(start.x) - std::min(-delta.x, start.x - this->m_map_tl.x);
				}
				else
				{
					this->m_camera.position.x = static_cast<size_t>(start.x) + std::min(delta.x, br.x - start.x);
				}
			}

			if (delta.y)
			{
				if (delta.y < 0)
				{
					this->m_camera.position.y = static_cast<size_t>(start.y) - std::min(-delta.y, start.y - this->m_map_tl.y);
				}
				else
				{
					this->m_camera.position.y = static_cast<size_t>(start.y) + std::min(delta.y, br.y - start.y);
				}
			}

			return { this->m_camera.position.x - start.x, this->m_camera.position.y - start.y };
		}
	}
}