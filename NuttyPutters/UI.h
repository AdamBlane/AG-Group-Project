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

	// Index value in winMgr list
	int p1StrokeMeshIndex = 0;
	int p2StrokeMeshIndex = 1;

	// Sets up basic HUD layout 
	void Setup(int players);

	// Increment stroke counter for a player
	void UpdateStrokeCounter(int playerIndex, int strokeCount);
};