#include "tile.h"

tile::tile(vec3 newPosition)
{
	position = newPosition;
	createTile();
}

tile::~tile()
{
}

vec3 tile::getPosition()
{
	return vec3(position);
}

void tile::createTile()
{
	//geometry_builder *floor = new geometry_builder(geometry_builder::CUBOID);
	//floor->setPosition(position.x, position.y, position.z);
	//floor->size(5.0f, 100.0f);
	//tileContent->push_back(*floor);

	//geometry_builder *border1 = new geometry_builder(geometry_builder::CUBOID);
	//border1->setPosition(position.x, position.y, position.z);
	//border1->size(100.0f, 20.0f);
	//tileContent->push_back(*border1);

	//geometry_builder *border2 = new geometry_builder(geometry_builder::CUBOID);
	//border2->setPosition(position.x + (floor->getCuboidSize().y - 20.0f), position.y, position.z);
	//border2->size(100.0f, 20.0f);
	//tileContent->push_back(*border2);

	//cout << tileContent->size() << " elements in the tile" <<endl;
}

//void tile::drawTile()
//{
//	for (auto &content : *tileContent)
//	{
//		content.draw();
//	}
//}
