#include "VectorTypes.h"
#include "MatrixTypes.h"

using namespace std;

int main()
{
	using T = double;

	vector<T> y_val = { 1.1, 1, 1, 0, 1, 1, 0, 0, 1 };

	Square<T> M( 3, y_val );
	M.show();

	Row<T> r( y_val );
	Column<T> c( y_val );
		
	( 5 * M ).show();
	( 4 * r ).show();
	( 3 * c ).show();

}

