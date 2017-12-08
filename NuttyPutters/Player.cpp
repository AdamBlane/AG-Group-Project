#include "Player.h"
#include <fstream>
#include <vector>
#include <sstream>

// Constructor - loads key config from file
Player::Player(string inputConfigFilePath)
{
	// Ensure flags are initially set to false
	firePressed = jumpPressed = upPressed = downPressed = leftPressed = rightPressed = zoomInPressed = zoomOutPressed = false;
	firePressedC = jumpPressedC = upPressedC = downPressedC = leftPressedC = rightPressedC = zoomInPressedC = zoomOutPressedC = false;

	// First set necessary vars
	power = 0.0f;
	// Open the file for reading
	ifstream inputConfig(inputConfigFilePath);
	// First read in every line found
	vector<string> lines;
	while (!inputConfig.eof())
	{
		// For the line currently being read
		string line;
		// Read line into the string var
		getline(inputConfig, line);
		// Add it to lines list
		lines.push_back(line);
	}
	// Then parse each line - function,button value
	for (auto &l : lines)
	{
		// Create a string stream for this line, to parse it
		istringstream iss(l);
		// Each line reads 'function, button_value'
		string function, button_value;
		// Split line on comma - this only gives first substring
		getline(iss, function, ',');
		// Put remaining substring into string var
		iss >> button_value;

		// Now set this player's input values accordingly
		if (function == "fire")
		{
			fireButtton =  stoi(button_value);
			continue;
		}
		else if (function == "jump")
		{
			jumpButton = stoi(button_value);
			continue;
		}
		else if (function == "up")
		{
			upButton = stoi(button_value);
			continue;
		}
		else if (function == "down")
		{
			downButton = stoi(button_value);
			continue;
		}
		else if (function == "left")
		{
			leftButton = stoi(button_value);
			continue;
		}
		else if (function == "right")
		{
			rightButton = stoi(button_value);
			continue;
		}
		else if (function == "zoomIn")
		{
			zoomInButton = stoi(button_value);
			continue;
		}
		else if (function == "zoomOut")
		{
			zoomOutButton = stoi(button_value);
			continue;
		}
		else if (function == "fireC")
		{
			fireButtonC = stoi(button_value);
			continue;
		}
		
	}

}