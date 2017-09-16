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
	Matrix2D<T> L;
	Matrix2D<T> U;
	// ...and matrix from base class

  public:
	LUdecomp(){}
	LUdecomp<T>( int size ): Matrix2D<T>( size, size ){}
	LUdecomp<T>( int size, vector<T>& v ): Matrix2D<T>( size, size, v ){}

	bool validate();

	void decompose()
	{
		// init LowerTri to eye.
		//
		// go to first non-zero element in the lower half of matrix
		// by travelling down columns, at i,j. (1-based: i*j >= 2, i > j)
		// mult row i-1 by (-1*matrix[i][j] / matrix[j][j]) and
		// add it to row i. substitute the result of the add
		// to row i.  Save the value to LowerTri[i][j]. 
		//
		// the next non-zero element is past i,j
		
		int size = this->getNumRows();
		auto mat = this->getMatrix();

		L = Eye<T>( size );
		U = *(mat);

		// size^2/2 - size/2
		// 2x2 = 2 - 1
		// 3x3 = 4.5 - 1.5
		// 4x4 = 8 - 2
		// 5x5 = 12.5 - 2.5
		int numToDo = static_cast<int>( 0.5*(size^2 - size) ); 

		int start_i = 1;
		int start_j = 0;

		// ensure matrix[0][0] != 0
		// debug:
		if( U[0][0] == static_cast<T>(0) )
		{
			cout << "problem " << __FILE__ << ':' << __LINE__ << endl; 
		}

		for(int k=0; k < numToDo; k++)
		{
			for(int j=start_j; j < size; j++)
			{
				for(int i=start_i; i < size; i++ )
				{
					if( U[i][j] )
					{
						double C = -1.0*U[i][j] / U[j][j];
						Row<T> thisRow( U[i] );
						Row<T> multRow( U[j] );
						Row<T> newRow = thisRow + C*multRow;
						U[i] = *newRow.getRowVec();
						
						L[i][j] = C;
					}
				}
			}
		}	
	}
};







#endif
