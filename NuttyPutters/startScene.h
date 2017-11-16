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
	float dt = 0.016; // Lock to 60fps for first frame
	
	// Used for navigating through menu options
	// This determines which button should be highlighted
	int button_manager = 1;
	float total_time = 5.0f;

	// SPIKE - save last button index visited; that's the button to make tex = unselected

	// HUD Elements
	// Only need one transform (can be reused for each mesh)
	Transform startSceneTransform;
	// Meshes
	Mesh* background;
	Mesh* startGameButton;
	Mesh* loadGameButton;
	Mesh* highscoresButton;
	Mesh* optionsButton;
	Mesh* internetButton;
	Mesh* exitButton;
	// Their textures
	Texture* backgroundTex;
	Texture* startGameBtnSelected;
	Texture* startGameBtnUnselected;
	Texture* loadGameBtnSelected;
	Texture* loadGameBtnUnselected;
	Texture* highscoresBtnSelected;
	Texture* highscoresBtnUnselected;
	Texture* optionsBtnSelected;
	Texture* optionsBtnUnselected;
	Texture* internetBtnSelected;
	Texture* internetBtnUnselected;
	Texture* exitBtnSelected;
	Texture* exitBtnUnselected;
	

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
