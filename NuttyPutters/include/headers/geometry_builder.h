#pragma once
#include "Mesh.h"
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
	void size(GLfloat side_x, GLfloat side_y = 1.0f, GLfloat side_z = 1.0f);
	void getSize();
	void translate(vec3 &translateVector);
	void draw();
	GLfloat getCubeSize();
	vec3 getCuboidSize();
	void createCube();

	//Mesh createMesh();

	Mesh *thisMesh;



private:
	
	void createCuboid();

	type3D type3d = CUBOID;
	vec3 position = vec3(0.0f, 0.0f, 0.0f);
	GLfloat side1 = 1.0f;
	GLfloat side2 = 1.0f;	
	GLfloat side3 = 1.0f;

};

