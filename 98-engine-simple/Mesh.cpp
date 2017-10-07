#include "Mesh.h"
#include <vector>

using namespace glm;

Mesh::Mesh(type3D thisType)
{
	type3d = thisType;
}

void Mesh::generateMesh(Vertex* vertices, unsigned int numVertices)
{
	m_drawCount = numVertices;
	//m_drawCount = numIndices;
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	// Used to pass texture info to the mesh
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	positions.reserve(numVertices);
	texCoords.reserve(numVertices);

	for (unsigned int i = 0; i < numVertices; i++)
	{
		positions.push_back(*vertices[i].GetPos());
		texCoords.push_back(*vertices[i].GetTexCoord());
	}

	// Create required buffers
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

	// Set Position values
	// Take this buffer in as an array
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	// Put the data on the GPU - size of vertex * number of vertices
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	// Tell OpenGL what to do with the position data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Set Tex values
	// Take this buffer in as an array
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	// Put the data on the GPU - size of vertex * number of vertices
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

	// Tell OpenGL what to do with the position data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	//// Put the data on the GPU - size of vertex * number of vertices
	//glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_QUADS, 0, m_drawCount);

	glBindVertexArray(0);
}

void Mesh::createMesh()
{
	switch (type3d) {
	case CUBOID:
		createCube();
		break;
	case BOX:
		createCube();
		break;
	default:
		createCube();
		break;
	}

}

void Mesh::createCube()
{
	Vertex vertices[] = 
	{ 
		// back face
		Vertex(vec3(position.x, position.y + side1, position.z - side1), vec2(0.0, 1.0)), // top left
		Vertex(vec3(position.x + side1, position.y + side1, position.z - side1), vec2(1.0, 1.0)), // top right
		Vertex(vec3(position.x + side1, position.y, position.z - side1), vec2(1.0, 0.0)), // bottom right
		Vertex(vec3(position.x, position.y, position.z - side1), vec2(0.0, 0.0)), // bottom left

		// front face
		Vertex(vec3(position.x, position.y + side1, position.z), vec2(0.0, 1.0)), // top left
		Vertex(vec3(position.x + side1, position.y + side1, position.z), vec2(1.0, 1.0)), // top right
		Vertex(vec3(position.x + side1, position.y, position.z), vec2(1.0, 0.0)), // bottom right
		Vertex(vec3(position.x, position.y, position.z), vec2(0.0, 0.0)), // bottom left

		// left face
		Vertex(vec3(position.x, position.y + side1, position.z), vec2(0.0, 1.0)), // top left
		Vertex(vec3(position.x, position.y + side1, position.z - side1), vec2(1.0, 1.0)), // top right
		Vertex(vec3(position.x, position.y, position.z - side1), vec2(1.0, 0.0)), // bottom right
		Vertex(vec3(position.x, position.y, position.z), vec2(0.0, 0.0)), // bottom left
	
		// right face
		Vertex(vec3(position.x + side1, position.y + side1, position.z), vec2(0.0, 1.0)), // top left
		Vertex(vec3(position.x + side1, position.y + side1, position.z - side1), vec2(1.0, 1.0)), // top right
		Vertex(vec3(position.x + side1, position.y, position.z - side1), vec2(1.0, 0.0)), // bottom right
		Vertex(vec3(position.x + side1, position.y, position.z), vec2(0.0, 0.0)), // bottom left

		// top face
		Vertex(vec3(position.x, position.y + side1, position.z), vec2(0.0, 1.0)), // top left
		Vertex(vec3(position.x, position.y + side1, position.z - side1), vec2(1.0, 1.0)), // top right
		Vertex(vec3(position.x + side1, position.y + side1, position.z - side1), vec2(1.0, 0.0)), // bottom right
		Vertex(vec3(position.x + side1, position.y + side1, position.z), vec2(0.0, 0.0)), // bottom left
	
		// bottom face
		Vertex(vec3(position.x, position.y, position.z), vec2(0.0, 1.0)), // top left
		Vertex(vec3(position.x, position.y, position.z - side1), vec2(1.0, 1.0)), // top right
		Vertex(vec3(position.x + side1, position.y, position.z - side1), vec2(1.0, 0.0)), // bottom right
		Vertex(vec3(position.x + side1, position.y, position.z), vec2(0.0, 0.0))  // bottom left
	};

	Mesh::generateMesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
}

void Mesh::setPosition(GLfloat newX, GLfloat newY, GLfloat newZ)
{
	position = vec3(newX, newY, newZ);
}

glm::vec3 Mesh::getPosition()
{
	return vec3(position);
}


void Mesh::size(GLfloat side_x, GLfloat side_y, GLfloat side_z)
{
	switch (type3d) {
	case CUBOID:
		side1 = side_x;
		side2 = side_y;
		side3 = side_z;
		break;
	case BOX:
		side1 = side_x;
		side2 = side_x;
		side3 = side_x;
		break;
	default:
		side1 = side_x;
		side2 = side_y;
		side3 = side_z;
		break;
	}
}

glm::vec3 Mesh::getSize()
{
	return vec3(side1, side2, side3);
}
