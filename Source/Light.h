#ifndef LIGHT_H
#define LiGHT_H

#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"

struct Light
{
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	// To do: add a constructor
	Light(){};
};

#endif