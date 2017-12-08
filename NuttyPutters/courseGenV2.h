#pragma once
// Externals
#include <vector>
#include <fstream>
// Internals
#include "courseGenTiles.h"


using namespace glm;
using namespace std;

class courseGenV2
{
public:
	// Size of side of tile
	int tileSize;
	// Total tiles this course
	int courseLimit;
	// Position of current tile yet to be placed
	vec3 curTileCoords;
	// Holds all game tiles added to course
	vector<BaseTile*> gameTiles;
	// Holds all potential tiles for next tile placement
	vector<BaseTile*> potentialTiles;
	// Sense of direction
	Direction dir;

	courseGenV2() {}
	courseGenV2(int difficulty);
	~courseGenV2() {};

	// Course generation algorithm functions
	vector<BaseTile*> run();
	void PlaceTile();
	void CheckStraights();
	void CheckCorners();
	bool tilePosTaken(vec3 checkPos);

	// These functions do not use proc gen alg
	// Load game seed 
	vector<int> SetupSeed(string seed, int courseLength);
	// Setup Alg tiles
	vector<BaseTile*> SetupAlgTiles(vector<int> levelSeed);
};


