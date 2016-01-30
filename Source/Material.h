#ifndef MATERIAL_H
#define MATERIAL_H

#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
//#include "MeshBuilder.h"

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"

struct Component
{
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f)
	{
		Set(r, g, b);
	}
	void Set(float r, float g, float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}
};

struct Material
{
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;
	// To do: add a constructor
	Material()
	{
	}
};

#endif