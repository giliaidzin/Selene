#ifndef SE_VECTOR2_H
#define SE_VECTOR2_H

namespace Selene
{
	class Vector2
	{
	public:
		Vector2();
		Vector2(float fVal);
		Vector2(float fX, float fY);
		Vector2(const Vector2& rvSource);
		~Vector2();

		void Normalize();
		Vector2 GetNormalized();

		float GetLength();
		float GetLengthSq();
		float GetDist(const Vector2& rvTarget);
		float GetDistSq(const Vector2& rvTarget);
		float Dot(const Vector2& rv);

		Vector2 operator+() const;
		Vector2 operator-() const;
		Vector2 operator+(const Vector2& rv) const;
		Vector2 operator-(const Vector2& rv) const;
		Vector2& operator+=(const Vector2& rv);
		Vector2& operator-=(const Vector2& rv);
		Vector2 operator*(float fVal) const;
		Vector2 operator/(float fVal) const;
		Vector2& operator*=(float fVal);
		Vector2& operator/=(float fVal);

	public:
		float x;
		float y;
	};

} // namespace Selene

#endif // SE_VECTOR2_H
