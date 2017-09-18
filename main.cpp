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

	LU<T> lu( 4, mat );
	Matrix2D<T> inv = lu.invert();
	inv.show();
}

