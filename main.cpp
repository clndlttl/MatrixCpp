#include "VectorTypes.h"
#include "MatrixTypes.h"

using namespace std;

int main()
{
	using T = double;

	vector<T> mat = { 1, 2, 4,
					  0, 1, -1,
   					  0, 0, 1  };

	Square<T> M( 3, mat );
	M.show();

	Square<T> Minv = M.inv();
	Minv.show();

}

