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
#include <fstream>
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

	bool buttonPressed[18] = { false };
	bool isFunctionEmpty = false;
	bool isFunctionEmptyKeyboard = false;
	int meshesInScene = 42; // Used so everytime a mesh is added the number doesnt need updating
	int indexAt99 = 0;
	int indexAtButton = 0;
	int indexAtKey = 0;

	bool keyboardButtonPressed[100] = { false };

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

	// ESC = 45
	// ENTER = 46
	// TAB = 47
	// BACKSPACE = 48
	// INSERT = 49
	// DELETE = 50
	// RIGHT = 51
	// LEFT = 52
	// DOWN = 53
	// UP = 54
	// PAGEUP = 55
	// PAGEDOWN = 56
	// HOME = 57
	// END = 58
	// CAPS = 59
	// SCROLL = 60
	// NUM LOCK = 61
	// PRINT SCREEN = 62 
	// PAUSE = 63
	// F1 = 64
	// F2 = 65
	// F3 = 66
	// F4 = 67
	// F5 = 68
	// F6 = 69
	// F7 = 70 
	// F8 = 71
	// F9 = 72
	// F10 = 73
	// F11 = 74
	// F12 = 75

	// PAD 0 = 76
	// PAD 1 = 77
	// PAD 2 = 78
	// PAD 3 = 79 
	// PAD 4 = 80
	// PAD 5 = 81
	// PAD 6 = 82
	// PAD 7 = 83
	// PAD 8 = 94
	// PAD 9 = 85
	// DECIMAL = 86
	// DIVIDE = 87
	// MULTIPLY = 88
	// SUBTRACT = 89
	// ADD = 90
	// ENTER = 91
	// EQUAL = 92

	// LEFT SHIFT = 93
	// LEFT CONTROL = 94
	// LEFT ALT = 95
	// RIGHT SHIFT = 96
	// RIGHT CONTROL = 97
	// RIGHT ALT = 98

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
	void updateKeyboardFunctionsList(int keyboardButtonNumber, int additionalNumber);
	// Draw stuff
	void Loop(GLFWwindow* win);
	// Input 
	void InputKeyboard(GLFWwindow* win);
	void InputController(GLFWwindow* win);
	// Setup
	void Init(GLFWwindow* win);
	// Update
	void Update(GLFWwindow* window);
	//Tracks Mouse
	void Track_Mouse(GLFWwindow* win);
	//Render
	void Render(GLFWwindow* win);
	// For mouse button actions
	void Click(GLFWwindow* win);
	// Load unqiue player buttons
	void InitPlayerButtons(GLFWwindow* win);
};