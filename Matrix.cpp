#include "Matrix.h"

using namespace std;

Row::Row( vector<T>& v )
{
	for(auto i : v)
	{
		data.push_back(i);
	}
}

Column::Column( vector<T>& v )
{
	for(auto i : v)
	{
		data.push_back(i);
	}
}

Matrix2D::Matrix2D( int nRows, int nCols, vector<T>& v )
{
	nr = nRows;
	nc = nCols;

	auto p = v.begin();

	for(int r = 0; r < nRows; r++)
	{
		vector<T> newRowVec (p,p+nCols);
		data.push_back( newRowVec );

		// incr p
		p += nCols;
	}
}

