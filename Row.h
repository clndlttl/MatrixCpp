
#ifndef ROW_H
#define ROW_H true

#include <vector>
#include <iostream>

#include "Column.h"
#include "Matrix.h"

using namespace std;



	/* Row
 	 *
 	 */


template< class T >
class Row
{
  protected:
	vector<T> data;

  public:
	Row(){}
	Row(int n){ data.resize(n); }
    Row<T>(const vector<T>& v){ data = v; }

	// show row
	void show();

	// get row vec
	vector<T>* getRowVecPtr(){ return &data; }

	// add element
	void add(T val){ data.push_back(val); }

	// multiplication
	Row<T> operator*(const T s);
	template <class G> friend Row<G> operator*(const G s, Row<G> me);
    T operator*(Column<T> c);
	Row<T> operator*(Matrix2D<T> m);

	// addition
	Row<T> operator+(Row<T> r);	

	// subtraction
	Row<T> operator-(Row<T> r);	

	// at[]
	T& operator[](int idx){ return data[idx]; }

	// checkDimensions
	void checkDimensions( int N, const char* file, int line );

	// get length of row
	int getLength(){ return data.size(); }

};
template <class T>
void Row<T>::show()
{
	for(auto i : data)
	{
		cout << ' ' << i;
	}
	cout << endl << endl;
}


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
		scal_rv += data[i] * c[i];
	}
	return scal_rv;
}


// row by mat
template <class T>
Row<T> Row<T>::operator*(Matrix2D<T> m)
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


	/* Addition
	 *
	 */

template <class T>
Row<T> Row<T>::operator+( Row<T> r )
{
	checkDimensions( r.getLength(), __FILE__, __LINE__ );
	
	int size = data.size();
	Row<T> row_rv( size );

	for(int i=0; i < size; i++)
	{
		row_rv[i] = data[i]+r[i];		
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
	
	int size = data.size();
	Row<T> row_rv( size );

	for(int i=0; i < size; i++)
	{
		row_rv[i] = data[i]-r[i];		
	}
	return row_rv;
}


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


#endif // ROW_H
