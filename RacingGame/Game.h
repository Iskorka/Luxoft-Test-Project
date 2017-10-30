#pragma once
#include <vector>



class Game
{
public:

	std::vector<std::string> track;

	Game();

	virtual void control() = 0;
	virtual void changeSpeed() = 0;
	virtual int getX() = 0;
	virtual int getY() = 0;
	virtual void setX(int X) = 0;
	virtual void setY(int Y) = 0;
	virtual int getSpeed() = 0;
	virtual void setSpeed(int sp) = 0;
	virtual char getSkin() = 0;

	//place a car on the track
	void placeCar();

	//output the track into a console
	void drawTrack();

	//create and approach an obstacle
	void generateObstacle();

	//if car bumped into an obstacle, reset score and time, set best results and take off gameIsOn flag
	void bump();

	//algorithm that launches the game
	void run();

	~Game();

private:
	int score_;
	int best_;
	int startTime_, endTime_, bestTime_;
	int obstacleX_, obstacleY_;
	bool gameIsOn_; //game-is-running-flag

	void removeObstacle();

	//generate random X axis for obstacle
	int computeObstacleX();

	int getTime();
};

