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

class playerSelectScene
{
public:
	// Constructors
	playerSelectScene();
	~playerSelectScene();

	// Gameplay 
	int selectedPlayers = 0;
	int selectedDifficulty = 0;

	// Getters
	inline bool selectedAmountOfPlayers() { return selectedPlayers; }
	inline bool selectedChosenDifficulty() { return selectedDifficulty; }

	// Create a target camera - used for HUD elements
	AllCamera::target_camera* tarCam;

	// Create a texture shader which is used to bind textures to geometry
	Shader* textureShader;

	// Used to lock framerate
	double lastFrame = 0;
	double thisFrame = glfwGetTime();
	float dt = 0.016; // Lock to 60fps

	// Only need one transform (can be reused for each mesh)
	Transform playerSelectTransform;

	// Background Mesh		 0
	// PlayersLabel Mesh     1
	// OnePlayerBtn Mesh	 2
	// TwoPlayerBtn Mesh	 3
	// DifficultyLabel Mesh  4
	// EasyBtn				 5
	// MediumBtn			 6
	// HardBtn				 7
	// StartGameBtn			 8
	// MainMenuBtn			 9

	// HUD geometry
	// Numbers Labels
	//Mesh* playersLabelMesh;
	//Mesh* numberOneLabelMesh;
	//Mesh* numberTwoLabelMesh;
	//Mesh* numberThreeLabelMesh;
	//Mesh* numberFourLabelMesh;
	//Transform playersLabelTrans;
	//Transform numberOneLabelTrans;
	//Transform numberTwoLabelTrans;
	//Transform numberThreeLabelTrans;
	//Transform numberFourLabelTrans;
	//// Difficulty Labels
	//Mesh* difficultyLabelMesh;
	//Mesh* easyLabelMesh;
	//Mesh* mediumLabelMesh;
	//Mesh* hardLabelMesh;
	//Transform difficultyLabelTrans;
	//Transform easyLabelTrans;
	//Transform mediumLabelTrans;
	//Transform hardLabelTrans;
	//// Option Labels 
	//Mesh* startGameLabelMesh;
	//Transform startGameLabelTrans;
	//Mesh* returnLabelMesh;
	//Transform returnLabelTrans;
	//// Background
	//Mesh* playerSelectBackgroundMesh;
	//Transform playerSelectBackgroundTrans;

	// Used for selection of labels
	int playerSelect = 1;
	int difficultySelect = 1;
	int buttonSelect = 1;
	int playerChoice = 0;
	int difficultyChoice = 0;
	float total_time = 5.0f;

	// Difficulty; number of tiles in level - NOT SURE WHAT THIS IS
	int courseLength = 12;

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