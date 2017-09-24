
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
	Row<T>(int size ): Vec<T>( size ){}
    Row<T>(const vector<T>& v): Vec<T>( v ){}

	// multiplication
	Row<T> operator*(const T& s);
	template <class G> friend Row<G> operator*(const G& s, Row<G> me);
    T operator*(const Column<T>& c);
	Row<T> operator*(const Matrix2D<T>& m);

	// addition
	Row<T> operator+(const Row<T>& r);	

	// subtraction
	Row<T> operator-(const Row<T>& r);	

	// transpose
	Column<T> t()
	{
		int size = this->data.size();
		Column<T> col_rv( size );
		vector<T>& p = col_rv.getVec();
		for (int i=0; i < size; i++)
		{
			p[i] = this->data[i];
		}
		return col_rv;
	}	
};


// row by scalar
template <class T>
Row<T> Row<T>::operator*(const T& s)
{
	int size = this->data.size();

	for (int i=0; i < size; i++)
	{
		this->data[i] *= s;
	}
	return *this;
}

template <class G>
Row<G> operator*(const G& s, Row<G> me)
{
	return me * s;
}


// row by col
template <class T>
T Row<T>::operator*(const Column<T>& c)
{
	this->checkDimensions( c.getLength(), __FILE__, __LINE__ );

	T scal_rv = static_cast<T>(0);
	for(int i=0; i < c.getLength(); i++)
	{
		scal_rv += this->data[i] * c[i];
	}
	return scal_rv;
}


// row by mat
template <class T>
Row<T> Row<T>::operator*(const Matrix2D<T>& m)
{
	int mat_numRows = m.getNumRows();
	int mat_numCols = m.getNumCols();

	this->checkDimensions( mat_numRows, __FILE__, __LINE__ );

	vector<T> newData( mat_numRows );

	for(int i=0; i < mat_numCols; i++)
	{
		T accum = static_cast<T>(0);
		for(int j=0; j < mat_numRows; j++)
		{
			accum += this->data[j] * m[j][i];
		}
		newData[i] = accum;
	}
	this->data = newData;

	return *this;
}


	/* Addition
	 *
	 */

template <class T>
Row<T> Row<T>::operator+( const Row<T>& r )
{
	this->checkDimensions( r.getLength(), __FILE__, __LINE__ );
	
	int size = this->data.size();

	for(int i=0; i < size; i++)
	{
		this->data[i] += r[i];		
	}
	return *this;
}


	/* Subtraction
	 *
	 */

template <class T>
Row<T> Row<T>::operator-( const Row<T>& r )
{
	this->checkDimensions( r.getLength(), __FILE__, __LINE__ );
	
	int size = this->data.size();

	for(int i=0; i < size; i++)
	{
		this->data[i] -= r[i];		
	}
	return *this;
}



#endif // ROW_H
