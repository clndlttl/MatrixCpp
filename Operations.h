#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "Matrix.h"
#include "MatrixTypes.h"

enum class STATUS
{
	OK,
	ERROR
};


template <class T>
class LUdecomp : public Matrix2D<T>
{
  private:
	Matrix2D<T> LowerTri;
	Matrix2D<T> UpperTri;

  public:
	LUdecomp(){}
	LUdecomp<T>( int size );
	LUdecomp<T>( int size, vector<T>& v );

	bool validate();

	void xfrmMatrixToLU();
	
};








#endif
