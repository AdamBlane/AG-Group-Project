#pragma once

#include <string>
#include "glew_glfw.h"

class Texture
{
public:
	// Default constructor
	// This allows Texture tex; as a property of Mesh.h
	Texture() {};
	Texture(const std::string& fileName);
	Texture(const std::string& PosXFilename, const std::string& NegXFilename, const std::string& PosYFilename, const std::string& NegYFilename, const std::string& PosZFilename, const std::string& NegZFilename);
	// Unit allows you to select a texture
	void Bind(unsigned int unit);

	virtual ~Texture();
private:
	// M - Commented this out, since it conflicts with SetTexture in Mesh.h
	//Texture(const Texture& other) {}
	//Texture& operator=(const Texture& other) {}
	bool isCubeMap = false;
	GLuint m_texture;
};