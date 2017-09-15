#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "Matrix.h"
#include "MatrixTypes.h"

enum class STATUS
{
	OK,
	ERROR
}


template <class T>
class LUdecomp : public Matrix2D
{
  private:
	Matrix2D<T> LowerTri;
	Matrix2D<T> UpperTri;

  public:
	LowerTri(){}
	LowerTri<T>( int size );
	LowerTri<T>( int size, vector<T>& v );

	bool validate();

	void xfrmMatrixToLU();
	
}








#endif
