#include "tileBuilder.h"
#include <time.h>

Tile::Tile(typeTile desiredType, string floorTexture, string borderTexture, vec3 newPosition, vec3 newMeasures)
{
	//setting tile properties
	//tilePos = newPosition;
	srand(time(NULL));
	transform.getPos() = newPosition;
	measures = newMeasures;

	this_borderTexture = borderTexture;
	this_floorTexture = floorTexture;
	thisTile = desiredType;


	//create tile method to generate meshes composing the tile
	createTile();
}

Tile::~Tile()
{
}

//returns position of the tile
vec3 Tile::getPosition()
{
	return vec3(tilePos);
}

//Create a tile with a cuboid as floor and 2 borders on left and right
void Tile::createTile()
{
	switch (thisTile)
	{
	case START:
		startTile();
		break;
	case END:
		endTile();
		break;
	case STRAIGHT:
		straightTile();
		break;
	case BRIDGE:
		bridgeTile();
		break;
	case CORNER:
		cornerTile();
		break;
	default:
		straightTile();
		break;
	}
}

void Tile::startTile()
{
	Mesh *floor = new Mesh(Mesh::CUBOID, this_floorTexture, tilePos, measures.x, measures.y, measures.z, true);
	tileContent.push_back(floor);

	Mesh *border1 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x - ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z), measures.y, measures.y, measures.z);
	tileContent.push_back(border1);

	Mesh *border2 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x + ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z), measures.y, measures.y, measures.z);
	tileContent.push_back(border2);

	Mesh *border3 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x, tilePos.y + measures.y, tilePos.z + ((measures.x - measures.y) / 2)), measures.x - (measures.y * 2), measures.y, measures.y);
	tileContent.push_back(border3);

}

void Tile::endTile()
{
	Mesh *floor1 = new Mesh(Mesh::CUBOID, this_floorTexture, vec3(tilePos.x, tilePos.y, tilePos.z + (ballSizeMargin * 2.0)), measures.x, measures.y, ((measures.z - ballSizeMargin) / 2.0), true);
	tileContent.push_back(floor1);

	Mesh *floor2 = new Mesh(Mesh::CUBOID, this_floorTexture, vec3(tilePos.x, tilePos.y, tilePos.z - (ballSizeMargin * 2.0)), measures.x, measures.y, ((measures.z - ballSizeMargin) / 1.95), true);
	tileContent.push_back(floor2);

	Mesh *floor3 = new Mesh(Mesh::CUBOID, this_floorTexture, vec3(tilePos.x - (ballSizeMargin * 2.0), tilePos.y, tilePos.z), ((measures.x - ballSizeMargin) / 1.95), measures.y, ballSizeMargin - 0.1, true);
	tileContent.push_back(floor3);

	Mesh *floor4 = new Mesh(Mesh::CUBOID, this_floorTexture, vec3(tilePos.x + (ballSizeMargin * 2.0), tilePos.y, tilePos.z), ((measures.x - ballSizeMargin) / 1.95), measures.y, ballSizeMargin - 0.1, true);
	tileContent.push_back(floor4);

	//Mesh *holePlane = new Mesh(Mesh::PLANE, this_floorTexture, vec3(tilePos.x, tilePos.y + ((measures.y / 2) + 0.1), tilePos.z), measures.x, true);
	//tileContent.push_back(holePlane);

	Mesh *border1 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x - ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z), measures.y, measures.y, measures.z);
	tileContent.push_back(border1);

	Mesh *border2 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x + ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z), measures.y, measures.y, measures.z);
	tileContent.push_back(border2);

	Mesh *border3 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x, tilePos.y + measures.y, tilePos.z + ((measures.x - measures.y) / 2)), measures.x - (measures.y * 2), measures.y, measures.y);
	tileContent.push_back(border3);
}

void Tile::straightTile()
{
	//Create a mesh forming the tile, then add it to a vector of Meshes
	Mesh *floor = new Mesh(Mesh::CUBOID, this_floorTexture, tilePos, measures.x, measures.y, measures.z, true);
	tileContent.push_back(floor);

	Mesh *border1 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x - ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z), measures.y, measures.y, measures.z);
	tileContent.push_back(border1);

	Mesh *border2 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x + ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z), measures.y, measures.y, measures.z);
	tileContent.push_back(border2);

	//Setting randomly the bool for the straight tile
	hasObstacle = randomBool();
	//if hasObstacle is true, it calls the obstacle method
	if (hasObstacle)
	{
		obstacle();
	}
}

void Tile::bridgeTile()
{
	//Mesh *floor1 = new Mesh(Mesh::CUBOID, this_floorTexture, vec3(tilePos.x, tilePos.y, tilePos.z - ((measures.x / 2)) - 1), measures.x, measures.y, measures.y, true);
	//tileContent.push_back(floor1);

	Mesh *bridge = new Mesh(Mesh::CUBOID, this_borderTexture, tilePos, ballSizeMargin, measures.y, measures.z - (measures.y * 2));
	tileContent.push_back(bridge);
}

void Tile::cornerTile()
{
	Mesh *floor = new Mesh(Mesh::CUBOID, this_floorTexture, tilePos, measures.x, measures.y, measures.z, true);
	tileContent.push_back(floor);

	Mesh *border1 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x - ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z), measures.y, measures.y, measures.z);
	tileContent.push_back(border1);

	Mesh *border2 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x + (measures.y / 2), tilePos.y + measures.y, tilePos.z - ((measures.x - measures.y) / 2)), measures.x - measures.y, measures.y, measures.y);
	tileContent.push_back(border2);

	Mesh *border3 = new Mesh(Mesh::BOX, this_borderTexture, vec3(tilePos.x + ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z + ((measures.x - measures.y) / 2)), measures.y);
	tileContent.push_back(border3);

}

//obstacle method generating obstacles of different types
void Tile::obstacle()
{

	cout << "Has obstacle!" << endl << endl << endl;


}

//calculation for the scale of a ramp tile, that needs to be a bit longer after rotation
double Tile::scaleRampTile(double rotationDegrees, double translationY)
{
	double a = measures.x / 2;

	//pythagoras
	double newSide = sqrt(pow(a, 2.0) + pow(translationY, 2.0));
	double scaleAmount = ((newSide * 2) / measures.x) + 0.05;

	return scaleAmount;
}

double Tile::getYAfterRotation(double degreesOfRotation)
{
	double translationY = (Tile::getDimension().x / 2.0) * tan(Mesh::toRads(degreesOfRotation));

	return translationY;
}

//draws a tile passing a shader, a transform and a camera, in order to call Update method of the shader itself and allowing different textures to be bound
void Tile::drawTile(Shader* shader, glm::mat4 camera)
{
	//one shader can be used to render more than 1 texture, but in must be updated after different textures are bind to it.
	//texture binded after a new shader.Update() should have index 0
	for (auto &t : tileContent)
	{
		if (t->isThisFloor == true)
		{
			t->thisTexture->Bind(0);

			//updates the shader with first texture and draws the tile
			shader->Update(transform, camera);
			t->Draw();

		}
		else
		{
			t->thisTexture->Bind(0);

			//Update the shader again with new textures
			shader->Update(transform, camera);

			//Draw borders of tile
			t->Draw();
		}
	}
}

//This method is not used at the moment
void Tile::bindTextures(unsigned int startIndex)
{
	for (auto &content : tileContent)
	{
		content->thisTexture->Bind(startIndex);
		startIndex++;
	}
}