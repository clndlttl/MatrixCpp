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
 * A row vector
 *
 */


template< class T >
class Row
{
  public:
	Row(){}

	// construct from std::vector
    Row<T>(const vector<T>& v);

	// show row
	void show();

	// scalar by row
	Row<T> operator*(const T& s);

	// row by col
    T operator*(const Column<T>& c);

	// row by mat
	Row<T> operator*(const Matrix2D<T>& m);

	// at[]
	T operator[](int idx){ return col[idx]; }

	vector<T> col;
};

/* Column
 *
 * A column vector
 *
 */
template< class T >
class Column
{
  public:
	// construct from std::vector
    Column<T>(const vector<T>& vin);

	// show
	void show();
	
	// col by scalar
	Column<T> operator*(const T& s);

	// col by row
	Matrix2D<T> operator*(const Row<T>& r);

	// at[]
	T operator[](int idx){ return row[idx]; }
    
	vector<T> row;
};

/* Matrix2D
 *
 * Defined as a column vector of row objects
 * 
 */

template <class T>
class Matrix2D
{
  public:
	// construct from std::vector
	Matrix2D<T>( int nRows, int nCols, const vector<T>& vals );
		
	// show matrix
	void show();
	
	// mat by col
	Column<T> operator*(const Column<T>& c);
	
	// mat by mat
	Matrix2D<T> operator*(const Matrix2D<T>& m_rhs);
	
	// mat by scalar
	Matrix2D<T> operator*(const T& s);
	
	// at[]
	Row<T> operator[](int idx){ return matrix[idx]; }

	int nr;
	int nc;
	vector< Row<T> > matrix;	
};


/* Constructors
 *
 */


template <class T>
Row<T>::Row( const vector<T>& v )
{
	for(auto i : v)
	{
		col.push_back(i);
	}
}

template <class T>
Column<T>::Column( const vector<T>& v )
{
	for(auto i : v)
	{
		row.push_back(i);
	}
}

template <class T>
Matrix2D<T>::Matrix2D( int nRows, int nCols, const vector<T>& v )
{
	nr = nRows;
	nc = nCols;

	auto p = v.begin();

	for(int r = 0; r < nRows; r++)
	{
		vector<T> newRowVec (p,p+nCols);
		matrix.push_back( newRowVec );
		p += nCols;
	}
}

/* Show
 *
 */


template <class T>
void Row<T>::show()
{
	for(int c=0; c<col.size(); c++)
	{
		cout << ' ' << col[c];
	}
	cout << endl;
}

template <class T>
void Column<T>::show()
{
	for(int r=0; r<row.size(); r++)
	{
		cout << ' ' << row[r];
	}
	cout << endl;
}

template <class T>
void Matrix2D<T>::show()
{
	for(int r=0; r<nr; r++)
	{
		for(int c=0; c<nc; c++)
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

	/* Row mult
	 *
	 */

// row by scalar
template <class T>
Row<T> Row<T>::operator*(const T& s)
{
	Row<T> rv;
	for (int i=0; i < col.size(); i++)
	{
		rv.col.push_back( s * col[i] );
	}
	return rv;
}


// row by col
template <class T>
T Row<T>::operator*(const Column<T>& c)
{

}


// row by mat
template <class T>
Row<T> Row<T>::operator*(const Matrix2D<T>& m)
{

}

	/* Col mult
	 *
	 */

// col by scalar
template <class T>
Column<T> Column<T>::operator*(const T& s){}

// col by row
template <class T>
Matrix2D<T> Column<T>::operator*(const Row<T>& r){}



	/* Mat mult
	 *
	 */
#if 0
// row by Mat
Row<T> Matrix2D<T>::operator*(const Row<T>& r, const Matrix2D<T>&){}

// mat by col
Column<T> Matrix2D<T>::operator*(const Matrix2D<T>&, const Column<T>& c){}
	
// mat by mat
Matrix2D<T> Matrix2D<T>::operator*(const Matrix2D<T>&, Matrix2D<T>& m_rhs){}
	
// mat by mat, me on right
Matrix2D<T> Matrix2D<T>::operator*(const Matrix2D<T>& lhs, Matrix2D<T>&){}
	
// scalar by mat
Matrix2D<T> Matrix2D<T>::operator*(const T& s, const Matrix2D& m){}

// mat by scalar
Matrix2D<T> Matrix2D<T>::operator*(const Matrix2D& m, const T& s){}

#endif

#endif
