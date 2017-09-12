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

#include "Code.h"

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

	// add element
	void add(T val){ data.push_back(val); }

	// row by scalar
	Row<T> operator*(const T s);

	// row by col
    T operator*(Column<T>& c);

	// row by mat
	Row<T> operator*(const Matrix2D<T>& m);

	// at[]
	T operator[](int idx){ return data[idx]; }

	// checkDimensions
	void checkDimensions( int N );

  private:
	// the actual data
	vector<T> data;
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
	Column<T>(){}

	// construct from std::vector
    Column<T>(const vector<T>& vin);

	// show
	void show();
	
	// add element
	void add(T val){ data.push_back(val); }

	// col by scalar
	Column<T> operator*(const T s);

	// col by row
	Matrix2D<T> operator*(const Row<T>& r);

	// at[]
	T operator[](int idx){ return data[idx]; }

  private:	
	vector<T> data;
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
	Matrix2D<T>(){ nr = nc = 0; }

	// construct from std::vector
	Matrix2D<T>( int nRows, int nCols, const vector<T>& vals );
		
	// show matrix
	void show();
	
	// add element
	void add(Row<T>& r){ matrix.push_back(r);
					  	 nr++; }	 
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
  private:
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
		add(i);
	}
}

template <class T>
Column<T>::Column( const vector<T>& v )
{
	for(auto i : v)
	{
		add(i);
	}
}



template <class T>
Matrix2D<T>::Matrix2D( int nRows, int nCols, const vector<T>& v )
{
	auto ptr = v.begin();

	for(int r = 0; r < nRows; r++)
	{
		vector<T> newRowVec (ptr, ptr+nCols);
		add( newRowVec );
		ptr += nCols;
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
		cout << ' ' << i;
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


// row by scalar
template <class T>
Row<T> Row<T>::operator*(const T s)
{
	Row<T> r;
	for (int i=0; i < data.size(); i++)
	{
		r.add( data[i] * s );
	}
	return r;
}


// row by col
template <class T>
T Row<T>::operator*(Column<T>& c)
{
	checkDimensions( c.data.size() );

	T s = static_cast<T>(0);
	for(int i=0; i < c.data.size(); i++)
	{
		s += data[i] * c[i];
	}
	return s;
}


// row by mat
template <class T>
Row<T> Row<T>::operator*(const Matrix2D<T>& m)
{

	checkDimensions( m.nr );

	Row<T> rv;
	for(int i=0; i < m.nc; i++)
	{
		rv.add( static_cast<T>(0) );
		for(int j=0; j < m.nr; j++)
		{
			rv[i] += data[j] * m[j][i];
		}
	}
	return rv;
}



// col by scalar
template <class T>
Column<T> Column<T>::operator*(const T s)
{
	Column<T> c;
	for(int i=0; i < data.size(); i++)
	{
		c.add( s * data[i] );
	}
	return c;
}

// col by row
template <class T>
Matrix2D<T> Column<T>::operator*(const Row<T>& r)
{
	Matrix2D<T> m;
	for(int i=0; i < data.size(); i++)
	{
		Row<T> newr;
		for(int j=0; j < r.data.size(); j++)
		{
			newr.add( data[i] * r[j] );
		}
		m.add(newr);
	}
	return m;
}



// mat by col
template <class T>
Column<T> Matrix2D<T>::operator*(const Column<T>& c){}
	
// mat by mat
template <class T>
Matrix2D<T> Matrix2D<T>::operator*(const Matrix2D<T>& m_rhs){}
	
// mat by scalar
template <class T>
Matrix2D<T> Matrix2D<T>::operator*(const T& s){}



	/* Error Handling
	 *
	 */

template <class T>
void Row<T>::checkDimensions( int N )
{
	if ( N != data.size() )
	{
		cout << "Dimension Error! "
			 << data.size() << " != " << N << endl;
	}
}





#endif // MATRIX_H
