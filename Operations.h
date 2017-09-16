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

	void show()
	{
		int size = this->numRows;

		// Show L
		cout << "L:" << endl;
		for(int r=0; r < size; r++)
		{
			for(int c=0; c < size; c++)
			{
				cout << ' ' << L[r][c];
			}
			cout << endl;
		}
		cout << endl;
	
		// Show U
		cout << "U:" << endl;	
		for(int r=0; r < size; r++)
		{
			for(int c=0; c < size; c++)
			{
				cout << ' ' << U[r][c];
			}
			cout << endl;
		}
		cout << endl;
	}

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
		
		int size = this->numRows;

		L = Eye<T>( size );
		U = this->matrix;

		// size^2/2 - size/2
		int numToDo = static_cast<int>( 0.5*(size^2 - size) ); 

		int start_i = 1;

		// ensure matrix[0][0] != 0
		// debug:
		if( U[0][0] == static_cast<T>(0) )
		{
			cout << "problem " << __FILE__ << ':' << __LINE__ << endl; 
		}

		for(int j=0; j < size; j++)
		{
			for(int i=start_i; i < size; i++ )
			{
				if( U[i][j] && ( static_cast<T>(0) != U[j][j] ) )
				{
					double C = -1.0*U[i][j] / U[j][j];
						
					for(int z=0; z < size; z++)
					{
						U[i][z] = U[i][z] + C * U[j][z]; 
					}
					
					L[i][j] = C;
				}
			}
			start_i++;
		}
	}
};







#endif
