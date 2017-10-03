#include "geometry_builder.h"

geometry_builder::geometry_builder(type3D thisType)
{
	type3d = thisType;
}

geometry_builder::~geometry_builder()
{
}

void geometry_builder::createCube()
{
	
	GLfloat vertices[] =
	{
		// front face
		position.x, position.y + side1, position.z, // top left
		position.x + side1, position.y + side1, position.z, // top right
		position.x + side1, position.y, position.z, // bottom right
		position.x, position.y, position.z, // bottom left

		// back face
		position.x, position.y + side1, position.z - side1, // top left
		position.x + side1, position.y + side1, position.z - side1, // top right
		position.x + side1, position.y, position.z - side1, // bottom right
		position.x, position.y, position.z - side1, // bottom left

		// left face
		position.x, position.y + side1, position.z, // top left
		position.x, position.y + side1, position.z - side1, // top right
		position.x, position.y, position.z - side1, // bottom right
		position.x, position.y, position.z, // bottom left

		// right face
		position.x + side1, position.y + side1, position.z, // top left
		position.x + side1, position.y + side1, position.z - side1, // top right
		position.x + side1, position.y, position.z - side1, // bottom right
		position.x + side1, position.y, position.z, // bottom left

		// top face
		position.x, position.y + side1, position.z, // top left
		position.x, position.y + side1, position.z - side1, // top right
		position.x + side1, position.y + side1, position.z - side1, // bottom right
		position.x + side1, position.y + side1, position.z, // bottom left

		// bottom face
		position.x, position.y, position.z, // top left
		position.x, position.y, position.z - side1, // top right
		position.x + side1, position.y, position.z - side1, // bottom right
		position.x + side1, position.y, position.z  // bottom left
	};


	GLfloat colour[] =
	{
		255, 0, 0,
		0, 255, 0,
		0, 0, 255
	};

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(colour[0], colour[2], colour[2]);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void geometry_builder::createCuboid()
{
	GLfloat vertices[] =
	{
		// front face
		position.x, position.y + side1, position.z, // top left
		position.x + side2, position.y + side1, position.z, // top right
		position.x + side2, position.y, position.z, // bottom right
		position.x, position.y, position.z, // bottom left

		// back face
		position.x, position.y + side1, position.z - side2, // top left
		position.x + side2, position.y + side1, position.z - side2, // top right
		position.x + side2, position.y, position.z - side2, // bottom right
		position.x, position.y, position.z - side2, // bottom left

		// left face
		position.x, position.y + side1, position.z, // top left
		position.x, position.y + side1, position.z - side2, // top right
		position.x, position.y, position.z - side2, // bottom right
		position.x, position.y, position.z, // bottom left

		// right face
		position.x + side2, position.y + side1, position.z, // top left
		position.x + side2, position.y + side1, position.z - side2, // top right
		position.x + side2, position.y, position.z - side2, // bottom right
		position.x + side2, position.y, position.z, // bottom left

		// top face
		position.x, position.y + side1, position.z, // top left
		position.x, position.y + side1, position.z - side2, // top right
		position.x + side2, position.y + side1, position.z - side2, // bottom right
		position.x + side2, position.y + side1, position.z, // bottom left

		// bottom face
		position.x, position.y, position.z, // top left
		position.x, position.y, position.z - side2, // top right
		position.x + side2, position.y, position.z - side2, // bottom right
		position.x + side2, position.y, position.z  // bottom left

	};


	GLfloat colour[] =
	{
		255, 0, 0,
		0, 255, 0,
		0, 0, 255
	};

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(colour[0], colour[2], colour[2]);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void geometry_builder::draw()
{
	switch (type3d) {
	case CUBOID:
		createCuboid();
		break;
	case BOX:
		createCube();
		break;
	default:
		createCube();
		break;
	}
}

void geometry_builder::setPosition(GLfloat newX, GLfloat newY, GLfloat newZ)
{
	//glTranslatef(newX, newY, newZ);
	position = vec3(newX, newY, newZ);

}

vec3 geometry_builder::getPosition()
{
	return vec3(position);
}

void geometry_builder::scale(GLfloat side)
{
	side1 = side;
}

GLfloat geometry_builder::getScale()
{
	return GLfloat(side1);
}

void geometry_builder::translate(vec3 &translateVector)
{
	position += translateVector;
}
