#include "stdafx.h"
#include "Game.h"
#include <ctime>
#include <windows.h>
#include "conio.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "Constants.h"

using namespace Constants;



Game::Game() : score_(0), best_(0), endTime_(0), bestTime_(0), obstacleX_(calculations.computeX(MIN_OBSTACLE_X, MAX_OBSTACLE_X)), obstacleY_(0)
{
	track_ = {	
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |",
		"|               |" 
	};
}



void Game::placeCar()
{
	setX(DEFAULT_CAR_X);
	setY(DEFAULT_CAR_Y);

	int x = getX();
	int y = getY();

	gameIsOn_ = true;

	//start of time counting
	startTime_ = clock();

	//clear the track
	for (int i = 1; i<MAX_X - 1; i++)
		for (int j = 0; j < MAX_Y; j++) {
			setTrack(j, i, ' ');
		}

	setTrack(y, x, getSkin());
	setTrack(y - 1, x, getSkin());
	setTrack(y - 2, x, getSkin());
	setTrack(y - 3, x, getSkin());
	setTrack(y, x - 1, getSkin());
	setTrack(y, x + 1, getSkin());
	setTrack(y - 2, x - 1, getSkin());
	setTrack(y - 2, x + 1, getSkin());;
}



void Game::generateObstacle()
{
	if (obstacleY_ < MAX_OBSTACLE_Y) {
		removeObstacle();

		obstacleY_ += 1;
		setTrack(obstacleY_, obstacleX_, 'T');
		setTrack(obstacleY_ + 1, obstacleX_, 'T');
		setTrack(obstacleY_ + 2, obstacleX_, 'T');
		setTrack(obstacleY_, obstacleX_ + 1, 'T');
		setTrack(obstacleY_ + 1, obstacleX_ + 1, 'T');
		setTrack(obstacleY_ + 2, obstacleX_ + 1, 'T');
		setTrack(obstacleY_, obstacleX_ - 1, 'T');
		setTrack(obstacleY_ + 1, obstacleX_ - 1, 'T');
		setTrack(obstacleY_ + 2, obstacleX_ - 1, 'T');
	}

	else if (obstacleY_ == MAX_OBSTACLE_Y) {
		removeObstacle();

		obstacleY_ = 0;
		obstacleX_ = calculations.computeX(MIN_OBSTACLE_X, MAX_OBSTACLE_X);
	}
}



void Game::bump()
{
	if (gameOver.isCrushed(track_, getSkin(), getY(), getX()))
	{
		std::cout << "Game Over\nPress ENTER to try again" << std::endl;

		if (score_ > best_) {
			best_ = score_;
		}

		if (calculations.getTime(startTime_, endTime_) > bestTime_) {
			bestTime_ = calculations.getTime(startTime_, endTime_);
		}

		setSpeed(DEFAULT_SPEED);

		obstacleY_ = 0;
		obstacleX_ = calculations.computeX(MIN_OBSTACLE_X, MAX_OBSTACLE_X);
		score_ = 0;

		gameIsOn_ = false;
	}
}



void Game::run()
{
	std::cout << "\n\t o\n\tooo\tRACING SIMULATOR\n\t o\n\tooo\n\nPress ENTER to RACE" << std::endl;
	std::cout << "\n\n\nCONTROLS:\nLEFT ARROW/RIGHT ARROW - move left/right\nUP ARROW/DOWN ARROW - speed up/down\nENTER - pause/resume\nESC - quit" << std::endl;

	while (true) {
		if (_getch() == KEY_ENTER) {
			placeCar();
			while (gameIsOn_) {
				system("cls");
				std::cout << "Score: " << score_ << " \tBest score: " << best_ << std::endl << "Time: " << calculations.getTime(startTime_, endTime_) << " \tBest time: " << bestTime_ << std::endl << "Speed: " << getSpeed() << std::endl;
				
				drawer.drawTrack(track_);
				bump();

				while (_kbhit()) {
					control(); //virtual from Car
				}

				changeSpeed(); //virtual from Car

				endTime_ = clock();

				if (score_ > 5) {
					generateObstacle();
				}

				score_++;
			}
		}
	}
}



void Game::removeObstacle()
{
	setTrack(obstacleY_, obstacleX_, ' ');
	setTrack(obstacleY_ + 1, obstacleX_, ' ');
	setTrack(obstacleY_ + 2, obstacleX_, ' ');
	setTrack(obstacleY_, obstacleX_ + 1, ' ');
	setTrack(obstacleY_ + 1, obstacleX_ + 1, ' ');
	setTrack(obstacleY_ + 2, obstacleX_ + 1, ' ');
	setTrack(obstacleY_, obstacleX_ - 1, ' ');
	setTrack(obstacleY_ + 1, obstacleX_ - 1, ' ');
	setTrack(obstacleY_ + 2, obstacleX_ - 1, ' ');
}





Game::~Game()
{
}
