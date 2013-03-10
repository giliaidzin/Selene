#include "Selene/Types/seVector4.h"
#include "Selene/Types/seVector3.h"

#include <math.h>

Selene::Vector4::Vector4()
{
	m_X = 0.0f;
	m_Y = 0.0f;
	m_Z = 0.0f;
	m_W = 1.0f;
}

Selene::Vector4::Vector4(float val)
{
	m_X = val;
	m_Y = val;
	m_Z = val;
	m_W = 1.0f;
}

Selene::Vector4::Vector4(float x, float y, float z)
{
	m_X = x;
	m_Y = y;
	m_Z = z;
	m_W = 1.0f;
}

Selene::Vector4::Vector4(float x, float y, float z, float w)
{
	m_X = x;
	m_Y = y;
	m_Z = z;
	m_W = w;
}

Selene::Vector4::Vector4(const Vector3& source)
{
	m_X = source.m_X;
	m_Y = source.m_Y;
	m_Z = source.m_Z;
	m_W = 1.0f;
}

Selene::Vector4::Vector4(const Vector4& source)
{
	m_X = source.m_X;
	m_Y = source.m_Y;
	m_Z = source.m_Z;
	m_W = source.m_W;
}

Selene::Vector4::~Vector4()
{
}

void Selene::Vector4::Normalize()
{
	float fLength = GetLength();
	*this /= fLength;
}

Selene::Vector4 Selene::Vector4::GetNormalized()
{
	Vector4 result(*this);
	result.Normalize();
	return result;
}

float Selene::Vector4::GetLength()
{
	return sqrtf(GetLengthSq());
}

float Selene::Vector4::GetLengthSq()
{
	return m_X * m_X + m_Y * m_Y + m_Z * m_Z + m_W * m_W;
}

float Selene::Vector4::GetDist(const Vector4& target)
{
	return sqrtf(GetDistSq(target));
}

float Selene::Vector4::GetDistSq(const Vector4& target)
{
	return (target.m_X - m_X) * (target.m_X - m_X) + 
		   (target.m_Y - m_Y) * (target.m_Y - m_Y) + 
		   (target.m_Z - m_Z) * (target.m_Z - m_Z) + 
		   (target.m_W - m_W) * (target.m_W - m_W);
}

float Selene::Vector4::Dot(const Vector4& v)
{
	return m_X * v.m_X + m_Y * v.m_Y + m_Z * v.m_Z + m_W * v.m_W;
}

Selene::Vector4 Selene::Vector4::operator+() const
{
	return *this;
}

Selene::Vector4 Selene::Vector4::operator-() const
{
	Vector4 result(*this);
	result *= -1.0f;
	return result;
}

Selene::Vector4 Selene::Vector4::operator+(const Vector4& rhs) const
{
	Vector4 result(*this);
	result.m_X += rhs.m_X;
	result.m_Y += rhs.m_Y;
	result.m_Z += rhs.m_Z;
	result.m_W += rhs.m_W;
	return result;
}

Selene::Vector4 Selene::Vector4::operator-(const Vector4& rhs) const
{
	Vector4 result(*this);
	result.m_X -= rhs.m_X;
	result.m_Y -= rhs.m_Y;
	result.m_Z -= rhs.m_Z;
	result.m_W -= rhs.m_W;
	return result;
}

Selene::Vector4& Selene::Vector4::operator+=(const Vector4& rhs)
{
	m_X += rhs.m_X;
	m_Y += rhs.m_Y;
	m_Z += rhs.m_Z;
	m_W += rhs.m_W;
	return *this;
}

Selene::Vector4& Selene::Vector4::operator-=(const Vector4& rhs)
{
	m_X -= rhs.m_X;
	m_Y -= rhs.m_Y;
	m_Z -= rhs.m_Z;
	m_W -= rhs.m_W;
	return *this;
}

Selene::Vector4 Selene::Vector4::operator*(float val) const
{
	Vector4 result(*this);
	result.m_X *= val;
	result.m_Y *= val;
	result.m_Z *= val;
	result.m_W *= val;
	return result;
}

Selene::Vector4 Selene::Vector4::operator/(float val) const
{
	Vector4 result(*this);
	result.m_X /= val;
	result.m_Y /= val;
	result.m_Z /= val;
	result.m_W /= val;
	return result;
}

Selene::Vector4& Selene::Vector4::operator*=(float val)
{
	m_X *= val;
	m_Y *= val;
	m_Z *= val;
	m_W *= val;
	return *this;
}

Selene::Vector4& Selene::Vector4::operator/=(float val)
{
	m_X /= val;
	m_Y /= val;
	m_Z /= val;
	m_W /= val;
	return *this;
}
