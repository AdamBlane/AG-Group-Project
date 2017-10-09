#include "courseGenerator.h"

// Setup 
courseGenerator::courseGenerator(int difficulty)
{
	// Take in difficulty for this game
	courseLimit = difficulty;
	// Set grid values
	// -1 makes odd number, allows for central tile
	gridLength = (courseLimit * 2) - 1;
	gridSize = gridLength * gridLength;
}

// Main algorithm function
void courseGenerator::run()
{


}
