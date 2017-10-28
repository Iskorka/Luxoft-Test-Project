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
private:
	int score;
	int best;
	int startTime, endTime, bestTime;
	int obstacleX, obstacleY;
	bool gameIsOn;

	void removeObstacle() {
		track[obstacleY][obstacleX] = ' ';
		track[obstacleY + 1][obstacleX] = ' ';
		track[obstacleY + 2][obstacleX] = ' ';
		track[obstacleY][obstacleX + 1] = ' ';
		track[obstacleY + 1][obstacleX + 1] = ' ';
		track[obstacleY + 2][obstacleX + 1] = ' ';
		track[obstacleY][obstacleX - 1] = ' ';
		track[obstacleY + 1][obstacleX - 1] = ' ';
		track[obstacleY + 2][obstacleX - 1] = ' ';
	}

	int randObstacleX() {
		srand(time(0));
		return rand() % (13 - 2 + 1) + 2; //rand() (b - a + 1) + a
	}

	int getTime() {
		return (endTime - startTime) / 1000;
	}

public:
	Game() : score(0), best(0), endTime(0), bestTime(0), obstacleX(randObstacleX()), obstacleY(0) {}

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

	void placeCar() {
		setX(8);
		setY(14);

		int x = getX();
		int y = getY();

		gameIsOn = true;

		//çàïóñê îòñ÷¸òà âðåìåíè
		startTime = clock();

		//î÷èñòêà òðåêà
		for (int i = 1; i<16; i++)
			for (int j = 0; j < 18; j++) {
				track[j][i] = ' ';
			}

		//ìàøèíêà
		track[y][x] = getSkin();
		track[y - 1][x] = getSkin();
		track[y - 2][x] = getSkin();
		track[y - 3][x] = getSkin();
		track[y][x - 1] = getSkin();
		track[y][x + 1] = getSkin();
		track[y - 2][x - 1] = getSkin();
		track[y - 2][x + 1] = getSkin();
	}

	void drawTrack() {
		system("cls");
		cout << "Score: " << score << " \tBest score: " << best << endl << "Time: " << getTime() << " \tBest time: " << bestTime << endl << "Speed: " << getSpeed() << endl;
		for (int i = 0; i < 18; i++) {
			cout << track[i] << endl;
		}
	}

	void generateObstacle() {
		if (obstacleY < 15) {
			removeObstacle();

			obstacleY += 1;
			track[obstacleY][obstacleX] = 'T';
			track[obstacleY + 1][obstacleX] = 'T';
			track[obstacleY + 2][obstacleX] = 'T';
			track[obstacleY][obstacleX + 1] = 'T';
			track[obstacleY + 1][obstacleX + 1] = 'T';
			track[obstacleY + 2][obstacleX + 1] = 'T';
			track[obstacleY][obstacleX - 1] = 'T';
			track[obstacleY + 1][obstacleX - 1] = 'T';
			track[obstacleY + 2][obstacleX - 1] = 'T';
		}

		else if (obstacleY == 15) {
			removeObstacle();

			obstacleY = 0;
			obstacleX = randObstacleX();
		}
	}

	bool gameOver() {
		char car = getSkin();

		int y = getY();
		int x = getX();
		if (track[y][x] != car || track[y - 1][x] != car || track[y - 2][x] != car
			|| track[y - 3][x] != car || track[y][x - 1] != car || track[y][x + 1] != car
			|| track[y - 2][x - 1] != car || track[y - 2][x + 1] != car) {
			cout << "Game Over\nPress ENTER to try again" << endl;
			if (score > best) best = score;
			if (getTime() > bestTime) bestTime = getTime();
			setSpeed(getDefaultSpeed());
			obstacleY = 0;
			obstacleX = randObstacleX();
			return false;
		}
		return true;
	}

	void run() {
		cout << "\n\t o\n\tooo\tRACING CHAMPION PRO GALAXY 9000 v1 GO\n\t o\n\tooo\n\nPress ENTER to RACE" << endl;
		cout << "\n\n\nCONTROLS:\nLEFT ARROW/RIGHT ARROW - move left/right\nUP ARROW/DOWN ARROW - speed up/down\nENTER - pause/resume\nESC - quit" << endl;
		while (true) {
			if (_getch() == 13) {
				placeCar();
				while (gameIsOn) {
					while (_kbhit()) {
						control(); //virtual from Car
					}
					changeSpeed(); //virtual from Car
					drawTrack();
					endTime = clock();
					gameIsOn = gameOver();
					if (score > 5) {
						generateObstacle();
					}
					score++;
				}
			}
		}
	}
};

class RegularCar : public Game
{
private:
	int x;
	int y;
	int speed;
	char skin;

	void removeCar() {
		track[y][x] = ' ';
		track[y - 1][x] = ' ';
		track[y - 2][x] = ' ';
		track[y - 3][x] = ' ';
		track[y][x - 1] = ' ';
		track[y][x + 1] = ' ';
		track[y - 2][x - 1] = ' ';
		track[y - 2][x + 1] = ' ';
	}
public:
	RegularCar() : x(8), y(14), speed(getDefaultSpeed()), skin('o') {}

	int getDefaultSpeed() { return 150; }

	void control() {
		switch (_getch()) {
		case 75:
			if (x == 2) break;
			removeCar();
			x -= 1;
			break;

		case 77:
			if (x == 14) break;
			removeCar();
			x += 1;
			break;

		case 72: if (speed > 50) speed -= 50; break;

		case 80: if (speed < 150) speed += 50; break;

		case 13:
			while (true) {
				if (_getch() == 13) {
					break;
				}
			}; break;

		case 27: exit(0); break;
		}

		track[y][x] = skin;
		track[y - 1][x] = skin;
		track[y - 2][x] = skin;
		track[y - 3][x] = skin;
		track[y][x - 1] = skin;
		track[y][x + 1] = skin;
		track[y - 2][x - 1] = skin;
		track[y - 2][x + 1] = skin;
	}

	void changeSpeed() {
		Sleep(speed);
	}

	int getX() { return x; }
	int getY() { return y; }
	void setX(int X) { x = X; }
	void setY(int Y) { y = Y; }

	int getSpeed() { return abs(speed - 150); }
	void setSpeed(int sp) { speed = sp; }
	char getSkin() { return skin; }
};

class VerySlowCar : public Game
{
private:
	int x;
	int y;
	int speed;
	char skin;

	void removeCar() {
		track[y][x] = ' ';
		track[y - 1][x] = ' ';
		track[y - 2][x] = ' ';
		track[y - 3][x] = ' ';
		track[y][x - 1] = ' ';
		track[y][x + 1] = ' ';
		track[y - 2][x - 1] = ' ';
		track[y - 2][x + 1] = ' ';
	}
public:
	VerySlowCar() : x(8), y(14), speed(getDefaultSpeed()), skin('S') {}

	int getDefaultSpeed() { return 400; }

	void control() {
		switch (_getch()) {
		case 75:
			if (x == 2) break;
			removeCar();
			x -= 1;
			break;

		case 77:
			if (x == 14) break;
			removeCar();
			x += 1;
			break;

		case 72: if (speed > 300) speed -= 20; break;

		case 80: if (speed < 400) speed += 20; break;

		case 13:
			while (true) {
				if (_getch() == 13) {
					break;
				}
			}; break;

		case 27: exit(0); break;
		}

		track[y][x] = skin;
		track[y - 1][x] = skin;
		track[y - 2][x] = skin;
		track[y - 3][x] = skin;
		track[y][x - 1] = skin;
		track[y][x + 1] = skin;
		track[y - 2][x - 1] = skin;
		track[y - 2][x + 1] = skin;
	}

	void changeSpeed() {
		Sleep(speed);
	}

	int getX() { return x; }
	int getY() { return y; }
	void setX(int X) { x = X; }
	void setY(int Y) { y = Y; }

	int getSpeed() { return abs(speed - 400); }
	void setSpeed(int sp) { speed = sp; }

	char getSkin() { return skin; }
};

int main()
{
	string choice;
	Game* g[] = {&VerySlowCar(), &RegularCar()};

	while (true) {
		cout << "Do you want slow car or the regular one? (input slow/regular)" << endl;

		cin >> choice;
		system("cls");
		if (choice == "slow") {
			g[0]->run();
		}
		else if (choice == "regular") {
			g[1]->run();
		}
		else cout << "INPUT SOMETHING RIGHT!" << endl;
	}

	return 0;
}