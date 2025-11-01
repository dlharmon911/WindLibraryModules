export module wind:uuid.base;

import :base;
import :string;
import :uuid.constants;

namespace wind
{
	export class uuid_t
	{
	public:
		uuid_t() = default;
		explicit uuid_t(const string_t& id) : m_id(id) {}
		~uuid_t() = default;
		uuid_t(const uuid_t&) = default;
		uuid_t(uuid_t&&) = default;
		uuid_t& operator=(const uuid_t&) = default;
		uuid_t& operator=(uuid_t&&) = default;

		auto swap(uuid_t& other) noexcept -> void
		{
			this->m_id.swap(other.m_id);
		}

		auto c_str() const noexcept -> const char*
		{
			return this->m_id.c_str();
		}

		explicit operator const std::string& () const
		{
			return this->m_id;
		}

		explicit operator bool() const noexcept
		{
			return !this->is_nil();
		}

		static auto nil() -> uuid_t
		{
			return uuid_t{ WIND::UUID::NIL_STRING };
		}

		auto is_nil() const -> bool
		{
			return this->m_id == WIND::UUID::NIL_STRING;
		}

		auto clear() -> void
		{
			this->m_id = WIND::UUID::NIL_STRING;
		}

		auto id() const -> const string_t&
		{
			return this->m_id;
		}

		auto regenerate() -> void
		{
			this->m_id = uuid_t::generate_uuid();
		}

		auto operator==(std::nullptr_t) const noexcept -> bool
		{
			return this->is_nil();
		}

		auto operator == (const uuid_t& other) const -> bool
		{
			return this->m_id == other.m_id;
		}

		auto operator <=> (const uuid_t& other) const -> std::strong_ordering
		{
			return this->m_id <=> other.m_id;
		}

		auto to_string() const -> string_t
		{
			return this->m_id;
		}

		auto from_string(const string_t& str) -> bool
		{
			if (uuid_t::is_valid(str))
			{
				this->m_id = str;
				return true;
			}

			if (uuid_t::is_valid_with_dashes(str))
			{
				*this = uuid_t::parse_and_strip_dashes(str);
				return true;
			}

			return false;
		}

		friend auto operator == (const string_t& lhs, const uuid_t& rhs) -> bool
		{
			return lhs == rhs.m_id;
		}

		friend auto operator == (const uuid_t& lhs, const string_t& rhs) -> bool
		{
			return lhs.m_id == rhs;
		}

		friend auto operator <=> (const string_t& lhs, const uuid_t& rhs) -> std::strong_ordering
		{
			return lhs <=> rhs.m_id;
		}

		friend auto operator <=> (const uuid_t& lhs, const string_t& rhs) -> std::strong_ordering
		{
			return lhs.m_id <=> rhs;
		}

		friend auto operator << (std::ostream& os, const uuid_t& uuid) -> std::ostream&
		{
			os << uuid.m_id;
			return os;
		}

		friend auto operator >> (std::istream& is, uuid_t& uuid) -> std::istream&
		{
			is >> uuid.m_id;
			return is;
		}

	private:
		static auto generate_uuid() -> std::string
		{
			std::random_device rd{};
			std::mt19937 gen{ rd() };
			std::uniform_int_distribution<uint32_t> dis{ 0, 0xFFFFFFFF };
			std::array<uint32_t, 4> data{ dis(gen), dis(gen), dis(gen), dis(gen) };
			std::ostringstream oss{};

			oss << std::hex << std::setfill('0')
				<< std::setw(8) << data[0] << '-'
				<< std::setw(4) << ((data[1] >> 16) & 0xFFFF) << '-'
				<< std::setw(4) << (data[1] & 0xFFFF) << '-'
				<< std::setw(4) << ((data[2] >> 16) & 0xFFFF) << '-'
				<< std::setw(4) << (data[2] & 0xFFFF)
				<< std::setw(8) << data[3];

			return oss.str();
		}

		static auto is_valid_with_dashes(const string_t& str) -> bool
		{
			// Simple regex or length/character check
			return str.size() == 36 && str.find_first_not_of("0123456789abcdefABCDEF-") == std::string::npos;
		}

		static auto is_valid(const string_t& str) -> bool
		{
			// Simple regex or length/character check
			return str.size() == WIND::UUID::STRING_LENGTH && str.find_first_not_of("0123456789abcdefABCDEF") == std::string::npos;
		}

		static auto parse_and_strip_dashes(const string_t& str) -> uuid_t
		{
			string_t result{};

			if (!uuid_t::is_valid_with_dashes(str))
			{
				return uuid_t::nil();
			}

			result.reserve(WIND::UUID::STRING_LENGTH);

			for (char ch : str)
			{
				if (ch != '-')
				{
					result += ch;
				}
			}

			if (result.size() != WIND::UUID::STRING_LENGTH)
			{
				return uuid_t::nil();
			}

			return uuid_t{ result };
		}

		string_t m_id{ uuid_t::generate_uuid() };
	};

	export const uuid_t nil_uuid{ WIND::UUID::NIL_STRING };
}

namespace WIND::UUID
{
	export const wind::uuid_t NIL{ WIND::UUID::NIL_STRING };
}

namespace std
{
	export template<> struct hash<wind::uuid_t>
	{
		auto operator()(const wind::uuid_t& uuid) const noexcept -> std::size_t
		{
			return std::hash<std::string>{}(uuid.id());
		}
	};
}
