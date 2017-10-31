#include "stdafx.h"
#include "Calculations.h"
#include <ctime>
#include <random>



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
	return (endTime - startTime) / 1000;
}



Calculations::~Calculations()
{
}
