/*	Matrix.h
 *
 *	Class Definition for the Matrix object
 *
 *	Author:	Colin Doolittle
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

using namespace std;

template <class T> class Column;
template <class T> class Matrix2D;

	/* Row
 	 *
 	 */


template< class T >
class Row
{
  private:
	vector<T> data;

  public:
	Row(){}
	Row(int n){ data.resize(n); }
    Row<T>(const vector<T>& v){ data = v; }

	// show row
	void show();

	// add element
	void add(T val){ data.push_back(val); }

	// row by scalar
	Row<T> operator*(const T s);

	// row by col
    T operator*(Column<T>& c);

	// row by mat
	Row<T> operator*(Matrix2D<T>& m);

	// at[]
	T& operator[](int idx){ return data[idx]; }

	// checkDimensions
	void checkDimensions( int N, const char* file, int line );

	// get size of data
	int getDataSize(){ return data.size(); }

};

	/* Column
 	 *
 	 */

template< class T >
class Column
{
  private:	
	vector<T> data;
 
  public:
	Column(){}
	Column(int n){ data.resize(n); }
    Column<T>(const vector<T>& v){ data = v; }

	// show
	void show();
	
	// add element
	void add(T val){ data.push_back(val); }

	// col by scalar
	Column<T> operator*(const T s);

	// col by row
	Matrix2D<T> operator*( Row<T>& r);

	// at[]
	T& operator[](int idx){ return data[idx]; }

	// get size of data
	int getDataSize(){ return data.size(); }
  
};



	/* Matrix2D
 	 *
 	 */

template <class T>
class Matrix2D
{
  private:
	vector< vector<T> > matrix;	
	int numRows;
	int numCols;

  public:
	Matrix2D(){ numRows = numCols = 0; }
	Matrix2D<T>( int rows, int cols );
	Matrix2D<T>( int rows, int cols, vector<T>& vals );
		
	// show matrix
	void show();
	
	// add element
	void add(vector<T>& row)
	{
		checkDimensions( row.size(), __FILE__, __LINE__ );

		matrix.push_back(row);
		numRows++;
		if( 0 == matrix.size() )
		{
			numCols = row.size();	 
		}						
	}

	// get num rows and cols
	int getNumRows(){ return numRows; }
	int getNumCols(){ return numCols; }

	// mat by col
	Column<T> operator*(Column<T>& c);
	
	// mat by mat
	Matrix2D<T> operator*(Matrix2D<T>& m_rhs);
	
	// mat by scalar
	Matrix2D<T> operator*(const T s);
	
	// at[]
	vector<T>& operator[](int idx){ return matrix[idx]; }

	// checkDimensions
	void checkDimensions( int N, const char* file, int line );

};


	/* Constructors
 	 *
 	 */

template <class T>
Matrix2D<T>::Matrix2D( int nRows, int nCols )
{
	matrix.resize(nRows);

	for(int r=0; r < nRows; r++)
	{
		matrix[r].resize(nCols);
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



	/* Show
 	 *
 	 */


template <class T>
void Row<T>::show()
{
	for(auto i : data)
	{
		cout << ' ' << i;
	}
	cout << endl;
}

template <class T>
void Column<T>::show()
{
	for(auto i : data)
	{
		cout << ' ' << i << endl;
	}
	cout << endl;
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


	/* Multiplication
 	 *
 	 */


// row by scalar
template <class T>
Row<T> Row<T>::operator*(const T s)
{
	int size = data.size();
	Row<T> row_rv( size );

	for (int i=0; i < size; i++)
	{
		row_rv[i] = data[i] * s;
	}
	return row_rv;
}


// row by col
template <class T>
T Row<T>::operator*(Column<T>& c)
{
	checkDimensions( c.getDataSize(), __FILE__, __LINE__ );

	T scal_rv = static_cast<T>(0);
	for(int i=0; i < c.getDataSize(); i++)
	{
		scal_rv += data[i] * c[i];
	}
	return scal_rv;
}


// row by mat
template <class T>
Row<T> Row<T>::operator*(Matrix2D<T>& m)
{
	int mat_numRows = m.getNumRows();
	int mat_numCols = m.getNumCols();

	checkDimensions( mat_numRows, __FILE__, __LINE__ );

	Row<T> row_rv( mat_numCols );
	for(int i=0; i < mat_numCols; i++)
	{
		T accum = static_cast<T>(0);
		for(int j=0; j < mat_numRows; j++)
		{
			accum += data[j] * m[j][i];
		}
		row_rv[i] = accum;
	}
	return row_rv;
}


// col by scalar
template <class T>
Column<T> Column<T>::operator*(const T s)
{
	int size = data.size();
	Column<T> col_rv( size );

	for(int i=0; i < size; i++)
	{
		col_rv[i] = s * data[i];
	}
	return col_rv;
}


// col by row
template <class T>
Matrix2D<T> Column<T>::operator*(Row<T>& r)
{
	Matrix2D<T> M;
	int n = r.getDataSize();

	for(int i=0; i < data.size(); i++)
	{
		vector<T> newRow( n );
		for(int j=0; j < n; j++)
		{
			newRow[j] = data[i] * r[j];
		}
		M.add( newRow );
	}
	return M;
}


// mat by col
template <class T>
Column<T> Matrix2D<T>::operator*(Column<T>& c)
{
	int size = c.getDataSize();
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
Matrix2D<T> Matrix2D<T>::operator*(Matrix2D<T>& m_rhs)
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
		M.add( newRow );
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
		M.add( newRow );
	}
	return M;
}



	/* Error Detection
	 *
	 */

template <class T>
void Row<T>::checkDimensions( int N, const char* file, int line )
{
	if ( N != data.size() )
	{
		cout << "Dimension mismatch! "
			 << data.size() << " != " << N << endl
			 << '\t' << file << ':' << line << endl;
	}
}

template <class T>
void Matrix2D<T>::checkDimensions( int N, const char* file, int line )
{
	if ( N != numCols )
	{
		cout << "Dimension mismatch! "
			 << numCols << " != " << N << endl
			 << '\t' << file << ':' << line << endl;
	}
}




#endif // MATRIX_H
