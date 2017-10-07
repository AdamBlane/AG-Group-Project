#pragma once
#include "Mesh.h"
#include <glm\glm.hpp>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>


using namespace glm;
using namespace std;

class tile
{
public:
	
	tile(vec3 newPosition = vec3(0.0f, 0.0f, 0.0f));
	~tile();
	vec3 getPosition();
	void drawTile();
	vector<Mesh> tileContent;

private:
	
	vec3 measures = vec3(1.0f, 0.1f, 1.0f);
	vec3 tilePos = vec3(0.0f, 0.0f, 0.0f);
	void createTile();
	
};

