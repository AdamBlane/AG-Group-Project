#include "tileBuilder.h"


Tile::Tile(typeTile desiredType, string floorTexture, string borderTexture, vec3 newPosition)
{
	//setting tile properties
	//tilePos = newPosition;

	transform.getPos() = newPosition;

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
		startTile();
		break;
	case STRAIGHT:
		straightTile();
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
	Mesh *floor = new Mesh(Mesh::CUBOID, this_floorTexture, tilePos, measures.x, measures.y, measures.z);
	tileContent.push_back(floor);

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
	Mesh *floor = new Mesh(Mesh::CUBOID, this_floorTexture, tilePos, measures.x, measures.y, measures.z);
	tileContent.push_back(floor);

	Mesh *border1 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x - ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z), measures.y, measures.y, measures.z);
	tileContent.push_back(border1);

	Mesh *border2 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x + ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z), measures.y, measures.y, measures.z);
	tileContent.push_back(border2);
}

void Tile::cornerTile()
{
	Mesh *floor = new Mesh(Mesh::CUBOID, this_floorTexture, tilePos, measures.x, measures.y, measures.z);
	tileContent.push_back(floor);

	Mesh *border1 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x - ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z), measures.y, measures.y, measures.z);
	tileContent.push_back(border1);

	Mesh *border2 = new Mesh(Mesh::CUBOID, this_borderTexture, vec3(tilePos.x + (measures.y / 2), tilePos.y + measures.y, tilePos.z - ((measures.x - measures.y) / 2)), measures.x - measures.y, measures.y, measures.y);
	tileContent.push_back(border2);

	Mesh *border3 = new Mesh(Mesh::BOX, this_borderTexture, vec3(tilePos.x + ((measures.x - measures.y) / 2), tilePos.y + measures.y, tilePos.z + ((measures.x - measures.y) / 2)), measures.y);
	tileContent.push_back(border3);

}

//draws a tile passing a shader, a transform and a camera, in order to call Update method of the shader itself and allowing different textures to be bound
void Tile::drawTile(Shader* shader, AllCamera::free_camera camera)
{
	//one shader can be used to render more than 1 texture, but in must be updated after different textures are bind to it.
	//texture binded after a new shader.Update() should have index 0
	tileContent[0]->thisTexture->Bind(0);

	//updates the shader with first texture and draws the tile
	shader->Update(transform, (camera.get_Projection() * camera.get_View()));
	tileContent[0]->Draw();

	//loops through remaining content of the vector of Mesh
	for (unsigned int i = 1; i < tileContent.size(); i++)
	{
		tileContent[i]->thisTexture->Bind(0);

		//Update the shader again with new textures
		shader->Update(transform ,(camera.get_Projection() * camera.get_View()));

		//Draw borders of tile
		tileContent[i]->Draw();
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