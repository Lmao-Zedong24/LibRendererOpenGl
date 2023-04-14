#include "LibMath/Matrix.h"

#include <stdexcept>

#include "LibMath/Arithmetic.h"
#include "LibMath/Trigonometry.h"
#include "LibMath/Angle/Radian.h"
#include "LibMath/Vector/Vector3.h"

using namespace LibMath::Exceptions;

namespace LibMath
{
	Matrix2x2::Matrix2x2() : Matrix(2, 2)
	{
	}

	Matrix2x2::Matrix2x2(const float scalar) : Matrix(2, 2, scalar)
	{
	}

	Matrix2x2::Matrix2x2(const Matrix& other) : Matrix(other)
	{
		if (other.getRowCount() != 2 || other.getColumnCount() != 2)
			throw IncompatibleMatrix();
	}

	Matrix2x2::Matrix2x2(Matrix&& other) : Matrix(other)
	{
		if (other.getRowCount() != 2 || other.getColumnCount() != 2)
			throw IncompatibleMatrix();
	}

	Matrix2x3::Matrix2x3() : Matrix(2, 3)
	{
	}

	Matrix2x3::Matrix2x3(const float scalar) : Matrix(2, 3, scalar)
	{
	}

	Matrix2x3::Matrix2x3(const Matrix& other) : Matrix(other)
	{
		if (other.getRowCount() != 2 || other.getColumnCount() != 3)
			throw IncompatibleMatrix();
	}

	Matrix2x3::Matrix2x3(Matrix&& other) : Matrix(other)
	{
		if (other.getRowCount() != 2 || other.getColumnCount() != 3)
			throw IncompatibleMatrix();
	}

	Matrix2x4::Matrix2x4() : Matrix(2, 4)
	{
	}

	Matrix2x4::Matrix2x4(const float scalar) : Matrix(2, 4, scalar)
	{
	}

	Matrix2x4::Matrix2x4(const Matrix& other) : Matrix(other)
	{
		if (other.getRowCount() != 2 || other.getColumnCount() != 4)
			throw IncompatibleMatrix();
	}

	Matrix2x4::Matrix2x4(Matrix&& other) : Matrix(other)
	{
		if (other.getRowCount() != 2 || other.getColumnCount() != 4)
			throw IncompatibleMatrix();
	}

	Matrix3x2::Matrix3x2() : Matrix(3, 2)
	{
	}

	Matrix3x2::Matrix3x2(const float scalar) : Matrix(3, 2, scalar)
	{
	}

	Matrix3x2::Matrix3x2(const Matrix& other) : Matrix(other)
	{
		if (other.getRowCount() != 3 || other.getColumnCount() != 2)
			throw IncompatibleMatrix();
	}

	Matrix3x2::Matrix3x2(Matrix&& other) : Matrix(other)
	{
		if (other.getRowCount() != 3 || other.getColumnCount() != 2)
			throw IncompatibleMatrix();
	}

	Matrix3x3::Matrix3x3() : Matrix(3, 3)
	{
	}

	Matrix3x3::Matrix3x3(const float scalar) : Matrix(3, 3, scalar)
	{
	}

	Matrix3x3::Matrix3x3(const Matrix& other) : Matrix(other)
	{
		if (other.getRowCount() != 3 || other.getColumnCount() != 3)
			throw IncompatibleMatrix();
	}

	Matrix3x3::Matrix3x3(Matrix&& other) : Matrix(other)
	{
		if (other.getRowCount() != 3 || other.getColumnCount() != 3)
			throw IncompatibleMatrix();
	}

	Matrix3x4::Matrix3x4() : Matrix(3, 4)
	{
	}

	Matrix3x4::Matrix3x4(const float scalar) : Matrix(3, 4, scalar)
	{
	}

	Matrix3x4::Matrix3x4(const Matrix& other) : Matrix(other)
	{
		if (other.getRowCount() != 3 || other.getColumnCount() != 4)
			throw IncompatibleMatrix();
	}

	Matrix3x4::Matrix3x4(Matrix&& other) : Matrix(other)
	{
		if (other.getRowCount() != 3 || other.getColumnCount() != 4)
			throw IncompatibleMatrix();
	}

	Matrix4x2::Matrix4x2() : Matrix(4, 2)
	{
	}

	Matrix4x2::Matrix4x2(const float scalar) : Matrix(4, 2, scalar)
	{
	}

	Matrix4x2::Matrix4x2(const Matrix& other) : Matrix(other)
	{
		if (other.getRowCount() != 4 || other.getColumnCount() != 2)
			throw IncompatibleMatrix();
	}

	Matrix4x2::Matrix4x2(Matrix&& other) : Matrix(other)
	{
		if (other.getRowCount() != 4 || other.getColumnCount() != 2)
			throw IncompatibleMatrix();
	}

	Matrix4x3::Matrix4x3() : Matrix(4, 3)
	{
	}

	Matrix4x3::Matrix4x3(const float scalar) : Matrix(4, 3, scalar)
	{
	}

	Matrix4x3::Matrix4x3(const Matrix& other) : Matrix(other)
	{
		if (other.getRowCount() != 4 || other.getColumnCount() != 3)
			throw IncompatibleMatrix();
	}

	Matrix4x3::Matrix4x3(Matrix&& other) : Matrix(other)
	{
		if (other.getRowCount() != 4 || other.getColumnCount() != 3)
			throw IncompatibleMatrix();
	}

	Matrix4x4::Matrix4x4() : Matrix(4, 4)
	{
	}

	Matrix4x4::Matrix4x4(const float scalar) : Matrix(4, 4, scalar)
	{
	}

	Matrix4x4::Matrix4x4(const Matrix& other) : Matrix(other)
	{
		if (other.getRowCount() != 4 || other.getColumnCount() != 4)
			throw IncompatibleMatrix();
	}

	Matrix4x4::Matrix4x4(Matrix&& other) : Matrix(other)
	{
		if (other.getRowCount() != 4 || other.getColumnCount() != 4)
			throw IncompatibleMatrix();
	}

	Matrix4x4 Matrix4x4::translation(const float x, const float y, const float z)
	{
		Matrix4x4 translationMatrix(1.f);

		translationMatrix[translationMatrix.getIndex(0, 3)] = x;
		translationMatrix[translationMatrix.getIndex(1, 3)] = y;
		translationMatrix[translationMatrix.getIndex(2, 3)] = z;

		return translationMatrix;
	}

	Matrix4x4 Matrix4x4::scaling(const float x, const float y, const float z)
	{
		Matrix4x4 scalingMatrix;

		scalingMatrix[scalingMatrix.getIndex(0, 0)] = x;
		scalingMatrix[scalingMatrix.getIndex(1, 1)] = y;
		scalingMatrix[scalingMatrix.getIndex(2, 2)] = z;
		scalingMatrix[scalingMatrix.getIndex(3, 3)] = 1.f;

		return scalingMatrix;
	}

	Matrix4x4 Matrix4x4::rotation(const Radian& angle, const Vector3& axis)
	{
		const Vector3 dir = axis.normalized();
		const float cos = LibMath::cos(angle);
		const float sin = LibMath::sin(angle);

		Matrix4x4 mat;

		mat[mat.getIndex(0, 0)] = cos + dir.m_x * dir.m_x * (1.f - cos);
		mat[mat.getIndex(0, 1)] = dir.m_x * dir.m_y * (1 - cos) - dir.m_z * sin;
		mat[mat.getIndex(0, 2)] = dir.m_x * dir.m_z * (1 - cos) + dir.m_y * sin;
		mat[mat.getIndex(0, 3)] = 0.f;

		mat[mat.getIndex(1, 0)] = dir.m_y * dir.m_x * (1 - cos) + dir.m_z * sin;
		mat[mat.getIndex(1, 1)] = cos + dir.m_y * dir.m_y * (1.f - cos);
		mat[mat.getIndex(1, 2)] = dir.m_y * dir.m_z * (1 - cos) - dir.m_x * sin;
		mat[mat.getIndex(1, 3)] = 0.f;

		mat[mat.getIndex(2, 0)] = dir.m_z * dir.m_x * (1 - cos) - dir.m_y * sin;
		mat[mat.getIndex(2, 1)] = dir.m_z * dir.m_y * (1 - cos) + dir.m_x * sin;
		mat[mat.getIndex(2, 2)] = cos + dir.m_z * dir.m_z * (1.f - cos);
		mat[mat.getIndex(2, 3)] = 0.f;

		mat[mat.getIndex(3, 0)] = 0.f;
		mat[mat.getIndex(3, 1)] = 0.f;
		mat[mat.getIndex(3, 2)] = 0.f;
		mat[mat.getIndex(3, 3)] = 1.f;

		return mat;
	}

	Matrix4x4 Matrix4x4::rotation(const Radian& yaw, const Radian& pitch, const Radian& roll)
	{
		const float cosYaw = cos(yaw);
		const float sinYaw = sin(yaw);

		const float cosPitch = cos(pitch);
		const float sinPitch = sin(pitch);

		const float cosRoll = cos(roll);
		const float sinRoll = sin(roll);

		Matrix4x4 rotationMat;

		rotationMat[rotationMat.getIndex(0, 0)] = cosYaw * cosRoll + sinYaw * sinPitch * sinRoll;
		rotationMat[rotationMat.getIndex(0, 1)] = -cosYaw * sinRoll + sinYaw * sinPitch * cosRoll;
		rotationMat[rotationMat.getIndex(0, 2)] = sinYaw * cosPitch;
		rotationMat[rotationMat.getIndex(0, 3)] = 0.f;

		rotationMat[rotationMat.getIndex(1, 0)] = sinRoll * cosPitch;
		rotationMat[rotationMat.getIndex(1, 1)] = cosRoll * cosPitch;
		rotationMat[rotationMat.getIndex(1, 2)] = -sinPitch;
		rotationMat[rotationMat.getIndex(1, 3)] = 0.f;

		rotationMat[rotationMat.getIndex(2, 0)] = -sinYaw * cosRoll + cosYaw * sinPitch * sinRoll;
		rotationMat[rotationMat.getIndex(2, 1)] = sinRoll * sinYaw + cosYaw * sinPitch * cosRoll;
		rotationMat[rotationMat.getIndex(2, 2)] = cosYaw * cosPitch;
		rotationMat[rotationMat.getIndex(2, 3)] = 0.f;

		rotationMat[rotationMat.getIndex(3, 0)] = 0.f;
		rotationMat[rotationMat.getIndex(3, 1)] = 0.f;
		rotationMat[rotationMat.getIndex(3, 2)] = 0.f;
		rotationMat[rotationMat.getIndex(3, 3)] = 1.f;

		return rotationMat;
	}

	Matrix4x4 Matrix4x4::rotationEuler(const Radian& xAngle, const Radian& yAngle, const Radian& zAngle)
	{
		return rotation(zAngle, xAngle, yAngle);
	}

	Matrix4x4 Matrix4x4::orthographicProjection(const float left, const float right,
		const float bottom, const float top, const float near, const float far)
	{
		Matrix4x4 mat;

		mat[mat.getIndex(0, 0)] = 2.f / (right - left);
		mat[mat.getIndex(0, 3)] = (right + left) / (left - right);

		mat[mat.getIndex(1, 1)] = 2.f / (top - bottom);
		mat[mat.getIndex(1, 3)] = (top + bottom) / (bottom - top);

		mat[mat.getIndex(2, 2)] = 2.f / (near - far);
		mat[mat.getIndex(2, 3)] = (far + near) / (near - far);

		mat[mat.getIndex(3, 3)] = 1.f;

		return mat;
	}

	Matrix4x4 Matrix4x4::perspectiveProjection(const Radian& fovY, const float aspect,
		const float near, const float far)
	{
		const float tanHalfFovY = tan(fovY * .5f);

		Matrix4x4 mat;

		mat[mat.getIndex(0, 0)] = 1.f / (aspect * tanHalfFovY);
		mat[mat.getIndex(1, 1)] = 1.f / tanHalfFovY;
		mat[mat.getIndex(2, 2)] = (far + near) / (near - far);
		mat[mat.getIndex(2, 3)] = (2.f * far * near) / (near - far);
		mat[mat.getIndex(3, 2)] = -1.f;

		return mat;
	}

	Matrix::Matrix(const length_t rows, const length_t columns)
	{
		if (rows == 0 || columns == 0)
			throw std::invalid_argument("Invalid matrix size");

		m_rows = rows;
		m_columns = columns;

		const size_t size = static_cast<size_t>(m_rows) * m_columns;

		m_values = new float[size]();

		// Builds a matrix filled with zeros
		for (size_t i = 0; i < size; i++)
			m_values[i] = 0;
	}

	Matrix::Matrix(const length_t rows, const length_t columns, const float scalar)
	{
		if (rows == 0 || columns == 0)
			throw std::invalid_argument("Invalid matrix size");

		m_rows = rows;
		m_columns = columns;

		const size_t size = static_cast<size_t>(m_rows) * m_columns;

		m_values = new float[size]();

		// Builds a diagonal matrix with the given scalar
		for (length_t row = 0; row < m_rows; row++)
			for (length_t col = 0; col < m_columns; col++)
				m_values[getIndex(row, col)] = row == col ? scalar : 0;
	}

	Matrix::length_t Matrix::getIndex(const length_t row, const length_t column) const
	{
		if (row < 0 || row >= m_rows || column < 0 || column >= m_columns)
			throw std::out_of_range("Index out of range");

		return row * m_columns + column;
	}

	Matrix::~Matrix()
	{
		delete[] m_values;
	}

	Matrix::Matrix(const Matrix& other)
	{
		const size_t size = static_cast<size_t>(other.m_rows) * other.m_columns;

		m_values = new float[size]();

		for (size_t i = 0; i < size; i++)
			m_values[i] = other[i];

		m_columns = other.m_columns;
		m_rows = other.m_rows;
	}

	Matrix::Matrix(Matrix&& other) noexcept
	{
		m_columns = other.m_columns;
		m_rows = other.m_rows;
		m_values = other.m_values;

		other.m_columns = other.m_rows = 0;
		other.m_values = nullptr;
	}

	Matrix& Matrix::operator=(const Matrix& other)
	{
		if (this == &other)
			return *this;

		delete[] m_values;

		const length_t size = other.m_columns * other.m_rows;

		m_values = new float[size]();

		for (length_t i = 0; i < size; i++)
			m_values[i] = other[i];

		m_columns = other.m_columns;
		m_rows = other.m_rows;

		return *this;
	}

	Matrix& Matrix::operator=(Matrix&& other) noexcept
	{
		if (this == &other)
			return *this;

		delete[] m_values;

		m_columns = other.m_columns;
		m_rows = other.m_rows;
		m_values = other.m_values;

		other.m_columns = other.m_rows = 0;
		other.m_values = nullptr;

		return *this;
	}

	float Matrix::operator[](const size_t index) const
	{
		const size_t size = static_cast<size_t>(m_rows) * m_columns;

		if (index < 0 || index >= size)
			throw std::out_of_range("Index out of range");

		return m_values[index];
	}

	float& Matrix::operator[](const size_t index)
	{
		const size_t size = static_cast<size_t>(m_rows) * m_columns;

		if (index < 0 || index >= size)
			throw std::out_of_range("Index out of range");

		return m_values[index];
	}

	Matrix& Matrix::operator+=(const Matrix& other)
	{
		if (other.m_columns != m_columns || other.m_rows != m_rows)
			throw IncompatibleMatrix();

		const size_t size = static_cast<size_t>(m_rows) * m_columns;

		for (size_t i = 0; i < size; i++)
			m_values[i] += other[i];

		return *this;
	}

	Matrix& Matrix::operator-=(const Matrix& other)
	{
		if (other.m_columns != m_columns || other.m_rows != m_rows)
			throw IncompatibleMatrix();

		const size_t size = static_cast<size_t>(m_rows) * m_columns;

		for (size_t i = 0; i < size; i++)
			m_values[i] -= other[i];

		return *this;
	}

	Matrix& Matrix::operator*=(const Matrix& other)
	{
		return (*this = *this * other);
	}

	Matrix& Matrix::operator/=(const Matrix& other)
	{
		return (*this = *this / other);
	}

	Matrix& Matrix::operator+=(const float scalar)
	{
		const size_t size = static_cast<size_t>(m_rows) * m_columns;

		for (size_t i = 0; i < size; i++)
			m_values[i] += scalar;

		return *this;
	}

	Matrix& Matrix::operator-=(const float scalar)
	{
		const size_t size = static_cast<size_t>(m_rows) * m_columns;

		for (size_t i = 0; i < size; i++)
			m_values[i] -= scalar;

		return *this;
	}

	Matrix& Matrix::operator*=(const float scalar)
	{
		const size_t size = static_cast<size_t>(m_rows) * m_columns;

		for (size_t i = 0; i < size; i++)
			m_values[i] *= scalar;

		return *this;
	}

	Matrix& Matrix::operator/=(const float scalar)
	{
		const size_t size = static_cast<size_t>(m_rows) * m_columns;

		for (size_t i = 0; i < size; i++)
			m_values[i] /= scalar;

		return *this;
	}

	Matrix Matrix::operator+(const Matrix& other) const
	{
		Matrix mat = *this;
		return mat += other;
	}

	Matrix Matrix::operator-(const Matrix& other) const
	{
		Matrix mat = *this;
		return mat -= other;
	}

	Matrix Matrix::operator*(const Matrix& other) const
	{
		if (other.m_rows != m_columns)
			throw IncompatibleMatrix();

		Matrix result(m_rows, other.m_columns);

		for (length_t otherCol = 0; otherCol < other.m_columns; otherCol++)
		{
			for (length_t row = 0; row < m_rows; row++)
			{
				float scalar = 0;

				for (length_t col = 0; col < m_columns; col++)
				{
					const length_t curIndex = getIndex(row, col);
					const length_t otherIndex = other.getIndex(col, otherCol);

					scalar += m_values[curIndex] * other[otherIndex];
				}

				const length_t resultIndex = result.getIndex(row, otherCol);
				result[resultIndex] = scalar;
			}
		}

		return result;
	}

	Matrix Matrix::operator/(const Matrix& other) const
	{
		return *this * other.inverse();
	}

	Matrix Matrix::operator+(const float scalar) const
	{
		Matrix mat = *this;
		return mat += scalar;
	}

	Matrix Matrix::operator-(const float scalar) const
	{
		Matrix mat = *this;
		return mat -= scalar;
	}

	Matrix Matrix::operator*(const float scalar) const
	{
		Matrix mat = *this;
		return mat *= scalar;
	}

	Matrix Matrix::operator/(const float scalar) const
	{
		Matrix mat = *this;
		return mat /= scalar;
	}

	Matrix Matrix::operator-() const
	{
		return *this * -1;
	}

	bool Matrix::operator==(const Matrix& other) const
	{
		if (other.m_rows != m_rows || other.m_columns != m_columns)
			return false;

		const size_t size = static_cast<size_t>(m_rows) * m_columns;

		for (size_t i = 0; i < size; i++)
			if (!floatEquals(m_values[i], other[i]))
				return false;

		return true;
	}

	bool Matrix::operator!=(const Matrix& other) const
	{
		return !(*this == other);
	}

	bool Matrix::isIdentity() const
	{
		if (m_rows != m_columns)
			return false;

		return *this == Matrix(m_rows, m_columns, 1.f);
	}

	Matrix::length_t Matrix::getRowCount() const
	{
		return m_rows;
	}

	Matrix::length_t Matrix::getColumnCount() const
	{
		return m_columns;
	}

	float Matrix::cofactor(const length_t row, const length_t column) const
	{
		if (m_rows != m_columns)
			throw NonSquareMatrix();

		if (m_rows == 1)
			return m_values[0];

		// The multiplier is (-1)^(i+j) so 1 when i + j is pair and -1 otherwise
		const float multiplier = (row + column) % 2 == 0 ? 1.f : -1.f;

		return multiplier * minor(row, column).determinant();
	}

	Matrix Matrix::minor(const length_t row, const length_t column) const
	{
		Matrix minor(m_rows - 1, m_columns - 1);
		length_t minorLine = 0;

		for (length_t i = 0; i < m_rows; i++)
		{
			if (i == row)
				continue;

			length_t minorCol = 0;

			for (length_t j = 0; j < m_columns; j++)
			{
				if (j == column)
					continue;

				minor[minor.getIndex(minorLine, minorCol++)] = m_values[getIndex(i, j)];
			}

			minorLine++;
		}

		return minor;
	}

	float Matrix::determinant2x2() const
	{
		// 0 1
		// 2 3
		return (*this)[0] * (*this)[3] - (*this)[1] * (*this)[2];
	}

	float Matrix::determinant3x3() const
	{
		// 0 1 2
		// 3 4 5
		// 6 7 8
		const float positive = (*this)[0] * (*this)[4] * (*this)[8] +
			(*this)[1] * (*this)[5] * (*this)[6] +
			(*this)[2] * (*this)[3] * (*this)[7];

		const float negative = (*this)[2] * (*this)[4] * (*this)[6] +
			(*this)[1] * (*this)[3] * (*this)[8] +
			(*this)[0] * (*this)[5] * (*this)[7];

		return positive - negative;
	}

	float Matrix::determinant() const
	{
		if (m_rows != m_columns)
			throw NonSquareMatrix();

		if (m_rows == 1)
			return m_values[0];

		if (m_rows == 2)
			return determinant2x2();

		if (m_rows == 3)
			return determinant3x3();

		float determinant = 0;

		for (length_t col = 0; col < m_columns; col++)
			determinant += m_values[col] * cofactor(0, col);

		return determinant;
	}

	Matrix Matrix::transposed() const
	{
		if (m_rows != m_columns)
			throw NonSquareMatrix();

		Matrix transposed(m_columns, m_rows);

		for (length_t i = 0; i < m_rows; i++)
			for (length_t j = 0; j < m_columns; j++)
				transposed[transposed.getIndex(j, i)] = m_values[getIndex(i, j)];

		return transposed;
	}

	Matrix Matrix::coMatrix() const
	{
		if (m_rows != m_columns)
			throw NonSquareMatrix();

		Matrix coMatrix(m_rows, m_columns);

		for (length_t row = 0; row < m_rows; row++)
			for (length_t col = 0; col < m_columns; col++)
				coMatrix[getIndex(row, col)] = cofactor(row, col);

		return coMatrix;
	}

	Matrix Matrix::adjugate() const
	{
		return coMatrix().transposed();
	}

	Matrix Matrix::inverse() const
	{
		if (m_rows != m_columns)
			throw NonSquareMatrix();

		const float det = determinant();

		if (det == 0.f)
			throw NonInvertibleMatrix();

		return adjugate() / det;
	}
}
