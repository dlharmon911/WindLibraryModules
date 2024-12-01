export module wind:vector3d;

import <cstdint>;
import <array>;
import :base;
import :string;

namespace WIND
{
	namespace VECTOR3D
	{
		namespace INDEX
		{
			export constexpr size_t ELEMENT_X = 0;
			export constexpr size_t ELEMENT_Y = 1;
			export constexpr size_t ELEMENT_Z = 2;
			export constexpr size_t COUNT = 3;
		}
	}
}

namespace wind
{
	export class vector3d_t
	{
	public:
		vector3d_t(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f);
		explicit vector3d_t(const std::array<float, WIND::VECTOR3D::INDEX::COUNT>& rhs);
		vector3d_t(const vector3d_t& vector);
		~vector3d_t();
		
		auto operator+(const vector3d_t& rhs) const->vector3d_t;
		auto operator-(const vector3d_t& rhs) const->vector3d_t;
		auto operator*(const float factor) const->vector3d_t;
		auto operator/(const float factor) const->vector3d_t;
		
		auto operator-() const->vector3d_t;
		
		auto operator+=(const vector3d_t& rhs)->vector3d_t&;
		auto operator-=(const vector3d_t& rhs)->vector3d_t&;
		auto operator*=(const float factor)->vector3d_t&;
		auto operator/=(const float factor)->vector3d_t&;

		auto operator=(const vector3d_t& rhs)->vector3d_t&;
		
		auto operator==(const vector3d_t& rhs) const -> bool;
		auto operator!=(const vector3d_t& rhs) const -> bool;
		auto dot_product(const vector3d_t& rhs) const -> float;
		auto cross_product(const vector3d_t& rhs) const->vector3d_t;
		auto is_zero() const -> bool;
		auto get_length() const -> float;
		auto get_squared_length() const -> float;
		auto set_length(float length) -> void;
		auto normalize() const->vector3d_t;
		auto zero_out() -> void;
		auto angle_between(const vector3d_t& v) -> float;
		auto rotate_x(float angle) -> void;
		auto rotate_y(float angle) -> void;
		auto rotate_z(float angle) -> void;
		auto rotate(float angleX, float angleY, float angleZ) -> void;

		explicit operator const std::array<float, WIND::VECTOR3D::INDEX::COUNT>& () const;

		auto get_x() const -> float;
		auto get_y() const -> float;
		auto get_z() const -> float;
		auto get_element(size_t index) const -> float;
		auto set_x(float value) -> void;
		auto set_y(float value) -> void;
		auto set_z(float value) -> void;
		auto set_element(size_t index, float value) -> void;

	private:
		std::array<float, WIND::VECTOR3D::INDEX::COUNT> m_array{ 0.0f, 0.0f, 0.0f };
	};
}