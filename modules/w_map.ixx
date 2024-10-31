export module wind:map;

import <string>;
import <array>;
import <vector>;
import <cstdint>;
import <memory>;
import allegro;
import :base;
import :bitmap;
import :tilemap;
import :string;

namespace WIND
{
	namespace MAP
	{
		namespace CELL
		{
			export enum : size_t
			{
				LAYER_BACK_GROUND_00,
				LAYER_BACK_GROUND_01,
				LAYER_SOLID_00,
				LAYER_SOLID_01,
				LAYER_SOLID_02,
				LAYER_FORE_GROUND_00,
				LAYER_FORE_GROUND_01,
				LAYER_UNDEFINED_00,
				LAYER_UNDEFINED_01,
				LAYER_COUNT
			};
		}
	}
}

namespace wind
{
	class map_t;

	namespace map
	{
		export class cell_t : public class_t<cell_t>
		{
		public:
			using element_type = tilemap::tile_t;
			using pointer_element_type = wind::add_pointer<element_type>::type;
			using const_pointer_element_type = wind::add_pointer<wind::add_const<element_type>::type>::type;
			using reference_element_type = wind::add_reference<element_type>::type;
			using const_reference_element_type = wind::add_reference<wind::add_const<element_type>::type>::type;

		private:
			using vector_type = std::array<element_type, WIND::MAP::CELL::LAYER_COUNT>;

		public:
			cell_t();
			cell_t(const cell_t& cell);
			~cell_t();
			auto operator = (const cell_t& cell) ->cell_t&;

			auto at(size_t index) -> reference_element_type;
			auto at(size_t index) const ->const_reference_element_type;
			auto operator [](size_t index)->reference_element_type;
			auto operator [](size_t index) const->const_reference_element_type;

			class iterator
			{
			private:
				iterator() = default;
			public:
				iterator(vector_type::iterator it) : m_it(it) {}
				auto operator == (const iterator& it) const -> bool { return (this->m_it == it.m_it); }
				auto operator != (const iterator& it) const -> bool { return !operator == (it); }
				auto operator ++() -> iterator& { ++this->m_it; return *this; }
				auto operator ++(int32_t) -> iterator { iterator tmp = *this; ++(*this); return tmp; }
				auto operator *() -> reference_element_type { return (*this->m_it); }
				auto operator ->() -> pointer_element_type { return &(*this->m_it); }

			private:
				vector_type::iterator m_it;
			};

			class const_iterator
			{
			private:
				const_iterator() = default;
			public:
				typedef std::ptrdiff_t difference_type;

				const_iterator(const vector_type::const_iterator it) : m_it(it) {}
				auto operator == (const const_iterator& it) const -> bool { return (this->m_it == it.m_it); }
				auto operator != (const const_iterator& it) const -> bool { return !operator == (it); }
				auto operator ++() -> const_iterator& { ++this->m_it; return *this; }
				auto operator ++(int32_t) -> const_iterator { const_iterator tmp = *this; ++(*this); return tmp; }
				auto operator *() const -> const_reference_element_type { return (*this->m_it); }
				auto operator ->() const -> const_pointer_element_type { return &(*this->m_it); }

			private:
				vector_type::const_iterator m_it;
			};

			auto begin()->iterator;
			auto end()->iterator;
			auto cbegin()->const_iterator;
			auto cend()->const_iterator;

		private:
			vector_type m_data;
		};

		export class camera_t : public class_t<camera_t>
		{
		public:
			camera_t();
			camera_t(const camera_t& camera);
			camera_t(ALLEGRO::SIZE<size_t> camera_size, ALLEGRO::POINT<size_t> tile_shift);
			~camera_t();
			auto operator = (const camera_t& camera) ->camera_t&;
			auto set_map(ALLEGRO::RECTANGLE<size_t> map) -> void;
			auto set_tile(ALLEGRO::POINT<size_t> shift) -> void;
			auto get_position() const ->ALLEGRO::POINT<size_t>;
			auto set_position(ALLEGRO::POINT<size_t> position) -> void;
			auto get_size() const -> const ALLEGRO::SIZE<size_t>&;
			auto set_size(ALLEGRO::SIZE<size_t> size) -> void;
			auto get_shift() const -> ALLEGRO::POINT<size_t>;
			auto move(const ALLEGRO::POINT<int32_t> delta) -> ALLEGRO::POINT<int32_t>;

		private:
			ALLEGRO::RECTANGLE<size_t> m_camera;
			ALLEGRO::RECTANGLE<size_t> m_tile;
			ALLEGRO::POINT<int32_t> m_map_tl;
			ALLEGRO::POINT<int32_t> m_map_br;
		};
	}

	export class map_t : public class_t<map_t>
	{
	public:
		using element_type = map::cell_t;
		using pointer_element_type = wind::add_pointer<element_type>::type;
		using const_pointer_element_type = wind::add_pointer<const element_type>::type;
		using reference_element_type = wind::add_reference<element_type>::type;
		using const_reference_element_type = wind::add_reference<const element_type>::type;

	private:
		using shared_type = std::shared_ptr<element_type[]>;

	public:
		map_t();
		map_t(size_t width, size_t height);
		map_t(ALLEGRO::SIZE<size_t> size);
		map_t(const map_t& map);
		~map_t();
		auto operator = (const map_t& map) -> map_t&;

		explicit operator bool () const;

		auto clear() -> void;

		auto reset(size_t width, size_t height) -> bool;
		auto reset(ALLEGRO::SIZE<size_t> size) -> bool;

		auto data() -> void*;
		auto data() const -> const void*;

		auto size() const -> const ALLEGRO::SIZE<size_t>&;

		auto at(size_t index) -> reference_element_type;
		auto at(size_t index) const->const_reference_element_type;
		auto operator [](size_t index)->reference_element_type;
		auto operator [](size_t index) const->const_reference_element_type;

		class iterator : public class_t<iterator>
		{
		private:
			iterator() = default;
		public:
			iterator(shared_type & data, size_t offset) : m_data(data.get()), m_offset(offset) {}
			auto operator == (iterator& it) const -> bool { return (this->m_data == it.m_data && this->m_offset == it.m_offset); }
			auto operator != (iterator& it) const -> bool { return !operator == (it); }
			auto operator ++ () -> iterator& { ++this->m_offset; return *this; }
			auto operator ++ (int32_t) -> iterator { iterator tmp = *this; ++(*this); return tmp; }
			auto operator * () -> reference_element_type { return (this->m_data[this->m_offset]); }
			auto operator -> () -> pointer_element_type { return &(this->m_data[this->m_offset]); }

		private:
			const pointer_element_type m_data;
			size_t m_offset;
		};

		class const_iterator : public class_t<const_iterator>
		{
		private:
			const_iterator() = default;
		public:
			const_iterator(const shared_type& data, size_t offset) : m_data(data.get()), m_offset(offset) {}
			auto operator == (const const_iterator& it) const -> bool { return (this->m_data == it.m_data && this->m_offset == it.m_offset); }
			auto operator != (const const_iterator& it) const -> bool { return !operator == (it); }
			auto operator ++ () -> const_iterator& { ++this->m_offset; return *this; }
			auto operator ++ (int32_t) -> const_iterator { const_iterator tmp = *this; ++(*this); return tmp; }
			auto operator * () const -> const_reference_element_type { return (this->m_data[this->m_offset]); }
			auto operator -> () const -> const_pointer_element_type { return &(this->m_data[this->m_offset]); }

		private:
			const pointer_element_type m_data;
			size_t m_offset;
		};

		auto begin()->iterator;
		auto end()->iterator;
		auto cbegin()->const_iterator;
		auto cend()->const_iterator;

	private:
		shared_type m_data;
		ALLEGRO::SIZE<size_t> m_size;
	};

	namespace map
	{
		export auto load(map_t& map, const string_t& filename) -> bool;
		export auto save(const map_t& map, const string_t& filename) -> bool;
		export auto draw(const map_t& map, const tilemap_t& tilemap, const map::camera_t& camera, ALLEGRO::POINT<size_t> position) -> void;
	}
}
