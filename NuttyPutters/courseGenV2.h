#pragma once
// Externals
#include <vector>
#include "include\glm-0.9.8.5\glm\glm\glm.hpp"
// Internals
#include "courseGenTiles.h"

using namespace glm;
using namespace std;

class courseGenV2
{
public:
	// Total tiles this course
	int courseLimit;
	// Position of last and current tiles
	vec3 lastTileCoords, curTileCoords;
	// Holds all game tiles added to course
	vector<BaseTile> gameTiles;
	// Holds all potential tiles for next tile placement
	vector<BaseTile> potentialTiles;
	// Sense of direction
	Direction dir;


	courseGenV2(int difficulty);
	~courseGenV2() {};

	void run();
	void PlaceTile();
	void CheckStraights();
	void CheckCorners();
	bool tilePosTaken(vec3 checkPos);
};


