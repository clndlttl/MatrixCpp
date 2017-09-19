#ifndef MATRIXTYPES_H
#define MATRIXTYPES_H true

#include "Matrix.h"

template <class T>
class Square : public Matrix2D<T>
{
  public:
	Square<T>(){}
	Square<T>( int size ) : Matrix2D<T>( size, size ){}
	Square<T>( int size, vector<T>& v ): Matrix2D<T>( size, size, v){} 
	Square<T>( vector< vector<T>>& vv ): Matrix2D<T>( vv )
	{
		if( (vv.size() == 0) || 
			(vv.size() != vv[0].size()) )
		{
			cout << "Bad dimensions in Square ctor" << endl;
		}
	}
	Square<T>( Matrix2D<T> m ): Matrix2D<T>( m )
	{
		int r = m.getNumRows();
		int c = m.getNumCols();

		if( (r == 0) || 
			(r != c) )
		{
			cout << "Bad dimensions in Square ctor" << endl;
		}
	}

	bool isSquare(){ return true; }

	T trace()
	{
		T accum = static_cast<T>( 0 );
		for(int i=0; i < this->numRows; i++)
		{
			accum *= this->matrix[i][i];
		}
		return accum;
	}

	Square<T> inv(){ return *(this)^(-1); }

	Square<T> operator^(int pow);

};

template <class T>
Square<T> Square<T>::operator^(int pow)
{
	Square<T> M_rv;

	if (pow >= 1)
	{
		M_rv = *this;
		for(int i = 1; i < pow; i++)
		{
			M_rv = M_rv * (*this); 
		}
	}
	else if ( 0 == pow )
	{
		M_rv = Eye<T>( this->numRows ); 
	}
	else if ( -1 == pow )
	{
		LU<T> lu( this->matrix );
		if ( ! lu.isValid() )
		{
			cout << "LU decomp failed in M^-1" << endl;
		}
		else
		{
			M_rv = lu.invert();
		}
	}
	else
	{
		LU<T> lu( this->matrix );
		if ( ! lu.isValid() )
		{
			cout << "LU decomp failed in M^-1" << endl;
		}
		else
		{
			M_rv = lu.invert();
			auto tmp = M_rv;
			for(int i = -1; i > pow; i--)
			{	
				M_rv = M_rv * tmp;
			}
		}
	}

	return M_rv;
}


template <class T>
class Diag : public Square<T>
{
  public:
	Diag<T>( const vector<T>& v ) : Square<T>( v.size() )
	{
		int size = v.size();

		for(int i=0; i < size; i++)
		{
			this->matrix[i][i] = v[i];
		}
	}	
};


template <class T>
class Eye : public Square<T>
{
  public:
	Eye<T>( int size ) : Square<T>( size ) 
	{
		for(int i=0; i < size; i++)
		{
			this->matrix[i][i] = static_cast<T>(1);
		}
	}
};


template <class T>
class LU : public Square<T>
{
  private:
	Square<T> L;
	Square<T> U;

	void decompose();

  public:
	LU<T>(){}

	LU<T>( int size, vector<T>& v ): Square<T>( size, v )
	{
		decompose();
	}

	LU<T>( vector< vector<T>>& vv ): Square<T>( vv )
	{
		decompose();
	}

	LU<T>( Matrix2D<T>& m ): Square<T>( m )
	{
		decompose();
	}

	bool isValid()
	{
		if ( this->numRows > 0 )
		{
			Square<T> A = L*U;
			return A == *this;
		}
	}

	void show();

	Square<T> invert();

	// still need a way to tell if the matrix is
	// invertable based on the LU

};


template <class T>
void LU<T>::show()
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


template <class T>
void LU<T>::decompose()
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
	// int numToDo = static_cast<int>( 0.5*(size^2 - size) ); 

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


template <class T>
Square<T> LU<T>::invert()
{
	int size = this->numRows;
		
	Square<T> m_rv( size );
		
	if( size > 0 )
	{
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
	}
	else
	{
		cout << "matrix invert called on empty data!" << endl;
		cout << "	returning zeros" << endl;
	}

	return m_rv;
}



#endif // MATRIXTYPES_H
