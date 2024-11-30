export module wind.datafile_addon;

import <cassert>;
import <memory>;
import <vector>;
import <string>;
import <cstdint>;
import <map>;
import allegro;
import wind;

namespace WIND
{
	namespace DATAFILE
	{
		namespace OBJECT
		{
			export enum
			{
				TYPE_UNDEFINED = -1,
				TYPE_DATAFILE,
				TYPE_BITMAP,
				TYPE_FONT,
				TYPE_TEXT,
				TYPE_TILESHEET,
				TYPE_COUNT,
				TYPE_USER_DEFINED = 0X100
			};
		}

		namespace OUTPUT_TYPE
		{
			export enum
			{
				HEADER,
				MODULE
			};
		}
	}
}

namespace wind
{
	export class datafile_t
	{
	public:
		using element_type = std::shared_ptr<void>;
		using pointer_element_type = wind::add_pointer<element_type>::type;
		using const_pointer_element_type = wind::add_pointer<wind::add_const<element_type>::type>::type;
		using reference_element_type = wind::add_reference<element_type>::type;
		using const_reference_element_type = wind::add_reference<wind::add_const<element_type>::type>::type;

	private:
		using vector_t = std::vector<std::shared_ptr<void>>;

	public:
		using object_info_t = std::pair<int32_t, string_t>;

		datafile_t();
		datafile_t(const datafile_t& datafile);
		~datafile_t();
		datafile_t& operator = (const datafile_t& datafile);

		size_t size() const;
		bool is_empty() const;
		void clear();

		void* data();
		const void* data() const;

		std::shared_ptr<void> get_object(size_t index);
		const std::shared_ptr<void> get_object(size_t index) const;
		std::shared_ptr<void> operator[](size_t index);
		const std::shared_ptr<void> operator[](size_t index) const;

		int32_t get_index(const string_t& name) const;

		object_info_t& get_info(size_t index);
		const object_info_t& get_info(size_t index) const;

		template <typename T>
		void push_back(int32_t type, const string_t& name, T* data, void (*deleter)(T*))
		{
			std::shared_ptr<T> object{ data, deleter };

			this->m_object_data.push_back(std::static_pointer_cast<void>(object));
			this->m_element_data.push_back({ type, name });
		}

		void push_back(int32_t type, const string_t& name, std::shared_ptr<void>& data);
		void pop_back();

		class iterator
		{
		private:
			iterator() = default;
		public:
			iterator(vector_t::iterator o, std::vector<object_info_t>::iterator e) : m_o(o), m_e(e) {}
			int32_t type() const { return this->m_e->first; }
			string_t name() const { return this->m_e->second; }
			reference_element_type data() { return *this->m_o; }

			bool operator == (const iterator& it) const { return (this->m_o == it.m_o && this->m_e == it.m_e); }
			bool operator != (const iterator& it) const { return !operator == (it); }
			iterator& operator ++() { ++this->m_o; ++this->m_e; return *this; }
			iterator operator++(int32_t) { iterator tmp = *this; ++(*this); return tmp; }
			reference_element_type operator *() { return *this->m_o; }
			pointer_element_type operator &() { return &(*this->m_o); }

		private:
			vector_t::iterator m_o;
			std::vector<object_info_t>::iterator m_e;
		};

		class const_iterator
		{
		private:
			const_iterator() = default;
		public:
			const_iterator(vector_t::const_iterator o, std::vector<object_info_t>::const_iterator e) : m_o(o), m_e(e) {}
			int32_t type() const { return this->m_e->first; }
			string_t name() const { return this->m_e->second; }
			const_reference_element_type data() const { return *this->m_o; }

			bool operator == (const const_iterator& it) const { return (this->m_o == it.m_o && this->m_e == it.m_e); }
			bool operator != (const const_iterator& it) const { return !operator == (it); }
			const_iterator& operator ++() { ++this->m_o; ++this->m_e; return *this; }
			const_iterator operator++(int32_t) { const_iterator tmp = *this; ++(*this); return tmp; }
			const_reference_element_type operator *() const { return *this->m_o; }
			const_pointer_element_type operator &() const { return &(*this->m_o); }

		private:
			vector_t::const_iterator m_o;
			std::vector<object_info_t>::const_iterator m_e;
		};

		iterator begin();
		iterator end();
		const_iterator cbegin();
		const_iterator cend();

	private:
		vector_t m_object_data;
		std::vector<object_info_t> m_element_data;
	};

	namespace datafile
	{
		export constexpr int32_t shortcut_prefix = '$';
		export bool generate_header_file(const string_t& manifest_filename, const string_t& header_filename, int32_t type = WIND::DATAFILE::OUTPUT_TYPE::HEADER, const char sListSep = ',');
		export datafile_t load(const string_t& filename, const char sListSep = ',');

		namespace parser
		{
			bool parse(const string_t& filename, datafile_t& datafile, const char sListSep);
		}

		struct object_struct_tag_t
		{
			int32_t m_type{ -1 };
			size_t m_index{ 0 };
			string_t m_name{};
			std::shared_ptr<void> m_object{};
		};

		export using object_t = object_struct_tag_t;

		namespace object
		{
			class data_t;
			bool datafile_parser(data_t& data, object_t& object);

			export class data_t
			{
			public:
				data_t();
				data_t(const data_t& data);
				~data_t();
				data_t& operator = (const data_t& data);
				explicit operator bool() const;
				bool has_children() const;
				bool contains(const string_t& name) const;
				const data_t get_child(const string_t& name) const;
				bool has_content() const;

				string_t get_string() const;

				template <typename T> bool find_data(const string_t& name, T& value, bool required = true) const
				{
					if (!this->contains(name))
					{
						if (!required)
						{
							wind::error::push(string::to_string("Missing \"%s\" attribute", name.c_str()), __FILE__, __LINE__, __FUNCTION__);
						}
						return false;
					}

					const object::data_t node = this->get_child(name);

					if (!node.has_content())
					{
						if (!required)
						{
							wind::error::push(string::to_string("Empty \"%s\" attribute", name.c_str()), __FILE__, __LINE__, __FUNCTION__);
						}
						return false;
					}

					value = node.get_string().get_as<T>();

					return true;
				}

				object_t find_object(const string_t& name);

				class iterator
				{
				public:
					using element_type = data_t;

					iterator() = default;

					string_t key() const { return this->m_iter.key(); };
					const data_t data() const { return data_t(this->m_objects, this->m_root, &(*this->m_iter), this->m_config); };

					bool operator == (const iterator& it) const { return (this->m_iter == it.m_iter); }
					bool operator != (const iterator& it) const { return !operator == (it); }
					iterator& operator ++() { ++this->m_iter; return *this; }
					iterator operator++(int32_t) { iterator tmp = *this; ++(*this); return tmp; }
					const data_t operator *() const { return data_t(this->m_objects, this->m_root, &(*this->m_iter), this->m_config); };

					friend class data_t;

				private:
					iterator(const std::shared_ptr<std::vector<object_t>>& objects, const dson_t* root, const dson_t::const_iterator& iter, const dson_t* config) : m_objects(objects), m_root(root), m_iter(iter), m_config(config) {}

					std::shared_ptr<std::vector<object_t>> m_objects;
					const dson_t* m_root;
					dson_t::const_iterator m_iter;
					const dson_t* m_config;
				};

				iterator begin();
				iterator end();

				friend class iterator;
				friend bool datafile_parser(data_t& data, object_t& object);
				friend bool datafile::parser::parse(const string_t& filename, datafile_t& datafile, const char sListSep);

			private:
				data_t(const std::shared_ptr<std::vector<object_t>>& objects, const dson_t* root, const dson_t* node, const dson_t* config);

				std::shared_ptr<std::vector<object_t>> m_objects;
				const dson_t* m_root;
				const dson_t* m_node;
				const dson_t* m_config;
			};

			export inline const string_t names[WIND::DATAFILE::OBJECT::TYPE_COUNT] =
			{
				"DATAFILE",
				"BITMAP",
				"FONT",
				"TEXT",
				"TILESHEET"
			};

			export using parser_func_t = bool (*)(data_t& data, object_t& object);

			export void register_type(int32_t type, const string_t& name, bool (*parser_func)(data_t& data, object_t& object));
			export int32_t get_type(const string_t& name);
			export std::map<int32_t, std::pair<string_t, parser_func_t>>& get_info();
			export bool datafile_parser(data_t& data, object_t& object);
			export bool bitmap_parser(data_t& data, object_t& object);
			export bool font_parser(data_t& data, object_t& object);
			export bool text_parser(data_t& data, object_t& object);
			export bool tilesheet_parser(data_t& data, object_t& object);
		}
	}
}