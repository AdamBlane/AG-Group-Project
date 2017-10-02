#include "geometry_builder.h"

geometry_builder::geometry_builder(type3D thisType)
{
	type3d = thisType;

	switch (type3d) {
	case CUBOID:
		break;
	case BOX:
		break;
	default:
		break;
	}
}

geometry_builder::~geometry_builder()
{
}

void geometry_builder::createCube()
{
	
	GLfloat vertices[] =
	{
		// front face
		xPos, yPos + side1, zPos, // top left
		xPos + side1, yPos + side1, zPos, // top right
		xPos + side1, yPos, zPos, // bottom right
		xPos, yPos, zPos, // bottom left

		// back face
		xPos, yPos + side1, zPos - side1, // top left
		xPos + side1, yPos + side1, zPos - side1, // top right
		xPos + side1, yPos, zPos - side1, // bottom right
		xPos, yPos, zPos - side1, // bottom left

		// left face
		xPos, yPos + side1, zPos, // top left
		xPos, yPos + side1, zPos - side1, // top right
		xPos, yPos, zPos - side1, // bottom right
		xPos, yPos, zPos, // bottom left

		// right face
		xPos + side1, yPos + side1, zPos, // top left
		xPos + side1, yPos + side1, zPos - side1, // top right
		xPos + side1, yPos, zPos - side1, // bottom right
		xPos + side1, yPos, zPos, // bottom left

		// top face
		xPos, yPos + side1, zPos, // top left
		xPos, yPos + side1, zPos - side1, // top right
		xPos + side1, yPos + side1, zPos - side1, // bottom right
		xPos + side1, yPos + side1, zPos, // bottom left

		// bottom face
		xPos, yPos, zPos, // top left
		xPos, yPos, zPos - side1, // top right
		xPos + side1, yPos, zPos - side1, // bottom right
		xPos + side1, yPos, zPos  // bottom left
	};
}

void geometry_builder::createCuboid()
{
	GLfloat vertices[] =
	{
		// front face
		xPos, yPos + side1, zPos, // top left
		xPos + side2, yPos + side1, zPos, // top right
		xPos + side2, yPos, zPos, // bottom right
		xPos, yPos, zPos, // bottom left

		// back face
		xPos, yPos + side1, zPos - side2, // top left
		xPos + side2, yPos + side1, zPos - side2, // top right
		xPos + side2, yPos, zPos - side2, // bottom right
		xPos, yPos, zPos - side2, // bottom left

		// left face
		xPos, yPos + side1, zPos, // top left
		xPos, yPos + side1, zPos - side2, // top right
		xPos, yPos, zPos - side2, // bottom right
		xPos, yPos, zPos, // bottom left

		// right face
		xPos + side2, yPos + side1, zPos, // top left
		xPos + side2, yPos + side1, zPos - side2, // top right
		xPos + side2, yPos, zPos - side2, // bottom right
		xPos + side2, yPos, zPos, // bottom left

		// top face
		xPos, yPos + side1, zPos, // top left
		xPos, yPos + side1, zPos - side2, // top right
		xPos + side2, yPos + side1, zPos - side2, // bottom right
		xPos + side2, yPos + side1, zPos, // bottom left

		// bottom face
		xPos, yPos, zPos, // top left
		xPos, yPos, zPos - side2, // top right
		xPos + side2, yPos, zPos - side2, // bottom right
		xPos + side2, yPos, zPos  // bottom left

	};
}
