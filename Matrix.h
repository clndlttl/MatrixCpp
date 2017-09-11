/*	Matrix.h
 *
 *	Class Definition for the Matrix object
 *
 *	Author:	Colin Doolittle
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

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
    Row(vector<T>& v);
    
  private:	
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
    Column(vector<T>& vin);
    
  private:	
    vector<T> data;
};

/* Matrix2D
 *
 * Defined as a column vector of row objects
 * 
 */

template<class T>
class Matrix2D : public Column
{
	public:
		Matrix2D( int nRows, int nCols, vector<T>& vals );

	private: 
		int nr;
		int nc;
		vector< Row<T> > data;	
};







#endif
