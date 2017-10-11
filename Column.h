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
	template <class G> friend Column<G> operator*(const int& s, Column<G>& me);
	template <class G> friend Column<G> operator*(const double& s, Column<G>& me);
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
		vector<T>& p = row_rv.getVec();
		for (int i=0; i < size; i++)
		{
			p[i] = this->data[i];
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

	Column<T> C_rv = *this;
	vector<T>& colRef = C_rv.getVec();

	for(int i=0; i < size; i++)
	{
		colRef[i] *= s;
	}
	return C_rv;
}


template <class G>
Column<G> operator*(const int& s, Column<G>& me)
{
	return me * static_cast<G>(s);
}

template <class G>
Column<G> operator*(const double& s, Column<G>& me)
{
	return me * static_cast<G>(s);
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
	this->checkDimensions( c.getLength(), __FILE__, __LINE__ );
	
	int size = this->data.size();

	Column<T> C_rv = *this;
	vector<T>& colRef = C_rv.getVec();

	for(int i=0; i < size; i++)
	{
		colRef[i] += c[i];		
	}
	return C_rv;
}


template <class T>
Column<T> Column<T>::operator-( const Column<T>& c )
{
	this->checkDimensions( c.getLength(), __FILE__, __LINE__ );
	
	int size = this->data.size();

	Column<T> C_rv = *this;
	vector<T>& colRef = C_rv.getVec();
	
	for(int i=0; i < size; i++)
	{
		colRef[i] -= c[i];		
	}
	return C_rv;
}



#endif // COLUMN_H
