#include "VectorTypes.h"
#include "MatrixTypes.h"

using namespace std;

int main()
{
	using T = double;

	vector<T> mat = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

	vector<T> row = { 3, 4, 5 };
	vector<T> col = { 1, 1, 1 };

	Square<T> M( 3, mat );
	M.show();

	Row<T> r( row );
	Column<T> c( col );

	( 2 * M ).show();
	( 2.0 * M ).show();

	( 2 * c ).show();
	( 2.0 * c ).show();

	( 2 * r ).show();
	( 2.0 * r ).show();

	( M * c ).show();

}

