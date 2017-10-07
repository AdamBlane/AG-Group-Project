#pragma once

#include <string>
#include <glew.h>
#include "Transform.h"
#include "Camera.h"

// Created by Calum - 5TH of October - Used to identify and store shader information

class Shader
{
public:
	Shader(const std::string& fileName);
	// Bind the shader method
	void Bind();
	void Update(const Transform& transform, const Camera& camera);

	virtual ~Shader();
private:
	// Num_shaders is used to identify the type - frag and vertex. If we need geometry shader change to 3.
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}

	enum
	{
		TRANSFORM_U,
		NUM_UNIFORMS
	};

	// Handle which keeps track of the program and will be used to keep track of the shader
	GLuint m_program;

	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

