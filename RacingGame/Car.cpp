#include "stdafx.h"
#include "Car.h"
#include <windows.h>
#include "conio.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "Constants.h"

using namespace Constants;


Car::Car() : carX_(DEFAULT_CAR_X), carY_(DEFAULT_CAR_Y), speed_(DEFAULT_SPEED), skin_('o') {}



void Car::control()
{
	switch (_getch()) {
		case KEY_LEFT:
			if (carX_ == MIN_CAR_X) {
				break;
			}

			drawCar(carY_, carX_, ' ');
			carX_ --;
			break;

		case KEY_RIGHT:
			if (carX_ == MAX_CAR_X) {
				break;
			}

			drawCar(carY_, carX_, ' ');
			carX_ ++;
			break;

		case KEY_UP:
			if (speed_ > MIN_SPEED) {
				speed_ -= SPEED_INCREMENT;
			}
			break;

		case KEY_DOWN:
			if (speed_ < MAX_SPEED) {
				speed_ += SPEED_INCREMENT;
			}
			break;

		case KEY_ENTER:
			while (true) {
				if (_getch() == 13) {
					break;
				}
			};
			break;

		case KEY_ESC: 
			exit(0);
			break;
	}

	drawCar(carY_, carX_, skin_);
}


//set delay (which represents speed of the car)
void Car::changeSpeed()
{
	Sleep(speed_);
}



int Car::getX() 
{
	return carX_;
}



int Car::getY() 
{
	return carY_;
}



void Car::setX(int x) 
{
	carX_ = x;
}



void Car::setY(int y) 
{
	carY_ = y;
}



int Car::getSpeed() 
{
	return abs(speed_ - DEFAULT_SPEED);
}



void Car::setSpeed(int speed) 
{
	speed_ = speed;
}



char Car::getSkin() 
{
	return skin_;
}



void Car::drawCar(int y, int x, char c)
{
	track[y][x] = c;
	track[y - 1][x] = c;
	track[y - 2][x] = c;
	track[y - 3][x] = c;
	track[y][x - 1] = c;
	track[y][x + 1] = c;
	track[y - 2][x - 1] = c;
	track[y - 2][x + 1] = c;
}



Car::~Car()
{
}


