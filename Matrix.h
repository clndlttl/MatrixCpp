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

/* Row
 *
 * A row vector
 *
 */

template< class T >
class Row
{
  public:
	// construct from vector
    Row<T>(const vector<T>& v);
    
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
	// construct from vector
    Column<T>(const vector<T>& vin);
    
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
		Matrix2D<T>( int nRows, int nCols, const vector<T>& vals );
		void show();


	private: 
		int nr;
		int nc;
		vector< Row<T> > data;	
};


template <class T>
Row<T>::Row( const vector<T>& v )
{
	for(auto i : v)
	{
		data.push_back(i);
	}
}

template <class T>
Column<T>::Column( const vector<T>& v )
{
	for(auto i : v)
	{
		data.push_back(i);
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
		data.push_back( newRowVec );

		// incr p
		p += nCols;
	}
}

template <class T>
void Matrix2D<T>::show()
{
	for(int r=0; r<nr; r++)
	{
		for(int c=0; c<nc; c++)
		{
			cout << ' ' << data[r].data[c];
		}
		cout << endl;
	}
}


#endif
