#include "Texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>


// This method replaces old constructor (Does the same thing)
void Texture::GenerateTexture(const std::string& fileName)
{
	// Store the width, height and number of components that make up a texture
	// NumCoponents is rarely used but good to have incase using complex textures
	int width, height, numComponents;

	// Load the texture data
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
	{
		std::cout << "Texture loading failed for texture: " << fileName << std::endl;
	}

	// Generate the texture
	glGenTextures(1, &m_texture);
	// Bind a 2D texture
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// Optional - can specify texture wrapping if outside the texture bounds
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	// If image takes up more pixels than specifies
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Anisotropic filter active
	float max_anisotropy;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);

	// Input texture information
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	
	//Generate mipmap of texture
	glGenerateMipmap(GL_TEXTURE_2D);

	// Free the GPU of the texture data
	stbi_image_free(imageData);
}

// Deconstructor
Texture::~Texture()
{
	// Delete texture once complete
	glDeleteTextures(1, &m_texture);
}

void Texture::Bind(unsigned int unit)
{
	// Make sure unit does not go out of range - can only be between 0 and 31
	assert(unit >= 0 && unit <= 31);

	// Set active texture to the value stored in the unit variable
	glActiveTexture(GL_TEXTURE0 + unit);
	// Bind that texture to the unit
	glBindTexture(GL_TEXTURE_2D, m_texture);

}
