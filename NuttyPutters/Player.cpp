#include "Player.h"
#include <fstream>
#include <vector>
#include <sstream>
#include "windowMgr.h" // to access singleton

// Constructor - loads key config from file
Player::Player(string inputConfigFilePath)
{
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


	// If the player using contoller one is player one then
	if (windowMgr::getInstance()->playerUsingControllerOne == 1)
	{
		
		// Loop through all the buttons player one has assigned to their controller and make them equal to arr[]
		for (int i = 0; i < 10; i++)
		{
			arr[i] = windowMgr::getInstance()->controllerXboxPOne[i]; // works
			//buttons[arr[i]] = windowMgr::getInstance()->controllerXboxPOne[i]; // want but wrong
			cout << "Functon " << i << " Equals " << windowMgr::getInstance()->controllerXboxPOne[i] << endl;
		}
	}
}

void Player::SetupControls()
{
	// Assign correct input file for this player
}