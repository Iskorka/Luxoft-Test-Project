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



Game::Game() : score_(0), best_(0), endTime_(0), bestTime_(0), obstacleX_(computeObstacleX()), obstacleY_(0)
{
	track = {	
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
			track[j][i] = ' ';
		}

	track[y][x] = getSkin();
	track[y - 1][x] = getSkin();
	track[y - 2][x] = getSkin();
	track[y - 3][x] = getSkin();
	track[y][x - 1] = getSkin();
	track[y][x + 1] = getSkin();
	track[y - 2][x - 1] = getSkin();
	track[y - 2][x + 1] = getSkin();
}



void Game::drawTrack()
{
	system("cls");

	std::cout << "Score: " << score_ << " \tBest score: " << best_ << std::endl << "Time: " << getTime() << " \tBest time: " << bestTime_ << std::endl << "Speed: " << getSpeed() << std::endl;
	
	for (int i = 0; i < 18; i++) {
		std::cout << track[i] << std::endl;
	}
}



void Game::generateObstacle()
{
	if (obstacleY_ < 15) {
		removeObstacle();

		obstacleY_ += 1;
		track[obstacleY_][obstacleX_] = 'T';
		track[obstacleY_ + 1][obstacleX_] = 'T';
		track[obstacleY_ + 2][obstacleX_] = 'T';
		track[obstacleY_][obstacleX_ + 1] = 'T';
		track[obstacleY_ + 1][obstacleX_ + 1] = 'T';
		track[obstacleY_ + 2][obstacleX_ + 1] = 'T';
		track[obstacleY_][obstacleX_ - 1] = 'T';
		track[obstacleY_ + 1][obstacleX_ - 1] = 'T';
		track[obstacleY_ + 2][obstacleX_ - 1] = 'T';
	}

	else if (obstacleY_ == 15) {
		removeObstacle();

		obstacleY_ = 0;
		obstacleX_ = computeObstacleX();
	}
}



void Game::bump()
{
	char car = getSkin();

	int y = getY();
	int x = getX();

	if (track[y][x] != car || 
		track[y - 1][x] != car || 
		track[y - 2][x] != car || 
		track[y - 3][x] != car || 
		track[y][x - 1] != car || 
		track[y][x + 1] != car || 
		track[y - 2][x - 1] != car || 
		track[y - 2][x + 1] != car) 
	{
		std::cout << "Game Over\nPress ENTER to try again" << std::endl;

		if (score_ > best_)
			best_ = score_;

		if (getTime() > bestTime_)
			bestTime_ = getTime();

		setSpeed(DEFAULT_SPEED);

		obstacleY_ = 0;
		obstacleX_ = computeObstacleX();

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
				drawTrack();
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
	track[obstacleY_][obstacleX_] = ' ';
	track[obstacleY_ + 1][obstacleX_] = ' ';
	track[obstacleY_ + 2][obstacleX_] = ' ';
	track[obstacleY_][obstacleX_ + 1] = ' ';
	track[obstacleY_ + 1][obstacleX_ + 1] = ' ';
	track[obstacleY_ + 2][obstacleX_ + 1] = ' ';
	track[obstacleY_][obstacleX_ - 1] = ' ';
	track[obstacleY_ + 1][obstacleX_ - 1] = ' ';
	track[obstacleY_ + 2][obstacleX_ - 1] = ' ';
}


//generate random X axis for obstacle
int Game::computeObstacleX()
{
	srand(time(0));
	return rand() % (MAX_OBSTACLE_X - MIN_OBSTACLE_X + 1) + MIN_OBSTACLE_X; //rand() (b - a + 1) + a
}


int Game::getTime()
{
	return (endTime_ - startTime_) / 1000;
}


Game::~Game()
{
}
