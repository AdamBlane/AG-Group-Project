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

	// Input - prevent input code from reocurring every frame button is held
	bool leftPressed, rightPressed, enterPressed = false;
	int button_manager = 1;
	
	// Meshes
	// Background	0
	





	// Draw stuff
	void Loop(GLFWwindow* win);
	// Input 
	void Input(GLFWwindow* win);
	// Setup
	void Init(GLFWwindow* win);
	// Update
	void Update(GLFWwindow* window);
	// Render
	void Render(GLFWwindow* window);

};