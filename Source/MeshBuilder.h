#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#pragma message ("XXX MeshBuilder:before imports")
#include "Mesh.h"
#include "Vertex.h"
#pragma message ("XXX MeshBuilder:after imports")

/******************************************************************************/
/*!
Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	Mesh test;
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	//static Mesh* GenerateQuad(const std::string &meshName, float lengthX, float lengthY);
	static Mesh* GenerateQuad(const std::string &meshName, Color color);
	static Mesh* GenerateCube(const std::string &meshName, Color color);
	static Mesh* GenerateCircle(const std::string &meshName, Color color, unsigned numSlices = 36 /*, float radius = 1.f*/);
	static Mesh* GenerateRing(const std::string &meshName, Color color, unsigned numSlices, unsigned innerRadius);
	static Mesh* GenerateSphere(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices);
};

#endif