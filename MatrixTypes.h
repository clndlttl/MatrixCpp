#ifndef MATRIXTYPES_H
#define MATRIXTYPES_H

#include "Matrix.h"

template <class T>
class Diag : public Matrix2D<T>
{
  public:
	Diag<T>( const vector<T>& v ) : Matrix2D<T>( v.size(), v.size() )
	{
		int size = v.size();

		for(int i=0; i < size; i++)
		{
			this->matrix[i][i] = v[i];
		}
	}	
};

template <class T>
class Eye : public Matrix2D<T>
{
  public:
	Eye<T>( int size ) : Matrix2D<T>( size, size ) 
	{
		for(int i=0; i < size; i++)
		{
			this->matrix[i][i] = static_cast<T>(1);
		}
	}
};





#endif
