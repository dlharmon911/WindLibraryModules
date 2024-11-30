export module wind:ninepatch;

import <cstdint>;
import <memory>;
import allegro;
import :base;
import :string;
import :memory;

namespace WIND
{
	namespace NINEPATCH
	{
		namespace DRAW_FLAG
		{
			enum
			{
				STRETCHED,
				TILED
			};
		}
	}
}

namespace wind
{
	class ninepatch_t;

	namespace ninepatch
	{
		export auto draw(const ninepatch_t& ninepatch, const ALLEGRO::POINT<int32_t>& position, const ALLEGRO::SIZE<int32_t>& size, int32_t flags = WIND::NINEPATCH::DRAW_FLAG::STRETCHED) -> void;
	}

	export class ninepatch_t
	{
	public:
		ninepatch_t();
		ninepatch_t(const string_t& filename);
		ninepatch_t(const ALLEGRO::BITMAP& bitmap);
		ninepatch_t(const ninepatch_t& ninepatch);
		~ninepatch_t();

		explicit operator bool() const;

		auto get_partition() const -> const ALLEGRO::BOX<int32_t>&;
		auto get_margin() const -> const ALLEGRO::BOX<int32_t>&;
		auto get_bitmap() const-> const ALLEGRO::BITMAP&;

		friend auto ninepatch::draw(const ninepatch_t& ninepatch, const ALLEGRO::POINT<int32_t>& position, const ALLEGRO::SIZE<int32_t>& size, int32_t flags) -> void;
	private:
		auto create(const ALLEGRO::BITMAP& bitmap) -> bool;
		auto load(const string_t& filename) -> bool;

		ALLEGRO::BITMAP m_bitmap{};
		ALLEGRO::BOX<int32_t> m_partition{ 0, 0, 0, 0 };
		ALLEGRO::BOX<int32_t> m_margin{ 0, 0, 0, 0 };
	};
}