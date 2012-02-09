#ifndef _MATRIX_
#define _MATRIX_

#include <math.h>
#include <vector>
#include "Vec2D.h"

class Matrix
{
private:

	float m_11, m_12, m_13;
    float m_21, m_22, m_23;
    float m_31, m_32, m_33;

  	//multiplies with mIn
  	inline void  matrixMultiply(Matrix &mIn);


public:

	Matrix()
	{
		//initialize the matrix to an identity matrix
		identity();
	}

	//create an identity matrix
	inline void identity();

	//create a transformation matrix
	inline void translate(float x, float y);

	//create a scale matrix
	inline void scale(float xScale, float yScale);

	//create a rotation matrix
	inline void  rotate(float rotation);

	//create a rotation matrix from a fwd and side 2D vector
	inline void  rotate(const Vec2D &fwd, const Vec2D &side);

	//applys a transformation matrix to a std::vector of points
	inline void transformVec2Ds(std::vector<Vec2D> &vPoints);

	//applys a transformation matrix to a point
	inline void transformVec2D(Vec2D &vPoint);

	//accessors to the matrix elements
	void _11(float val){m_11 = val;}
	void _12(float val){m_12 = val;}
	void _13(float val){m_13 = val;}

	void _21(float val){m_21 = val;}
	void _22(float val){m_22 = val;}
	void _23(float val){m_23 = val;}

	void _31(float val){m_31 = val;}
	void _32(float val){m_32 = val;}
	void _33(float val){m_33 = val;}

};



//multiply two matrices together
inline void Matrix::matrixMultiply(Matrix &mIn)
{
  Matrix mat_temp;

  //first row
  mat_temp.m_11 = (m_11 * mIn.m_11) + (m_12 * mIn.m_21) + (m_13 * mIn.m_31);
  mat_temp.m_12 = (m_11 * mIn.m_12) + (m_12 * mIn.m_22) + (m_13 * mIn.m_32);
  mat_temp.m_13 = (m_11 * mIn.m_13) + (m_12 * mIn.m_23) + (m_13 * mIn.m_33);

  //second
  mat_temp.m_21 = (m_21 * mIn.m_11) + (m_22 * mIn.m_21) + (m_23 * mIn.m_31);
  mat_temp.m_22 = (m_21 * mIn.m_12) + (m_22 * mIn.m_22) + (m_23 * mIn.m_32);
  mat_temp.m_23 = (m_21 * mIn.m_13) + (m_22 * mIn.m_23) + (m_23 * mIn.m_33);

  //third
  mat_temp.m_31 = (m_31 * mIn.m_11) + (m_32 * mIn.m_21) + (m_33 * mIn.m_31);
  mat_temp.m_32 = (m_31 * mIn.m_12) + (m_32 * mIn.m_22) + (m_33 * mIn.m_32);
  mat_temp.m_33 = (m_31 * mIn.m_13) + (m_32 * mIn.m_23) + (m_33 * mIn.m_33);

  *this = mat_temp;
}

//applies a 2D transformation matrix to a std::vector of Vec2Ds
inline void Matrix::transformVec2Ds(std::vector<Vec2D> &vPoint)
{
  for (std::vector<Vec2D>::size_type i=0; i<vPoint.size(); ++i)
  {
    float tempX =(m_11 * vPoint[i].x()) + (m_21*vPoint[i].y()) + (m_31);

    float tempY = (m_12*vPoint[i].x()) + (m_22*vPoint[i].y()) + (m_32);

    vPoint[i].x() = tempX;

    vPoint[i].y() = tempY;

  }
}

//applies a 2D transformation matrix to a single Vec2D
inline void Matrix::transformVec2D(Vec2D &vPoint)
{

	float tempX = (m_11*vPoint.x()) + (m_21*vPoint.y()) + (m_31);

	float tempY = (m_12*vPoint.x()) + (m_22*vPoint.y()) + (m_32);

	vPoint.x() = tempX;

	vPoint.y() = tempY;
}



//create an identity matrix
inline void Matrix::identity()
{
	m_11 = 1; m_12 = 0; m_13 = 0;

	m_21 = 0; m_22 = 1; m_23 = 0;

	m_31 = 0; m_32 = 0; m_33 = 1;
}

//create a transformation matrix
inline void Matrix::translate(float x, float y)
{
  Matrix mat;

  mat.m_11 = 1; mat.m_12 = 0; mat.m_13 = 0;

  mat.m_21 = 0; mat.m_22 = 1; mat.m_23 = 0;

  mat.m_31 = x; mat.m_32 = y; mat.m_33 = 1;

  //and multiply
  matrixMultiply(mat);
}

//create a scale matrix
inline void Matrix::scale(float xScale, float yScale)
{
  Matrix mat;

  mat.m_11 = xScale; mat.m_12 = 0; mat.m_13 = 0;

  mat.m_21 = 0; mat.m_22 = yScale; mat.m_23 = 0;

  mat.m_31 = 0; mat.m_32 = 0; mat.m_33 = 1;

  //and multiply
  matrixMultiply(mat);
}


//create a rotation matrix
inline void Matrix::rotate(float rot)
{
  Matrix mat;

  float Sin = sin(rot);
  float Cos = cos(rot);

  mat.m_11 = Cos;  mat.m_12 = Sin; mat.m_13 = 0;

  mat.m_21 = -Sin; mat.m_22 = Cos; mat.m_23 = 0;

  mat.m_31 = 0; mat.m_32 = 0;mat.m_33 = 1;

  //and multiply
  matrixMultiply(mat);
}


//create a rotation matrix from a 2D vector
inline void Matrix::rotate(const Vec2D &fwd, const Vec2D &side)
{
  Matrix mat;

  mat.m_11 = fwd.x();  mat.m_12 = fwd.y(); mat.m_13 = 0;

  mat.m_21 = side.x(); mat.m_22 = side.y(); mat.m_23 = 0;

  mat.m_31 = 0; mat.m_32 = 0;mat.m_33 = 1;

  //and multiply
  matrixMultiply(mat);
}





#endif
