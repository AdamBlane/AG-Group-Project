#pragma once
// Externals
#include "glew_glfw.h"
#include <map>
#include <time.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include <random>
#include <windows.h>
#include <atlimage.h>
#include <gdiplusimaging.h>

// Internals
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "free_camera.h"
#include "chase_camera.h"
#include "tileBuilder.h"
#include "target_camera.h"
#include "Player.h"
#include "courseGenTiles.h"
#include "UI.h"
#include "Physics.h"

class UI
{
public:
	UI() {}
	~UI() {}

	int tempInt = 0;
	string temp;
	string minutesAsString, tenthsAsString, secondsAsString, timeCombined;
	int timeRemainingInSeconds = 0, timeRemainingInTenths = 0, timeRemainingInMinutes = 0;
	//Player player; need this?

	bool updateStrokeMesh(int strokeCounter); // Method which updates the users stroke counter
	bool updateTimer(int timeSinceContinueWasPressed, int timeToThisMethod, int holeTimer);
	bool hasUserCompletedTheHole(Player &player);

	// Sets up meshes and texures stored in winMgr
	void Init();
	// Game loop and its functions
	void Loop(GLFWwindow* window);
	void Input(GLFWwindow* window);
	void Update(GLFWwindow* window);
};