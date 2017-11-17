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
	bool leftPressed, rightPressed, enterPressed = false;

	// Create a target camera - used for HUD elements
	AllCamera::target_camera* tarCam;

	
	// HUD elements
	//Transform loadGameTransform;
	// Meshes
	// Background	0
	

	// Textures
	Texture* backgroundTex;


	int button_manager = 1;

	float total_time = 2.0f;

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