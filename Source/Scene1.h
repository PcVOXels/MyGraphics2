#ifndef SCENE_1_H
#define SCENE_1_H

#include "Scene.h"

class Scene1 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_TRIANGLE_1,
		GEO_TRIANGLE_2,
		GEO_TRIANGLE_3,
		NUM_GEOMETRY,
	};

	enum GEOMETRY_CAR
	{
		CAR_TRIANGLE_1,
		NUM_GEMOMETRY,
	};

public:
	Scene1();
	~Scene1();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_ColorBuffer[NUM_GEOMETRY];
	unsigned m_programID;

	unsigned m_vertexArrayTriangle2;
	unsigned m_vertexArrayTriangle3;
};

#endif