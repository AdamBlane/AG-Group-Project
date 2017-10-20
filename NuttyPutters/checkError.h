#pragma once
#include "glew_glfw.h"
#include <iostream>
#define CHECK_GL_ERROR get_GL_error(__LINE__, __FILE__)



inline bool get_GL_error(int line, const std::string &file) {
	// Get the current error
	GLenum error = glGetError();
	// If there is an error display message
	if (error) {
		// Display error
		std::cerr << "OpenGL Error: " << error << std::endl;
		std::cerr << "At line " << line << " in file " << file << std::endl;
		return true;
	}
	return false;
}