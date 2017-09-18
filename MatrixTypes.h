#ifndef MATRIXTYPES_H
#define MATRIXTYPES_H true

#include "Matrix.h"


template <class T>
class Diag : public Matrix2D<T>
{
  public:
	Diag<T>( const vector<T>& v ) : Matrix2D<T>( v.size(), v.size() )
	{
		int size = v.size();

		for(int i=0; i < size; i++)
		{
			this->matrix[i][i] = v[i];
		}
	}	
};


template <class T>
class Eye : public Matrix2D<T>
{
  public:
	Eye<T>( int size ) : Matrix2D<T>( size, size ) 
	{
		for(int i=0; i < size; i++)
		{
			this->matrix[i][i] = static_cast<T>(1);
		}
	}
};


template <class T>
class LU : public Matrix2D<T>
{
  private:
	Matrix2D<T> L;
	Matrix2D<T> U;
	// ...and matrix from base class

  public:
	LU(){}
	LU<T>( int size ): Matrix2D<T>( size, size ){}
	LU<T>( int size, vector<T>& v ): Matrix2D<T>( size, size, v ){}
	LU<T>( vector< vector<T>>& vv ): Matrix2D<T>( vv )
	{
		if( ! this->isSquare() )
		{
			cout << "not a square matrix in LU ctor" << endl;
		}
		else
		{
			decompose();
		}

		if ( ! isValid() )
		{
			cout << "LU decomp failed" << endl;
		}
	}

	bool isValid()
	{
		if ( this->numRows > 0 )
		{
			Matrix2D<T> A = L*U;
			return A == *this;
		}
	}

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

		for(int j=0; j < size; j++)
		{
			for(int i=start_i; i < size; i++ )
			{
				if( U[i][j] && ( static_cast<T>(0) != U[j][j] ) )
				{
					double C = U[i][j] / U[j][j];
						
					for(int z=0; z < size; z++)
					{
						U[i][z] = U[i][z] - C * U[j][z]; 
					}
					
					L[i][j] = C;
				}
			}
			start_i++;
		}
	}

	Matrix2D<T> invert()
	{	// assume LU exist already
		// check for squareness
		int size = this->numRows;
		
		Matrix2D<T> m_rv( size, size );

		Eye<T> I( size );

		// for each column of the inverse
		for(int c=0; c < size; c++)
		{
			// solve for y:  Ly = I_i
			// top-down

			vector<T> y( size );
			vector<T> x( size );
			int i;
			for(i=0; i < size; i++)
			{
				T accum = static_cast<T>(0);
				// first accumulate numerator
				for(int a=0; a < i; a++)
				{
					accum += L[i][a] * y[a];
				}

				y[i] = ( I[i][c] - accum ) / L[i][i];
			}

			// then solve for x:  Ux = y
			// bottom-up

			for(i = size-1; i > -1; i--)
			{
				T accum = static_cast<T>(0);
				// first accumulate numerator
				for(int a=(size-1); a > i; a--)
				{
					accum += U[i][a] * x[a]; 
				}

				x[i] = ( y[i] - accum ) / U[i][i];
			}		
			
			// add col x to return var 
			for(i = 0; i < size; i++)
			{
				m_rv[i][c] = x[i];
			}
		}
		return m_rv;
	}
};


#endif // MATRIXTYPES_H
