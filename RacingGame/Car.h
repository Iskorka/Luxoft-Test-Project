#pragma once
#include "Game.h"

class Car : public Game
{
public:
	Car();

	
	void control();

	//set delay (which represents speed of the car)
	void changeSpeed();

	inline int getX();

	inline int getY();

	inline void setX(int x);

	inline void setY(int y);

	inline int getSpeed();

	inline void setSpeed(int speed);

	inline char getSkin();

	~Car();
private:
	int carX_;
	int carY_;
	int speed_;
	char skin_;


	void drawCar(int y, int x, char c);

	
};

