#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "conio.h"
#include <string>
#include <vector>
#include "math.h"

using namespace std;


std::vector<std::string> track = {
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

class Game
{
public:
	Game() : score_(0), best_(0), endTime_(0), bestTime_(0), obstacleX_(computeObstacleX()), obstacleY_(0) {}

	virtual void control() = 0;
	virtual void changeSpeed() = 0;
	virtual int getX() = 0;
	virtual int getY() = 0;
	virtual void setX(int X) = 0;
	virtual void setY(int Y) = 0;
	virtual int getSpeed() = 0;
	virtual void setSpeed(int sp) = 0;
	virtual int getDefaultSpeed() = 0;
	virtual char getSkin() = 0;


	//place a car on the track
	void placeCar() 
	{
		setX(8);
		setY(14);

		int x = getX();
		int y = getY();

		gameIsOn_ = true;

		//start of time counting
		startTime_ = clock();

		//clear the track
		for (int i = 1; i<16; i++)
			for (int j = 0; j < 18; j++) {
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


	void drawTrack() 
	{
		system("cls");

		cout << "Score: " << score_ << " \tBest score: " << best_ << endl << "Time: " << getTime() << " \tBest time: " << bestTime_ << endl << "Speed: " << getSpeed() << endl;

		for (int i = 0; i < 18; i++) {
			cout << track[i] << endl;
		}
	}


	//create and approach an obstacle
	void generateObstacle() 
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


	//if car bumped into an obstacle, reset score and time, set best results and take off gameIsOn flag
	bool isBumped() 
	{
		char car = getSkin();

		int y = getY();
		int x = getX();

		if (track[y][x] != car || track[y - 1][x] != car || track[y - 2][x] != car
			|| track[y - 3][x] != car || track[y][x - 1] != car || track[y][x + 1] != car
			|| track[y - 2][x - 1] != car || track[y - 2][x + 1] != car) {
			cout << "Game Over\nPress ENTER to try again" << endl;

			if (score_ > best_) 
				best_ = score_;

			if (getTime() > bestTime_) 
				bestTime_ = getTime();

			setSpeed(getDefaultSpeed());

			obstacleY_ = 0;
			obstacleX_ = computeObstacleX();

			return false;
		}
		return true;
	}


	//algorithm that launches the game
	void run() 
	{
		cout << "\n\t o\n\tooo\tRACING CHAMPION PRO GALAXY 9000 v1 GO\n\t o\n\tooo\n\nPress ENTER to RACE" << endl;
		cout << "\n\n\nCONTROLS:\nLEFT ARROW/RIGHT ARROW - move left/right\nUP ARROW/DOWN ARROW - speed up/down\nENTER - pause/resume\nESC - quit" << endl;

		while (true) {
			if (_getch() == 13) {
				placeCar();

				while (gameIsOn_) {
					while (_kbhit()) {
						control(); //virtual from Car
					}

					changeSpeed(); //virtual from Car

					drawTrack();

					endTime_ = clock();

					gameIsOn_ = isBumped();

					if (score_ > 5) {
						generateObstacle();
					}

					score_++;
				}
			}
		}
	}


private:
	int score_;
	int best_;
	int startTime_, endTime_, bestTime_;
	int obstacleX_, obstacleY_;
	bool gameIsOn_; //game-is-running-flag

	void removeObstacle() 
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
	int computeObstacleX() 
	{
		srand(time(0));
		return rand() % (13 - 2 + 1) + 2; //rand() (b - a + 1) + a
	}


	int getTime() 
	{
		return (endTime_ - startTime_) / 1000;
	}
};




//just a regular car
class RegularCar : public Game
{
public:
	RegularCar() : carX_(8), carY_(14), speed_(getDefaultSpeed()), skin_('o') {}


	int getDefaultSpeed() 
	{
		return 150; 
	}


	//key binding: 75 - left, 77 - right, 72 - up, 80 - down, 13 - enter, 27 - esc
	void control() 
	{
		switch (_getch()) {
		case 75:
			if (carX_ == 2) 
				break;

			removeCar();
			carX_ -= 1;
			break;

		case 77:
			if (carX_ == 14) 
				break;

			removeCar();
			carX_ += 1;
			break;

		case 72: if (speed_ > 50) 
					speed_ -= 50; 
			break;

		case 80: if (speed_ < 150) 
					speed_ += 50; 
			break;

		case 13:
			while (true) {
				if (_getch() == 13) {
					break;
				}
			}; 
			break;

		case 27: exit(0); 
			break;
		}

		track[carY_][carX_] = skin_;
		track[carY_ - 1][carX_] = skin_;
		track[carY_ - 2][carX_] = skin_;
		track[carY_ - 3][carX_] = skin_;
		track[carY_][carX_ - 1] = skin_;
		track[carY_][carX_ + 1] = skin_;
		track[carY_ - 2][carX_ - 1] = skin_;
		track[carY_ - 2][carX_ + 1] = skin_;
	}


	//set delay (which represents speed of the car)
	void changeSpeed() 
	{
		Sleep(speed_);
	}


	int getX() {
		return carX_; 
	}


	int getY() { 
		return carY_; 
	}


	void setX(int x) { 
		carX_ = x;
	}


	void setY(int y) {
		carY_ = y; 
	}


	int getSpeed() {
		return abs(speed_ - 150);
	}


	void setSpeed(int speed) {
		speed_ = speed; 
	}


	char getSkin() { 
		return skin_; 
	}


private:
	int carX_;
	int carY_;
	int speed_;
	char skin_;


	void removeCar() 
	{
		track[carY_][carX_] = ' ';
		track[carY_ - 1][carX_] = ' ';
		track[carY_ - 2][carX_] = ' ';
		track[carY_ - 3][carX_] = ' ';
		track[carY_][carX_ - 1] = ' ';
		track[carY_][carX_ + 1] = ' ';
		track[carY_ - 2][carX_ - 1] = ' ';
		track[carY_ - 2][carX_ + 1] = ' ';
	}
};


//superslow car — identical to previous class, but with different speed_ and skin_ fields
class VerySlowCar : public Game
{
public:
	VerySlowCar() : carX_(8), carY_(14), speed_(getDefaultSpeed()), skin_('S') {}


	int getDefaultSpeed() { 
		return 400; 
	}


	void control() 
	{
		switch (_getch()) {
		case 75:
			if (carX_ == 2) 
				break;

			removeCar();
			carX_ -= 1;
			break;

		case 77:
			if (carX_ == 14) 
				break;

			removeCar();
			carX_ += 1;
			break;

		case 72: if (speed_ > 300) 
					speed_ -= 20; 
			break;

		case 80: if (speed_ < 400) 
					speed_ += 20; 
			break;

		case 13:
			while (true) {
				if (_getch() == 13) {
					break;
				}
			}; 
			break;

		case 27: exit(0); 
			break;
		}

		track[carY_][carX_] = skin_;
		track[carY_ - 1][carX_] = skin_;
		track[carY_ - 2][carX_] = skin_;
		track[carY_ - 3][carX_] = skin_;
		track[carY_][carX_ - 1] = skin_;
		track[carY_][carX_ + 1] = skin_;
		track[carY_ - 2][carX_ - 1] = skin_;
		track[carY_ - 2][carX_ + 1] = skin_;
	}


	void changeSpeed()
	{
		Sleep(speed_);
	}


	int getX() { 
		return carX_;
	}


	int getY() { 
		return carY_; 
	}


	void setX(int x) { 
		carX_ = x; 
	}


	void setY(int y) {
		carY_ = y; 
	}


	int getSpeed() {
		return abs(speed_ - 400);
	}


	void setSpeed(int speed) {
		speed_ = speed; 
	}


	char getSkin() {
		return skin_; 
	}


private:
	int carX_;
	int carY_;
	int speed_;
	char skin_;


	void removeCar() 
	{
		track[carY_][carX_] = ' ';
		track[carY_ - 1][carX_] = ' ';
		track[carY_ - 2][carX_] = ' ';
		track[carY_ - 3][carX_] = ' ';
		track[carY_][carX_ - 1] = ' ';
		track[carY_][carX_ + 1] = ' ';
		track[carY_ - 2][carX_ - 1] = ' ';
		track[carY_ - 2][carX_ + 1] = ' ';
	}
};

int main()
{
	//player can choose between two cars
	string choice;

	//pointers are assigned by references to temorary objects
	Game* game[] = { &VerySlowCar(), &RegularCar() };

	while (true) {
		cout << "Do you want slow car or the regular one? (input slow/regular)" << endl;

		cin >> choice;
		system("cls");

		//run the algorithm
		if (choice == "slow") {
			game[0]->run();
		}
		else if (choice == "regular") {
			game[1]->run();
		}

		else cout << "INPUT SOMETHING RIGHT!" << endl;
	}

	delete[] game;

	return 0;
}