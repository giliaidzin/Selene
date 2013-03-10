#include "Selene/Types/seVector2.h"

#include <math.h>

Selene::Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

Selene::Vector2::Vector2(float fVal)
{
	x = fVal;
	y = fVal;
}

Selene::Vector2::Vector2(float fX, float fY)
{
	x = fX;
	y = fY;
}

Selene::Vector2::Vector2(const Vector2& rvSource)
{
	x = rvSource.x;
	y = rvSource.y;
}

Selene::Vector2::~Vector2()
{
}

void Selene::Vector2::Normalize()
{
	float fLength = GetLength();
	*this /= fLength;
}

Selene::Vector2 Selene::Vector2::GetNormalized()
{
	Vector2 vRes(*this);
	vRes.Normalize();
	return vRes;
}

float Selene::Vector2::GetLength()
{
	return sqrtf(GetLengthSq());
}

float Selene::Vector2::GetLengthSq()
{
	return x * x + y * y;
}

float Selene::Vector2::GetDist(const Vector2& rvTarget)
{
	return sqrtf(GetDistSq(rvTarget));
}

float Selene::Vector2::GetDistSq(const Vector2& rvTarget)
{
	return (rvTarget.x - x) * (rvTarget.x - x) + 
		   (rvTarget.y - y) * (rvTarget.y - y);
}

float Selene::Vector2::Dot(const Vector2& rv)
{
	return x * rv.x + y * rv.y;
}

Selene::Vector2 Selene::Vector2::operator+() const
{
	return *this;
}

Selene::Vector2 Selene::Vector2::operator-() const
{
	Vector2 vRet(*this);
	vRet *= -1.0f;
	return vRet;
}

Selene::Vector2 Selene::Vector2::operator+(const Vector2& rv) const
{
	Vector2 vRet(*this);
	vRet.x += rv.x;
	vRet.y += rv.y;
	return vRet;
}

Selene::Vector2 Selene::Vector2::operator-(const Vector2& rv) const
{
	Vector2 vRet(*this);
	vRet.x -= rv.x;
	vRet.y -= rv.y;
	return vRet;
}

Selene::Vector2& Selene::Vector2::operator+=(const Vector2& rv)
{
	x += rv.x;
	y += rv.y;
	return *this;
}

Selene::Vector2& Selene::Vector2::operator-=(const Vector2& rv)
{
	x -= rv.x;
	y -= rv.y;
	return *this;
}

Selene::Vector2 Selene::Vector2::operator*(float fVal) const
{
	Vector2 vRet(*this);
	vRet.x *= fVal;
	vRet.y *= fVal;
	return vRet;
}

Selene::Vector2 Selene::Vector2::operator/(float fVal) const
{
	Vector2 vRet(*this);
	vRet.x /= fVal;
	vRet.y /= fVal;
	return vRet;
}

Selene::Vector2& Selene::Vector2::operator*=(float fVal)
{
	x *= fVal;
	y *= fVal;
	return *this;
}

Selene::Vector2& Selene::Vector2::operator/=(float fVal)
{
	x /= fVal;
	y /= fVal;
	return *this;
}

