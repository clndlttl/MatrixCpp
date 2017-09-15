#ifndef MATRIXTYPES_H
#define MATRIXTYPES_H

#include "Matrix.h"

template <class T>
class Diag : public Matrix2D
{
  public:
	Diag<T>( const vector<T>& v )
	{
		numRows = numCols = v.size();

		for(int i=0; i < numRows; i++)
		{
			vector<T> tmp( numCols );
			tmp[i] = v[i];
			matrix.push_back( tmp );
		}
	}	
}

template <class T>
class Eye : public Matrix2D
{
  public:
	Eye<T>( int size )
	{
		numRows = numCols = size;

		for(int i=0; i < numRows; i++)
		{
			vector<T> tmp( numCols );
			tmp[i] = static_cast<T>(1);
			matrix.push_back( tmp );
		}
	}
}





#endif
