#pragma once
#include "glfw3.h"
#include <stdlib.h>
#include <stdio.h>
#include <glm\glm.hpp>

using namespace glm;

class geometry_builder
{
public:
	enum type3D { CUBOID, BOX };

	geometry_builder(type3D type3d);
	~geometry_builder();

	void setPosition();
	vec3 getPosition();
	void scale();
	GLfloat getScale();


private:
	void createCube();
	void createCuboid();
	type3D type3d = CUBOID;
	vec3 position = vec3(800.0f / 2.0f, 600.0f / 2.0f, -250.0f);
	GLfloat side1 = 20.0f;
	GLfloat side2 = 50.0f;
};

