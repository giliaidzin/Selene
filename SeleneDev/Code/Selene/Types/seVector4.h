#ifndef SE_VECTOR4_H
#define SE_VECTOR4_H

namespace Selene
{
	class Vector3;

	class Vector4
	{
	public:
		Vector4();
		Vector4(float val);
		Vector4(float x, float y, float z);
		Vector4(float x, float y, float z, float w);
		Vector4(const Vector3& source);
		Vector4(const Vector4& source);
		~Vector4();

		void Normalize();
		Vector4 GetNormalized();

		float GetLength();
		float GetLengthSq();
		float GetDist(const Vector4& target);
		float GetDistSq(const Vector4& target);
		float Dot(const Vector4& v);

		Vector4 operator+() const;
		Vector4 operator-() const;
		Vector4 operator+(const Vector4& rhs) const;
		Vector4 operator-(const Vector4& rhs) const;
		Vector4& operator+=(const Vector4& rhs);
		Vector4& operator-=(const Vector4& rhs);
		Vector4 operator*(float val) const;
		Vector4 operator/(float val) const;
		Vector4& operator*=(float val);
		Vector4& operator/=(float val);

	public:
		float m_X;
		float m_Y;
		float m_Z;
		float m_W;
	};

} // namespace Selene

#endif // SE_VECTOR4_H
