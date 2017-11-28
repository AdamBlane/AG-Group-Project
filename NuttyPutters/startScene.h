#pragma once
// Externals
#include "glew_glfw.h"
#include <map>
#include <time.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include <random>

// Internals
#include "Mesh.h"
#include "Transform.h"
#include "target_camera.h"
#include "Shader.h"

class startScene
{
public:
	// Default constructor
	startScene();
	// Deconstructor
	~startScene();



	// Used to lock framerate
	double lastFrame = 0;
	double thisFrame = glfwGetTime();
	float dt = 0.016; // Lock to 60fps for first frame
	
	// Used for navigating through menu options
	float total_time = 5.0f;

	

	// Only need one transform (can be reused for each mesh)
	Transform startSceneTransform;

	// Background Mesh   0
	// StartGameBtn      1
	// LoadGameBtn		 2

	// Draw stuff
	void Loop(GLFWwindow* win);
	// Input 
	void Input(GLFWwindow* win);
	// Setup
	void Init(GLFWwindow* win);
	// Update
	void Update(GLFWwindow* window);
	// Render
	//Tracks Mouse
	void Track_Mouse(GLFWwindow* win);
	void Render(GLFWwindow* window);
	// For mouse button actions
	void Action(GLFWwindow* window);
};
