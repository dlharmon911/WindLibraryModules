export module wind:json.base;

import :base;
import :string;
import :json.constants;

namespace wind
{
	class json_t;

	namespace json
	{
		export using type_t = WIND::JSON::TYPE;
		export using key_t = string_t;
		export using pair_t = std::pair<key_t, json_t>;
		export using object_t = std::map<key_t, json_t>;
		export using array_t = std::vector<json_t>;
	}

	export class json_t
	{
	public:
		json_t() : m_type(WIND::JSON::TYPE::NULL), m_data(al::ustr_new(WIND::JSON::STRING::NULL_.c_str())) {}
		explicit json_t(bool value) : m_type(WIND::JSON::TYPE::BOOLEAN), m_data(al::ustr_new(value ? WIND::JSON::STRING::TRUE_.c_str() : WIND::JSON::STRING::FALSE_.c_str())) {}
		explicit json_t(double value) : m_type(WIND::JSON::TYPE::NUMBER), m_data(al::ustr_new(std::to_string(value).c_str())) {}
		explicit json_t(const string_t& value) : m_type(WIND::JSON::TYPE::STRING), m_data(al::ustr_new(value.c_str())) {}
		explicit json_t(const json::object_t& value) : m_type(WIND::JSON::TYPE::OBJECT), m_data(std::make_shared<json::object_t>(value)) {}
		explicit json_t(const json::array_t& value) : m_type(WIND::JSON::TYPE::ARRAY), m_data(std::make_shared<json::array_t>(value)) {}
		json_t(const json_t& json) = default;
		~json_t() = default;
		auto operator = (const json_t& json) -> json_t & = default;

		auto is_defined() const -> bool
		{
			return static_cast<bool>(this->m_data);
		}

		auto clear() -> void
		{
			this->m_type = WIND::JSON::TYPE::NULL;
			this->m_data.reset();
		}

		auto get_type() const -> json::type_t
		{
			return this->m_type;
		}

		auto is_null() const -> bool
		{
			return (this->m_type == WIND::JSON::TYPE::NULL);
		}

		auto is_boolean() const -> bool
		{
			return (this->m_type == WIND::JSON::TYPE::BOOLEAN);
		}

		auto is_number() const -> bool
		{
			return (this->m_type == WIND::JSON::TYPE::NUMBER);
		}

		auto is_string() const -> bool
		{
			return (this->m_type == WIND::JSON::TYPE::STRING);
		}

		auto is_object() const -> bool
		{
			return (this->m_type == WIND::JSON::TYPE::OBJECT);
		}

		auto set_as_boolean(bool val) -> bool
		{
			this->m_type = WIND::JSON::TYPE::BOOLEAN;
			this->m_data = al::ustr_new(val ? WIND::JSON::STRING::TRUE_.c_str() : WIND::JSON::STRING::FALSE_.c_str());
			return static_cast<bool>(this->m_data);
		}

		auto set_as_number(double val) -> bool
		{
			this->m_type = WIND::JSON::TYPE::NUMBER;
			this->m_data = al::ustr_new(std::to_string(val).c_str());
			return static_cast<bool>(this->m_data);
		}

		auto set_as_string(const string_t& val) -> bool
		{
			this->m_type = WIND::JSON::TYPE::STRING;
			this->m_data = al::ustr_new(val.c_str());
			return static_cast<bool>(this->m_data);
		}

		auto set_as_object(const json::object_t& val) -> bool
		{
			this->m_type = WIND::JSON::TYPE::OBJECT;
			this->m_data = std::make_shared<json::object_t>(val);
			return static_cast<bool>(this->m_data);
		}

		auto set_as_array(const json::array_t& val) -> bool
		{
			this->m_type = WIND::JSON::TYPE::ARRAY;
			this->m_data = std::make_shared<json::array_t>(val);
			return static_cast<bool>(this->m_data);
		}

		auto get_as_boolean() const -> bool
		{
			if (this->m_type == WIND::JSON::TYPE::BOOLEAN && this->m_data)
			{
				ALLEGRO::USTRING ptr = std::static_pointer_cast<ALLEGRO::INTERNAL::USTRING_DATA>(this->m_data);

				if (!ptr || al::ustr_size(ptr) == 0)
				{
					throw std::runtime_error("JSON number string is empty");
				}

				return (std::strcmp(al::c_str(ptr), WIND::JSON::STRING::TRUE_.c_str()) == 0);
			}
			throw std::runtime_error("JSON value is not a boolean");
		}

		auto get_as_number() const -> double
		{
			if (this->m_type == WIND::JSON::TYPE::NUMBER && this->m_data)
			{
				ALLEGRO::USTRING ptr = std::static_pointer_cast<ALLEGRO::INTERNAL::USTRING_DATA>(this->m_data);

				if (!ptr || al::ustr_size(ptr) == 0)
				{
					throw std::runtime_error("JSON number string is empty");
				}

				return std::stod(al::c_str(ptr));
			}
			throw std::runtime_error("JSON value is not a number");
		}

		template <typename T> auto get_as_number() const -> T
		{
			return static_cast<T>(this->get_as_number());
		}

		auto get_as_string() const -> wind::string_t
		{
			if (this->m_type == WIND::JSON::TYPE::STRING && this->m_data)
			{
				ALLEGRO::USTRING ptr = std::static_pointer_cast<ALLEGRO::INTERNAL::USTRING_DATA>(this->m_data);

				if (!ptr || al::ustr_size(ptr) == 0)
				{
					throw std::runtime_error("JSON number string is empty");
				}

				return wind::string_t(al::c_str(ptr));
			}

			throw std::runtime_error("JSON value is not a string");
		}

		auto get_as_ustring() -> ALLEGRO::USTRING
		{
			if (this->m_type == WIND::JSON::TYPE::STRING && this->m_data)
			{
				ALLEGRO::USTRING ptr = std::static_pointer_cast<ALLEGRO::INTERNAL::USTRING_DATA>(this->m_data);

				if (!ptr || al::ustr_size(ptr) == 0)
				{
					throw std::runtime_error("JSON number string is empty");
				}

				return ptr;
			}

			throw std::runtime_error("JSON value is not a string");
		}

		auto get_as_ustring() const -> const ALLEGRO::USTRING
		{
			if (this->m_type == WIND::JSON::TYPE::STRING && this->m_data)
			{
				ALLEGRO::USTRING ptr = std::static_pointer_cast<ALLEGRO::INTERNAL::USTRING_DATA>(this->m_data);

				if (!ptr || al::ustr_size(ptr) == 0)
				{
					throw std::runtime_error("JSON number string is empty");
				}

				return ptr;
			}

			throw std::runtime_error("JSON value is not a string");
		}

		auto get_as_object() -> json::object_t&
		{
			if (this->m_type == WIND::JSON::TYPE::OBJECT && this->m_data)
			{
				return *std::static_pointer_cast<json::object_t>(this->m_data);
			}
			throw std::runtime_error("JSON value is not an object");
		}

		auto get_as_object() const -> const json::object_t&
		{
			if (this->m_type == WIND::JSON::TYPE::OBJECT && this->m_data)
			{
				return *std::static_pointer_cast<json::object_t>(this->m_data);
			}
			throw std::runtime_error("JSON value is not an object");
		}

		auto get_as_array() -> json::array_t&
		{
			if (this->m_type == WIND::JSON::TYPE::ARRAY && this->m_data)
			{
				return *std::static_pointer_cast<json::array_t>(this->m_data);
			}
			throw std::runtime_error("JSON value is not an array");
		}

		auto get_as_array() const -> const json::array_t&
		{
			if (this->m_type == WIND::JSON::TYPE::ARRAY && this->m_data)
			{
				return *std::static_pointer_cast<json::array_t>(this->m_data);
			}

			throw std::runtime_error("JSON value is not an array");
		}

		explicit operator bool() const
		{
			return this->get_as_boolean();
		}

		explicit operator double() const
		{
			return this->get_as_number();
		}

		explicit operator string_t()
		{
			return this->get_as_string();
		}

		explicit operator const string_t() const
		{
			return this->get_as_string();
		}

		explicit operator json::object_t& ()
		{
			return this->get_as_object();
		}

		explicit operator const json::object_t& () const
		{
			return this->get_as_object();
		}

		explicit operator json::array_t& ()
		{
			return this->get_as_array();
		}

		explicit operator const json::array_t& () const
		{
			return this->get_as_array();
		}

	private:
		std::shared_ptr<void> m_data{};
		WIND::JSON::TYPE m_type{ WIND::JSON::TYPE::NULL };
	};
}
