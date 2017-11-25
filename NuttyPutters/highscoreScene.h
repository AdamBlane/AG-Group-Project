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

class highscoreScene
{
public:
	// Default constructor
	highscoreScene();
	// Deconstructor
	~highscoreScene();

	// Used to lock framerate
	double lastFrame = 0;
	double thisFrame = glfwGetTime();
	float dt = 0.016; // Lock to 60fps

	Transform optionSceneTransform;

	bool buttonPressed[18] = { false };
	bool isFunctionEmpty = false;
	bool isFunctionEmptyKeyboard = false;
	int meshesInScene = 37; // Used so everytime a mesh is added the number doesnt need updating
	int indexAt99 = 0;
	int indexAtButton = 0;
	int indexAtKey = 0;

	bool keyboardButtonPressed[45] = { false };

	// KEYBOARD - One
	// Comma = 0
	// Minus = 1
	// Full stop = 2
	// Forward Slash = 3
	// Num 0 = 4
	// Num 1 = 5
	// Num 2 = 6
	// Num 3 = 7
	// Num 4 = 8
	// Num 5 = 9
	// Num 6 = 10
	// Num 7 = 11
	// Num 8 = 12
	// Num 9 = 13
	// SemiColon ; = 14
	// Equals = = 15
	// A = 16
	// B = 17 
	// C = 18
	// D = 19
	// E = 20
	// F = 21
	// G = 22
	// H = 23
	// I = 24
	// J = 25
	// K = 26
	// L = 27
	// M = 28
	// N = 29
	// O = 30
	// P = 31
	// Q = 32
	// R = 33
	// S = 34
	// T = 35
	// U = 36
	// V = 37
	// W = 38 
	// X = 39
	// Y = 40
	// Z = 41
	// Left bracket [ = 42
	// Back slash = 43
	// Right bracket ] = 44

	// BUTTONS
	// A/Sqaure = 0
	// B/X(PS) = 1
	// X(XB)/Circle = 2
	// Y/Triangle = 3
	// LB/L1 = 4
	// RB/R1 = 5
	// Back/L2 = 6
	// Start/R2 = 7
	// Left Stick Push/Select = 8
	// Right Stick Push/Start = 9
	// DPAD UP/Left Stick Push = 10
	// DPAD LEFT/Right Stick Push = 11
	// DPAD DOWN/PS Button =12
	// DPAD RIGHT/Pad = 13
	// /DPAD UP = 14
	// /DPAD LEFT = 15 
	// /DPAD DOWN = 16
	// /DPAD RIGHT = 17

	// FUCTIONS
	// Select/fire = 0
	// Back/Reset = 1
	// Pause = 2
	// DPAD UP = 3
	// DPAD LEFT = 4
	// DPAD DOWN = 5
	// DPAD RIGHT = 6
	// Jump = 7
	// Zoom in = 8
	// Zoom out = 9

	// Update the keyboard functions list
	void updateKeyboardFunctionsList(int keyboardButtonNumber);
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