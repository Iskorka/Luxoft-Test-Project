#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "conio.h"
#include <string>
#include <vector>

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


class Car
{
private:
	void clearTrack() {
		track[y][x] = ' ';
		track[y - 1][x] = ' ';
		track[y - 2][x] = ' ';
		track[y - 3][x] = ' ';
		track[y][x - 1] = ' ';
		track[y][x + 1] = ' ';
		track[y - 2][x - 1] = ' ';
		track[y - 2][x + 1] = ' ';
	}

protected:
	int x;
	int y;
	int speed;
public:
	Car() : speed(150) {};

	//назначение клавиш: 75 - лево, 77 - право, 72 - верх, 80 - низ, 13 - энтер, 27 - эскейп
	void control() {
		switch (_getch()) {
			case 75:
				if (x == 2) break;
				clearTrack();
				x -= 1;
				break;

			case 77:
				if (x == 14) break;
				clearTrack();
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

	void setX(int X) {
		x = X;
	}

	void setY(int Y) {
		y = Y;
	}
};

class Obstacle
{
private:
	//генерирует случайное положение препятствия
	int randObstacleX() {
		srand(time(0));
		return rand() % (13 - 2 + 1) + 2; //rand() (b - a + 1) + a
	}

	void clearTrack() {
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
protected:
	int obstacleX;
	int obstacleY;
	char obstacle;
public:
	Obstacle() : obstacleX(randObstacleX()), obstacleY(0), obstacle('T') {}

	//приближения препятствия
	void approach() {
			if (obstacleY < 15) {
				clearTrack();

				obstacleY += 1;
				track[obstacleY][obstacleX] = obstacle;
				track[obstacleY + 1][obstacleX] = obstacle;
				track[obstacleY + 2][obstacleX] = obstacle;
				track[obstacleY][obstacleX + 1] = obstacle;
				track[obstacleY + 1][obstacleX + 1] = obstacle;
				track[obstacleY + 2][obstacleX + 1] = obstacle;
				track[obstacleY][obstacleX - 1] = obstacle;
				track[obstacleY + 1][obstacleX - 1] = obstacle;
				track[obstacleY + 2][obstacleX - 1] = obstacle;
			}

			else if (obstacleY == 15) {
				clearTrack();

				obstacleY = 0;
				obstacleX = randObstacleX();
			}
	}

	void setObstacleY(int y) {
		obstacleY = y;
	}
};

class Game : public Car, public Obstacle
{
private:
	int score;
	int best;
	int startTime, endTime, bestTime;
	bool gameIsOn;


	int getTime() {
		return (endTime - startTime) / 1000;
	}
public:
	Game() : score(0), best(0), endTime(0), bestTime(0) {}

	void run() {
		cout << "\n\t o\n\tooo\tRACING CHAMPION PRO GALAXY 9000 v1 GO\n\t o\n\tooo\n\nPress ENTER to RACE" << endl;
		cout << "\n\n\nCONTROLS:\nLEFT ARROW/RIGHT ARROW - move left/right\nUP ARROW/DOWN ARROW - speed up/down\nENTER - pause/resume\nESC - quit" << endl;


		while (true) {
			if (_getch() == 13) {
				placeCar();

				while (gameIsOn) {

					while (_kbhit()) {
							control();
					}

					Sleep(speed);
					system("cls");

					cout << "Score: " << score << " \tBest score: " << best << endl << "Time: " << getTime() << " \tBest time: " << bestTime << endl << endl;

					for (int i = 0; i < 18; i++) {
						cout << track[i] << endl;
					}

					//конец отсчёта обновляется при каждом прохождении
					endTime = clock();

					gameIsOn = gameOver();

					if (score > 5) {
						approach();
					}
					score++;
				}
			}
		}
	}

	void placeCar() {
		setX(8);
		setY(14);

		gameIsOn = true;

		//запуск отсчёта времени
		startTime = clock();

		//очистка трека
		for (int i = 1; i<16; i++)
			for (int j = 0; j < 18; j++) {
				track[j][i] = ' ';
			}

		//машинка
		track[y][x] = 'o';
		track[y - 1][x] = 'o';
		track[y - 2][x] = 'o';
		track[y - 3][x] = 'o';
		track[y][x - 1] = 'o';
		track[y][x + 1] = 'o';
		track[y - 2][x - 1] = 'o';
		track[y - 2][x + 1] = 'o';
	}

	bool gameOver() {
		if (track[y][x] != 'o' || track[y - 1][x] != 'o' || track[y - 2][x] != 'o'
			|| track[y - 3][x] != 'o' || track[y][x - 1] != 'o' || track[y][x + 1] != 'o'
			|| track[y - 2][x - 1] != 'o' || track[y - 2][x + 1] != 'o') {
			cout << "Game Over\nPress ENTER to try again" << endl;
			if (score > best) best = score;
			if (getTime() > bestTime) bestTime = getTime();
			speed = 150;
			setObstacleY(0);
			return false;
		}
		return true;
	}

};

int main()
{
	Game g;
	g.run();

	system("pause");
    return 0;
}

