/*	Matrix.h
 *
 *	Class Definition for the Matrix object
 *
 *	Author:	Colin Doolittle
 */

#ifndef MATRIX_H
#define MATRIX_H true

#include "Row.h"
#include "Column.h"

template <class T> class Eye;
template <class T> class LU;
template <class T> class Column;
template <class T> class Row;

	/* Matrix2D
 	 *
 	 */

template <class T>
class Matrix2D
{
  protected:
	vector< vector<T> > matrix;	
	int numRows;
	int numCols;

  public:
	Matrix2D(){ numRows = numCols = 0; }
	Matrix2D<T>( int rows, int cols );
	Matrix2D<T>( int rows, int cols, vector<T>& v );
	Matrix2D<T>( vector< vector<T>>& vv );
		
	// show matrix
	virtual void show();
	
	// add element
	void addRow(vector<T>& row)
	{
		checkDimensions( row.size(), __FILE__, __LINE__ );

		matrix.push_back(row);
		numRows++;
		if( 1 == numRows )
		{
			numCols = row.size();	 
		}						
	}

	// get private data
	int getNumRows(){ return numRows; }
	int getNumCols(){ return numCols; }
	
	// return a reference to private matrix
	vector< vector<T> >* getMatrix(){ return &matrix; }

	// multiplication
	virtual Column<T> operator*(Column<T> c);
	virtual Matrix2D<T> operator*(Matrix2D<T> m_rhs);
	virtual Matrix2D<T> operator*(const T s);
	template <class G> friend Matrix2D<G> operator*(const G s, Matrix2D<G> me);

	// exponent
	virtual Matrix2D<T> operator^(int pow);
	
	// addition
	virtual Matrix2D<T> operator+(Matrix2D<T> m);
	
	// subtraction
	virtual Matrix2D<T> operator-(Matrix2D<T> m);	

	// at[]
	vector<T>& operator[](int idx){ return matrix[idx]; }

	// equality
	bool operator==( Matrix2D<T>& m )
	{
		if ( matrix == *( m.getMatrix() ) )
		{
			return true;
		}
		else
		{
			return false;
		}	
	}

	bool operator==( vector< vector<T> >& v )
	{
		if ( matrix == v )
		{
			return true;
		}
		else
		{
			return false;
		}	
	}

	// checkDimensions
	void checkDimensions( int N, const char* file, int line );
	void checkDimensionsAddSub( int NR, int NC, const char* file, int line );

	// transpose
	Matrix2D<T> t()
	{
		Matrix2D<T> m_rv;

		for(int j=0; j < numCols; j++)
		{
			vector<T> tmp( numRows );
			for(int i=0; i < numRows; i++)
			{
				tmp[i] = matrix[i][j];
			}
			m_rv.addRow( tmp );
		}

		return m_rv;
	}

};


template <class T>
Matrix2D<T>::Matrix2D( int rows, int cols )
{
	numRows = rows;
	numCols = cols;
	
	matrix.resize(numRows);

	for(int r=0; r < numRows; r++)
	{
		matrix[r].resize(numCols);
	}
}


template <class T>
Matrix2D<T>::Matrix2D( int rows, int cols, vector<T>& v )
{
	numRows = rows;
	numCols = cols;
	auto ptr = v.begin();

	for(int r = 0; r < numRows; r++)
	{
		vector<T> newRow (ptr, ptr + numCols);
		matrix.push_back( newRow );
		ptr += numCols;
	}
}


template <class T>
Matrix2D<T>::Matrix2D( vector< vector<T> >& vv )
{
	numRows = vv.size();
	numCols = vv[0].size();
	matrix = vv;
}


template <class T>
void Matrix2D<T>::show()
{
	for(int r=0; r<numRows; r++)
	{
		for(int c=0; c<numCols; c++)
		{
			cout << ' ' << matrix[r][c];
		}
		cout << endl;
	}
	cout << endl;
}


// mat by col
template <class T>
Column<T> Matrix2D<T>::operator*(Column<T> c)
{
	int size = c.getLength();
	checkDimensions( size, __FILE__, __LINE__ );

	Column<T> col_rv( numRows );

	for(int i=0; i < numRows; i++)
	{
		T accum = static_cast<T>(0);
		for(int j=0; j < size; j++)
		{
			accum += matrix[i][j] * c[j];
		}
		col_rv[i] = accum;
	}
	return col_rv;
}

	
// mat by mat
template <class T>
Matrix2D<T> Matrix2D<T>::operator*(Matrix2D<T> m_rhs)
{
	int rhs_numRows = m_rhs.getNumRows();
	int rhs_numCols = m_rhs.getNumCols();

	checkDimensions( rhs_numRows, __FILE__, __LINE__ );

	Matrix2D<T> M;

	for(int i=0; i < numRows; i++)
	{
		vector<T> newRow( rhs_numCols );
		for(int j=0; j < rhs_numCols; j++)
		{
			T accum = static_cast<T>(0);
			for(int k=0; k < numCols; k++)
			{
				accum += matrix[i][k] * m_rhs[k][j];
			}
			newRow[j] = accum;	 	
		}
		M.addRow( newRow );
	}
	return M;
}
	

// mat by scalar
template <class T>
Matrix2D<T> Matrix2D<T>::operator*(const T s)
{
	Matrix2D<T> M;

	for(int i=0; i < numRows; i++)
	{
		vector<T> newRow(numCols);
		for(int j=0; j < numCols; j++)
		{
			newRow[j] = matrix[i][j] * s;
		}
		M.addRow( newRow );
	}
	return M;
}


template <class G>
Matrix2D<G> operator*(const G s, Matrix2D<G> me)
{
	return me * s;
}


template <class T>
Matrix2D<T> Matrix2D<T>::operator^(int pow)
{
	checkDimensions( numRows, __FILE__, __LINE__ );

	Matrix2D<T> M_rv;

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
		M_rv = Eye<T>( numRows ); 
	}
	else if ( -1 == pow )
	{
		M_rv = LU<T>( matrix ).invert();
	}
	else
	{
		M_rv = LU<T>( matrix ).invert();
		auto inv = M_rv;
		for(int i = -1; i > pow; i--)
		{	
			M_rv = M_rv * LU<T>( matrix ).invert();
		}
	}

	return M_rv;
}


template <class T>
Matrix2D<T> Matrix2D<T>::operator+( Matrix2D<T> m )
{
	checkDimensionsAddSub( m.getNumRows(), m.getNumCols(), __FILE__, __LINE__ );

	Matrix2D<T> M_rv;

	for(int i=0; i < numRows; i++)
	{
		vector<T> newRow( numCols );
 		for(int j=0; j < numCols; j++)
		{
			newRow[j] = matrix[i][j] + m[i][j];
		}
		M_rv.addRow( newRow );
	}
	return M_rv;
}


template <class T>
Matrix2D<T> Matrix2D<T>::operator-( Matrix2D<T> m )
{
	checkDimensionsAddSub( m.getNumRows(), m.getNumCols(), __FILE__, __LINE__ );

	Matrix2D<T> M_rv;

	for(int i=0; i < numRows; i++)
	{
		vector<T> newRow( numCols );
 		for(int j=0; j < numCols; j++)
		{
			newRow[j] = matrix[i][j] - m[i][j];
		}
		M_rv.addRow( newRow );
	}
	return M_rv;
}


template <class T>
void Matrix2D<T>::checkDimensions( int N, const char* file, int line )
{
	if ( (numRows > 0) && (N != numCols) )
	{
		cout << "Dimension mismatch! "
			 << numCols << " != " << N << endl
			 << '\t' << file << ':' << line << endl;
	}
}


template <class T>
void Matrix2D<T>::checkDimensionsAddSub( int NR, int NC, const char* file, int line )
{
	if ( (numRows > 0) && (NR != numRows) )
	{
		cout << "Dimension mismatch! "
			 << numRows << " != " << NR << endl
			 << '\t' << file << ':' << line << endl;
	}

	if ( (numRows > 0) && (NC != numCols) )
	{
		cout << "Dimension mismatch! "
			 << numCols << " != " << NC << endl
			 << '\t' << file << ':' << line << endl;
	}
}


#endif // MATRIX_H
