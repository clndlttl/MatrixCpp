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

#define OK true
#define ERROR false

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
	Matrix2D<T>( int rows, int cols, const vector<T>& v );
	Matrix2D<T>( const vector< vector<T>>& vv );
		
	// show matrix
	virtual void show() const;
	
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

	void addRow(Row<T>& row)
	{
		vector<T>& rowData = row.getVec(); 

		checkDimensions( row.getLength(), __FILE__, __LINE__ );

		matrix.push_back(rowData);
		numRows++;
		if( 1 == numRows )
		{
			numCols = rowData.size();	 
		}						
	}
	
	// get protected data
	int getNumRows() const { return numRows; }
	int getNumCols() const { return numCols; }
	
	// return a reference to protected matrix
	vector< vector<T> >& getMatrix(){ return matrix; }

	// multiplication
	Column<T> operator*(const Column<T>& c);
	Matrix2D<T> operator*(const Matrix2D<T>& m_rhs);
	Matrix2D<T> operator*(const T& s);
	template <class G, class W> friend Matrix2D<T> operator*(const G& s, Matrix2D<T> me);

	// addition
	Matrix2D<T> operator+(const Matrix2D<T>& m);
	
	// subtraction
	Matrix2D<T> operator-(const Matrix2D<T>& m);	

	// read-only at[]
	vector<T> operator[](int idx) const { return matrix[idx]; }

	// equality
	bool operator==( const Matrix2D<T>& m )
	{
		if( numRows != m.getNumRows() )
		{
			return false;
		}

		for(int i=0; i < numRows; i++)
		{
			if ( ! (matrix[i] == m[i] ) )
			{
				return false;
			}
		}

		return true;
	}

	bool operator==( const vector< vector<T> >& v )
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

	bool isSquare(){ return numRows == numCols; }

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
Matrix2D<T>::Matrix2D( int rows, int cols, const vector<T>& v )
{
	if( v.size() < (rows*cols) )
	{
		cout << "vector too short in Matrix2D ctor!" << endl;
	}

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
Matrix2D<T>::Matrix2D( const vector< vector<T> >& vv )
{
	numRows = vv.size();
	numCols = vv[0].size();
	matrix = vv;
}


template <class T>
void Matrix2D<T>::show() const
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
Column<T> Matrix2D<T>::operator*(const Column<T>& c)
{
	int size = c.getLength();
	checkDimensions( size, __FILE__, __LINE__ );

	Column<T> col_rv( numRows );
	vector<T>& newColData = col_rv.getVec(); 

	for(int i=0; i < numRows; i++)
	{
		T accum = static_cast<T>(0);
		for(int j=0; j < size; j++)
		{
			accum += matrix[i][j] * c[j];
		}
		newColData[i] = accum;
	}
	return col_rv;
}

	
// mat by mat
template <class T>
Matrix2D<T> Matrix2D<T>::operator*(const Matrix2D<T>& m_rhs)
{
	int rhs_numRows = m_rhs.getNumRows();
	int rhs_numCols = m_rhs.getNumCols();

	checkDimensions( rhs_numRows, __FILE__, __LINE__ );

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
		matrix[i] = newRow;
	}

	numCols = rhs_numCols;

	return *this;
}
	

// mat by scalar
template <class T>
Matrix2D<T> Matrix2D<T>::operator*(const T& s)
{
	for(int i=0; i < numRows; i++)
	{
		for(int j=0; j < numCols; j++)
		{
			matrix[i][j] *= s;
		}
	}
	return *this;
}


template <class G, class W>
Matrix2D<W> operator*(const G& s, Matrix2D<W> me)
{
	return me * s;
}




template <class T>
Matrix2D<T> Matrix2D<T>::operator+( const Matrix2D<T>& m )
{
	checkDimensionsAddSub( m.getNumRows(), m.getNumCols(), __FILE__, __LINE__ );

	for(int i=0; i < numRows; i++)
	{
 		for(int j=0; j < numCols; j++)
		{
			matrix[i][j] += m[i][j];
		}
	}
	return *this;
}


template <class T>
Matrix2D<T> Matrix2D<T>::operator-( const Matrix2D<T>& m )
{
	checkDimensionsAddSub( m.getNumRows(), m.getNumCols(), __FILE__, __LINE__ );

	for(int i=0; i < numRows; i++)
	{
 		for(int j=0; j < numCols; j++)
		{
			matrix[i][j] -= m[i][j];
		}
	}
	return *this;
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
