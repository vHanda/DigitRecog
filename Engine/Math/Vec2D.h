#ifndef _Vec2D_
#define _Vec2D_

#include <cmath>
#include <iosfwd>

#define PI 3.14159265

class Vec2D
{
public:
	Vec2D() 						{ set( 0.00f, 0.00f);  	}
	Vec2D(float new_x, float new_y) { set(new_x, new_y); 	}
	explicit Vec2D(float value) 	{ set(value, value); 	}

	void set(float new_x, float new_y){ x() = new_x; y() = new_y; }

	float& x()			{return _c[0];}
	float& y()			{return _c[1];}
	float  x() const	{return _c[0];}
	float  y() const	{return _c[1];}

	void operator=(float value) { set(value, value); }

	void operator+=(const Vec2D& other){ set(x() + other.x(), y() + other.y());}
	void operator-=(const Vec2D& other){ set(x() - other.x(), y() - other.y());}
	void operator*=(float factor){ set(x() * factor, y() * factor);}
	void operator/=(float factor){ set(x() / factor, y() / factor);}

	void zero() { set(0.00, 0.00); }
	float lengthSq()	const	{return x()*x() + y()*y();		}
	float length()		const	{return std::sqrt(lengthSq()); 	}
	const Vec2D & normalize() 			{ operator/=(length()); return *this; }
	const Vec2D & invert()				{ x() = -x(); y() = -y();	return *this;}
 	void truncate(float value)
	{ if( lengthSq() > value*value ){ normalize(); operator*=(value);} }

	operator const float*() const {  return _c; }

	float dot(const Vec2D & rhs) const { return x()*rhs.x() + y()*rhs.y(); }
	float cross(const Vec2D & rhs) const { return x()*rhs.y() - y()*rhs.x(); }

	Vec2D perp()  const { return Vec2D( -y(), x() ); }
	float distance(const Vec2D & rhs) const
	{ float xSep = rhs.x() - x(); float ySep = rhs.y() - y();
		return sqrt( xSep*xSep + ySep*ySep ); }
	float distanceSq(const Vec2D & rhs) const
	{ float xSep = rhs.x() - x(); float ySep = rhs.y() - y();
		return xSep*xSep + ySep*ySep; }
	int sign(const Vec2D & rhs) const
	{ float dot = this->dot(rhs); if(dot > 0) return 1; if(dot < 0 ) return -1; return 1; }


private:
	float _c[2];
};

inline const Vec2D operator+(const Vec2D& one, const Vec2D& two)
{
	return Vec2D(one.x() + two.x(), one.y() + two.y());
}

inline const Vec2D operator-(const Vec2D& one, const Vec2D& two)
{
	return Vec2D(one.x() - two.x(), one.y() - two.y());
}

inline const Vec2D operator-(const Vec2D& one)
{
	return Vec2D(-one.x(), -one.y());
}

inline const Vec2D operator*(const Vec2D& one, float factor)
{
	return Vec2D(one.x() * factor, one.y() * factor);
}

inline const Vec2D operator*(float factor, const Vec2D& one)
{
	return Vec2D(one.x() * factor, one.y() * factor);
}

inline const Vec2D operator/(const Vec2D& one, float factor)
{
	return Vec2D(one.x() / factor, one.y() / factor);
}

//dotproduct

//inline float operator*(const Vec2D& one, const Vec2D& two){
//	return one.x() * two.x() + one.y() * two.y();
//}

inline bool operator==(const Vec2D& one, const Vec2D& two)
{
	return one.x() == two.x() and one.y() == two.y();
}

inline bool operator!=(const Vec2D& one, const Vec2D& two)
{
	return !(one == two);
}

inline Vec2D vec2DNormalize(const Vec2D & vec)
{
	return Vec2D(vec).normalize();
}
inline float vec2DDistance(const Vec2D & one, const Vec2D & two)
{
	return (two-one).length();
}

inline float vec2DDistanceSq(const Vec2D & one, const Vec2D & two)
{
	return (two-one).lengthSq();
}

#endif
