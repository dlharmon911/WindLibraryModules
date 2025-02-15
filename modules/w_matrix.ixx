export module wind:matrix;

import <cstdint>;
import <array>;
import allegro;
import :base;
import :string;
import :array;

namespace wind
{
	export class matrix_t
	{
	public:
		matrix_t();
		matrix_t(size_t column, size_t row);
		matrix_t(const matrix_t& rhs);
		~matrix_t();
		auto operator=(const matrix_t& rhs)->matrix_t&;
		auto operator-() const->matrix_t;
		auto operator+=(const float factor)->matrix_t&;
		auto operator-=(const float factor)->matrix_t&;
		auto operator*=(const float factor)->matrix_t&;
		auto operator/=(const float factor)->matrix_t&;
		auto operator+=(const matrix_t& rhs)->matrix_t&;
		auto operator-=(const matrix_t& rhs)->matrix_t&;
		auto operator*=(const matrix_t& rhs)->matrix_t&;
		auto operator==(const matrix_t& rhs) const -> bool;
		auto get(size_t column, size_t row) const -> float;
		auto set(size_t column, size_t row, float value) -> void;
		auto zero_out() -> void;
		auto get_transpose() const->matrix_t;
		auto calculate_determinant() const -> float;
		auto rotate(const float xfactor = 0.0, const float yfactor = 0.0, const float zfactor = 0.0) -> matrix_t&;
		auto scale(const float xfactor = 1.0, const float yfactor = 1.0, const float zfactor = 1.0) -> matrix_t&;
		auto translate(const float xfactor = 1.0, const float yfactor = 1.0, const float zfactor = 1.0) -> matrix_t&;
		auto rotate(const float xfactor = 0.0, const float yfactor = 0.0, const float zfactor = 0.0) const->matrix_t;
		auto scale(const float xfactor = 1.0, const float yfactor = 1.0, const float zfactor = 1.0) const->matrix_t;
		auto translate(const float xfactor = 1.0, const float yfactor = 1.0, const float zfactor = 1.0) const->matrix_t;
		auto is_identity() const -> bool;
		auto is_square() const -> bool;

		friend auto operator + (const matrix_t& lhs, const float factor)->matrix_t;
		friend auto operator - (const matrix_t& lhs, const float factor)->matrix_t;
		friend auto operator * (const matrix_t& lhs, const float factor)->matrix_t;
		friend auto operator / (const matrix_t& lhs, const float factor)->matrix_t;
		friend auto operator + (const matrix_t& lhs, const matrix_t& rhs)->matrix_t;
		friend auto operator - (const matrix_t& lhs, const matrix_t& rhs)->matrix_t;
		friend auto operator * (const matrix_t& lhs, const matrix_t& rhs)->matrix_t;

	private:
		wind::array_t<float> m_array{};
		size_t m_row{ 0 };
		size_t m_column{ 0 };
	};
}
