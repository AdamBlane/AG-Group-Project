#pragma once

#include <glm\glm.hpp>
#include "glew.h"

// Class which hold Vertex Information
class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
	}

	// Getters
	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }
private:
	glm::vec3 pos;
	glm::vec2 texCoord;
};

// Class which holds Mesh Information
class Mesh
{
public:
	enum type3D { CUBOID, BOX, WALL };

	Mesh(type3D thisType);
	//Mesh(const Mesh& other);
	void Draw();

	void createMesh();
	
	void setPosition(GLfloat newX, GLfloat newY, GLfloat newZ);
	glm::vec3 getPosition();
	void size(GLfloat side_x, GLfloat side_y = 0.2f, GLfloat side_z = 0.2f);
	glm::vec3 getSize();

	virtual ~Mesh();

private:
	
	void operator=(const Mesh& other);

	void createCube();
	void createCuboid();
	void createWall();
	void generateMesh(Vertex* vertices, unsigned int numVertices);


	type3D type3d = CUBOID;
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	GLfloat side1 = 0.2f;
	GLfloat side2 = 0.2f;
	GLfloat side3 = 0.2f;

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};

