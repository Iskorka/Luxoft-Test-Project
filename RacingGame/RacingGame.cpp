#include "stdafx.h"
#include "Game.h"
#include "Car.h"
#include <ctime>
#include <iostream>

int main()
{
	Car car;

	Game* game = &car ;

	game->run();

	return 0;
}