#include "tileBuilder.h"
#include <time.h>
#include <random>

Tile::Tile(typeTile desiredType, vec3 newPosition, int obstacleID, string floorTexture, string borderTexture, string bridgeSurroundingTexture)
{
	//setting tile properties
	//tilePos = newPosition;
	srand(time(NULL));
	transform.getPos() = newPosition;
	thisObstacleID = obstacleID;
	this_borderTexture = borderTexture;
	this_floorTexture = floorTexture;
	this_bridgeSurroundingTexture = bridgeSurroundingTexture;
	thisTile = desiredType;

	if (thisObstacleID != 0)
	{
		//Setting randomly the bool for the straight tile
		obstacle();
	}

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
	case THICKER_STRAIGHT:
		thickerStraightTile();
		break;
	case BRIDGE:
		bridgeTile();
		break;
	case CORNER:
		cornerTile();
		break;
	case SCENERY:
		sceneryTile();
		break;
	default:
		straightTile();
		break;
	}
}

void Tile::startTile()
{
	/*Mesh *floor = new Mesh(Mesh::CUBOID, this_floorTexture, tilePos, measures.x, measures.y, measures.z, true);
	tileContent.push_back(floor);

	Mesh *border1 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x - ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z), measures.y, measures.y, measures.z);
	tileContent.push_back(border1);

	Mesh *border2 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x + ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z), measures.y, measures.y, measures.z);
	tileContent.push_back(border2);

	Mesh *border3 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x, tilePos.y + measures.y, tilePos.z + ((measures.x - measures.y) / 2)), measures.x - (measures.y * 2), measures.y, measures.y);
	tileContent.push_back(border3);*/

}

void Tile::endTile()
{
	//Mesh *floor1 = new Mesh(Mesh::CUBOID, this_floorTexture, vec3(tilePos.x, tilePos.y, tilePos.z + (ballSizeMargin * 2.0)), measures.x, measures.y, ((measures.z - ballSizeMargin) / 2.0), true);
	//tileContent.push_back(floor1);

	//Mesh *floor2 = new Mesh(Mesh::CUBOID, this_floorTexture, vec3(tilePos.x, tilePos.y, tilePos.z - (ballSizeMargin * 2.0)), measures.x, measures.y, ((measures.z - ballSizeMargin) / 1.95), true);
	//tileContent.push_back(floor2);

	//Mesh *floor3 = new Mesh(Mesh::CUBOID, this_floorTexture, vec3(tilePos.x - (ballSizeMargin * 2.0), tilePos.y, tilePos.z), ((measures.x - ballSizeMargin) / 1.95), measures.y, ballSizeMargin - 0.1, true);
	//tileContent.push_back(floor3);

	//Mesh *floor4 = new Mesh(Mesh::CUBOID, this_floorTexture, vec3(tilePos.x + (ballSizeMargin * 2.0), tilePos.y, tilePos.z), ((measures.x - ballSizeMargin) / 1.95), measures.y, ballSizeMargin - 0.1, true);
	//tileContent.push_back(floor4);

	///////Trying to set a plane on top of hole to set a texture and pretend it is a circle hole

	//Mesh *holePlane = new Mesh(Mesh::PLANE, this_floorTexture, vec3(tilePos.x, tilePos.y + ((measures.y / 2) + 0.1), tilePos.z), measures.x, true);
	//tileContent.push_back(holePlane);

	//Mesh *border1 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x - ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z), measures.y, measures.y, measures.z);
	//tileContent.push_back(border1);

	//Mesh *border2 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x + ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z), measures.y, measures.y, measures.z);
	//tileContent.push_back(border2);

	//Mesh *border3 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x, tilePos.y + measures.y, tilePos.z + ((measures.x - measures.y) / 2)), measures.x - (measures.y * 2), measures.y, measures.y);
	//tileContent.push_back(border3);

	//////Tring to rotate a piece of border to have the texture stretched on same direction as others

	//Mesh *border3 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x, tilePos.y + measures.y, tilePos.z + ((measures.x - measures.y) / 2)), measures.y, measures.y, measures.z - (measures.y * 2));
	//border3->thisTransform.setRot(glm::vec3(0, Mesh::toRads(90), 0));
	//tileContent.push_back(border3);
}

void Tile::straightTile()
{
	//Create a mesh forming the tile, then add it to a vector of Meshes
	//Mesh *floor = new Mesh(Mesh::CUBOID, this_floorTexture, tilePos, measures.x, measures.y, measures.z, true);
	//tileContent.push_back(floor);

	//Mesh *border1 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x - ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z), measures.y, measures.y, measures.z);
	//tileContent.push_back(border1);

	//Mesh *border2 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x + ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z), measures.y, measures.y, measures.z);
	//tileContent.push_back(border2);


	//if hasObstacle is true, it calls the obstacle method
	//if (hasObstacle)
	//{
	//	obstacle();
	//}
}

void Tile::sceneryTile()
{
	//Create a mesh forming the tile, then add it to a vector of Meshes
	//Mesh *floor = new Mesh(Mesh::CUBOID, this_floorTexture, tilePos, measures.x, measures.y, measures.z, true);
	//tileContent.push_back(floor);
}

void Tile::thickerStraightTile()
{
	int randomTunnel = randomNumber(0, 2);

	//Mesh *floor = new Mesh(Mesh::CUBOID, this_floorTexture, tilePos, measures.x, measures.y, measures.z, true);
	//tileContent.push_back(floor);

	switch (randomTunnel)
	{
	case 0:
		middleTunnel();
		break;
	case 1:
		leftTunnel();
		break;
	case 2:
		rightTunnel();
		break;
	default:
		middleTunnel();
		break;
	}
}

void Tile::leftTunnel()
{
	//Mesh *border1 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x + ((ballSizeMargin / 2) + ((((measures.x - ballSizeMargin) / 4) / 2) * 3)), tilePos.y + measures.y, tilePos.z), ((measures.x - ballSizeMargin) / 4) * 1, measures.y, measures.z);
	//tileContent.push_back(border1);

	//Mesh *border2 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x - ((ballSizeMargin / 2) + ((((measures.x - ballSizeMargin) / 4) / 2) * 1)), tilePos.y + measures.y, tilePos.z), ((measures.x - ballSizeMargin) / 4) * 3, measures.y, measures.z);
	//tileContent.push_back(border2);

}

void Tile::rightTunnel()
{
	/*Mesh *border1 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x + ((ballSizeMargin / 2) + ((((measures.x - ballSizeMargin) / 4) / 2) * 1)), tilePos.y + measures.y, tilePos.z), ((measures.x - ballSizeMargin) / 4) * 3, measures.y, measures.z);
	tileContent.push_back(border1);

	Mesh *border2 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x - ((ballSizeMargin / 2) + ((((measures.x - ballSizeMargin) / 4) / 2) * 3)), tilePos.y + measures.y, tilePos.z), ((measures.x - ballSizeMargin) / 4) * 1, measures.y, measures.z);
	tileContent.push_back(border2);*/

}

void Tile::middleTunnel()
{
	//Mesh *border1 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x + ((ballSizeMargin / 2) + ((((measures.x - ballSizeMargin) / 4) / 2) * 2)), tilePos.y + measures.y, tilePos.z), ((measures.x - ballSizeMargin) / 4) * 2, measures.y, measures.z);
	//tileContent.push_back(border1);

	//Mesh *border2 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x - ((ballSizeMargin / 2) + ((((measures.x - ballSizeMargin) / 4) / 2) * 2)), tilePos.y + measures.y, tilePos.z), ((measures.x - ballSizeMargin) / 4) * 2, measures.y, measures.z);
	//tileContent.push_back(border2);

}

void Tile::bridgeTile()
{
	//Mesh *floor = new Mesh(Mesh::PLANE, this_floorTexture, vec3(tilePos.x, tilePos.y - (measures.y / 3), tilePos.z), measures.x, true);
	//tileContent.push_back(floor);

	//Mesh *surrounding = new Mesh(Mesh::PLANE, this_bridgeSurroundingTexture, tilePos, measures.x, false, true);
	//tileContent.push_back(surrounding);

	//Mesh *bridge = new Mesh(Mesh::CUBOID, this_borderTexture, tilePos, ballSizeMargin, measures.y, measures.z);
	//tileContent.push_back(bridge);

	//Mesh *border1 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x - ((measures.x - measures.y) / 2), tilePos.y + (measures.y / 2), tilePos.z), measures.y, measures.y * 2, measures.z);
	//tileContent.push_back(border1);

	//Mesh *border2 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x + ((measures.x - measures.y) / 2), tilePos.y + (measures.y / 2), tilePos.z), measures.y, measures.y * 2, measures.z);
	//tileContent.push_back(border2);
}

void Tile::cornerTile()
{
	//Mesh *floor = new Mesh(Mesh::CUBOID, this_floorTexture, tilePos, measures.x, measures.y, measures.z, true);
	//tileContent.push_back(floor);

	//Mesh *border1 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x - ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z), measures.y, measures.y, measures.z);
	//tileContent.push_back(border1);

	//Mesh *border2 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x + (measures.y / 2), tilePos.y + measures.y, tilePos.z - ((measures.x - measures.y) / 2)), measures.x - measures.y, measures.y, measures.y);
	//tileContent.push_back(border2);

	//Mesh *border3 = new Mesh(Mesh::BOX, this_borderTexture, vec3(tilePos.x + ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z + ((measures.x - measures.y) / 2)), measures.y);
	//tileContent.push_back(border3);

}

int Tile::randomNumber(int min, int max)
{
	// Create random engine 	
	default_random_engine random(random_device{}());
	uniform_int_distribution<int> range(min, max);
	int getRandom = range(random);

	return getRandom;
}

//obstacle method generating obstacles of different types
void Tile::obstacle()
{
	int randomObstacle = randomNumber(0, 1);

	switch (randomObstacle)
	{
	case 0:
		cout << "Has obstacle 0!" << endl << endl << endl;
		obstacleSlalom();
		break;
	case 1:
		cout << "Has obstacle 1!" << endl << endl << endl;
		obstacleCube();
		break;
	default:
		obstacleCube();
		break;
	}

}

void Tile::obstacleCube()
{
//	Mesh *cube = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x, tilePos.y + measures.y, tilePos.z), measures.y*2, measures.y, measures.y*2);
//	tileObstacle.push_back(cube);

}

void Tile::obstacleSlalom()
{
	//Mesh *bar1 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x - (ballSizeMargin / 2), tilePos.y + measures.y, tilePos.z + ballSizeMargin * 2), measures.x - (measures.y * 2) - ballSizeMargin, measures.y, measures.y);
	//tileObstacle.push_back(bar1);

	//Mesh *bar2 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x + (ballSizeMargin / 2), tilePos.y + measures.y, tilePos.z - ballSizeMargin * 2), measures.x - (measures.y * 2) - ballSizeMargin, measures.y, measures.y);
	//tileObstacle.push_back(bar2);

	////Doesn't work :(
	//obstacleTransform.getRot().y = Mesh::toRads(90);
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
	//double translationY = (Tile::getDimension().x / 2.0) * tan(Mesh::toRads(degreesOfRotation));
	double translationY = 0.1;
	return translationY;
}

//draws a tile passing a shader, a transform and a camera, in order to call Update method of the shader itself and allowing different textures to be bound
void Tile::drawTile(Shader* shader, glm::mat4 camera, Shader* waterShader)
{
	//one shader can be used to render more than 1 texture, but in must be updated after different textures are bind to it.
	//texture binded after a new shader.Update() should have index 0
	for (auto &t : tileContent)
	{
		if (t->isThisFloor == true)
		{
			//t->thisTexture->Bind(0);

			//updates the shader with first texture and draws the tile
			//shader->Update(transform, camera);
			//t->Draw();

		}
		else if (t->isThisFluid == true)
		{
			/*t->thisTexture->Bind(1);


			waterShader->Update(transform, camera);
			t->Draw();*/
		}
		else
		{
			//t->thisTexture->Bind(0);

			////Update the shader again with new textures
			//shader->Update(transform, camera);

			////Draw borders of tile
			//t->Draw();
		}
	}

	if (thisObstacleID != 0)
	{
		for (auto &o : tileObstacle)
		{
			//o->thisTexture->Bind(0);

			////updates the shader with texture and draws the obstacle
			//shader->Update(transform, camera);
			//o->Draw();
		}
	}

}

//This method is not used at the moment
void Tile::bindTextures(unsigned int startIndex)
{
	for (auto &content : tileContent)
	{
		/*content->thisTexture->Bind(startIndex);
		startIndex++;*/
	}
}