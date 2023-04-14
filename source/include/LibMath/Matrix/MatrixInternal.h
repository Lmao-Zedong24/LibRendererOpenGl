#ifndef __LIBMATH__MATRIX_MATRIXINTERNAL_H__
#define __LIBMATH__MATRIX_MATRIXINTERNAL_H__
#include <exception>

namespace LibMath
{
	namespace Exceptions
	{
		class IncompatibleMatrix : public std::exception
		{
		public:
			IncompatibleMatrix() noexcept
				: exception("Incompatible matrix")
			{
			}
		};

		class NonSquareMatrix : public std::exception
		{
		public:
			NonSquareMatrix() noexcept
				: exception("Non-square matrix")
			{
			}
		};

		class NonInvertibleMatrix : public std::exception
		{
		public:
			NonInvertibleMatrix() noexcept
				: exception("Non-invertible matrix")
			{
			}
		};
	}

	class Matrix
	{
	public:
		using			length_t = int;

						Matrix(length_t rows, length_t columns);
						Matrix(length_t rows, length_t columns, float scalar);
						Matrix(Matrix const& other);
						Matrix(Matrix&& other) noexcept;
		virtual			~Matrix();

		Matrix&			operator=(Matrix const& other);
		Matrix&			operator=(Matrix&& other) noexcept;

		float			operator[](size_t index) const;
		float&			operator[](size_t index);

		Matrix&			operator+=(Matrix const& other);
		Matrix&			operator-=(Matrix const& other);
		Matrix&			operator*=(Matrix const& other);
		Matrix&			operator/=(Matrix const& other);

		Matrix&			operator+=(float scalar);
		Matrix&			operator-=(float scalar);
		Matrix&			operator*=(float scalar);
		Matrix&			operator/=(float scalar);

		Matrix			operator+(Matrix const& other) const;
		Matrix			operator-(Matrix const& other) const;
		Matrix			operator*(Matrix const& other) const;
		Matrix			operator/(Matrix const& other) const;

		Matrix			operator+(float scalar) const;
		Matrix			operator-(float scalar) const;
		Matrix			operator*(float scalar) const;
		Matrix			operator/(float scalar) const;

		Matrix			operator-() const;

		bool			operator==(const Matrix& other) const;
		bool			operator!=(const Matrix& other) const;
		bool			isIdentity() const;

		length_t		getRowCount() const;
		length_t		getColumnCount() const;
		length_t		getIndex(length_t row, length_t column) const;

		float			determinant() const;
		float			cofactor(length_t row, length_t column) const;

		Matrix			minor(length_t row, length_t column) const;
		Matrix			transposed() const;
		Matrix			coMatrix() const;
		Matrix			adjugate() const;
		Matrix			inverse() const;

	protected:
		float			determinant2x2() const;
		float			determinant3x3() const;

		length_t		m_rows;
		length_t		m_columns;
		float*			m_values;
	};
}

#endif // !__LIBMATH__MATRIX_MATRIXINTERNAL_H__