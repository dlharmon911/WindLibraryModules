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
		export class cell_t
		{
		public:
			using value_type = tilemap::tile_t;
			using pointer_type = value_type*;
			using const_pointer_type = const value_type*;
			using reference_type = value_type&;
			using const_reference_type = const value_type&;

		private:
			using vector_type = std::array<value_type, WIND::MAP::CELL::LAYER_COUNT>;

		public:
			cell_t();
			cell_t(const cell_t& cell);
			~cell_t();
			cell_t& operator = (const cell_t& cell);

			reference_type at(size_t index);
			const_reference_type at(size_t index) const;
			reference_type operator [](size_t index);
			const_reference_type operator [](size_t index) const;

			class iterator
			{
			private:
				iterator() = default;
			public:
				typedef std::ptrdiff_t difference_type;

				iterator(vector_type::iterator it) : m_it(it) {}
				bool operator == (const iterator& it) const { return (this->m_it == it.m_it); }
				bool operator != (const iterator& it) const { return !operator == (it); }
				iterator& operator ++() { ++this->m_it; return *this; }
				iterator operator ++(int) { iterator tmp = *this; ++(*this); return tmp; }
				reference_type operator *() { return (*this->m_it); }
				pointer_type operator ->() { return &(*this->m_it); }

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
				bool operator == (const const_iterator& it) const { return (this->m_it == it.m_it); }
				bool operator != (const const_iterator& it) const { return !operator == (it); }
				const_iterator& operator ++() { ++this->m_it; return *this; }
				const_iterator operator ++(int) { const_iterator tmp = *this; ++(*this); return tmp; }
				const_reference_type operator *() const { return (*this->m_it); }
				const_pointer_type operator ->() const { return &(*this->m_it); }

			private:
				vector_type::const_iterator m_it;
			};

			iterator begin();
			iterator end();
			const_iterator cbegin();
			const_iterator cend();

		private:
			vector_type m_data;
		};

		export class camera_t
		{
		public:
			camera_t();
			camera_t(const camera_t& camera);
			camera_t(ALLEGRO::SIZE<size_t> camera_size, ALLEGRO::POINT<size_t> tile_shift);
			~camera_t();
			camera_t& operator = (const camera_t& camera);

			void set_map(ALLEGRO::RECTANGLE<size_t> map);
			void set_tile(ALLEGRO::POINT<size_t> shift);

			ALLEGRO::POINT<size_t> get_position() const;
			void set_position(ALLEGRO::POINT<size_t> position);

			const ALLEGRO::SIZE<size_t>& get_size() const;
			void set_size(ALLEGRO::SIZE<size_t> size);

			ALLEGRO::POINT<size_t> get_shift() const;

			ALLEGRO::POINT<int32_t> move(const ALLEGRO::POINT<int32_t> delta);

		private:
			ALLEGRO::RECTANGLE<size_t> m_camera;
			ALLEGRO::RECTANGLE<size_t> m_tile;
			ALLEGRO::POINT<int32_t> m_map_tl;
			ALLEGRO::POINT<int32_t> m_map_br;
		};
	}

	export class map_t
	{
	public:
		using value_type = map::cell_t;
		using pointer_type = value_type*;
		using const_pointer_type = const value_type*;
		using reference_type = value_type&;
		using const_reference_type = const value_type&;

	private:
		using shared_type = std::shared_ptr<value_type[]>;

	public:
		map_t();
		map_t(size_t width, size_t height);
		map_t(ALLEGRO::SIZE<size_t> size);
		map_t(const map_t& map);
		~map_t();
		map_t& operator = (const map_t& map);

		explicit operator bool() const;

		void clear();

		bool reset(size_t width, size_t height);
		bool reset(ALLEGRO::SIZE<size_t> size);

		void* data();
		const void* data() const;

		const ALLEGRO::SIZE<size_t>& size() const;

		reference_type at(size_t index);
		const_reference_type at(size_t index) const;
		reference_type operator [](size_t index);
		const_reference_type operator [](size_t index) const;

		class iterator
		{
		private:
			iterator() = default;
		public:
			typedef std::ptrdiff_t difference_type;

			iterator(shared_type & data, size_t offset) : m_data(data.get()), m_offset(offset) {}
			bool operator == (iterator& it) const { return (this->m_data == it.m_data && this->m_offset == it.m_offset); }
			bool operator != (iterator& it) const { return !operator == (it); }
			iterator& operator ++() { ++this->m_offset; return *this; }
			iterator operator ++(int) { iterator tmp = *this; ++(*this); return tmp; }
			reference_type operator *() { return (this->m_data[this->m_offset]); }
			pointer_type operator ->() { return &(this->m_data[this->m_offset]); }

		private:
			const pointer_type m_data;
			size_t m_offset;
		};

		class const_iterator
		{
		private:
			const_iterator() = default;
		public:
			typedef std::ptrdiff_t difference_type;

			const_iterator(const shared_type& data, size_t offset) : m_data(data.get()), m_offset(offset) {}
			bool operator == (const const_iterator& it) const { return (this->m_data == it.m_data && this->m_offset == it.m_offset); }
			bool operator != (const const_iterator& it) const { return !operator == (it); }
			const_iterator& operator ++() { ++this->m_offset; return *this; }
			const_iterator operator ++(int) { const_iterator tmp = *this; ++(*this); return tmp; }
			const_reference_type operator *() const { return (this->m_data[this->m_offset]); }
			const_pointer_type operator ->() const { return &(this->m_data[this->m_offset]); }

		private:
			const pointer_type m_data;
			size_t m_offset;
		};

		iterator begin();
		iterator end();
		const_iterator cbegin();
		const_iterator cend();

	private:
		shared_type m_data;
		ALLEGRO::SIZE<size_t> m_size;
	};

	namespace map
	{
		export bool load(map_t& map, const string_t& filename);
		export bool save(const map_t& map, const string_t& filename);
		export void draw(const map_t& map, const tilemap_t& tilemap, const map::camera_t& camera, ALLEGRO::POINT<size_t> position);
	}
}
