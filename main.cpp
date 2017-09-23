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

	Matrix2D<T> M( 3, 3, mat );
	M.addRow( row );
	M.addRow( col );

	M.show();
	M.t().show();
	
	Matrix2D<T> S = M.t() * M;

	S.show();
}

