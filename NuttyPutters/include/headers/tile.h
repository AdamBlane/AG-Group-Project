#pragma once
#include "geometry_builder.h"
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
	
	tile(vec3 newPosition = vec3(500.0f, 150.0f, 0.0f));
	~tile();
	vec3 getPosition();
	void drawTile();

private:
	vector<geometry_builder*> tileContent;
	vec2 measures = vec2(50.0f, 50.0f);
	vec3 position = vec3(500.0f, 150.0f, 0.0f);
	void createTile();
	
};

