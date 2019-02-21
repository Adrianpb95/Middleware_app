/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
10 / 06 / 2018
*/


#ifndef ELEMENTS_HEADER
#define ELEMENTS_HEADER

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <vector>
#include "Texture.hpp"
#include <nanogui/opengl.h>

////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
using std::vector;
namespace example
{
	////////////////////////////////////////////////////////////
	//ELEMENTOS GENERICOS 
	////////////////////////////////////////////////////////////

	struct Point2f
	{
		float x, y;
	};

	struct Point3f
	{
		float x, y, z;
	};

	struct Point4f
	{
		float x, y, z, w;
	};

	typedef vector< Point4f  > Color;
	typedef vector< Point3f  > Vertex;
	typedef vector< Point2f  > TextCoord;
	typedef vector< unsigned > Index;
	typedef Point2f Coord2D;
	typedef Point3f Coord3D;
}

#endif