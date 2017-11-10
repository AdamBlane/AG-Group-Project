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

class optionsScene
{
public:
	// Default constructor
	optionsScene();
	// Deconstructor
	~optionsScene();

	// Create a target camera - used for HUD elements
	AllCamera::target_camera* tarCam;

	Shader* textureShader;

	Mesh* backButton;
	Transform backButtonTrans;

	Mesh* background;
	Transform backgroundTrans;

	Mesh* fullButton;
	Transform fullButtonTrans;

	Mesh* wiwButton;
	Transform wiwButtonTrans;

	int button_manager = 1;

	float total_time = 2.0f;


	// Draw stuff
	void Loop(GLFWwindow* win);

	void Input(GLFWwindow* win);

	void Init(GLFWwindow* win);
	// Update
	void Update(GLFWwindow* window);
	// Render
	void Render(GLFWwindow* window);
};