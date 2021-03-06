#ifndef MATRIXTYPES_H
#define MATRIXTYPES_H true

#include "Matrix.h"

template <class T>
class Square : public Matrix2D<T>
{
  private:
	Square<T> perm( int size, int r1, int r2 );

  public:
	Square<T>(){}
	Square<T>( int size ) : Matrix2D<T>( size, size ){}
	Square<T>( int size, const vector<T>& v ): Matrix2D<T>( size, size, v){} 
	Square<T>( const vector< vector<T>>& vv ): Matrix2D<T>( vv )
	{
		if( (vv.size() == 0) || 
			(vv.size() != vv[0].size()) )
		{
			cout << "Bad dimensions in Square ctor" << endl;
		}
	}
	Square<T>( const Matrix2D<T>& m ): Matrix2D<T>( m )
	{
		int r = m.getNumRows();
		int c = m.getNumCols();

		if( (r == 0) || 
			(r != c) )
		{
			cout << "Bad dimensions in Square ctor" <<  endl;
			cout << "r " << r << " c " << c << endl;
		}
	}


	T trace()
	{
		T accum = static_cast<T>( 0 );
		for(int i=0; i < this->numRows; i++)
		{
			accum += this->matrix[i][i];
		}
		return accum;
	}

	Square<T> inv();

	Square<T> operator^(int pow);

	// Square matrix can't add rows
	void addRow(vector<T>& row) = delete;

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
		M_rv = inv();
	}
	else
	{
		M_rv = inv();
		auto tmp = M_rv;
		for(int i = -1; i > pow; i--)
		{	
			M_rv = M_rv * tmp;
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
	Eye<T>(){}
	Eye<T>( int size ) : Square<T>( size ) 
	{
		for(int i=0; i < size; i++)
		{
			this->matrix[i][i] = static_cast<T>(1);
		}
	}
};




template <class T>
Square<T> Square<T>::perm( int size, int r1, int r2 )
{
	Eye<T> I( size );

	vector< vector<T>>& M = I.getMatrix();

	vector<T> tmp = M[r2];
	M[r2] = M[r1];
	M[r1] = tmp;

	return I;
}


template <class T>
Square<T> Square<T>::inv()
{
	int size = this->numRows;

	if ( 0 == size )
	{
		cout << "wtf, size 0 in inv()" << endl;
		return *this;
	}

	Eye<T> L_mat( size );
	auto L = L_mat.getMatrix();

	Square<T> U_mat( this->matrix );
	auto U = U_mat.getMatrix();

	// init Permutation matrix to Identity
	Square<T> P = L_mat;	

	//******** If needed, apply permutations
	bool swapNeeded = false;

	for(int i=0; i < size; i++)
	{
		if( ! U[i][i] )
		{
			swapNeeded = true;
		
			for(int x = 0; x < size; x++)
			{
				if( U[x][i] )
				{
					// swap those rows
					vector<T> tmp = U[x];
					U[x] = U[i];
					U[i] = tmp;

					// permutation the existing permutation
					P = perm( size, i, x) * P;

					cout << "perm: swapped rows " << i << " <--> " << x << endl;
					swapNeeded = false;
					break;
				}
			}

			if( swapNeeded )
			{
				// matrix is not invertible
				cout << "Not full rank in inv(), aborting inverse" << endl;
				return *this;
			}
		}
	}

	//******** Do the LU decomp
	// init LowerTri to eye.
	//
	// go to first non-zero element in the lower half of matrix
	// by travelling down columns, at i,j. (1-based: i*j >= 2, i > j)
	// mult row i-1 by (-1*matrix[i][j] / matrix[j][j]) and
	// add it to row i. substitute the result of the add
	// to row i.  Save the value to LowerTri[i][j]. 
	//
	// the next non-zero element is past i,j
	int start_i = 1;

	for(int j=0; j < size; j++)
	{
		for(int i=start_i; i < size; i++ )
		{
			if( U[i][j] && U[j][j] )
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

	//******* sanity check **************

	if ( ! ( (*this) == (L_mat * U_mat) ) )
	{
		cout << "LU != A" << endl;
		return *this;
	}

	//******* solve system of eqns ******
		
	Square<T> M_inv( size );
	vector< vector<T>>& setM_inv = M_inv.getMatrix(); 
		
	const Eye<T> I( size );

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
			setM_inv[i][c] = x[i];
		}
	}

	// undo permutations and return

	return M_inv * P;
}



#endif // MATRIXTYPES_H
