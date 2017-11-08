#ifndef CAR_H
#define CAR_H
#include "Game.h"
#include "Execution.h"
#include "Constants.h"

using namespace Constants;

class Car : public Execution
{
public:
	Car();

	
	void control();

	//set delay (which represents speed of the car)
	void changeSpeed();

	int getX() const;

	int getY() const;

	void setX(int x);

	void setY(int y);

	int getSpeed() const;

	void setSpeed(int speed);

	char getSkin() const;

	~Car();
private:
	int carX_;
	int carY_;
	int speed_;
	char skin_;


	void drawCar(int y, int x, char carSkin);

	
};

inline int Car::getX() const
{
	return carX_;
}



inline int Car::getY() const
{
	return carY_;
}



inline char Car::getSkin() const
{
	return skin_;
}



inline int Car::getSpeed() const
{
	return abs(speed_ - DEFAULT_SPEED);
}



inline void Car::setY(int y)
{
	carY_ = y;
}




inline void Car::setSpeed(int speed)
{
	speed_ = speed;
}



inline void Car::setX(int x)
{
	carX_ = x;
}

#endif