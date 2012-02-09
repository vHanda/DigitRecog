#include "Vec2D.h"
#include <SDL/SDL.h>
#include <iostream>

inline bool ct_Rect_Rect(const Vec2D & tl1, const Vec2D & br1,
						 const Vec2D & tl2, const Vec2D & br2)
{
	if(br1.x() < tl2.x()) return false;
	if(br2.x() < tl1.x()) return false;
	if(br1.y() < tl2.y()) return false;
	if(br2.y() < tl1.y()) return false;
	return true;
}

inline bool ct_Rect_Rect(const SDL_Rect & r1, const SDL_Rect & r2)
{
	return ct_Rect_Rect( Vec2D(r1.x, r1.y), Vec2D(r1.x+r1.w, r1.y+r1.h),
						 Vec2D(r2.x, r2.y), Vec2D(r2.x+r2.w, r2.y+r2.h));
}

inline bool ct_Circle_Circle(const Vec2D & c1, float r1,
							 const Vec2D & c2, float r2)
{
	const float distSq = vec2DDistanceSq(c1,c2);
	const float totalRadiusSq = (r1+r2)*(r1+r2);
	if(distSq < totalRadiusSq)
		return true;
	return false;
}

inline bool ct_Circle_Point(const Vec2D & c1, float r, const Vec2D & point)
{
	const float distSq = vec2DDistanceSq(c1,point);
	if(distSq <= r*r)
		return true;
	return false;
}

inline bool ct_Point_Circle(const Vec2D & point, const Vec2D & c1, float r)
{
	return ct_Circle_Point(c1,r,point);
}

inline bool ct_Rect_Point(const Vec2D & tl, const Vec2D & br, const Vec2D & p)
{
	if( p.x() < tl.x() ) return 0;
	if( p.x() > br.x() ) return 0;
	if( p.y() < tl.y() ) return 0;
	if( p.y() > br.y() ) return 0;
	return true;
}

inline bool ct_Rect_Point(const SDL_Rect & r, const Vec2D & p)
{
    return ct_Rect_Point( Vec2D(r.x,r.y), Vec2D(r.x+r.w, r.y+r.h), p);
}

inline bool ct_Point_Rect(const Vec2D & p, const Vec2D & tl, const Vec2D & br)
{
	return ct_Rect_Point(tl,br,p);
}

inline SDL_Rect make_rect(const Vec2D & c, float radius)
{
	SDL_Rect r;
	r.x = c.x() - radius;
	r.y = c.y() - radius;
	r.w = 2*radius;
	r.h = 2*radius;
	return r;
}

inline SDL_Rect make_rect(const Vec2D & tl, const Vec2D & br)
{
	SDL_Rect r;
	r.x = tl.x();
	r.y = tl.y();
	r.w = r.x - br.x();
	r.h = r.y - br.y();
	return r;
}
