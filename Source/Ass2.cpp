#include "Ass2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

Ass2::Ass2()
{
}

Ass2::~Ass2()
{
}

void Ass2::Init()
{
	// Init VBO here

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Load vertex and fragment shaders
	m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
	// Use our shader
	glUseProgram(m_programID);
	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	//variable to rotate geometry
	rotateAngle = 0;

	isArmRotating = true;
	isLegRotating = true;
	isTenticleRotating = true;
	rotateArmAngle = 0;
	rotateLegAngle = 0;
	rotateTenticleAngle = 0;
	jfBody = 90;

	//Initialize camera settings
	camera.Init(Vector3(4, 3, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GROUND_MESH] = MeshBuilder::GenerateQuad("floor", Color (0.62f, 0.76f, 0.25f));

	meshList[GEO_SB_BODY] = MeshBuilder::GenerateCube("sb_body", Color(1.0f, 1.0f, 0.0f));
	meshList[GEO_SB_PANTS] = MeshBuilder::GenerateCube("sb_pants", Color(0.8f, 0.4f, 0.12f));
	meshList[GEO_SB_HAND] = MeshBuilder::GenerateCube("sb_hands", Color(1.0f, 1.0f, 0.0f));
	meshList[GEO_SB_LEG] = MeshBuilder::GenerateCube("sb_legs", Color(1.0f, 1.0f, 0.0f));
	meshList[GEO_SB_EYE_BALL] = MeshBuilder::GenerateSphere("sb_eye_ball(white part[outer])", Color(1, 1, 1), 19 /*half this from numSlices for hemisphere*/, 36);
	meshList[GEO_SB_EYE_PUPIL] = MeshBuilder::GenerateSphere("sb_eye_pupil(black part[inner])", Color(0, 0, 0), 19 /*half this from numSlices for hemisphere*/, 36);

	meshList[GEO_JF_BODY] = MeshBuilder::GenerateSphere("jf_body", Color(1, 0, 1), 19 /*half this from numSlices for hemisphere*/, 36);
	meshList[GEO_JF_TENTICLE] = MeshBuilder::GenerateCube("jf_tenticle", Color(1.0f, 1.0f, 0.0f));




	//meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("circle", Color(1, 0, 0), 36);
	//meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(1, 0, 0), 36, 5);
	//meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 1), 36 /*half this from numSlices for hemisphere*/, 36);
	//meshList[GEO_SPHERE1] = MeshBuilder::GenerateSphere("sphere1", Color(1, 0, 1), 36, 36);

	// setup intial model

	Mtx44 translate, rotation, scale;
	//Mtx44 translateSBpants, scaleSBpants;

	// Body
	scale.SetToScale(2.0f, 2.5f, 0.8f);
	translate.SetToIdentity();
	//translate.SetToTranslation();
	sbBodyModel = translate * scale;

	// Pants
	scale.SetToScale(2.0f, 0.8f, 0.8f);
	translate.SetToTranslation(0.0f, -1.65f, 0.0f);
	sbPantsModel = translate * scale;

	//// Hands size
	//scale.SetToScale(1.0f, 0.2f, 0.2f);

	//// Right hand
	//translate.SetToTranslation(1.5f, -1.0f, 0.0f);
	//sbRightHandModel = translate * scale;

	//// Left hand
	//translate.SetToTranslation(-1.5f, -1.0f, 0.0f);
	//sbLeftHandModel = translate * scale;
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void Ass2::Update(double dt)
{
	camera.Update(dt);

	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	rotateAngle += (float)(10 * dt);

	// Arm rotation check
	if (isArmRotating)
	{
		if (rotateArmAngle < 45.0f)
		{
			rotateArmAngle += (float)(20 * dt);
		}
		else
		{
			isArmRotating = false;
		}
	}
	else
	{
		if (rotateArmAngle > -45.0f)
		{
			rotateArmAngle -= (float)(20 * dt);
		}
		else
		{
			isArmRotating = true;
		}
	}

	// Leg rotation check
	if (isLegRotating)
	{
		if (rotateLegAngle < 45.0f)
		{
			rotateLegAngle += (float)(20 * dt);
		}
		else
		{
			isLegRotating = false;
		}
	}
	else
	{
		if (rotateLegAngle > -45.0f)
		{
			rotateLegAngle -= (float)(20 * dt);
		}
		else
		{
			isLegRotating = true;
		}
	}

	// Tenticle rotation check
	if (isTenticleRotating)
	{
		if (rotateTenticleAngle < 25.0f)
		{
			rotateTenticleAngle += (float)(20 * dt);
		}
		else
		{
			isTenticleRotating = false;
		}
	}
	else
	{
		if (rotateTenticleAngle > 0.0f)
		{
			rotateTenticleAngle -= (float)(20 * dt);
		}
		else
		{
			isTenticleRotating = true;
		}
	}
}



void Ass2::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Temp variables
	Mtx44 translate, rotate, scale, translatePivotToOrigin;
	Mtx44 MVP;

	//These will be replaced by matrix stack soon
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 animation;
	Mtx44 jfAnimation;
	Mtx44 armAnim;
	Mtx44 legAnim;
	Mtx44 tenticleAnim;

	//Set all matrices to identity
	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	armAnim.SetToIdentity();
	legAnim.SetToIdentity();
	tenticleAnim.SetToIdentity();

	//Set view matrix using camera settings
	view.SetToLookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);

	//Set projection matrix to perspective mode
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f); //FOV, Aspect Ratio, Near plane, Far plane

	model.SetToIdentity();
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_AXES]->Render();

	// Sponge bob parenting
	rotate.SetToRotation(rotateAngle, 0, 1, 0);
	translate.SetToTranslation(0.0f, 3.0f, 0.0f);
	animation = /*rotate **/ translate;

	// Jelly fish parenting
	translate.SetToTranslation(1.0f, 1.0f, 1.0f);
	jfAnimation = translate;

	// Gound Mesh
	scale.SetToScale(50.0f, 50.0f, 50.0f);
	model = scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GROUND_MESH]->Render();

	/* Spongebob */

	// Body
	model = animation * sbBodyModel;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_SB_BODY]->Render();

	// Pants
	model = animation * sbPantsModel;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_SB_PANTS]->Render();

	// Arm animation (Right)
	scale.SetToScale(1.0f, 0.2f, 0.2f);
	translatePivotToOrigin.SetToTranslation(0.5f, 0.0f, 0.0f);
	armAnim.SetToRotation(rotateArmAngle, 0, 0, 1);
	translate.SetToTranslation(1.0f, -1.0f, 0.0f);

	// Right Hand
	model = animation * translate * armAnim * translatePivotToOrigin * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_SB_HAND]->Render();

	// Arm animation (Left)
	translatePivotToOrigin.SetToTranslation(-0.5f, 0.0f, 0.0f);
	armAnim.SetToRotation(-rotateArmAngle, 0, 0, 1);
	translate.SetToTranslation(-1.0f, -1.0f, 0.0f);

	// Left Hand
	model = animation * translate * armAnim * translatePivotToOrigin * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_SB_HAND]->Render();

	// Leg animation (Right)
	scale.SetToScale(0.2f, 1.0f, 0.2f);
	translatePivotToOrigin.SetToTranslation(0.0f, -0.5f, 0.0f);
	legAnim.SetToRotation(rotateLegAngle, 1, 0, 0);
	translate.SetToTranslation(0.5f, -2.0f, 0.0f);

	// Right Leg
	model = animation * translate * legAnim * translatePivotToOrigin * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_SB_LEG]->Render();

	// Leg animation (Left)
	scale.SetToScale(0.2f, 1.0f, 0.2f);
	translatePivotToOrigin.SetToTranslation(0.0f, -0.5f, 0.0f);
	legAnim.SetToRotation(-rotateLegAngle, 1, 0, 0);
	translate.SetToTranslation(-0.5f, -2.0f, 0.0f);

	// Left Leg
	model = animation * translate * legAnim * translatePivotToOrigin * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_SB_LEG]->Render();

	/* Jelly Fish */

	// Body
	rotate.SetToRotation(-90, 1, 0, 0);
	translate.SetToTranslation(-3.0f, 5.0f, -1.0f);
	scale.SetToScale(0.5f, 0.5f, 0.5f);

	model = animation * jfAnimation * /*translate **/  scale * rotate;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_JF_BODY]->Render();

	// Tenticle 1 (TOP) [Animation]
	translatePivotToOrigin.SetToTranslation(-0.5f, 0.0f, 0.0f);
	tenticleAnim.SetToRotation(-rotateTenticleAngle, 0, 0, 1);
	//translate.SetToTranslation(-1.0f, -1.0f, 0.0f);

	// Tenticle 1 (TOP) [Position]
	translate.SetToTranslation(-0.05f, -0.25f, -0.05f);
	scale.SetToScale(0.1f, 0.5f, 0.1f);

	model = animation * tenticleAnim * translatePivotToOrigin * jfAnimation * translate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_JF_TENTICLE]->Render();
	
	// Tenticle 2 (TOP)
	translate.SetToTranslation(0.25f, -0.25f, -0.25f);
	scale.SetToScale(0.1f, 0.5f, 0.1f);

	model = animation * jfAnimation * translate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_JF_TENTICLE]->Render();

	// Tenticle 3 (TOP)
	translate.SetToTranslation(-0.25f, -0.25f, 0.25f);
	scale.SetToScale(0.1f, 0.5f, 0.1f);

	model = animation * jfAnimation * translate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_JF_TENTICLE]->Render();

	// Tenticle 4 (TOP)
	translate.SetToTranslation(0.25f, -0.25f, 0.25f);
	scale.SetToScale(0.1f, 0.5f, 0.1f);

	model = animation * jfAnimation * translate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_JF_TENTICLE]->Render();

}

void Ass2::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
