#ifndef COLUMN_H
#define COLUMN_H true

#include "Vec.h"
#include "Row.h"
#include "Matrix.h"

using namespace std;

	/* Column
 	 *
 	 */

template< class T >
class Column : public Vec<T>
{
 
  public:
	Column(){}
	Column<T>(int n): Vec<T>( n ){}
    Column<T>(const vector<T>& v): Vec<T>( v ){}

	// show
	void show();
	
	// multiplication
	Column<T> operator*(const T& s);
	template <class G> friend Column<G> operator*(const G& s, Column<G> me);
	Matrix2D<T> operator*( const Row<T>& r);

	// addition
	Column<T> operator+(const Column<T>& c);

	// subtraction
	Column<T> operator-(const Column<T>& c);	

	// transpose
	Row<T> t()
	{
		int size = this->data.size();
		Row<T> row_rv( size );
		for (int i=0; i < size; i++)
		{
			row_rv[i] = this->data[i];
		}
		return row_rv;
	}	

};


template <class T>
void Column<T>::show()
{
	for(auto i : this->data)
	{
		cout << ' ' << i << endl;
	}
	cout << endl;
}


// col by scalar
template <class T>
Column<T> Column<T>::operator*(const T& s)
{
	int size = this->data.size();

	for(int i=0; i < size; i++)
	{
		this->data[i] *= s;
	}
	return *this;
}

template <class G>
Column<G> operator*(const G& s, Column<G> me)
{
	return me * s;
}



// col by row
template <class T>
Matrix2D<T> Column<T>::operator*(const Row<T>& r)
{
	Matrix2D<T> M;
	int n = r.getLength();

	for(int i=0; i < this->data.size(); i++)
	{
		vector<T> newRow( n );
		for(int j=0; j < n; j++)
		{
			newRow[j] = this->data[i] * r[j];
		}
		M.addRow( newRow );
	}
	return M;
}


template <class T>
Column<T> Column<T>::operator+( const Column<T>& c )
{
	checkDimensions( c.getLength(), __FILE__, __LINE__ );
	
	int size = this->data.size();

	for(int i=0; i < size; i++)
	{
		this->data[i] += c[i];		
	}
	return *this;
}


template <class T>
Column<T> Column<T>::operator-( const Column<T>& c )
{
	checkDimensions( c.getLength(), __FILE__, __LINE__ );
	
	int size = this->data.size();

	for(int i=0; i < size; i++)
	{
		this->data[i] -= c[i];		
	}
	return *this;
}



#endif // COLUMN_H
