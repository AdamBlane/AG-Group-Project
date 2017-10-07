#include "tile.h"


tile::tile(vec3 newPosition)
{
	tilePos = newPosition;
	createTile();
}

tile::~tile()
{
}

vec3 tile::getPosition()
{
	return vec3(tilePos);
}

void tile::createTile()
{
	Mesh floor(Mesh::CUBOID);
	floor.setPosition(tilePos.x, tilePos.y, tilePos.z);
	floor.size(measures.x, measures.y, measures.z);
	floor.createMesh();
	tileContent.push_back(floor);

	Mesh border1(Mesh::CUBOID);
	border1.setPosition(tilePos.x, tilePos.y + floor.getSize().x, tilePos.z);
	border1.size(0.1f, 0.1f, 1.0f);
	border1.createMesh();
	tileContent.push_back(border1);

	Mesh border2(Mesh::CUBOID);
	border2.setPosition(tilePos.x + (floor.getSize().y - 0.1f), tilePos.y + floor.getSize().x, tilePos.z);
	border2.size(0.1f, 0.1f, 1.0f);
	border2.createMesh();
	tileContent.push_back(border2);

}

void tile::drawTile()
{
	for (auto &content : tileContent)
	{
		content.Draw();
	}
}
