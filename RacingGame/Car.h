#ifndef CAR_H
#define CAR_H
#include "Game.h"
#include "Constants.h"

using namespace Constants;

class Car : public Game
{
public:
	Car();

	
	void control();

	//set delay (which represents speed of the car)
	void changeSpeed();

	inline int getX() const;

	inline int getY() const;

	inline void setX(int);

	inline void setY(int);

	inline int getSpeed() const;

	inline void setSpeed(int);

	inline char getSkin() const;

	~Car();
private:
	int carX_;
	int carY_;
	int speed_;
	char skin_;


	void drawCar(int y, int x, char c);

	
};

int Car::getX() const
{
	return carX_;
}



int Car::getY() const
{
	return carY_;
}



char Car::getSkin() const
{
	return skin_;
}



int Car::getSpeed() const
{
	return abs(speed_ - DEFAULT_SPEED);
}



void Car::setY(int y)
{
	carY_ = y;
}




void Car::setSpeed(int speed)
{
	speed_ = speed;
}



void Car::setX(int x)
{
	carX_ = x;
}

#endif