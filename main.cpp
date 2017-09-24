#include "VectorTypes.h"
#include "MatrixTypes.h"

using namespace std;

int main()
{
	using T = double;

	vector<T> mat = { 2, 0, 2,
					  1, -5, 0,
   					  0, 3, 1  };

	vector<T> row = { 7,-8, 2 };
	Row<T> r( row );

	vector<T> col = { -4, 1, 3 };
	Column<T> c( col );

	Square<T> M( 3, mat );

	M.show();
}

