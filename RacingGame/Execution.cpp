#include "stdafx.h"
#include "Execution.h"

#include "conio.h"
#include "Constants.h"

using namespace Constants;


Execution::Execution() : Game()
{
}

void Execution::placeCar()
{
	setX(DEFAULT_CAR_X);
	setY(DEFAULT_CAR_Y);

	int x = getX();
	int y = getY();

	gameIsOn_ = true;

	//start of time counting
	startTime_ = clock();

	//clear the track
	for (int i = MIN_X + 1; i<MAX_X - 1; i++)
		for (int j = MIN_Y; j < MAX_Y; j++) {
			setTrack(j, i, ' ');
		}

	setTrack(y, x, getSkin());
	setTrack(y - AXIS_SHIFT, x, getSkin());
	setTrack(y - AXIS_DOUBLE_SHIFT, x, getSkin());
	setTrack(y - AXIS_TRIPLE_SHIFT, x, getSkin());
	setTrack(y, x - AXIS_SHIFT, getSkin());
	setTrack(y, x + AXIS_SHIFT, getSkin());
	setTrack(y - AXIS_DOUBLE_SHIFT, x - AXIS_SHIFT, getSkin());
	setTrack(y - AXIS_DOUBLE_SHIFT, x + AXIS_SHIFT, getSkin());;
}



void Execution::generateObstacle()
{
	if (obstacleY_ < MAX_OBSTACLE_Y) {
		removeObstacle();

		obstacleY_++;
		setTrack(obstacleY_, obstacleX_, OBSTACLE_SKIN);
		setTrack(obstacleY_ + AXIS_SHIFT, obstacleX_, OBSTACLE_SKIN);
		setTrack(obstacleY_ + AXIS_DOUBLE_SHIFT, obstacleX_, OBSTACLE_SKIN);
		setTrack(obstacleY_, obstacleX_ + AXIS_SHIFT, OBSTACLE_SKIN);
		setTrack(obstacleY_ + AXIS_SHIFT, obstacleX_ + AXIS_SHIFT, OBSTACLE_SKIN);
		setTrack(obstacleY_ + AXIS_DOUBLE_SHIFT, obstacleX_ + AXIS_SHIFT, OBSTACLE_SKIN);
		setTrack(obstacleY_, obstacleX_ - AXIS_SHIFT, OBSTACLE_SKIN);
		setTrack(obstacleY_ + AXIS_SHIFT, obstacleX_ - AXIS_SHIFT, OBSTACLE_SKIN);
		setTrack(obstacleY_ + AXIS_DOUBLE_SHIFT, obstacleX_ - AXIS_SHIFT, OBSTACLE_SKIN);
	}

	else if (obstacleY_ == MAX_OBSTACLE_Y) {
		removeObstacle();

		obstacleY_ = 0;
		obstacleX_ = calculations_.computeX(MIN_OBSTACLE_X, MAX_OBSTACLE_X);
	}
}



void Execution::bump()
{
	if (gameOver_.isCrushed(track_, getSkin(), getY(), getX()))
	{
		std::cout << "Game Over\nPress ENTER to try again" << std::endl;

		if (score_ > best_) {
			best_ = score_;
		}

		if (calculations_.getTime(startTime_, endTime_) > bestTime_) {
			bestTime_ = calculations_.getTime(startTime_, endTime_);
		}

		setSpeed(DEFAULT_SPEED);

		obstacleY_ = 0;
		obstacleX_ = calculations_.computeX(MIN_OBSTACLE_X, MAX_OBSTACLE_X);
		score_ = 0;

		gameIsOn_ = false;
	}
}



void Execution::run()
{
	std::cout << "\n\t o\n\tooo\tRACING SIMULATOR\n\t o\n\tooo\n\nPress ENTER to RACE" << std::endl;
	std::cout << "\n\n\nCONTROLS:\nLEFT ARROW/RIGHT ARROW - move left/right\nUP ARROW/DOWN ARROW - speed up/down\nENTER - pause/resume\nESC - quit" << std::endl;

	while (true) {
		if (_getch() == KEY_ENTER) {
			placeCar();
			while (gameIsOn_) {
				system("cls");
				std::cout << "Score: " << score_ << " \tBest score: " << best_ << std::endl << "Time: " << calculations_.getTime(startTime_, endTime_) << " \tBest time: " << bestTime_ << std::endl << "Speed: " << getSpeed() << std::endl;

				drawer_.drawTrack(track_);
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

void Execution::removeObstacle()
{
	setTrack(obstacleY_, obstacleX_, ' ');
	setTrack(obstacleY_ + AXIS_SHIFT, obstacleX_, ' ');
	setTrack(obstacleY_ + AXIS_DOUBLE_SHIFT, obstacleX_, ' ');
	setTrack(obstacleY_, obstacleX_ + AXIS_SHIFT, ' ');
	setTrack(obstacleY_ + AXIS_SHIFT, obstacleX_ + AXIS_SHIFT, ' ');
	setTrack(obstacleY_ + AXIS_DOUBLE_SHIFT, obstacleX_ + AXIS_SHIFT, ' ');
	setTrack(obstacleY_, obstacleX_ - AXIS_SHIFT, ' ');
	setTrack(obstacleY_ + AXIS_SHIFT, obstacleX_ - AXIS_SHIFT, ' ');
	setTrack(obstacleY_ + AXIS_DOUBLE_SHIFT, obstacleX_ - AXIS_SHIFT, ' ');
}


Execution::~Execution()
{
}
