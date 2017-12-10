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

	// Sets pause screen mesh properties
	void PauseScreen();

	// Render endgame scoreboard for 1p game
	void p1GameScoreboard(int score);
	// Render endgame scoreboard for 2p game
	void p2GameScoreboard(int p1Score, int p2Score);
	//Function to pass values from GameLogic
	//void SetScoreToPrint(int nPlayers, int p1score, int p2score = 0);

	int usedMeshesP1;
	int usedMeshesP2;

private:

	//Values passed from GameLogic
	int scoreP1;
	int scoreP2;
	//int Nplayers;

	//From : https://obtalk.wordpress.com/2013/02/28/c-count-the-number-of-digits-in-an-integer/
	//To count how many digits in an integer
	int countDigits(int number);
	void digitsToVector(int number, vector<int> scoreDigits);



	//vector<int> p1;
	//vector<int> p2;

};