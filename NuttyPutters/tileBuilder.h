#pragma once
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "free_camera.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace AllCamera;
using namespace glm;
using namespace std;

class Tile
{
public:

	enum typeTile
	{
		START,
		END,
		STRAIGHT,
		CORNER

	};

	Transform transform;

	//tile constructor, taking floor and border textures file paths and new position --> not perfectly working
	Tile(typeTile desiredType, string floorTexture, string borderTexture, vec3 newPosition);
	~Tile();

	//returns position of the tile
	vec3 getPosition();

	//returns tile dimensions
	vec3 getDimension() { return measures; };

	//Get translation on y axis after rotation of the tile using Pythagoras, knowing the angle of rotation(positive degrees) and half of tile length
	//double getYAfterRotation(double degreesOfRotation);

	//draws a tile passing a shader, a transform and a camera, in order to call Update method of the shader itself and allowing different textures to be bound
	void drawTile(Shader* shader, glm::mat4 camera);

	//Not used --> should bind textures from a starting index (usually 0)
	void bindTextures(unsigned int startIndexs);

	//Vector of Mesh* used to
	vector<Mesh*> tileContent;

private:

	//measures of the tile
	vec3 measures = vec3(10.0f, 1.0f, 10.0f);

	//position of the tile
	vec3 tilePos;

	//Strings for texture file paths
	string this_borderTexture;
	string this_floorTexture;

	//Create a tile with a cuboid as floor and 2 borders on left and right
	void createTile();
	typeTile thisTile = STRAIGHT;
	void startTile();
	void straightTile();
	void cornerTile();

};