#include "stdafx.h"
#include "Game.h"
#include "Car.h"



int main()
{
	Car car;

	Game* game = &car ;

	game->run();

	delete game;

	return 0;
}