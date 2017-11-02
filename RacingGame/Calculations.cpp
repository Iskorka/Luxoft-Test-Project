#include "stdafx.h"
#include "Calculations.h"
#include <ctime>
#include <random>
#include "Constants.h"


Calculations::Calculations()
{
}



int Calculations::computeX(int min, int max)
{
	srand(time(0));
	return rand() % (max - min + 1) + min; //rand() (b - a + 1) + a
}


int Calculations::getTime(int startTime, int endTime)
{
	return (endTime - startTime) / Constants::ONE_SECOND;
}



Calculations::~Calculations()
{
}
