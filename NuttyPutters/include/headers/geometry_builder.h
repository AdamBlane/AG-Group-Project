#pragma once
#include "glew.h"
#include <glm\glm.hpp>


using namespace glm;

class geometry_builder
{
public:
	enum type3D { CUBOID, BOX };

	geometry_builder(type3D type3d);
	~geometry_builder();
	void setPosition(GLfloat newX, GLfloat newY, GLfloat newZ);
	vec3 getPosition();
	void size(GLfloat side_1, GLfloat side_2 = 20.0f);
	void getSize();
	void translate(vec3 &translateVector);
	void draw();
	GLfloat getCubeSize();
	vec2 getCuboidSize();

private:
	void createCube();
	void createCuboid();

	type3D type3d = CUBOID;
	vec3 position = vec3(800.0f / 2.0f, 600.0f / 2.0f, 0.0f);
	GLfloat side1 = 20.0f;
	GLfloat side2 = 50.0f;
};

