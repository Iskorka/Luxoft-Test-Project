#ifndef GAME_H
#define GAME_H
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Constants.h"
#include "Drawer.h"
#include "GameOver.h"
#include "Calculations.h"

using namespace Constants;


class Game
{
public:
	Game();

	virtual void control() = 0;
	virtual void changeSpeed() = 0;
	virtual int getX() const = 0;
	virtual int getY() const = 0;
	virtual void setX(int X) = 0;
	virtual void setY(int Y) = 0;
	virtual int getSpeed() const = 0;
	virtual void setSpeed(int sp) = 0;
	virtual char getSkin() const = 0;
	
	void setTrack(int y, int x, char skin);

	std::vector<std::string> getTrack() const;

	void placeCar();

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
	std::vector<std::string> track_;
	void removeObstacle();

	Drawer drawer_;
	GameOver gameOver_;
	Calculations calculations_;
};




inline void Game::setTrack(int y, int x, char skin) {
	track_[y][x] = skin;
}




inline std::vector<std::string> Game::getTrack() const {
	return track_;
}

#endif