#include "courseGenTiles.h"

// Dir constructor
Direction::Direction()
{
	going_up = false;
	going_right = false;
	going_down = true;	// Always going down first
	going_left = false;
}

void Direction::SetDir()
{
	// Based on direction and type of last tile
	// tile has an outDir, set when 
	// Based on difference in position from last tile
}



void StraightTile_V::FindNextTileCoords(Direction dir)
{
}

void StraightTile_H::FindNextTileCoords(Direction dir)
{

}

void CornerTile_BL::FindNextTileCoords(Direction dir)
{
}

void CornerTile_BR::FindNextTileCoords(Direction dir)
{
}

void CornerTile_TL::FindNextTileCoords(Direction dir)
{
}

void CornerTile_TR::FindNextTileCoords(Direction dir)
{
}
