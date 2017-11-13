#pragma once

#include <string>
#include "glew_glfw.h"

class Texture
{
public:
	// Default constructor
	Texture() {}; // This allows textures to be initialised in header files
	void GenerateTexture(const std::string& fileName);

	// Unit allows you to select a texture
	void Bind(unsigned int unit);

	virtual ~Texture();
private:
	//Texture(const Texture& other) {}
	//Texture& operator=(const Texture& other) {}

	GLuint m_texture;
};

