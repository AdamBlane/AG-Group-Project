#pragma once

// GLFW
#include "glew_glfw.h"
#include <vector>

using namespace std;

// This scene lists previously saved levels
// Suggestion - Page(s) of images are shown, tiled. Max n images per
//              screen/page, so would need to move between pages.
// How - Make an image grid; all images same size, read from file (image
//		 is taken of course with target cam, the filename is that level's seed)

// How - Just load all images from saves file. Once clicked, take its name (level seed)
//       and then find that level in the file (so you don't need to load all seeds)

// Load images onto grid
// wait for input
// act on choice
//   search saves file for that seed (image name is string, files are read as string, can use str.contains() in search)
class loadGameScene
{
public:
	// Default constructor
	loadGameScene();
	// Deconstructor
	~loadGameScene();
	
	// Hold all seeds
	vector<string> seeds;
	// Seed navigation
	int currentSeed = 0; // Index of seeds
	bool leftPressed, rightPressed;

	// Setup scene
	void Init(GLFWwindow* win);
	// Draw stuff
	void Loop(GLFWwindow* win);

	void Input(GLFWwindow* win);
	void Render(GLFWwindow* win);

};