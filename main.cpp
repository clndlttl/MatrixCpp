#include "VectorTypes.h"
#include "MatrixTypes.h"

using namespace std;

int main()
{
	using T = double;

	vector<T> mat = { 1, 0, 2,
					  2,-1, 4,
   					  4, 1, 7 };

	Row<T> row( mat );
	row.show();
	Column<T> col = row.t(); // not working...
	col.show();

	Column<T> col2( mat );
	col2.show();
	Row<T> row2 = col2.t();
	row2.show();

}

