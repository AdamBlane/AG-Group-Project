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
	// Image viewer navigation
	int lastImageSelected, currentImageSelected, maxImagetoSelect; // Index of image mesh
	int savesImagesIndex; // Index to look up textures and seeds
	int currentPage; // Track which page we're on
	float pageCount, totalImages; // Number of pages, total images

	// Input - prevent input code from reocurring every frame button is held
	bool upPressed, downPressed, leftPressed, rightPressed, enterPressed;
	int enterCooldown, enterCooldownMax = 300;
	// Width and height of image meshes
	// 1600 / 3 = 533.33rec     900 / 3 = 300
	// 533.33 / 168 = 3.175	    300 / 168 = 1.786
	const float w = 2.0f, h = 1.2f;
	const float selectedW = 1.8f, selectedH = 1.0f;
	// Background	0




	
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

};