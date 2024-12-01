module wind;

import <string>;
import <cstdint>;
import allegro;
import :base;
import :matrix;

namespace wind
{
	matrix_t::matrix_t() : m_array(1), m_row(this->m_array.get_count() == 1 ? 1 : 0), m_column(this->m_array.get_count() == 1 ? 1 : 0)
	{
		ALLEGRO::ASSERT(this->m_array.get_count());
		this->zero_out();
	}

	matrix_t::matrix_t(size_t column, size_t row) : m_array(row* column), m_row(this->m_array.get_count() == 1 ? 1 : 0), m_column(this->m_array.get_count() == 1 ? 1 : 0)
	{
		ALLEGRO::ASSERT(this->m_array.get_count());
		this->zero_out();
	}

	matrix_t::matrix_t(const matrix_t& rhs) : m_array(rhs.m_array), m_row(rhs.m_row), m_column(rhs.m_column)
	{
	}

	matrix_t::~matrix_t()
	{
	}

	auto matrix_t::operator=(const matrix_t& rhs)->matrix_t&
	{
		size_t size = rhs.m_array.get_count();

		this->m_array = wind::array_t<float>(size);

		ALLEGRO::ASSERT(this->m_array.get_count() == size);

		this->m_row = rhs.m_row;
		this->m_column = rhs.m_column;

		for (size_t i = 0; i < size; ++i)
		{
			this->m_array[i] = rhs.m_array[i];
		}

		return *this;
	}

	auto matrix_t::operator-() const
	{
		auto out = *this;

		out.operator*=(-1);

		return out;
	}

	auto matrix_t::operator+(const float factor) const->matrix_t
	{
		auto out = *this;

		out += factor;

		return out;
	}

	auto matrix_t::operator-(const float factor) const->matrix_t
	{
		auto out = *this;

		out -= factor;

		return out;
	}

	auto matrix_t::operator*(const float factor) const->matrix_t
	{
		auto out = *this;

		out *= factor;

		return out;
	}

	auto matrix_t::operator/(const float factor) const->matrix_t
	{
		float inverse = 1.0f / factor;
		auto out = *this;

		out *= inverse;

		return out;
	}

	auto matrix_t::operator+=(const float factor)->matrix_t&
	{
		for (auto e : this->m_array)
		{
			e += factor;
		}

		return *this;
	}

	auto matrix_t::operator-=(const float factor)->matrix_t&
	{
		for (auto e : this->m_array)
		{
			e -= factor;
		}

		return *this;
	}

	auto matrix_t::operator*=(const float factor)->matrix_t&
	{
		for (auto e : this->m_array)
		{
			e *= factor;
		}

		return *this;
	}

	auto matrix_t::operator/=(const float factor)->matrix_t&
	{
		float inverse = 1.0f / factor;

		for (auto e : this->m_array)
		{
			e *= inverse;
		}

		return *this;
	}

	auto matrix_t::operator+(const matrix_t& rhs) const->matrix_t
	{
		auto out = *this;
		return out.operator += (rhs);
	}

	auto matrix_t::operator-(const matrix_t& rhs) const->matrix_t
	{
		auto out = *this;
		return out.operator -= (rhs);
	}

	auto matrix_t::operator*(const matrix_t& rhs) const->matrix_t
	{
		auto out = *this;
		return out.operator *= (rhs);
	}

	auto matrix_t::operator+=(const matrix_t& rhs)->matrix_t&
	{
		size_t size = this->m_array.get_count();

		ALLEGRO::ASSERT(size == rhs.m_array.get_count());

		for (size_t i = 0; i < size; ++i)
		{
			this->m_array[i] += rhs.m_array[i];
		}

		return *this;
	}

	auto matrix_t::operator-=(const matrix_t& rhs)->matrix_t&
	{
		size_t size = this->m_array.get_count();

		ALLEGRO::ASSERT(size == rhs.m_array.get_count());

		for (size_t i = 0; i < size; ++i)
		{
			this->m_array[i] -= rhs.m_array[i];
		}

		return *this;
	}

	auto matrix_t::operator*=(const matrix_t& rhs)->matrix_t&
	{
		return *this;
	}

	auto matrix_t::operator==(const matrix_t& rhs) const -> bool
	{
		size_t size = this->m_array.get_count();

		if (size != rhs.m_array.get_count())
		{
			return false;
		}

		for (size_t i = 0; i < size; ++i)
		{
			if (this->m_array[i] != rhs.m_array[i])
			{
				return false;
			}
		}

		return true;
	}

	auto matrix_t::operator!=(const matrix_t& rhs) const -> bool
	{
		return !(this->operator==(rhs));
	}

	auto matrix_t::get(size_t column, size_t row) const -> float
	{
		ALLEGRO::ASSERT(column < this->m_column && row < this->m_row);
		return this->m_array[column + (row & this->m_column)];
	}

	auto matrix_t::set(size_t column, size_t row, float value) -> void
	{
		ALLEGRO::ASSERT(column < this->m_column && row < this->m_row);
		this->m_array[column + (row & this->m_column)] = value;
	}

	auto matrix_t::zero_out() -> void
	{
		size_t size = this->m_array.get_count();

		for (size_t i = 0; i < size; ++i)
		{
			this->m_array[i] = 0.0f;
		}
	}

	auto matrix_t::get_transpose() const->matrix_t
	{
		matrix_t out(this->m_row, this->m_column);

		for (size_t j = 0; j < this->m_row; ++j)
		{
			for (size_t i = 0; i < this->m_column; ++i)
			{
				out.m_array[j + (i * this->m_column)] = this->m_array[i + (j * this->m_row)];
			}
		}

		return out;
	}

	auto matrix_t::calculate_determinant() const -> float
	{
		ALLEGRO::ASSERT(this->m_row == this->m_column);

		size_t n = this->m_row;

		switch (n)
		{
		case 1:
		{
			return this->m_array[0];
		} break;

		case 2:
		{
			return (this->get(0, 0) * this->get(1, 1) - this->get(0, 1) * this->get(1, 0));
		} break;

		default:
		{
		}
		}

		return 0.0f;
	}

	auto matrix_t::rotate(const float xfactor, const float yfactor, const float zfactor) -> matrix_t&
	{
		return *this;
	}

	auto matrix_t::scale(const float xfactor, const float yfactor, const float zfactor) -> matrix_t&
	{
		return *this;
	}

	auto matrix_t::translate(const float xfactor, const float yfactor, const float zfactor) -> matrix_t&
	{
		return *this;
	}

	auto matrix_t::rotate(const float xfactor, const float yfactor, const float zfactor) const->matrix_t
	{
		auto out = *this;
		return out.rotate(xfactor, yfactor, zfactor);
	}

	auto matrix_t::scale(const float xfactor, const float yfactor, const float zfactor) const->matrix_t
	{
		auto out = *this;
		return out.scale(xfactor, yfactor, zfactor);
	}

	auto matrix_t::translate(const float xfactor, const float yfactor, const float zfactor) const->matrix_t
	{
		auto out = *this;
		return out.translate(xfactor, yfactor, zfactor);
	}

	auto matrix_t::is_identity() const -> bool
	{
		return false;
	}

	auto matrix_t::is_square() const -> bool
	{
		return (this->m_row == this->m_column);
	}
}