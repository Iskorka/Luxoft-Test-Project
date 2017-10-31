#include "stdafx.h"
#include "GameOver.h"
#include <vector>
#include <string>
#include <iostream>
#include "Constants.h"
#include <Windows.h>
#include <ctime>

using namespace Constants;

GameOver::GameOver()
{
}



bool GameOver::isCrushed(std::vector<std::string> track, char car, int carY, int carX)
{
	if (track[carY][carX] != car ||
		track[carY - 1][carX] != car ||
		track[carY - 2][carX] != car ||
		track[carY - 3][carX] != car ||
		track[carY][carX - 1] != car ||
		track[carY][carX + 1] != car ||
		track[carY - 2][carX - 1] != car ||
		track[carY - 2][carX + 1] != car){

		return true;
	}

	return false;
}



GameOver::~GameOver()
{
}
