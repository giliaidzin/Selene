#include "Selene/Types/seMatrix4.h"
#include "Selene/Types/seVector3.h"

#include <math.h>

Selene::Matrix4::Matrix4()
{
	m[0][0] = 1.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;
	//
	m[1][0] = 0.0f;
	m[1][1] = 1.0f;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;
	//
	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f;
	m[2][3] = 0.0f;
	//
	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

Selene::Matrix4::Matrix4(const Matrix4& source)
{
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			m[i][j] = source.m[i][j];
		}
	}
}

Selene::Matrix4::~Matrix4()
{
}

Selene::Matrix4 Selene::Matrix4::operator+() const
{
	return *this;
}

Selene::Matrix4 Selene::Matrix4::operator-() const
{
	Matrix4 result(*this);
	result *= -1.0f;
	return result;
}

Selene::Matrix4 Selene::Matrix4::operator+(const Matrix4& rhs) const
{
	Matrix4 result(*this);
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			result.m[i][j] += rhs.m[i][j];
		}
	}
	return result;
}

Selene::Matrix4 Selene::Matrix4::operator-(const Matrix4& rhs) const
{
	Matrix4 result(*this);
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			result.m[i][j] -= rhs.m[i][j];
		}
	}
	return result;
}

Selene::Matrix4& Selene::Matrix4::operator+=(const Matrix4& rhs)
{
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			m[i][j] += rhs.m[i][j];
		}
	}
	return *this;
}

Selene::Matrix4& Selene::Matrix4::operator-=(const Matrix4& rhs)
{
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			m[i][j] -= rhs.m[i][j];
		}
	}
	return *this;
}

Selene::Matrix4 Selene::Matrix4::operator*(float val) const
{
	Matrix4 result(*this);
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			result.m[i][j] *= val;
		}
	}
	return result;
}

Selene::Matrix4 Selene::Matrix4::operator/(float val) const
{
	Matrix4 result(*this);
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			result.m[i][j] /= val;
		}
	}
	return result;
}

Selene::Matrix4& Selene::Matrix4::operator*=(float val)
{
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			m[i][j] *= val;
		}
	}
	return *this;
}

Selene::Matrix4& Selene::Matrix4::operator/=(float val)
{
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			m[i][j] /= val;
		}
	}
	return *this;
}

Selene::Matrix4 Selene::Matrix4::operator*(const Matrix4& rhs) const
{
	Matrix4 result(*this);
	result.m[0][0] = m[0][0] * rhs.m[0][0] + m[0][1] * rhs.m[1][0] + m[0][2] * rhs.m[2][0] + m[0][3] * rhs.m[3][0];
	result.m[0][1] = m[0][0] * rhs.m[0][1] + m[0][1] * rhs.m[1][1] + m[0][2] * rhs.m[2][1] + m[0][3] * rhs.m[3][1];
	result.m[0][2] = m[0][0] * rhs.m[0][2] + m[0][1] * rhs.m[1][2] + m[0][2] * rhs.m[2][2] + m[0][3] * rhs.m[3][2];
	result.m[0][3] = m[0][0] * rhs.m[0][3] + m[0][1] * rhs.m[1][3] + m[0][2] * rhs.m[2][3] + m[0][3] * rhs.m[3][3];
	result.m[1][0] = m[1][0] * rhs.m[0][0] + m[1][1] * rhs.m[1][0] + m[1][2] * rhs.m[2][0] + m[1][3] * rhs.m[3][0];
	result.m[1][1] = m[1][0] * rhs.m[0][1] + m[1][1] * rhs.m[1][1] + m[1][2] * rhs.m[2][1] + m[1][3] * rhs.m[3][1];
	result.m[1][2] = m[1][0] * rhs.m[0][2] + m[1][1] * rhs.m[1][2] + m[1][2] * rhs.m[2][2] + m[1][3] * rhs.m[3][2];
	result.m[1][3] = m[1][0] * rhs.m[0][3] + m[1][1] * rhs.m[1][3] + m[1][2] * rhs.m[2][3] + m[1][3] * rhs.m[3][3];
	result.m[2][0] = m[2][0] * rhs.m[0][0] + m[2][1] * rhs.m[1][0] + m[2][2] * rhs.m[2][0] + m[2][3] * rhs.m[3][0];
	result.m[2][1] = m[2][0] * rhs.m[0][1] + m[2][1] * rhs.m[1][1] + m[2][2] * rhs.m[2][1] + m[2][3] * rhs.m[3][1];
	result.m[2][2] = m[2][0] * rhs.m[0][2] + m[2][1] * rhs.m[1][2] + m[2][2] * rhs.m[2][2] + m[2][3] * rhs.m[3][2];
	result.m[2][3] = m[2][0] * rhs.m[0][3] + m[2][1] * rhs.m[1][3] + m[2][2] * rhs.m[2][3] + m[2][3] * rhs.m[3][3];
	result.m[3][0] = m[3][0] * rhs.m[0][0] + m[3][1] * rhs.m[1][0] + m[3][2] * rhs.m[2][0] + m[3][3] * rhs.m[3][0];
	result.m[3][1] = m[3][0] * rhs.m[0][1] + m[3][1] * rhs.m[1][1] + m[3][2] * rhs.m[2][1] + m[3][3] * rhs.m[3][1];
	result.m[3][2] = m[3][0] * rhs.m[0][2] + m[3][1] * rhs.m[1][2] + m[3][2] * rhs.m[2][2] + m[3][3] * rhs.m[3][2];
	result.m[3][3] = m[3][0] * rhs.m[0][3] + m[3][1] * rhs.m[1][3] + m[3][2] * rhs.m[2][3] + m[3][3] * rhs.m[3][3];
	return result;
}

Selene::Matrix4& Selene::Matrix4::operator*=(const Matrix4& rhs)
{
	return *this;
}

Selene::Matrix4& Selene::Matrix4::Transpose()
{
	float temp = 0.0f;
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			temp = m[i][j];
			m[i][j] = m[j][i];
			m[j][i] = temp;
		}
	}
	return *this;
}

Selene::Matrix4& Selene::Matrix4::RotateOnX(float angle)
{
	float cosAngle = cosf(angle);
	float sinAngle = sinf(angle);

	m[0][0] = 1.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = cosAngle;
	m[1][2] = sinAngle;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = -sinAngle;
	m[2][2] = cosAngle;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;

	return *this;
}

Selene::Matrix4& Selene::Matrix4::RotateOnY(float angle)
{
	float cosAngle = cosf(angle);
	float sinAngle = sinf(angle);

	m[0][0] = cosAngle;
	m[0][1] = 0.0f;
	m[0][2] = -sinAngle;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = 1.0f;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = sinAngle;
	m[2][1] = 0.0f;
	m[2][2] = cosAngle;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;

	return *this;
}

Selene::Matrix4& Selene::Matrix4::RotateOnZ(float angle)
{
	float cosAngle = cosf(angle);
	float sinAngle = sinf(angle);

	m[0][0] = cosAngle;
	m[0][1] = -sinAngle;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = sinAngle;
	m[1][1] = cosAngle;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;

	return *this;
}

Selene::Matrix4& Selene::Matrix4::RotateOnAxis(float angle, const Vector3& axis)
{
	float cosAngle = cosf(angle);
	float sinAngle = sinf(angle);
	float t = 1.0f - cosAngle;

	m[0][0] = t * axis.m_X * axis.m_X + cosAngle;
	m[0][1] = t * axis.m_X * axis.m_Y + sinAngle * axis.m_Z;
	m[0][2] = t * axis.m_X * axis.m_Z - sinAngle * axis.m_Y;
	m[0][3] = 0.0f;

	m[1][0] = t * axis.m_X * axis.m_Y - sinAngle * axis.m_Z;
	m[1][1] = t * axis.m_Y * axis.m_Y + cosAngle;
	m[1][2] = t * axis.m_Y * axis.m_Z + sinAngle * axis.m_X;
	m[1][3] = 0.0f;

	m[2][0] = t * axis.m_X * axis.m_Z + sinAngle * axis.m_Y;
	m[2][1] = t * axis.m_Y * axis.m_Z - sinAngle * axis.m_X;
	m[2][2] = t * axis.m_Z * axis.m_Z + cosAngle;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;

	return *this;
}
