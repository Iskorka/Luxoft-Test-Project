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
		track[y][x] = 'o';
		track[y - 1][x] = 'o';
		track[y - 2][x] = 'o';
		track[y - 3][x] = 'o';
		track[y][x - 1] = 'o';
		track[y][x + 1] = 'o';
		track[y - 2][x - 1] = 'o';
		track[y - 2][x + 1] = 'o';
	}

	void drawTrack() {
		system("cls");
		cout << "Score: " << score << " \tBest score: " << best << endl << "Time: " << getTime() << " \tBest time: " << bestTime << endl << "Speed: " << abs(getSpeed() - 150) << endl;
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
		int y = getY();
		int x = getX();
		if (track[y][x] != 'o' || track[y - 1][x] != 'o' || track[y - 2][x] != 'o'
			|| track[y - 3][x] != 'o' || track[y][x - 1] != 'o' || track[y][x + 1] != 'o'
			|| track[y - 2][x - 1] != 'o' || track[y - 2][x + 1] != 'o') {
			cout << "Game Over\nPress ENTER to try again" << endl;
			if (score > best) best = score;
			if (getTime() > bestTime) bestTime = getTime();
			setSpeed(150);
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

class Car : public Game
{
private:
	int x;
	int y;
	int speed;

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
	Car() : x(8), y(14), speed(150) {}

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

		case 80: if (speed < 250) speed += 50; break;

		case 13:
			while (true) {
				if (_getch() == 13) {
					break;
				}
			}; break;

		case 27: exit(0); break;
		}

		track[y][x] = 'o';
		track[y - 1][x] = 'o';
		track[y - 2][x] = 'o';
		track[y - 3][x] = 'o';
		track[y][x - 1] = 'o';
		track[y][x + 1] = 'o';
		track[y - 2][x - 1] = 'o';
		track[y - 2][x + 1] = 'o';
	}

	void changeSpeed() {
		Sleep(speed);
	}

	int getX() { return x; }
	int getY() { return y; }
	void setX(int X) { x = X; }
	void setY(int Y) { y = Y; }

	int getSpeed() { return speed; }
	void setSpeed(int sp) { speed = sp; }
};

int main()
{
	Game* g = &Car();

	g->run();

	return 0;
}