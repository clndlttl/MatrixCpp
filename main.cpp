#include "VectorTypes.h"
#include "MatrixTypes.h"

using namespace std;

int main()
{
	using T = double;

	vector<T> mat = { 0, 0, 2,
					  1, 0, 0,
   					  0, 3, 0  };

	vector<T> row = { 7,-8, 2 };
	Row<T> r( row );

	vector<T> col = { 7,-8, 2 };
	Column<T> c( col );

	Square<T> M( 3, mat );

	T res = r*M*c;
	cout << res << endl;
}

