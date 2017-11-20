
#include "courseGenTiles.h"
#include "gameScene.h"



// Set coords of this tile
void BaseTile::SetCoords(vec3 coords) {	thisCoords = coords; }

// Set next coords of this tile
void BaseTile::SetNextCoords(vec3 coords) {	thisCoords = coords; }

// Getter of next coords
vec3 BaseTile::GetNextCoords() { return nextCoords; }

// Getter of this coords
vec3 BaseTile::GetThisCoords() { return thisCoords; }