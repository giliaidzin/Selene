#ifndef SE_COLOR_H
#define SE_COLOR_H

namespace Selene
{
	class Color
	{
	public:
		Color();
		Color(float val);
		Color(float r, float g, float b);
		Color(float r, float g, float b, float a);
		Color(const Color& rhs);
		~Color();

		Color operator+() const;
		Color operator-() const;
		Color operator+(const Color& rhs) const;
		Color operator-(const Color& rhs) const;
		Color& operator+=(const Color& rhs);
		Color& operator-=(const Color& rhs);
		Color operator*(float val) const;
		Color operator/(float val) const;
		Color& operator*=(float val);
		Color& operator/=(float val);

	public:
		float m_R;
		float m_G;
		float m_B;
		float m_A;
	};

} // namespace Selene

#endif // SE_COLOR_H
