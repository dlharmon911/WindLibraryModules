module wind.datafile_addon;

import <cassert>;
import <vector>;
import <string>;
import <cstdint>;
import <map>;
import std;
import allegro;
import allegro.physfs_addon;
import wind;

namespace wind
{
	namespace datafile
	{
		static bool registered = false;

		namespace config
		{
			int32_t expand_string(const dson_t& config_file, const string_t& name, string_t& output)
			{
				bool has_shortcut = false;
				size_t i = 0;

				output.clear();

				while (i < name.size())
				{
					if (name[i] == shortcut_prefix)
					{
						has_shortcut = true;
						string_t s{};

						++i;
						if (name[i] != '(')
						{
							wind::error::push("Missing opening parenthesis", __FILE__, __LINE__, __FUNCTION__);
							return -1;
						}
						++i;
						while (name[i] != ')')
						{
							if (i == name.size())
							{
								wind::error::push("Missing closing parenthesis", __FILE__, __LINE__, __FUNCTION__);
								return -1;
							}
							s.push_back(name[i]);
							++i;
						}
						dson_t sk = config_file.get_property(s);
						string_t shortcut = sk.get_content();
						if (shortcut.size() <= 0)
						{
							return -1;
						}

						output.append(shortcut);
					}
					else
					{
						output.push_back(name[i]);
					}
					++i;
				}

				if (has_shortcut)
				{
					string_t input = output;
					output.clear();
					return expand_string(config_file, input, output);
				}

				return 0;
			}

			string_t get_content(dson_t& config_file, const string_t& name, const string_t& default_value)
			{
				string_t expansion;

				if (expand_string(config_file, name, expansion) == 0)
				{
					dson_t& d = config_file.get_property(expansion);

					if (d.empty())
					{
						d.set_content(default_value);
					}

					if (expand_string(config_file, d.get_content(), expansion) < 0)
					{
						return string_t();
					}
				}
				return expansion;
			}

			void set_content(dson_t& config_file, const string_t& name, const string_t& value)
			{
				config_file.get_property(name).set_content(value);
			}

			template <typename T>
			T get_as(dson_t& config_file, const string_t& name, const T default_value) = delete;

			template <>
			int32_t get_as(dson_t& config_file, const string_t& name, const int32_t default_value)
			{
				string_t str = config::get_content(config_file, name, std::to_string(default_value));
				return std::atoi(str.c_str());
			}

			template <>
			double get_as(dson_t& config_file, const string_t& name, const double default_value)
			{
				string_t str = config::get_content(config_file, name, std::to_string(default_value));
				return std::atof(str.c_str());
			}

			template <>
			bool get_as(dson_t& config_file, const string_t& name, const bool default_value)
			{
				string_t str = config::get_content(config_file, name, (default_value ? "true" : "false"));
				return string::to_lower(str) == "true";
			}

			template <typename T>
			void set_as(dson_t& config_file, const string_t& name, const T value) = delete;

			template <>
			void set_as(dson_t& config_file, const string_t& name, int32_t value)
			{
				config::set_content(config_file, name, std::to_string(value));
			}

			template <>
			void set_as(dson_t& config_file, const string_t& name, double value)
			{
				config::set_content(config_file, name, std::to_string(value));
			}

			template <>
			void set_as(dson_t& config_file, const string_t& name, bool value)
			{
				config::set_content(config_file, name, string_t(value ? "true" : "false"));
			}
		}

		namespace object
		{
			std::map<int32_t, std::pair<string_t, parser_func_t>> m_info;

			int32_t get_type(const string_t& name);
			std::map<int32_t, std::pair<string_t, parser_func_t>>& get_info();

			data_t::data_t() : m_objects(nullptr), m_root(nullptr), m_node(nullptr), m_config(nullptr)
			{
			}

			data_t::data_t(const std::shared_ptr<std::vector<object_t>>& objects, const dson_t* root, const dson_t* node, const dson_t* config) : m_objects(objects), m_root(root), m_node(node), m_config(config)
			{
			}

			data_t::data_t(const data_t& data) : m_objects(data.m_objects), m_root(data.m_root), m_node(data.m_node), m_config(data.m_config)
			{
			}

			data_t::~data_t()
			{
			}

			data_t& data_t::operator = (const data_t& data)
			{
				this->m_root = data.m_root;
				this->m_node = data.m_node;
				this->m_config = data.m_config;
				return *this;
			}

			data_t::operator bool() const
			{
				return (this->m_node != nullptr);
			}

			bool data_t::has_children() const
			{
				return this->m_node->has_children();
			}

			bool data_t::contains(const string_t& name) const
			{
				return this->m_node->contains(name);
			}

			const data_t data_t::get_child(const string_t& name) const
			{
				return data_t(this->m_objects, this->m_root, &((*this->m_node)[name]), this->m_config);
			}

			bool data_t::has_content() const
			{
				return this->m_node->has_content();
			}

			string_t data_t::get_string() const
			{
				string_t output;

				if (this->m_node->has_content())
				{
					string_t temp = this->m_node->get_content();
					int32_t rv = config::expand_string(*this->m_config, temp, output);

					if (rv < 0)
					{
						output.clear();
					}
				}

				return output;
			}

			bool load_object(data_t& data, object_t& object)
			{
				string_t type_string{};

				if (!data.find_data("type", type_string))
				{
					wind::error::push("Missing \"type\" attribute", __FILE__, __LINE__, __FUNCTION__);
					return false;
				}

				object.m_type = object::get_type(type_string);

				if (object.m_type == WIND::DATAFILE::OBJECT::TYPE_UNDEFINED)
				{
					wind::error::push("Invalid \"type\" attribute", __FILE__, __LINE__, __FUNCTION__);
					return false;
				}

				object::parser_func_t func = object::get_info()[object.m_type].second;

				if (!func(data, object))
				{
					wind::error::push("Unregistered \"type\" object", __FILE__, __LINE__, __FUNCTION__);
					return false;
				}

				if (!object.m_object)
				{
					return false;
				}

				return true;
			}

			object_t data_t::find_object(const string_t& name)
			{
				size_t index = 0;

				for (auto it = this->m_objects.get()->cbegin(); it != this->m_objects.get()->cend(); ++it)
				{
					if (it->m_name == name)
					{
						return (*it);
					}
				}

				for (auto it = this->m_root->cbegin(); it != this->m_root->cend(); ++it)
				{
					if (it.key()[0] == shortcut_prefix)
					{
						continue;
					}

					if (it.key() == name)
					{
						data_t node(this->m_objects, this->m_root, &(*it), this->m_config);

						object_t object{ WIND::DATAFILE::OBJECT::TYPE_USER_DEFINED, index, name, nullptr };

						if (load_object(node, object))
						{
							this->m_objects->push_back(object);
							return object;
						}

						break;
					}

					++index;
				}

				wind::error::push(string::to_string("Object \"%s\" not found", name.c_str()), __FILE__, __LINE__, __FUNCTION__);

				return { WIND::DATAFILE::OBJECT::TYPE_USER_DEFINED, 0, string_t(), nullptr };
			}

			data_t::iterator data_t::begin()
			{
				return data_t::iterator(this->m_objects, this->m_root, this->m_node->cbegin(), this->m_config);
			}

			data_t::iterator data_t::end()
			{
				return data_t::iterator(this->m_objects, this->m_root, this->m_node->cend(), this->m_config);
			}

			/****************************************************************************************************/

			int32_t get_type(const string_t& name)
			{
				for (auto t : m_info)
				{
					if (string::to_lower(name) == t.second.first) return t.first;
				}

				return -1;
			}

			std::map<int32_t, std::pair<string_t, parser_func_t>>& get_info()
			{
				return m_info;
			}

			extern bool datafile_parser(data_t& data, object_t& object);
			extern void register_default_types();
		}
	}

	datafile_t::datafile_t() : m_object_data(), m_element_data() {}

	datafile_t::datafile_t(const datafile_t& datafile) : m_object_data(datafile.m_object_data), m_element_data(datafile.m_element_data) {}

	datafile_t::~datafile_t()
	{
		this->clear();
	}

	datafile_t& datafile_t::operator = (const datafile_t& datafile)
	{
		this->m_object_data = datafile.m_object_data;
		this->m_element_data = datafile.m_element_data;

		return *this;
	}

	void datafile_t::clear()
	{
		while (this->m_object_data.size() > 0)
		{
			this->pop_back();
		}
		this->m_element_data.clear();
	}

	void* datafile_t::data()
	{
		return this->m_object_data.data();
	}

	const void* datafile_t::data() const
	{
		return this->m_object_data.data();
	}

	size_t datafile_t::size() const
	{
		return this->m_object_data.size();
	}

	bool datafile_t::is_empty() const
	{
		return this->m_object_data.empty();
	}

	void datafile_t::push_back(int32_t type, const string_t& name, std::shared_ptr<void>& data)
	{
		this->m_object_data.push_back(data);
		this->m_element_data.push_back({ type, name });
	}

	void datafile_t::pop_back()
	{
		ALLEGRO::ASSERT(this->m_object_data.size() > 0);
		this->m_object_data.pop_back();
		this->m_element_data.pop_back();
	}

	std::shared_ptr<void> datafile_t::get_object(size_t index)
	{
		if (index < this->m_object_data.size())
		{
			return this->m_object_data[index];
		}
		return nullptr;
	}

	const std::shared_ptr<void> datafile_t::get_object(size_t index) const
	{
		if (index < this->m_object_data.size())
		{
			return this->m_object_data[index];
		}
		return nullptr;
	}

	std::shared_ptr<void> datafile_t::operator[](size_t index)
	{
		return this->get_object(index);
	}

	const std::shared_ptr<void> datafile_t::operator[](size_t index) const
	{
		return this->get_object(index);
	}

	int32_t datafile_t::get_index(const string_t& name) const
	{
		int32_t index = 0;

		for (auto it = this->m_element_data.cbegin(); it != this->m_element_data.cend(); ++it)
		{
			if (string::to_lower(it->second) == string::to_lower(name))
			{
				return index;
			}

			++index;
		}

		return -1;
	}

	datafile_t::object_info_t& datafile_t::get_info(size_t index)
	{
		ALLEGRO::ASSERT(index < this->m_element_data.size());
		return this->m_element_data[index];
	}

	const datafile_t::object_info_t& datafile_t::get_info(size_t index) const
	{
		ALLEGRO::ASSERT(index < this->m_element_data.size());
		return this->m_element_data[index];
	}

	datafile_t::iterator datafile_t::begin()
	{
		return datafile_t::iterator(this->m_object_data.begin(), this->m_element_data.begin());
	}

	datafile_t::iterator datafile_t::end()
	{
		return datafile_t::iterator(this->m_object_data.end(), this->m_element_data.end());
	}

	datafile_t::const_iterator datafile_t::cbegin()
	{
		return datafile_t::const_iterator(this->m_object_data.cbegin(), this->m_element_data.cbegin());
	}

	datafile_t::const_iterator datafile_t::cend()
	{
		return datafile_t::const_iterator(this->m_object_data.cend(), this->m_element_data.cend());
	}

	namespace datafile
	{
		namespace parser
		{
			std::vector<string_t> m_path;

			int32_t process_shortcuts(const dson_t& dson, dson_t& config, const string_t& prefix = "")
			{
				for (auto i = dson.cbegin(); i != dson.cend(); ++i)
				{
					string_t key = i.key();

					if (key[0] == shortcut_prefix)
					{
						string_t name = key.substr(1);
						string_t value = i->get_content();

						if (value.size() == 0)
						{
							wind::error::push("Empty variable string", __FILE__, __LINE__, __FUNCTION__);
							return -1;
						}

						if (prefix.size() == 0)
						{
							config[name].set_content(value);
						}
						else
						{
							config.get_property(prefix)[name].set_content(value);
						}
					}
					else
					{
						string_t _prefix = prefix;
						if (_prefix.size() > 0)
						{
							_prefix.push_back('.');
						}

						const dson_t child = dson[key];

						if (process_shortcuts(child, config, _prefix + key) < 0)
						{
							return -1;
						}
					}
				}

				return 0;
			}

			bool parse(const string_t& filename, datafile_t& datafile, const char sListSep)
			{
				const char* s = filename.c_str();

				if (!registered)
				{
					object::register_default_types();
					registered = true;
				}

				datafile.clear();

				if (al::filename_exists(filename.c_str()))
				{
					dson_t dson;

					if (dson_t::read(dson, filename))
					{
						dson_t config;

						if (process_shortcuts(dson, config) < 0)
						{
							return false;
						}

						std::vector<object_t> temp;

						std::shared_ptr<std::vector<object_t>> objects{ nullptr };

						object::data_t data(objects, &dson, &dson, &config);

						object_t object = { WIND::DATAFILE::OBJECT::TYPE_USER_DEFINED, 0, string_t(), nullptr };

						if (!object::datafile_parser(data, object))
						{
							return false;
						}

						datafile = *((datafile_t*)object.m_object.get());

						return true;
					}
				}

				return false;
			}

			string_t write_header_object(ALLEGRO::FILE& pfile, const dson_t& dson, std::vector<string_t>& header, const string_t& name, const string_t& type_name, size_t index)
			{
				string_t out = "\tconstexpr auto " + string::fuse(header, '_') + " = " + std::to_string(index) + ';';
				while (out.size() < 56) out.push_back(' ');
				out.append("/* ");
				out.append(string::to_upper(type_name));
				out.append(" */");

				return out;
			}

			bool write_header_datafile(ALLEGRO::FILE& pfile, const dson_t& dson, std::vector<string_t>& header, int32_t output_type)
			{
				size_t index = 0;

				for (auto i = dson.cbegin(); i != dson.cend(); ++i)
				{
					string_t entry{};
					string_t key{ i.key() };
					const dson_t& node{ dson[key] };

					if (key[0] == shortcut_prefix)
					{
						continue;
					}

					if (!node.contains("type"))
					{
						wind::error::push("Missing \"type\" attribute", __FILE__, __LINE__, __FUNCTION__);
						return false;
					}

					const dson_t& node_type = node.get_child("type");

					if (!node_type.has_content())
					{
						wind::error::push("Empty \"type\" attribute", __FILE__, __LINE__, __FUNCTION__);
						return false;
					}

					int32_t type = object::get_type(node_type.get_content());

					if (type == WIND::DATAFILE::OBJECT::TYPE_UNDEFINED)
					{
						wind::error::push("Invalid \"type\" attribute", __FILE__, __LINE__, __FUNCTION__);
						return false;
					}

					header.push_back(key);
					entry = write_header_object(pfile, node, header, key, node_type.get_content(), index);
					header.pop_back();

					pfile << entry;
					pfile << "\n";

					if (type == WIND::DATAFILE::OBJECT::TYPE_DATAFILE)
					{
						if (!write_header_datafile(pfile, dson, header, type))
						{
							return false;
						}
					}

					++index;
				}

				header.push_back("count");
				pfile << "\tconstexpr auto " << string::fuse(header, '_') + " = " << std::to_string(index) << ";\n";
				header.pop_back();

				return true;
			}

			bool write_header(const dson_t& dson, const string_t& input_text_filename, const string_t& output_filename, int32_t output_type)
			{
				std::vector<string_t> header{};
				int32_t n = 0;
				string_t output = path::make_canonical(output_filename);
				ALLEGRO::FILE pfile{ al::fopen(output.c_str(), "wb") };
				string_t prefix = "datafile";

				if (!pfile)
				{
					wind::error::push(string::to_string("Could not open file: \"%s\"", output.c_str()), __FILE__, __LINE__, __FUNCTION__);
					return false;
				}

				if (dson.contains("$prefix"))
				{
					prefix = dson.get_child("$prefix").get_content();
				}

				pfile << "/* Datafile object indexes */\n"
					<< "/* Index File: "
					<< input_text_filename
					<< " */\n"
					<< "/* Date: "
					<< system::timestamp()
					<< " */ \n"
					<< "/* Do not hand edit! */\n\n";

				if (output_type == WIND::DATAFILE::OUTPUT_TYPE::MODULE)
				{
					pfile << "export module " << string::to_lower(prefix) << ";\n\n"

						<< "export namespace " << string::to_upper(prefix) << "\n"
						<< "{\n";
				}

				if (output_type == WIND::DATAFILE::OUTPUT_TYPE::HEADER)
				{
					header.push_back(prefix);
				}

				if (!write_header_datafile(pfile, dson, header, output_type))
				{
					return false;
				}

				if (output_type == WIND::DATAFILE::OUTPUT_TYPE::MODULE)
				{
					pfile << "}";
				}

				if (output_type == WIND::DATAFILE::OUTPUT_TYPE::HEADER)
				{
					header.pop_back();
				}

				pfile << "\n\n";

				return true;
			}
		}

		bool generate_header_file(const string_t& manifest_filename, const string_t& header_filename, int32_t type, const char sListSep)
		{
			dson_t dson{};

			if (!registered)
			{
				object::register_default_types();
				registered = true;
			}

			if (!dson_t::read(dson, manifest_filename, sListSep))
			{
				return false;
			}

			return datafile::parser::write_header(dson, manifest_filename, header_filename, type);
		}

		datafile_t load(const string_t& filename, const char sListSep)
		{
			string_t filepath = path::make_canonical(filename);
			string_t base;
			string_t ext;
			string_t path;
			datafile_t output;
			bool archive = false;
			bool error = false;

			filepath = path::make_canonical(filename);
			path::split_filepath(filepath, path, base, ext);

			const PHYSFS_ArchiveInfo** i = nullptr;
			for (i = PHYSFS_supportedArchiveTypes(); *i != nullptr; i++)
			{
				if (string::to_upper(ext) == (*i)->extension)
				{
					archive = true;
					break;
				}
			}

			if (archive)
			{
				const ALLEGRO::FILE_INTERFACE file_interface = al::get_new_file_interface();

				if (PHYSFS_mount(filename.c_str(), nullptr, 1))
				{
					al::physfs_addon::set_file_interface();
					if (!datafile::parser::parse("index.ini", output, sListSep))
					{
						error = true;
					}
					PHYSFS_unmount(filename.c_str());
				}

				al::set_new_file_interface(file_interface);
			}
			else
			{
				string_t dir = al::get_current_directory();

				al::change_directory((dir + ALLEGRO::NATIVE_PATH_SEP + path).c_str());
				if (!datafile::parser::parse(base + "." + ext, output, sListSep))
				{
					error = true;
				}
				al::change_directory(dir.c_str());
			}

			if (error)
			{
				output.clear();
			}

			return output;
		}

		namespace object
		{
			void register_type(int32_t type, const string_t& name, bool (*parser_func)(data_t& data, object_t& object))
			{
				get_info()[type] = { string::to_lower(name), parser_func };
			}

			void register_default_types()
			{
				register_type(WIND::DATAFILE::OBJECT::TYPE_BITMAP, names[WIND::DATAFILE::OBJECT::TYPE_BITMAP], bitmap_parser);
				register_type(WIND::DATAFILE::OBJECT::TYPE_FONT, names[WIND::DATAFILE::OBJECT::TYPE_FONT], font_parser);
				register_type(WIND::DATAFILE::OBJECT::TYPE_TEXT, names[WIND::DATAFILE::OBJECT::TYPE_TEXT], text_parser);
				register_type(WIND::DATAFILE::OBJECT::TYPE_DATAFILE, names[WIND::DATAFILE::OBJECT::TYPE_DATAFILE], datafile_parser);
				register_type(WIND::DATAFILE::OBJECT::TYPE_TILESHEET, names[WIND::DATAFILE::OBJECT::TYPE_TILESHEET], tilesheet_parser);
			}

			bool temp_data_compare(const object_t& a, const object_t& b)
			{
				return (a.m_index < b.m_index);
			}

			size_t object_count(data_t& data)
			{
				size_t size = 0;

				for (auto it = data.begin(); it != data.end(); ++it)
				{
					if (it.key()[0] == shortcut_prefix)
					{
						continue;
					}
					++size;
				}

				return size;
			}

			bool datafile_parser(data_t& data, object_t& object)
			{
				size_t size = object_count(data);
				size_t count = 0;

				data.m_objects = std::make_shared<std::vector<object_t>>(size);

				if (!data.m_objects)
				{
					wind::error::push("Memory allocation", __FILE__, __LINE__, __FUNCTION__);
					return false;
				}

				object.m_object = std::make_shared<datafile_t>();

				if (object.m_object)
				{
					object_t child = { WIND::DATAFILE::OBJECT::TYPE_USER_DEFINED, 0, string_t(), nullptr };

					for (auto it = data.begin(); it != data.end(); ++it)
					{
						bool found = false;
						string_t type_string{};
						data_t node{ (*it) };

						child.m_type = WIND::DATAFILE::OBJECT::TYPE_USER_DEFINED;
						child.m_name = it.key();
						child.m_object.reset();

						node.m_root = data.m_node;

						if (child.m_name[0] == shortcut_prefix)
						{
							continue;
						}

						for (auto it = data.m_objects.get()->cbegin(); it != data.m_objects.get()->cend(); ++it)
						{
							if (it->m_name == child.m_name)
							{
								found = true;
							}
						}

						if (found)
						{
							continue;
						}

						if (!node.find_data("type", type_string))
						{
							return false;
						}

						child.m_type = object::get_type(type_string);

						if (child.m_type == WIND::DATAFILE::OBJECT::TYPE_UNDEFINED)
						{
							wind::error::push("Invalid \"type\" attribute", __FILE__, __LINE__, __FUNCTION__);
							return false;
						}

						object::parser_func_t func = object::get_info()[child.m_type].second;

						if (!func(node, child))
						{
							wind::error::push("Unregistered object type", __FILE__, __LINE__, __FUNCTION__);
							return false;
						}

						if (!child.m_object)
						{
							return false;
						}

						(*data.m_objects)[count] = child;

						++count;
						++child.m_index;
					}

					std::sort(data.m_objects->begin(), data.m_objects->end(), temp_data_compare);

					for (auto o : *(data.m_objects.get()))
					{
						((datafile_t*)object.m_object.get())->push_back(o.m_type, o.m_name, o.m_object);
					}
				}

				return (bool)object.m_object && (size == count);
			}
		}
	}
}