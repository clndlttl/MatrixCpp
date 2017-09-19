#include "VectorTypes.h"
#include "MatrixTypes.h"

using namespace std;

int main()
{
	using T = double;

	vector<T> mat = { 1, 0, 0, 0,
					  0, 1, 0, 0,
   					  0, 0, 1, 0,
   					  2, 0, 0, 1 };

	Square<T> M( 4, mat );
	M.show();

	Eye<T> I( 4 );
	I.show();

	Square<T> M2( M*I );
	M2.show();

	//Square<T> Minv = lu.invert();
	//Minv.show();
}

