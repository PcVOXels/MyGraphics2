#ifndef SCENE_TEXTURE_H
#define SCENE_TEXTURE_H

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"

class SceneTexture : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		GEO_CIRCLE,
		GEO_RING,
		GEO_SPHERE,

		// Spongebob parts~~
		GROUND_MESH,
		GEO_SB_BODY,
		GEO_SB_PANTS,
		GEO_SB_HAND,
		GEO_SB_LEG,
		GEO_SB_EYE_BALL,
		GEO_SB_EYE_PUPIL,

		// Jelly fish parts~~
		GEO_JF_BODY,
		GEO_JF_TENTICLE,

		NUM_GEOMETRY,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TOTAL,
	};
public:
	SceneTexture();
	~SceneTexture();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_programShading;
	unsigned m_programTexture;
	unsigned m_parameters[U_TOTAL];

	float rotateAngle;

	Camera camera;
};

#endif