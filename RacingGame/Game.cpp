#include "stdafx.h"
#include "Game.h"
#include <ctime>
#include <windows.h>
#include "conio.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "Constants.h"

using namespace Constants;



Game::Game() : score_(0), best_(0), endTime_(0), bestTime_(0), obstacleX_(calculations_.computeX(MIN_OBSTACLE_X, MAX_OBSTACLE_X)), obstacleY_(0)
{
	track_ = {	
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |" 
	};
}


Game::~Game()
{
}
