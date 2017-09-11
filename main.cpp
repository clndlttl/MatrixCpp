#include "Matrix.h"

using namespace std;

int main()
{
	vector<int> m = {1,2,3,4,5,6,7,8,9};
	
	Matrix2D<int> M(3,3,m);

	M.show();
}
