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
	int button_manager = 1;

	float total_time = 0.0f;
	int previousMenuItem, currentMenuItem;

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
	void Click_or_Enter_depending_on_which_key_was_pressed_but_that_was_why_this_function_was_created_ignoring_that_this_function_is_called_whenever_those_specific_keys_are_pressed(GLFWwindow* window);
};