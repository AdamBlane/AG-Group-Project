#pragma once

#include <string>
#include "glew.h"

class Texture
{
public:
	Texture(const std::string& fileName);

	// Unit allows you to select a texture
	void Bind(unsigned int unit);

	virtual ~Texture();
private:
	Texture(const Texture& other) {}
	Texture& operator=(const Texture& other) {}

	GLuint m_texture;
};

