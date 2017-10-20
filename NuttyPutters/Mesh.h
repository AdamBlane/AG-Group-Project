#pragma once
// External
#include "glew_glfw.h"
#include "include\glm-0.9.8.5\glm\glm\glm.hpp"
// Interal
#include "obj_loader.h"



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
	enum typeShape
	{
		TRIANGLE_REGULAR,
		TRIANGLE_IRREGULAR,
		QUAD,
		RECTANGLE,
		PLANE,
		BOX,
		CUBOID

	};
	Mesh() {};
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	Mesh(const std::string& fileName);
	Mesh(typeShape shape, glm::vec3 newPosition, GLfloat size1, GLfloat size2 = 1.0f, GLfloat size3 = 1.0f);

	void cuboid();

	void InitMesh(const IndexedModel& model);

	void Draw();

	virtual ~Mesh();

	glm::vec3 getPos() { return position; }

private:
	Mesh(const Mesh& other);
	void operator=(const Mesh& other);

	typeShape thisShape = CUBOID;

	void chooseGeometry();

	void triangleR();
	void triangleI();
	void quad();
	void rectangle();
	void plane();
	void box();


	void generateMesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

	GLfloat side1 = 1.0f;
	GLfloat side2 = 1.0f;
	GLfloat side3 = 1.0f;
	GLfloat halfSide1 = 0.5f;
	GLfloat halfSide2 = 0.5f;
	GLfloat halfSide3 = 0.5f;


	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};

