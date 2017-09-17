#ifndef COLUMN_H
#define COLUMN_H true

#include <vector>
#include <iostream>

#include "Row.h"
#include "Matrix.h"

using namespace std;

template <class T> class Matrix2D;
template <class T> class Row;


	/* Column
 	 *
 	 */

template< class T >
class Column
{
  protected:	
	vector<T> data;
 
  public:
	Column(){}
	Column(int n){ data.resize(n); }
    Column<T>(const vector<T>& v){ data = v; }

	// show
	void show();
	
	// add element
	void add(T val){ data.push_back(val); }

	// multiplication
	Column<T> operator*(const T s);
	template <class G> friend Column<G> operator*(const G s, Column<G> me);
	Matrix2D<T> operator*( Row<T> r);

	// addition
	Column<T> operator+(Column<T> c);

	// subtraction
	Column<T> operator-(Column<T> c);	

	// at[]
	T& operator[](int idx){ return data[idx]; }

	// get length of column
	int getLength(){ return data.size(); }
  
	// checkDimensions
	void checkDimensions( int N, const char* file, int line );

};


template <class T>
void Column<T>::show()
{
	for(auto i : data)
	{
		cout << ' ' << i << endl;
	}
	cout << endl;
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

template <class G>
Column<G> operator*(const G s, Column<G> me)
{
	return me * s;
}



// col by row
template <class T>
Matrix2D<T> Column<T>::operator*(Row<T> r)
{
	Matrix2D<T> M;
	int n = r.getLength();

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


template <class T>
Column<T> Column<T>::operator+( Column<T> c )
{
	checkDimensions( c.getLength(), __FILE__, __LINE__ );
	
	int size = data.size();
	Column<T> col_rv( size );

	for(int i=0; i < size; i++)
	{
		col_rv[i] = data[i]+c[i];		
	}
	return col_rv;
}


template <class T>
Column<T> Column<T>::operator-( Column<T> c )
{
	checkDimensions( c.getLength(), __FILE__, __LINE__ );
	
	int size = data.size();
	Column<T> col_rv( size );

	for(int i=0; i < size; i++)
	{
		col_rv[i] = data[i]-c[i];		
	}
	return col_rv;
}


template <class T>
void Column<T>::checkDimensions( int N, const char* file, int line )
{
	if ( N != data.size() )
	{
		cout << "Dimension mismatch! "
			 << data.size() << " != " << N << endl
			 << '\t' << file << ':' << line << endl;
	}
}


#endif // COLUMN_H
