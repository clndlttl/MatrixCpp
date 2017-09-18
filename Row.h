
#ifndef ROW_H
#define ROW_H true

#include "Vec.h"
#include "Column.h"
#include "Matrix.h"


	/* Row
 	 *
 	 */


template< class T >
class Row : public Vec<T>
{

  public:
	Row(){}
	Row(int size ): Vec<T>( size ){}
    Row<T>(const vector<T>& v): Vec<T>( v ){}

	// multiplication
	Row<T> operator*(const T s);
	template <class G> friend Row<G> operator*(const G s, Row<G> me);
    T operator*(Column<T> c);
	Row<T> operator*(Matrix2D<T> m);

	// addition
	Row<T> operator+(Row<T> r);	

	// subtraction
	Row<T> operator-(Row<T> r);	

	// transpose
	Column<T> t()
	{
		int size = this->data.size();
		Column<T> col_rv( size );
		for (int i=0; i < size; i++)
		{
			col_rv[i] = this->data[i];
		}
		return col_rv;
	}	
};


// row by scalar
template <class T>
Row<T> Row<T>::operator*(const T s)
{
	int size = this->data.size();
	Row<T> row_rv( size );

	for (int i=0; i < size; i++)
	{
		row_rv[i] = this->data[i] * s;
	}
	return row_rv;
}

template <class G>
Row<G> operator*(const G s, Row<G> me)
{
	return me * s;
}


// row by col
template <class T>
T Row<T>::operator*(Column<T> c)
{
	checkDimensions( c.getLength(), __FILE__, __LINE__ );

	T scal_rv = static_cast<T>(0);
	for(int i=0; i < c.getLength(); i++)
	{
		scal_rv += this->data[i] * c[i];
	}
	return scal_rv;
}


// row by mat
template <class T>
Row<T> Row<T>::operator*(Matrix2D<T> m)
{
	int mat_numRows = m.getNumRows();
	int mat_numCols = m.getNumCols();

	this->checkDimensions( mat_numRows, __FILE__, __LINE__ );

	Row<T> row_rv( mat_numCols );
	for(int i=0; i < mat_numCols; i++)
	{
		T accum = static_cast<T>(0);
		for(int j=0; j < mat_numRows; j++)
		{
			accum += this->data[j] * m[j][i];
		}
		row_rv[i] = accum;
	}
	return row_rv;
}


	/* Addition
	 *
	 */

template <class T>
Row<T> Row<T>::operator+( Row<T> r )
{
	checkDimensions( r.getLength(), __FILE__, __LINE__ );
	
	int size = this->data.size();
	Row<T> row_rv( size );

	for(int i=0; i < size; i++)
	{
		row_rv[i] = this->data[i]+r[i];		
	}
	return row_rv;
}


	/* Subtraction
	 *
	 */

template <class T>
Row<T> Row<T>::operator-( Row<T> r )
{
	checkDimensions( r.getLength(), __FILE__, __LINE__ );
	
	int size = this->data.size();
	Row<T> row_rv( size );

	for(int i=0; i < size; i++)
	{
		row_rv[i] = this->data[i]-r[i];		
	}
	return row_rv;
}



#endif // ROW_H
