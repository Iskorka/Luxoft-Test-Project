#ifndef GAMEOVER_H
#define GAMEOVER_H
#include <vector>
#include <string>

class GameOver
{
public:
	GameOver();

	bool isCrushed(std::vector<std::string> track, char car, int carY, int carX);

	~GameOver();

};

#endif