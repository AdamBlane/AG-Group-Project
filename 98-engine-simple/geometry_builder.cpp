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
}

//Mesh geometry_builder::createMesh()
//{
//	return Mesh();
//}

void geometry_builder::createCuboid()
{

	//// bottom face
	//  Vertex(vec3(0.0, 0.5, 0.0), vec2(0.0, 0.0)), // top left
	//	Vertex(vec3(0.0, 0.5, 0.0), vec2(0.0, 0.0)), // top right
	//	Vertex(vec3(0.0, 0.5, 0.0), vec2(0.0, 0.0)), // bottom right
	//	Vertex(vec3(0.0, 0.5, 0.0), vec2(0.0, 0.0))  // bottom left


	GLfloat vertices[] =
	{
		// front face
		position.x, position.y + side1, position.z, // top left
		position.x + side2, position.y + side1, position.z, // top right
		position.x + side2, position.y, position.z, // bottom right
		position.x, position.y, position.z, // bottom left

		// back face
		position.x, position.y + side1, position.z - side3, // top left
		position.x + side2, position.y + side1, position.z - side3, // top right
		position.x + side2, position.y, position.z - side3, // bottom right
		position.x, position.y, position.z - side3, // bottom left

		// left face
		position.x, position.y + side1, position.z, // top left
		position.x, position.y + side1, position.z - side3, // top right
		position.x, position.y, position.z - side3, // bottom right
		position.x, position.y, position.z, // bottom left

		// right face
		position.x + side2, position.y + side1, position.z, // top left
		position.x + side2, position.y + side1, position.z - side3, // top right
		position.x + side2, position.y, position.z - side3, // bottom right
		position.x + side2, position.y, position.z, // bottom left

		// top face
		position.x, position.y + side1, position.z, // top left
		position.x, position.y + side1, position.z - side3, // top right
		position.x + side2, position.y + side1, position.z - side3, // bottom right
		position.x + side2, position.y + side1, position.z, // bottom left

		// bottom face
		position.x, position.y, position.z, // top left
		position.x, position.y, position.z - side3, // top right
		position.x + side2, position.y, position.z - side3, // bottom right
		position.x + side2, position.y, position.z  // bottom left

	};
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
	position = vec3(newX, newY, newZ);

}

vec3 geometry_builder::getPosition()
{
	return vec3(position);
}

void geometry_builder::size(GLfloat side_x, GLfloat side_y, GLfloat side_z)
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

void geometry_builder::getSize()
{
	switch (type3d) {
	case CUBOID:
		getCubeSize();
		break;
	case BOX:
		getCuboidSize();
		break;
	default:
		getCubeSize();
		break;
	}
}

GLfloat geometry_builder::getCubeSize()
{
	return GLfloat(side1);
}

vec3 geometry_builder::getCuboidSize()
{
	return vec3(side1, side2, side3);
}

void geometry_builder::translate(vec3 &translateVector)
{
	position += translateVector;
}
