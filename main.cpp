#include "Matrix.h"
#include "MatrixTypes.h"

int main()
{
	using T = double;

	vector<T> mat = { 1, 0, 2,
					  2, -1, 3,
   					  4, 1, 8 };
	
	Matrix2D<T> M( 3,3,mat );
	M.show();

	Matrix2D<T> inv = M^-1;
	inv.show();

	Matrix2D<T> eye1 = (M^(-1)) * M;
	eye1.show();

	Matrix2D<T> eye2 = M * (M^(-1));
	eye2.show();

}

