#ifndef SE_VECTOR3_H
#define SE_VECTOR3_H

namespace Selene
{
	class Vector4;
	class Matrix4;

	class Vector3
	{
	public:
		Vector3();
		Vector3(float val);
		Vector3(float x, float y, float z);
		Vector3(const Vector3& source);
		Vector3(const Vector4& source);
		~Vector3();

		void Normalize();
		Vector3 GetNormalized();

		float GetLength();
		float GetLengthSq();
		float GetDist(const Vector3& target);
		float GetDistSq(const Vector3& target);
		float Dot(const Vector3& v);
		Vector3 Cross(const Vector3& v);

		Vector3 operator+() const;
		Vector3 operator-() const;
		Vector3 operator+(const Vector3& rhs) const;
		Vector3 operator-(const Vector3& rhs) const;
		Vector3& operator+=(const Vector3& rhs);
		Vector3& operator-=(const Vector3& rhs);
		Vector3 operator*(float val) const;
		Vector3 operator/(float val) const;
		Vector3& operator*=(float val);
		Vector3& operator/=(float val);

		Vector3 operator*(const Matrix4& rhs) const;
		Vector3& operator*=(const Matrix4& rhs);

	public:
		float m_X;
		float m_Y;
		float m_Z;
		float m_W;
	};

} // namespace Selene

#endif // SE_VECTOR3_H