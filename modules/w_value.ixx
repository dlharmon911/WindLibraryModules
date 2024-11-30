export module wind:value;

import <cstdint>;
import :base;
import :string;

namespace wind
{
	export class value_t
	{
	public:
		value_t();
		value_t(const value_t& value);
		explicit value_t(bool value);
		explicit value_t(int32_t value);
		explicit value_t(uint32_t value);
		explicit value_t(int64_t value);
		explicit value_t(uint64_t value);
		explicit value_t(float value);
		explicit value_t(double value);
		explicit value_t(const char* value);
		explicit value_t(const string_t& value);
		~value_t();

		auto clear() -> void;

		auto operator = (const value_t& value)->value_t&;
		auto operator = (bool value)->value_t&;
		auto operator = (int32_t value)->value_t&;
		auto operator = (uint32_t value)->value_t&;
		auto operator = (int64_t value)->value_t&;
		auto operator = (uint64_t value)->value_t&;
		auto operator = (float value)->value_t&;
		auto operator = (double value)->value_t&;
		auto operator = (const char* value)->value_t&;
		auto operator = (const string_t& value)->value_t&;

		auto operator == (const value_t& value) const -> bool;
		auto operator != (const value_t& value) const -> bool;
		auto operator == (bool value) const -> bool;
		auto operator != (bool value) const -> bool;
		auto operator == (int32_t value) const -> bool;
		auto operator != (int32_t value) const -> bool;
		auto operator == (uint32_t value) const -> bool;
		auto operator != (uint32_t value) const -> bool;
		auto operator == (int64_t value) const -> bool;
		auto operator != (int64_t value) const -> bool;
		auto operator == (uint64_t value) const -> bool;
		auto operator != (uint64_t value) const -> bool;
		auto operator == (float value) const -> bool;
		auto operator != (float value) const -> bool;
		auto operator == (double value) const -> bool;
		auto operator != (double value) const -> bool;
		auto operator == (const char* value) const -> bool;
		auto operator != (const char* value) const -> bool;
		auto operator == (const string_t& value) const -> bool;
		auto operator != (const string_t& value) const -> bool;

		explicit operator bool() const;
		explicit operator int32_t() const;
		explicit operator uint32_t() const;
		explicit operator int64_t() const;
		explicit operator uint64_t() const;
		explicit operator float() const;
		explicit operator double() const;
		explicit operator const char* () const;
		explicit operator const string_t& () const;

	private:
		string_t m_value;
	};
}

export auto operator == (bool lhs, const wind::value_t& rhs) -> bool;
export auto operator != (bool lhs, const wind::value_t& rhs) -> bool;
export auto operator == (int32_t lhs, const wind::value_t& rhs) -> bool;
export auto operator != (int32_t lhs, const wind::value_t& rhs) -> bool;
export auto operator == (uint32_t lhs, const wind::value_t& rhs) -> bool;
export auto operator != (uint32_t lhs, const wind::value_t& rhs) -> bool;
export auto operator == (int64_t lhs, const wind::value_t& rhs) -> bool;
export auto operator != (int64_t lhs, const wind::value_t& rhs) -> bool;
export auto operator == (uint64_t lhs, const wind::value_t& rhs) -> bool;
export auto operator != (uint64_t lhs, const wind::value_t& rhs) -> bool;
export auto operator == (float lhs, const wind::value_t& rhs) -> bool;
export auto operator != (float lhs, const wind::value_t& rhs) -> bool;
export auto operator == (double lhs, const wind::value_t& rhs) -> bool;
export auto operator != (double lhs, const wind::value_t& rhs) -> bool;
export auto operator == (const char* lhs, const wind::value_t& rhs) -> bool;
export auto operator != (const char* lhs, const wind::value_t& rhs) -> bool;
export auto operator == (const wind::string_t& lhs, const wind::value_t& rhs) -> bool;
export auto operator != (const wind::string_t& lhs, const wind::value_t& rhs) -> bool;