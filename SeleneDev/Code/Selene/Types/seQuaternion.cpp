#include "Selene/Types/seVector3.h"

#include <math.h>

Selene::Vector3::Vector3()
{
	m_X = 0.0f;
	m_Y = 0.0f;
	m_Z = 0.0f;
}

Selene::Vector3::Vector3(float val)
{
	m_X = val;
	m_Y = val;
	m_Z = val;
}

Selene::Vector3::Vector3(float x, float y, float z)
{
	m_X = x;
	m_Y = y;
	m_Z = z;
}

Selene::Vector3::Vector3(const Vector3& source)
{
	m_X = source.m_X;
	m_Y = source.m_Y;
	m_Z = source.m_Z;
}

Selene::Vector3::~Vector3()
{
}

void Selene::Vector3::Normalize()
{
	float fLength = GetLength();
	*this /= fLength;
}

Selene::Vector3 Selene::Vector3::GetNormalized()
{
	Vector3 result(*this);
	result.Normalize();
	return result;
}

float Selene::Vector3::GetLength()
{
	return sqrtf(GetLengthSq());
}

float Selene::Vector3::GetLengthSq()
{
	return m_X * m_X + m_Y * m_Y + m_Z * m_Z;
}

float Selene::Vector3::GetDist(const Vector3& target)
{
	return sqrtf(GetDistSq(target));
}

float Selene::Vector3::GetDistSq(const Vector3& target)
{
	return (target.m_X - m_X) * (target.m_X - m_X) + 
		   (target.m_Y - m_Y) * (target.m_Y - m_Y) + 
		   (target.m_Z - m_Z) * (target.m_Z - m_Z);
}

float Selene::Vector3::Dot(const Vector3& v)
{
	return m_X * v.m_X + m_Y * v.m_Y + m_Z * v.m_Z;
}

Selene::Vector3 Selene::Vector3::operator+() const
{
	return *this;
}

Selene::Vector3 Selene::Vector3::operator-() const
{
	Vector3 result(*this);
	result *= -1.0f;
	return result;
}

Selene::Vector3 Selene::Vector3::operator+(const Vector3& rhs) const
{
	Vector3 result(*this);
	result.m_X += rhs.m_X;
	result.m_Y += rhs.m_Y;
	result.m_Z += rhs.m_Z;
	return result;
}

Selene::Vector3 Selene::Vector3::operator-(const Vector3& rhs) const
{
	Vector3 result(*this);
	result.m_X -= rhs.m_X;
	result.m_Y -= rhs.m_Y;
	result.m_Z -= rhs.m_Z;
	return result;
}

Selene::Vector3& Selene::Vector3::operator+=(const Vector3& rhs)
{
	m_X += rhs.m_X;
	m_Y += rhs.m_Y;
	m_Z += rhs.m_Z;
	return *this;
}

Selene::Vector3& Selene::Vector3::operator-=(const Vector3& rhs)
{
	m_X -= rhs.m_X;
	m_Y -= rhs.m_Y;
	m_Z -= rhs.m_Z;
	return *this;
}

Selene::Vector3 Selene::Vector3::operator*(float val) const
{
	Vector3 result(*this);
	result.m_X *= val;
	result.m_Y *= val;
	result.m_Z *= val;
	return result;
}

Selene::Vector3 Selene::Vector3::operator/(float val) const
{
	Vector3 result(*this);
	result.m_X /= val;
	result.m_Y /= val;
	result.m_Z /= val;
	return result;
}

Selene::Vector3& Selene::Vector3::operator*=(float val)
{
	m_X *= val;
	m_Y *= val;
	m_Z *= val;
	return *this;
}

Selene::Vector3& Selene::Vector3::operator/=(float val)
{
	m_X /= val;
	m_Y /= val;
	m_Z /= val;
	return *this;
}
