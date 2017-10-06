
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


	GLfloat colour[] = {
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f
	};


	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	glColor3f(colour[5], colour[5], colour[5]);
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_VERTEX_ARRAY);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colour), colour, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);


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


	GLfloat colour[] = {
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f
	};


	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//	glColor3f(colour[5], colour[5], colour[5]);
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_VERTEX_ARRAY);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colour), colour, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
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
	side1 = side_x;
	side2 = side_y;
	side3 = side_z;
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
