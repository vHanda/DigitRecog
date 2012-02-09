#ifndef _TRANSFORMATION_
#define _TRANSFORMATION_

#include "Matrix.h"

inline Vec2D PointToWorldSpace(	const Vec2D & point,
								const Vec2D & agent_heading,
								const Vec2D & agent_side,
								const Vec2D & agent_pos )
{
	Vec2D transPoint(point);
	Matrix transMatrix;
	transMatrix.rotate(agent_heading, agent_side);
	transMatrix.translate(agent_pos.x(), agent_pos.y());
	
	transMatrix.transformVec2D( transPoint );
	return transPoint;
}

inline Vec2D VectorToWorldSpace(const Vec2D & point,
								const Vec2D & agent_heading,
								const Vec2D & agent_side,
								const Vec2D & agent_pos )
{
	Vec2D transVec(point);
	Matrix transMatrix;
	transMatrix.rotate(agent_heading, agent_side);
	
	transMatrix.transformVec2D( transVec );
	return transVec;
}

inline Vec2D PointToLocalSpace( const Vec2D & point,
								const Vec2D & agent_heading,
								const Vec2D & agent_side,
								const Vec2D & agent_pos )
{
	Vec2D transPoint(point);
	
	Matrix matTransform;
	float tx = -agent_pos.dot(agent_heading);
	float ty = -agent_pos.dot(agent_side);
	
	matTransform._11(agent_heading.x()); matTransform._12(agent_side.x());
	matTransform._21(agent_heading.y()); matTransform._22(agent_side.y());
	matTransform._31(tx);           matTransform._32(ty);
	
	matTransform.transformVec2D( transPoint );
	return transPoint;
}

inline Vec2D VectorToLocalSpace(const Vec2D & point,
								const Vec2D & agent_heading,
								const Vec2D & agent_side,
								const Vec2D & agent_pos )
{
	Vec2D transVec(point);
	
	Matrix matTransform;
	
	matTransform._11(agent_heading.x()); matTransform._12(agent_side.x());
	matTransform._21(agent_heading.y()); matTransform._22(agent_side.y());
	
	matTransform.transformVec2D( transVec );
	return transVec;
}


#endif
