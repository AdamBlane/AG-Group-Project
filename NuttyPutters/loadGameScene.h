#pragma once
// Externals
#include "glew_glfw.h"
#include <map>
#include <time.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include <random>
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
	
	// Number of meshes used from winMgr list before image viewer grid is made
	const int diff = 1; 
	// Hold all seeds
	vector<string> seeds;

	// Player count - load game with 1 or 2 players
	int playerCount = 1;
	// Image viewer navigation
	int lastImageSelected, currentImageSelected, maxImagetoSelect; // Index of image mesh
	int savesImagesIndex; // Index to look up textures and seeds
	int currentPage; // Track which page we're on
	float pageCount, totalImages; // Number of pages, total images
	// Input - prevent input code from reocurring every frame button is held
	bool upPressed, downPressed, leftPressed, rightPressed, enterPressed;
	bool mouseLpressed;
	// Enforce delay perdio before enter action may be undertaken on press/release
	int enterCooldown, enterCooldownMax = 300;
	// Width and height of image meshes
	float w = 1.8f, h = 1.0f;	
	float selectedW = 1.6f, selectedH = 0.9f;
	float hoverW = 1.7f, hoverH = 0.95f;
	// Background	0
	int Menuselection ,prevselection;
	int selection, otherprevselection , OtherSelection;

	int controllerOneButtonCount;
	const unsigned char *controllerOne;
	int controllerOneAxisCount;
	const float *controllerOneAxis;
	
	bool backButtonPressedController = false; // Boolean used to see if the back button was pressed for controller
	bool backButtonPressedKeyboard = false; // Boolean used to see if the back button was pressed for keyboard

	// Setup
	void Init(GLFWwindow* win);
	// Draw stuff
	void Loop(GLFWwindow* win);
	// Load next page of images
	void NextPage();
	// Load previous page of images
	void LastPage();
	// Resize current and last selected image mesh
	void ResizeCurLastSelected();
	// Input 
	void Input(GLFWwindow* win);
	// Update
	void Update(GLFWwindow* window);
	// Render
	void Render(GLFWwindow* window);
	//Tracks mouse
	void Track_Mouse(GLFWwindow* win);
	//Tracks the action
	void Click_or_Enter(GLFWwindow* win);
	void Down();
	void Up();
	void Left();
	void Right();
};