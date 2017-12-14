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
	//AllCamera::target_camera* tarCam;

	//Shader* textureShader;

	Transform optionSceneTransform;

	float total_time = 0.0f;

	int previousMenuItem, currentMenuItem;
	int controllerOneButtonCount;
	const unsigned char *controllerOne;
	int controllerOneAxisCount;
	const float *controllerOneAxis;

	bool backButtonPressedController = false; // Boolean used to see if the back button was pressed for controller
	bool backButtonPressedKeyboard = false; // Boolean used to see if the back button was pressed for keyboard

	// Draw stuff
	void Loop(GLFWwindow* win);

	void Input(GLFWwindow* win);

	void Init(GLFWwindow* win);

	void Track_Mouse(GLFWwindow* win);
	// Update
	void Update(GLFWwindow* window);
	// Render
	void Render(GLFWwindow* window);
	//to track and change textures
	void ChangeTexutes(GLFWwindow* win);
	//for action keys
	void Click_or_Enter(GLFWwindow* window);
};