#include "Scene1.h"
#include "GL\glew.h"

#include "shader.hpp"


Scene1::Scene1()
{
}

Scene1::~Scene1()
{
}

void Scene1::Init()
{
	// Init VBO here

	// Set the background color to dark blue
	glClearColor(0.0f, 0.6f, 0.9f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_ColorBuffer[0]);

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat vertex_buffer_data[] = 
	{
		//-0.5f, 0.5f, 0.0f,			// New code
		//-0.5, 0.0f, 0.0f,
		//0.0f, 0.5f, 0.0f,
		//0.0f, 0.0f, 0.0f,
		//0.5f, 0.5f, 0.0f,
		//0.5f, 0.0f, 0.0f
		-1.0f, -0.6f, 0.0f,			// Vertex 0 of triangle
		1.0f, -0.6f, 0.0f,			// Vertex 1 of triangle
		0.0f, -500.0f, 0.9f,			// Vertex 2 of triangle
	};

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);

	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

	// An array of 3 vectors which represents the colors of the 3 vertices
	static const GLfloat color_buffer_data[] = 
	{
		//1.0f, 0.0f, 0.0f,			// New code
		//1.0f, 0.0f, 0.0f,
		//1.0f, 0.0f, 0.0f,
		//1.0f, 0.0f, 0.0f,
		//1.0f, 0.0f, 0.0f,
		//1.0f, 0.0f, 0.0f,
		0.7f, 0.3f, 0.0f,			// Vertex 0 of triangle (RED), (GREEN), (Blue)
		0.7f, 0.3f, 0.0f,			// Vertex 1 of triangle 
		0.7f, 0.3f, 0.0f,			// Vertex 2 of triangle 
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	// Drawing the second triangle
		glGenVertexArrays(1, &m_vertexArrayTriangle2);
		glBindVertexArray(m_vertexArrayTriangle2);
		static const GLfloat vertex_buffer_Triangle2[] =
		{
			-0.92f, -0.6f, 0.0f,		// Vertex 0 of triangle
			-0.92f, 0.0f, 0.0f,			// Vertex 1 of triangle
			-0.8f, -0.6f, 0.0f,			// Vertex 2 of triangle		
		};
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_Triangle2), vertex_buffer_Triangle2, GL_STATIC_DRAW);
	// Coloring the second triagnle
		static const GLfloat color_buffer_Triangle2[] =
		{
			0.5f, 0.1f, 0.1f,
			0.5f, 0.1f, 0.1f,
			0.5f, 0.1f, 0.1f,
		};
		glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer[GEO_TRIANGLE_2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_Triangle2), color_buffer_Triangle2, GL_STATIC_DRAW);

	// Triangle 3
		glGenVertexArrays(1, &m_vertexArrayTriangle3);
		glBindVertexArray(m_vertexArrayTriangle3);
		static const GLfloat vertex_buffer_Triangle3[] =
		{
			-0.8f, 0.0f, 0.0f,			// Vertex 0 of triangle
			-0.92f, 0.0f, 0.0f,			// Vertex 1 of triangle
			-0.8f, -0.6f, 0.0f,			// Vertex 2 of triangle		
		};
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_Triangle3), vertex_buffer_Triangle3, GL_STATIC_DRAW);
	// Coloring the third triagnle
		static const GLfloat color_buffer_Triangle3[] =
		{
			0.5f, 0.1f, 0.1f,
			0.5f, 0.1f, 0.1f,
			0.5f, 0.1f, 0.1f,
		};
		glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer[GEO_TRIANGLE_3]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_Triangle3), color_buffer_Triangle3, GL_STATIC_DRAW);


	// Load vertex and fragment shaders
	m_programID = LoadShaders(
		"Shader//SimpleVertexShader.vertexshader",
		"shader//SimpleFragmentShader.fragmentshader");
	// Use our shader
	glUseProgram(m_programID);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
}

void Scene1::Update(double dt)
{
}

void Scene1::Render()
{
	// Render VBO here

	// Clear color buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0);		// 1st attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer
		(
		0,			// Attribute 0. Must watch the layout in the shadder. Usually 0 is for the vertex
		3,			// Size
		GL_FLOAT,	// Type
		GL_FALSE,	// Normalized?
		0,			// Stride
		0			// Array buffer offset
		);

	glEnableVertexAttribArray(1);		// 2nd attribute buffer : colors
	glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);	// Starting from vertex 0; 3 vertices = 1 triangle

	glDisableVertexAttribArray(1);

	// Second triangle
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
		glVertexAttribPointer
			(
				0,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				0
			);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer[GEO_TRIANGLE_2]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(1);

	// Third triangle
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
		glVertexAttribPointer
			(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			0
			);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer[GEO_TRIANGLE_3]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(1);

}

void Scene1::Exit()
{
	// Cleanup VBO here

	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_ColorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteVertexArrays(1, &m_vertexArrayTriangle2);
	glDeleteVertexArrays(1, &m_vertexArrayTriangle3);

	glDeleteProgram(m_programID);
}
