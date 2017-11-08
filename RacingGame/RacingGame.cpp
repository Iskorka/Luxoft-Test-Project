#include "stdafx.h"
#include "Game.h"
#include "Execution.h"
#include "Car.h"



int main()
{
	Car car;

	Execution* game = &car ;

	game->run();

	delete game;

	return 0;
}