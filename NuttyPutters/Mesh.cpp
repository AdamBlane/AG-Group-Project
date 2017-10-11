#include "Mesh.h"
#include <vector>

Mesh::Mesh(const std::string& fileName)
{
	IndexedModel model = OBJModel(fileName).ToIndexedModel();
	InitMesh(model);
}

Mesh::Mesh(typeShape shape, glm::vec3 newPosition, GLfloat size1, GLfloat size2, GLfloat size3)
{
	thisShape = shape;
	position = newPosition;
	side1 = size1;
	side2 = size2;
	side3 = size3;
	halfSide1 = side1 / 2.0f;
	halfSide2 = side2 / 2.0f;
	halfSide3 = side3 / 2.0f;

	chooseGeometry();
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
	}

	for (unsigned int i = 0; i < numIndices; i++)
	{
		model.indices.push_back(indices[i]);
	}

	InitMesh(model);
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::chooseGeometry()
{
	switch (thisShape)
	{
	case TRIANGLE_REGULAR:
		triangleR();
		break;
	case TRIANGLE_IRREGULAR:
		triangleI();
		break;
	case QUAD:
		quad();
		break;
	case RECTANGLE:
		rectangle();
		break;
	case PLANE:
		plane();
		break;
	case BOX:
		box();
		break;
	case CUBOID:
		cuboid();
		break;
	default:
		cuboid();
		break;
	}
}

void Mesh::triangleR()
{
}

void Mesh::triangleI()
{
}

void Mesh::quad()
{
}

void Mesh::rectangle()
{
}

void Mesh::plane()
{
}

void Mesh::box()
{
}

void Mesh::cuboid()
{
	Vertex vertices[] = {
		/////////FRONT
		//TR1
		Vertex(glm::vec3(position.x - halfSide1, position.y - halfSide2, position.z + halfSide3), glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(position.x + halfSide1, position.y - halfSide2, position.z + halfSide3), glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(position.x - halfSide1, position.y + halfSide2, position.z + halfSide3), glm::vec2(0.0, 1.0)),
		//TR2
		Vertex(glm::vec3(position.x - halfSide1, position.y + halfSide2, position.z + halfSide3), glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(position.x + halfSide1, position.y - halfSide2, position.z + halfSide3), glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(position.x + halfSide1, position.y + halfSide2, position.z + halfSide3), glm::vec2(1.0, 1.0)),

		/////////BACK
		//TR1
		Vertex(glm::vec3(position.x - halfSide1, position.y - halfSide2, position.z - halfSide3), glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(position.x - halfSide1, position.y + halfSide2, position.z - halfSide3), glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(position.x + halfSide1, position.y - halfSide2, position.z - halfSide3), glm::vec2(1.0, 0.0)),
		//TR2
		Vertex(glm::vec3(position.x - halfSide1, position.y + halfSide2, position.z - halfSide3), glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(position.x + halfSide1, position.y + halfSide2, position.z - halfSide3), glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(position.x + halfSide1, position.y - halfSide2, position.z - halfSide3), glm::vec2(1.0, 0.0)),

		/////////LEFT
		//TR1
		Vertex(glm::vec3(position.x - halfSide1, position.y - halfSide2, position.z - halfSide3), glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(position.x - halfSide1, position.y - halfSide2, position.z + halfSide3), glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(position.x - halfSide1, position.y + halfSide2, position.z - halfSide3), glm::vec2(0.0, 1.0)),
		//TR2
		Vertex(glm::vec3(position.x - halfSide1, position.y - halfSide2, position.z + halfSide3), glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(position.x - halfSide1, position.y + halfSide2, position.z + halfSide3), glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(position.x - halfSide1, position.y + halfSide2, position.z - halfSide3), glm::vec2(0.0, 1.0)),

		/////////RIGHT
		//TR1
		Vertex(glm::vec3(position.x + halfSide1, position.y - halfSide2, position.z - halfSide3), glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(position.x + halfSide1, position.y + halfSide2, position.z - halfSide3), glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(position.x + halfSide1, position.y - halfSide2, position.z + halfSide3), glm::vec2(1.0, 0.0)),
		//TR2
		Vertex(glm::vec3(position.x + halfSide1, position.y - halfSide2, position.z + halfSide3), glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(position.x + halfSide1, position.y + halfSide2, position.z - halfSide3), glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(position.x + halfSide1, position.y + halfSide2, position.z + halfSide3), glm::vec2(1.0, 1.0)),

		/////////TOP
		//TR1
		Vertex(glm::vec3(position.x - halfSide1, position.y + halfSide2, position.z + halfSide3), glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(position.x + halfSide1, position.y + halfSide2, position.z + halfSide3), glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(position.x - halfSide1, position.y + halfSide2, position.z - halfSide3), glm::vec2(0.0, 1.0)),
		//TR2
		Vertex(glm::vec3(position.x + halfSide1, position.y + halfSide2, position.z + halfSide3), glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(position.x + halfSide1, position.y + halfSide2, position.z - halfSide3), glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(position.x - halfSide1, position.y + halfSide2, position.z - halfSide3), glm::vec2(0.0, 1.0)),

		/////////BOTTOM
		//TR1
		Vertex(glm::vec3(position.x - halfSide1, position.y - halfSide2, position.z + halfSide3), glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(position.x - halfSide1, position.y - halfSide2, position.z - halfSide3), glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(position.x + halfSide1, position.y - halfSide2, position.z + halfSide3), glm::vec2(1.0, 0.0)),
		//TR2
		Vertex(glm::vec3(position.x + halfSide1, position.y - halfSide2, position.z + halfSide3), glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(position.x - halfSide1, position.y - halfSide2, position.z - halfSide3), glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(position.x + halfSide1, position.y - halfSide2, position.z - halfSide3), glm::vec2(1.0, 1.0))
	};

	unsigned int indices[] = {
		0, 1, 2, 3, 4, 5,
		6, 7, 8, 9, 10, 11,
		12, 13, 14, 15, 16, 17,
		18, 19, 20, 21, 22, 23,
		24, 25, 26, 27, 28, 29,
		30, 31, 32, 33, 34, 35
	};

	generateMesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
}

void Mesh::generateMesh(Vertex * vertices, unsigned int numVertices, unsigned int * indices, unsigned int numIndices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
	}

	for (unsigned int i = 0; i < numIndices; i++)
	{
		model.indices.push_back(indices[i]);
	}

	InitMesh(model);

}

void Mesh::InitMesh(const IndexedModel& model)
{
	m_drawCount = model.indices.size();

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	// Create required buffers
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

	// Set Position values
	// Take this buffer in as an array
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	// Put the data on the GPU - size of vertex * number of vertices
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);
	// Tell OpenGL what to do with the position data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Set Tex values
	// Take this buffer in as an array
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	// Put the data on the GPU - size of vertex * number of vertices
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);
	// Tell OpenGL what to do with the position data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Set Index values
	// Take this buffer in as an array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	// Put the data on the GPU - size of vertex * number of vertices
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);

	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
