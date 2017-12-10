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



	// Sets up basic HUD layout 
	void p1Setup();
	void p2Setup();
	// Update game clock
	void UpdateHUDClock(int time);
	// Update world clock
	void UpdateWorldClock(int time);
	// Increment stroke counter for a player
	void UpdateStrokeCounter(int playerIndex, int strokeCount);
};