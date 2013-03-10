#include "Selene/Types/seColor.h"

#include <math.h>

Selene::Color::Color()
:m_R(0.0f)
,m_G(0.0f)
,m_B(0.0f)
,m_A(0.0f)
{
}

Selene::Color::Color(float val)
:m_R(val)
,m_G(val)
,m_B(val)
,m_A(1.0f)
{
}

Selene::Color::Color(float r, float g, float b)
:m_R(r)
,m_G(g)
,m_B(b)
,m_A(1.0f)
{
}
Selene::Color::Color(float r, float g, float b, float a)
:m_R(r)
,m_G(g)
,m_B(b)
,m_A(a)
{
}

Selene::Color::Color(const Color& rhs)
:m_R(rhs.m_R)
,m_G(rhs.m_G)
,m_B(rhs.m_B)
,m_A(rhs.m_A)
{
}

Selene::Color::~Color()
{
}

Selene::Color Selene::Color::operator+() const
{
	return *this;
}

Selene::Color Selene::Color::operator-() const
{
	Color result(*this);
	result *= -1.0f;
	return result;
}

Selene::Color Selene::Color::operator+(const Color& rhs) const
{
	Color result(*this);
	result.m_R += rhs.m_R;
	result.m_G += rhs.m_G;
	result.m_B += rhs.m_B;
	result.m_A += rhs.m_A;
	return result;
}

Selene::Color Selene::Color::operator-(const Color& rhs) const
{
	Color result(*this);
	result.m_R -= rhs.m_R;
	result.m_G -= rhs.m_G;
	result.m_B -= rhs.m_B;
	result.m_A -= rhs.m_A;
	return result;
}

Selene::Color& Selene::Color::operator+=(const Color& rhs)
{
	m_R += rhs.m_R;
	m_G += rhs.m_G;
	m_B += rhs.m_B;
	m_A += rhs.m_A;
	return *this;
}

Selene::Color& Selene::Color::operator-=(const Color& rhs)
{
	m_R -= rhs.m_R;
	m_G -= rhs.m_G;
	m_B -= rhs.m_B;
	m_A -= rhs.m_A;
	return *this;
}

Selene::Color Selene::Color::operator*(float val) const
{
	Color result(*this);
	result.m_R *= val;
	result.m_G *= val;
	result.m_B *= val;
	result.m_A *= val;
	return result;
}

Selene::Color Selene::Color::operator/(float val) const
{
	Color result(*this);
	result.m_R /= val;
	result.m_G /= val;
	result.m_B /= val;
	result.m_A /= val;
	return result;
}

Selene::Color& Selene::Color::operator*=(float val)
{
	m_R *= val;
	m_G *= val;
	m_B *= val;
	m_A *= val;
	return *this;
}

Selene::Color& Selene::Color::operator/=(float val)
{
	m_R /= val;
	m_G /= val;
	m_B /= val;
	m_A /= val;
	return *this;
}
