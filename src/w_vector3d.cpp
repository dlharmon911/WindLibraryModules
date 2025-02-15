module wind;

import <cstdint>;
import <cmath>;
import <limits>;
import :base;
import :vector3d;

namespace wind
{
	vector3d_t::vector3d_t(const float x, const float y, const float z) : m_array({ x, y, z })
	{
	}

	vector3d_t::vector3d_t(const std::array<float, WIND::VECTOR3D::INDEX::COUNT>& rhs) : m_array({ rhs[WIND::VECTOR3D::INDEX::ELEMENT_X], rhs[WIND::VECTOR3D::INDEX::ELEMENT_Y], rhs[WIND::VECTOR3D::INDEX::ELEMENT_Z] })
	{
	}

	vector3d_t::vector3d_t(const vector3d_t& vector) : m_array(vector.m_array)
	{
	}

	vector3d_t::~vector3d_t()
	{
	}

	auto vector3d_t::operator-() const -> vector3d_t
	{
		return vector3d_t(-this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X],
			-this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y],
			-this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z]);
	}

	auto vector3d_t::operator+=(const vector3d_t& rhs) -> vector3d_t&
	{
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] = this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] + rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_X];
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] = this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] + rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y];
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] = this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] + rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z];

		return *this;
	}

	auto vector3d_t::operator-=(const vector3d_t& rhs) -> vector3d_t&
	{
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] = this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] - rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_X];
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] = this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] - rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y];
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] = this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] - rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z];

		return *this;
	}

	auto vector3d_t::operator*=(const float factor) -> vector3d_t&
	{
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] = this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] * factor;
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] = this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] * factor;
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] = this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] * factor;

		return *this;
	}

	auto vector3d_t::operator/=(const float factor) -> vector3d_t&
	{
		return this->operator*=(1.0f / factor);
	}

	auto vector3d_t::operator=(const vector3d_t& rhs) -> vector3d_t&
	{
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] = rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_X];
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] = rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y];
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] = rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z];

		return *this;
	}

	auto vector3d_t::operator==(const vector3d_t& rhs) const -> bool
	{
		return (std::abs(this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] - rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_X]) <= std::numeric_limits<float>::epsilon() &&
			std::abs(this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] - rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y]) <= std::numeric_limits<float>::epsilon() &&
			std::abs(this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] - rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z]) <= std::numeric_limits<float>::epsilon());
	}

	auto vector3d_t::dot_product(const vector3d_t& rhs) const -> float
	{
		return (this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] * rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] +
			this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] * rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] +
			this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] * rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z]);
	}

	auto vector3d_t::cross_product(const vector3d_t& rhs) const -> vector3d_t
	{
		return vector3d_t((this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] * rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z]) - (this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] * rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y]),
			(this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] * rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_X]) - (this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] * rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z]),
			(this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] * rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y]) - (this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] * rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_X]));
	}

	auto vector3d_t::is_zero() const -> bool
	{
		return (std::abs(this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X]) <= std::numeric_limits<float>::epsilon() &&
			std::abs(this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y]) <= std::numeric_limits<float>::epsilon() &&
			std::abs(this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z]) <= std::numeric_limits<float>::epsilon());
	}

	auto vector3d_t::get_length() const -> float
	{
		return sqrt(this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] * this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] +
			this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] * this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] +
			this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] * this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z]);
	}

	auto vector3d_t::get_squared_length() const -> float
	{
		return (this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] * this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] +
			this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] * this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] +
			this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] * this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z]);
	}

	auto vector3d_t::set_length(float length) -> void
	{
		if (length <= std::numeric_limits<float>::epsilon())
		{
			this->zero_out();
		}
		else
		{
			float factor = (length / this->get_length());

			this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] = this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] * factor;
			this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] = this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] * factor;
			this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] = this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] * factor;
		}
	}

	auto vector3d_t::normalize() const -> vector3d_t
	{
		vector3d_t temp = *this;

		temp.set_length(0.0f);

		return temp;
	}

	auto vector3d_t::zero_out() -> void
	{
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] = 0.0f;
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] = 0.0f;
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] = 0.0f;
	}

	auto vector3d_t::angle_between(const vector3d_t& v) -> float
	{
		return (this->dot_product(v) / (this->get_length() * v.get_length()));
	}

	auto vector3d_t::rotate_x(float angle) -> void
	{
		float a = angle;
		float c = std::cos(a);
		float s = std::sin(a);
		float ty = c * this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] + s * this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z];

		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] = c * this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] - s * this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y];
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] = ty;
	}

	auto vector3d_t::rotate_y(float angle) -> void
	{
		float a = angle;
		float c = std::cos(a);
		float s = std::sin(a);
		float tx = c * this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] + s * this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z];

		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] = c * this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] - s * this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X];
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] = tx;
	}

	auto vector3d_t::rotate_z(float angle) -> void
	{
		float a = angle;
		float c = std::cos(a);
		float s = std::sin(a);
		float ty = c * this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] + s * this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X];
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] = c * this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] - s * this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y];
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] = ty;
	}

	auto vector3d_t::rotate(float angleX, float angleY, float angleZ) -> void
	{
		this->rotate_x(angleX);
		this->rotate_y(angleY);
		this->rotate_z(angleZ);
	}

	vector3d_t::operator const std::array<float, WIND::VECTOR3D::INDEX::COUNT>& () const
	{
		return this->m_array;
	}

	auto vector3d_t::get_x() const -> float
	{
		return this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X];
	}

	auto vector3d_t::get_y() const -> float
	{
		return this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y];
	}

	auto vector3d_t::get_z() const -> float
	{
		return this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z];
	}

	auto vector3d_t::get_element(size_t index) const -> float
	{
		ALLEGRO::ASSERT(index < WIND::VECTOR3D::INDEX::COUNT);
		return this->m_array[index];
	}

	auto vector3d_t::set_x(float value) -> void
	{
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] = value;
	}

	auto vector3d_t::set_y(float value) -> void
	{
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] = value;
	}

	auto vector3d_t::set_z(float value) -> void
	{
		this->m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] = value;
	}

	auto vector3d_t::set_element(size_t index, float value) -> void
	{
		ALLEGRO::ASSERT(index < WIND::VECTOR3D::INDEX::COUNT);
		this->m_array[index] = value;
	}

	auto operator+(const vector3d_t& lhs, const vector3d_t& rhs) -> vector3d_t
	{
		return vector3d_t(lhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] + rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_X],
			lhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] + rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y],
			lhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] + rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z]);
	}

	auto operator-(const vector3d_t& lhs, const vector3d_t& rhs) -> vector3d_t
	{
		return vector3d_t(lhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] - rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_X],
			lhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] - rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y],
			lhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] - rhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z]);
	}

	auto operator*(const vector3d_t& lhs, const float factor) -> vector3d_t
	{
		return vector3d_t(lhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_X] * factor,
			lhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Y] * factor,
			lhs.m_array[WIND::VECTOR3D::INDEX::ELEMENT_Z] * factor);
	}

	auto operator/(const vector3d_t& lhs, const float factor) -> vector3d_t
	{
		return lhs * (1.0f / factor);
	}
}
