#ifndef SE_MATRIX4_H
#define SE_MATRIX4_H

namespace Selene
{
	class Vector3;

	class Matrix4
	{
	public:
		Matrix4();
		Matrix4(const Matrix4& source);
		~Matrix4();


		Matrix4 operator+() const;
		Matrix4 operator-() const;
		Matrix4 operator+(const Matrix4& rhs) const;
		Matrix4 operator-(const Matrix4& rhs) const;
		Matrix4& operator+=(const Matrix4& rhs);
		Matrix4& operator-=(const Matrix4& rhs);
		Matrix4 operator*(float val) const;
		Matrix4 operator/(float val) const;
		Matrix4& operator*=(float val);
		Matrix4& operator/=(float val);

		Matrix4 operator*(const Matrix4& rhs) const;
		Matrix4& operator*=(const Matrix4& rhs);

		Matrix4& Transpose();
		Matrix4& RotateOnX(float angle);
		Matrix4& RotateOnY(float angle);
		Matrix4& RotateOnZ(float angle);
		Matrix4& RotateOnAxis(float angle, const Vector3& axis);

	public:
		float m[4][4];
	};

} // namespace Selene

#endif // SE_MATRIX4_H
