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

		camera_t::camera_t(const ALLEGRO::VECTOR_2D<size_t>& camera_size, const ALLEGRO::VECTOR_2D<size_t>& tile_shift) : m_camera({ ALLEGRO::VECTOR_2D<size_t>(), camera_size}), m_tile({tile_shift, ALLEGRO::VECTOR_2D<size_t>((1 << tile_shift.get_x()), (1 << tile_shift.get_y()))}), m_map_tl(), m_map_br() {}

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
			this->m_map_tl = ALLEGRO::VECTOR_2D<int32_t>((map.get_position().get_x() << this->m_tile.get_position().get_x()), (map.get_position().get_y() << this->m_tile.get_position().get_y()) );
			this->m_map_br = ALLEGRO::VECTOR_2D<int32_t>(this->m_map_tl.get_x() + ((map.get_size().get_x() - 1) << this->m_tile.get_position().get_x()), this->m_map_tl.get_y() + ((map.get_size().get_y() - 1) << this->m_tile.get_position().get_y()) );
		}

		auto camera_t::set_tile(const ALLEGRO::VECTOR_2D<size_t>& shift) -> void
		{
			this->m_tile = { shift, ALLEGRO::VECTOR_2D<size_t>((1 << shift.get_x()), (1 << shift.get_y())) };
		}

		auto camera_t::get_size() const -> const ALLEGRO::VECTOR_2D<size_t>&
		{
			return this->m_camera.get_size();
		}

		auto camera_t::set_size(const ALLEGRO::VECTOR_2D<size_t>& size) -> void
		{
			this->m_camera.get_size() = size;
		}

		auto camera_t::get_position() const -> ALLEGRO::VECTOR_2D<size_t>
		{
			return { (this->m_camera.get_position().get_x() >> this->m_tile.get_position().get_x()), (this->m_camera.get_position().get_y() >> this->m_tile.get_position().get_y()) };
		}

		auto camera_t::set_position(const ALLEGRO::VECTOR_2D<size_t>& position) -> void
		{
			this->m_camera.get_position().get_x() = (position.get_x() << this->m_tile.get_position().get_x());
			this->m_camera.get_position().get_y() = (position.get_y() << this->m_tile.get_position().get_y());
		}

		auto camera_t::get_shift() const -> ALLEGRO::VECTOR_2D<size_t>
		{
			return { this->m_camera.get_position().get_x() % this->m_tile.get_size().get_x(), this->m_camera.get_position().get_y() % this->m_tile.get_size().get_y() };
		}

		auto camera_t::move(const ALLEGRO::VECTOR_2D<int32_t>& delta) -> ALLEGRO::VECTOR_2D<int32_t>
		{
			const ALLEGRO::VECTOR_2D<int32_t> br(this->m_map_br.get_x() - (this->m_camera.get_size().get_x() << this->m_tile.get_position().get_x()), this->m_map_br.get_y() - (this->m_camera.get_size().get_y() << this->m_tile.get_position().get_y()));
			const ALLEGRO::VECTOR_2D<int32_t> start(this->m_camera.get_position());

			if (delta.get_x())
			{
				if (delta.get_x() < 0)
				{
					this->m_camera.get_position().get_x() = static_cast<size_t>(start.get_x()) - std::min(-delta.get_x(), start.get_x() - this->m_map_tl.get_x());
				}
				else
				{
					this->m_camera.get_position().get_x() = static_cast<size_t>(start.get_x()) + std::min(delta.get_x(), br.get_x() - start.get_x());
				}
			}

			if (delta.get_y())
			{
				if (delta.get_y() < 0)
				{
					this->m_camera.get_position().get_y() = static_cast<size_t>(start.get_y()) - std::min(-delta.get_y(), start.get_y() - this->m_map_tl.get_y());
				}
				else
				{
					this->m_camera.get_position().get_y() = static_cast<size_t>(start.get_y()) + std::min(delta.get_y(), br.get_y() - start.get_y());
				}
			}

			return ALLEGRO::VECTOR_2D<int32_t>(this->m_camera.get_position().get_x() - start.get_x(), this->m_camera.get_position().get_y() - start.get_y() );
		}
	}
}
