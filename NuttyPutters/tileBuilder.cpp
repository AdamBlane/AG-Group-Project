#include "tileBuilder.h"
#include "windowMgr.h"
#include <time.h>
#include <random>

Tile::Tile(typeTile desiredType, vec3 newPosition, int obstacleID)
{
	//setting tile properties
	//tilePos = newPosition;
	srand(time(NULL));
	transform.getPos() = newPosition;
	thisObstacleID = obstacleID;

	//this_borderTexture = borderTexture;
	//this_floorTexture = floorTexture;
	//this_bridgeSurroundingTexture = bridgeSurroundingTexture;
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
	windowMgr::getInstance()->tileMeshes.at(0)->SetScale(measures.x, measures.y, measures.z);
	windowMgr::getInstance()->tileMeshes.at(0)->SetPos(tilePos);
	windowMgr::getInstance()->tileMeshes.at(0)->SetAsFloor(true);
	windowMgr::getInstance()->tileMeshes.at(0)->SetTexture(windowMgr::getInstance()->tileTextures["floorGrass"]);
	tileContent.push_back(windowMgr::getInstance()->tileMeshes.at(0));

	//Side border on left
	windowMgr::getInstance()->tileMeshes.at(1)->SetScale(measures.y, measures.y, measures.z);
	windowMgr::getInstance()->tileMeshes.at(1)->SetPos(vec3(tilePos.x - ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z));
	windowMgr::getInstance()->tileMeshes.at(1)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileContent.push_back(windowMgr::getInstance()->tileMeshes.at(1));

	//Side border on right
	windowMgr::getInstance()->tileMeshes.at(2)->SetScale(measures.y, measures.y, measures.z);
	windowMgr::getInstance()->tileMeshes.at(2)->SetPos(vec3(tilePos.x + ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z));
	windowMgr::getInstance()->tileMeshes.at(2)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileContent.push_back(windowMgr::getInstance()->tileMeshes.at(2));

	//border closing the start tile
	windowMgr::getInstance()->tileMeshes.at(3)->SetScale(measures.x - (measures.y * 2), measures.y, measures.y);
	windowMgr::getInstance()->tileMeshes.at(3)->SetPos(vec3(tilePos.x, tilePos.y + measures.y, tilePos.z + ((measures.x - measures.y) / 2)));
	windowMgr::getInstance()->tileMeshes.at(3)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileContent.push_back(windowMgr::getInstance()->tileMeshes.at(3));
}

void Tile::endTile()
{
	//Getting mesh 6 and not 0 for end tile as texture applies to all tiles
	windowMgr::getInstance()->tileMeshes.at(6)->SetScale(measures.x, measures.y, measures.z);
	windowMgr::getInstance()->tileMeshes.at(6)->SetPos(tilePos);
	windowMgr::getInstance()->tileMeshes.at(6)->SetAsFloor(true);
	windowMgr::getInstance()->tileMeshes.at(6)->SetTexture(windowMgr::getInstance()->tileTextures["grassHole"]);
	tileContent.push_back(windowMgr::getInstance()->tileMeshes.at(6));

	//Side border on left
	windowMgr::getInstance()->tileMeshes.at(1)->SetScale(measures.y, measures.y, measures.z);
	windowMgr::getInstance()->tileMeshes.at(1)->SetPos(vec3(tilePos.x - ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z));
	windowMgr::getInstance()->tileMeshes.at(1)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileContent.push_back(windowMgr::getInstance()->tileMeshes.at(1));

	//Side border on right
	windowMgr::getInstance()->tileMeshes.at(2)->SetScale(measures.y, measures.y, measures.z);
	windowMgr::getInstance()->tileMeshes.at(2)->SetPos(vec3(tilePos.x + ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z));
	windowMgr::getInstance()->tileMeshes.at(2)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileContent.push_back(windowMgr::getInstance()->tileMeshes.at(2));

	//Border on the end tile and corner
	windowMgr::getInstance()->tileMeshes.at(3)->SetScale(measures.x - (measures.y * 2), measures.y, measures.y);
	windowMgr::getInstance()->tileMeshes.at(3)->SetPos(vec3(tilePos.x, tilePos.y + measures.y, tilePos.z + ((measures.x - measures.y) / 2)));
	windowMgr::getInstance()->tileMeshes.at(3)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileContent.push_back(windowMgr::getInstance()->tileMeshes.at(3));
}

void Tile::straightTile()
{
	//Create a mesh forming the tile, then add it to a vector of Meshes

	windowMgr::getInstance()->tileMeshes.at(0)->SetScale(measures.x, measures.y, measures.z);
	windowMgr::getInstance()->tileMeshes.at(0)->SetPos(tilePos);
	windowMgr::getInstance()->tileMeshes.at(0)->SetAsFloor(true);
	windowMgr::getInstance()->tileMeshes.at(0)->SetTexture(windowMgr::getInstance()->tileTextures["floorGrass"]);
	tileContent.push_back(windowMgr::getInstance()->tileMeshes.at(0));

	//Side border on left
	windowMgr::getInstance()->tileMeshes.at(1)->SetScale(measures.y, measures.y, measures.z);
	windowMgr::getInstance()->tileMeshes.at(1)->SetPos(vec3(tilePos.x - ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z));
	windowMgr::getInstance()->tileMeshes.at(1)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileContent.push_back(windowMgr::getInstance()->tileMeshes.at(1));

	//Side border on right
	windowMgr::getInstance()->tileMeshes.at(2)->SetScale(measures.y, measures.y, measures.z);
	windowMgr::getInstance()->tileMeshes.at(2)->SetPos(vec3(tilePos.x + ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z));
	windowMgr::getInstance()->tileMeshes.at(2)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileContent.push_back(windowMgr::getInstance()->tileMeshes.at(2));
}

void Tile::sceneryTile()
{
	//Not using mesh 0 but mesh 7 as different texture is used for scenery tile
	windowMgr::getInstance()->tileMeshes.at(7)->SetScale(measures.x, measures.y, measures.z);
	windowMgr::getInstance()->tileMeshes.at(7)->SetPos(tilePos);
	windowMgr::getInstance()->tileMeshes.at(7)->SetAsFloor(true);
	windowMgr::getInstance()->tileMeshes.at(7)->SetTexture(windowMgr::getInstance()->tileTextures["grassScenery"]);
	tileContent.push_back(windowMgr::getInstance()->tileMeshes.at(7));
}

void Tile::thickerStraightTile()
{
	int randomTunnel = randomNumber(0, 2);

	windowMgr::getInstance()->tileMeshes.at(0)->SetScale(measures.x, measures.y, measures.z);
	windowMgr::getInstance()->tileMeshes.at(0)->SetPos(tilePos);
	windowMgr::getInstance()->tileMeshes.at(0)->SetAsFloor(true);
	windowMgr::getInstance()->tileMeshes.at(0)->SetTexture(windowMgr::getInstance()->tileTextures["floorGrass"]);
	tileContent.push_back(windowMgr::getInstance()->tileMeshes.at(0));

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
	windowMgr::getInstance()->obstacleMeshes.at(3)->SetScale(((measures.x - ballSizeMargin) / 4) * 1, measures.y, measures.z);
	windowMgr::getInstance()->obstacleMeshes.at(3)->SetPos(vec3(tilePos.x + ((ballSizeMargin / 2) + ((((measures.x - ballSizeMargin) / 4) / 2) * 3)), tilePos.y + measures.y, tilePos.z));
	windowMgr::getInstance()->obstacleMeshes.at(3)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileContent.push_back(windowMgr::getInstance()->obstacleMeshes.at(3));

	windowMgr::getInstance()->obstacleMeshes.at(4)->SetScale(((measures.x - ballSizeMargin) / 4) * 3, measures.y, measures.z);
	windowMgr::getInstance()->obstacleMeshes.at(4)->SetPos(vec3(tilePos.x - ((ballSizeMargin / 2) + ((((measures.x - ballSizeMargin) / 4) / 2) * 1)), tilePos.y + measures.y, tilePos.z));
	windowMgr::getInstance()->obstacleMeshes.at(4)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileContent.push_back(windowMgr::getInstance()->obstacleMeshes.at(4));
}

void Tile::rightTunnel()
{
	windowMgr::getInstance()->obstacleMeshes.at(5)->SetScale(((measures.x - ballSizeMargin) / 4) * 3, measures.y, measures.z);
	windowMgr::getInstance()->obstacleMeshes.at(5)->SetPos(vec3(tilePos.x + ((ballSizeMargin / 2) + ((((measures.x - ballSizeMargin) / 4) / 2) * 1)), tilePos.y + measures.y, tilePos.z));
	windowMgr::getInstance()->obstacleMeshes.at(5)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileContent.push_back(windowMgr::getInstance()->obstacleMeshes.at(5));

	windowMgr::getInstance()->obstacleMeshes.at(6)->SetScale(((measures.x - ballSizeMargin) / 4) * 1, measures.y, measures.z);
	windowMgr::getInstance()->obstacleMeshes.at(6)->SetPos(vec3(tilePos.x - ((ballSizeMargin / 2) + ((((measures.x - ballSizeMargin) / 4) / 2) * 3)), tilePos.y + measures.y, tilePos.z));
	windowMgr::getInstance()->obstacleMeshes.at(6)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileContent.push_back(windowMgr::getInstance()->obstacleMeshes.at(6));
}

void Tile::middleTunnel()
{
	windowMgr::getInstance()->obstacleMeshes.at(7)->SetScale(((measures.x - ballSizeMargin) / 4) * 2, measures.y, measures.z);
	windowMgr::getInstance()->obstacleMeshes.at(7)->SetPos(vec3(tilePos.x + ((ballSizeMargin / 2) + ((((measures.x - ballSizeMargin) / 4) / 2) * 2)), tilePos.y + measures.y, tilePos.z));
	windowMgr::getInstance()->obstacleMeshes.at(7)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileContent.push_back(windowMgr::getInstance()->obstacleMeshes.at(7));

	windowMgr::getInstance()->obstacleMeshes.at(8)->SetScale(((measures.x - ballSizeMargin) / 4) * 2, measures.y, measures.z);
	windowMgr::getInstance()->obstacleMeshes.at(8)->SetPos(vec3(tilePos.x - ((ballSizeMargin / 2) + ((((measures.x - ballSizeMargin) / 4) / 2) * 2)), tilePos.y + measures.y, tilePos.z));
	windowMgr::getInstance()->obstacleMeshes.at(8)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileContent.push_back(windowMgr::getInstance()->obstacleMeshes.at(8));
}

void Tile::bridgeTile()
{

	windowMgr::getInstance()->planeMeshes.at(0)->SetScale(measures.x);
	windowMgr::getInstance()->planeMeshes.at(0)->SetPos(vec3(tilePos.x, tilePos.y - (measures.y / 3), tilePos.z));
	windowMgr::getInstance()->planeMeshes.at(0)->SetAsFloor(true);
	windowMgr::getInstance()->planeMeshes.at(0)->SetTexture(windowMgr::getInstance()->tileTextures["bottomBridge"]);
	tileContent.push_back(windowMgr::getInstance()->planeMeshes.at(0));

	//Mesh *floor = new Mesh(Mesh::PLANE, this_floorTexture, vec3(tilePos.x, tilePos.y - (measures.y / 3), tilePos.z), measures.x, true);
	//tileContent.push_back(floor);


	windowMgr::getInstance()->planeMeshes.at(1)->SetScale(measures.x);
	windowMgr::getInstance()->planeMeshes.at(1)->SetPos(tilePos);
	//windowMgr::getInstance()->planeMeshes.at(1)->SetAsFloor(true);
	windowMgr::getInstance()->planeMeshes.at(1)->SetTexture(windowMgr::getInstance()->tileTextures["waterBridge"]);
	tileContent.push_back(windowMgr::getInstance()->planeMeshes.at(1));


	//Mesh *surrounding = new Mesh(Mesh::PLANE, this_bridgeSurroundingTexture, tilePos, measures.x, false, true);
	//tileContent.push_back(surrounding);

	windowMgr::getInstance()->obstacleMeshes.at(8)->SetScale(ballSizeMargin, measures.y, measures.z);
	windowMgr::getInstance()->obstacleMeshes.at(8)->SetPos(tilePos);
	windowMgr::getInstance()->obstacleMeshes.at(8)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileContent.push_back(windowMgr::getInstance()->obstacleMeshes.at(8));

	//Mesh *bridge = new Mesh(Mesh::CUBOID, this_borderTexture, tilePos, ballSizeMargin, measures.y, measures.z);
	//tileContent.push_back(bridge);

	windowMgr::getInstance()->tileMeshes.at(9)->SetScale(measures.y, measures.y * 2, measures.z);
	windowMgr::getInstance()->tileMeshes.at(9)->SetPos(vec3(tilePos.x - ((measures.x - measures.y) / 2), tilePos.y + (measures.y / 2), tilePos.z));
	windowMgr::getInstance()->tileMeshes.at(9)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileContent.push_back(windowMgr::getInstance()->tileMeshes.at(9));

	//Mesh *border1 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x - ((measures.x - measures.y) / 2), tilePos.y + (measures.y / 2), tilePos.z), measures.y, measures.y * 2, measures.z);
	//tileContent.push_back(border1);

	windowMgr::getInstance()->tileMeshes.at(10)->SetScale(measures.y, measures.y * 2, measures.z);
	windowMgr::getInstance()->tileMeshes.at(10)->SetPos(vec3(tilePos.x + ((measures.x - measures.y) / 2), tilePos.y + (measures.y / 2), tilePos.z));
	windowMgr::getInstance()->tileMeshes.at(10)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileContent.push_back(windowMgr::getInstance()->tileMeshes.at(10));

	//Mesh *border2 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x + ((measures.x - measures.y) / 2), tilePos.y + (measures.y / 2), tilePos.z), measures.y, measures.y * 2, measures.z);
	//tileContent.push_back(border2);
}

void Tile::cornerTile()
{

	windowMgr::getInstance()->tileMeshes.at(0)->SetScale(measures.x, measures.y, measures.z);
	windowMgr::getInstance()->tileMeshes.at(0)->SetPos(tilePos);
	windowMgr::getInstance()->tileMeshes.at(0)->SetAsFloor(true);
	windowMgr::getInstance()->tileMeshes.at(0)->SetTexture(windowMgr::getInstance()->tileTextures["floorGrass"]);
	tileContent.push_back(windowMgr::getInstance()->tileMeshes.at(0));

	//Side border on left
	windowMgr::getInstance()->tileMeshes.at(1)->SetScale(measures.y, measures.y, measures.z);
	windowMgr::getInstance()->tileMeshes.at(1)->SetPos(vec3(tilePos.x - ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z));
	windowMgr::getInstance()->tileMeshes.at(1)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileContent.push_back(windowMgr::getInstance()->tileMeshes.at(1));

	//Border on the end tile and corner
	windowMgr::getInstance()->tileMeshes.at(4)->SetScale(measures.x - measures.y, measures.y, measures.y);
	windowMgr::getInstance()->tileMeshes.at(4)->SetPos(vec3(tilePos.x + (measures.y / 2), tilePos.y + measures.y, tilePos.z - ((measures.x - measures.y) / 2)));
	windowMgr::getInstance()->tileMeshes.at(4)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileContent.push_back(windowMgr::getInstance()->tileMeshes.at(4));

	//tiny box for corner
	windowMgr::getInstance()->tileMeshes.at(5)->SetScale(measures.y, measures.y, measures.y);
	windowMgr::getInstance()->tileMeshes.at(5)->SetPos(vec3(tilePos.x + ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z + ((measures.x - measures.y) / 2)));
	windowMgr::getInstance()->tileMeshes.at(5)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileContent.push_back(windowMgr::getInstance()->tileMeshes.at(5));
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
	windowMgr::getInstance()->obstacleMeshes.at(0)->SetScale(measures.y * 2, measures.y, measures.y * 2);
	windowMgr::getInstance()->obstacleMeshes.at(0)->SetPos(vec3(tilePos.x, tilePos.y + measures.y, tilePos.z));
	windowMgr::getInstance()->obstacleMeshes.at(0)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileObstacle.push_back(windowMgr::getInstance()->obstacleMeshes.at(0));

}

void Tile::obstacleSlalom()
{
	windowMgr::getInstance()->obstacleMeshes.at(1)->SetScale(measures.x - (measures.y * 2) - ballSizeMargin, measures.y, measures.y);
	windowMgr::getInstance()->obstacleMeshes.at(1)->SetPos(vec3(tilePos.x - (ballSizeMargin / 2), tilePos.y + measures.y, tilePos.z + ballSizeMargin * 2));
	windowMgr::getInstance()->obstacleMeshes.at(1)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileObstacle.push_back(windowMgr::getInstance()->obstacleMeshes.at(1));

	windowMgr::getInstance()->obstacleMeshes.at(2)->SetScale(measures.x - (measures.y * 2) - ballSizeMargin, measures.y, measures.y);
	windowMgr::getInstance()->obstacleMeshes.at(2)->SetPos(vec3(tilePos.x + (ballSizeMargin / 2), tilePos.y + measures.y, tilePos.z - ballSizeMargin * 2));
	windowMgr::getInstance()->obstacleMeshes.at(2)->SetTexture(windowMgr::getInstance()->tileTextures["tileWood"]);
	tileObstacle.push_back(windowMgr::getInstance()->obstacleMeshes.at(2));
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
	//double translationY = (Tile::getDimension().x / 2.0) * tan(Mesh::DegtoRads(degreesOfRotation));
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
			t->thisTexture.Bind(0);

			//updates the shader with first texture and draws the tile
			shader->Update(transform, camera);
			t->Draw();

		}
		//else if (t->isThisFluid == true)
		//{
		//	/*t->thisTexture->Bind(1);


		//	waterShader->Update(transform, camera);
		//	t->Draw();*/
		//}
		else
		{
			t->thisTexture.Bind(0);

			//Update the shader again with new textures
			shader->Update(transform, camera);

			//Draw borders of tile
			t->Draw();
		}
	}

	if (thisObstacleID != 0)
	{
		for (auto &o : tileObstacle)
		{
			o->thisTexture.Bind(0);

			//updates the shader with texture and draws the obstacle
			shader->Update(transform, camera);
			o->Draw();
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