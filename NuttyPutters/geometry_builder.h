#pragma once
#include "glfw3.h"
#include <stdlib.h>
#include <stdio.h>


class geometry_builder
{
public:
	enum type3D { CUBOID, BOX };
	type3D type3d = CUBOID;
	geometry_builder(type3D type3d);
	~geometry_builder();
	void createCube();
	void createCuboid();
	void setPosition();
	

private:
	GLfloat xPos = 0.0f;
	GLfloat yPos = 0.0f;
	GLfloat zPos = 0.0f;
	GLfloat side1 = 20.0f;
	GLfloat side2 = 50.0f;
};

