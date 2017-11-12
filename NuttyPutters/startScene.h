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

	// Create a target camera - used for HUD elements
	AllCamera::target_camera* tarCam;

	// Create a texture shader which is used to bind textures to geometry
	Shader* textureShader;

	// Used to lock framerate
	double lastFrame = 0;
	double thisFrame = glfwGetTime();
	float dt = 0.016; // Lock to 60fps

	// HUD geometry
	// Start Game Label 
	Mesh* playersLabelMesh;
	Transform playersLabelTrans;
	// Numbers Labels
	Mesh* numberOneLabelMesh;
	Mesh* numberTwoLabelMesh;
	Mesh* numberThreeLabelMesh;
	Mesh* numberFourLabelMesh;
	Transform numberOneLabelTrans;
	Transform numberTwoLabelTrans;
	Transform numberThreeLabelTrans;
	Transform numberFourLabelTrans;
	// Difficulty Labels
	Mesh* easyLabelMesh;
	Mesh* mediumLabelMesh;
	Mesh* hardLabelMesh;
	Transform easyLabelTrans;
	Transform mediumLabelTrans;
	Transform hardLabelTrans;
	// Option Labels 
	Mesh* startGameLabelMesh;
	Transform startGameLabelTrans;
	Mesh* returnLabelMesh;
	Transform returnLabelTrans;
	// Background
	Mesh* startSceneBackgroundMesh;
	Transform startSceneBackgroundTrans;

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
