#pragma once
// Externals
#include "glew_glfw.h"
#include <map>
#include <time.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include <random>
#include <sstream>
#include <vector>
// Internals
#include "Mesh.h"
#include "Transform.h"
#include "target_camera.h"
#include "Shader.h"



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

	// Create a target camera - used for HUD elements
	AllCamera::target_camera* tarCam;

	Shader* textureShader;

	Mesh* backButton;
	Transform backButtonTrans;

	Mesh* background;
	Transform backgroundTrans;

	int button_manager = 1;

	float total_time = 2.0f;

	// Draw stuff
	void Loop(GLFWwindow* win);
	// Input 
	void Input(GLFWwindow* win);
	// Setup
	void Init(GLFWwindow* win);
	// Update
	//void Update(GLFWwindow* window);
	// Render
	void Render(GLFWwindow* window);

};