#ifndef EXECUTION_H
#define EXECUTION_H
#include "Game.h"
class Execution :
	public Game
{
public:
	Execution();

	void setTrack(int y, int x, char skin);

	std::vector<std::string> getTrack() const;

	void placeCar();

	void generateObstacle();

	//if car bumped into an obstacle, reset score and time, set best results and take off gameIsOn flag
	void bump();

	//algorithm that launches the game
	void run();

	

	~Execution();

private:
	void removeObstacle();
};


inline void Execution::setTrack(int y, int x, char skin) {
track_[y][x] = skin;
}




inline std::vector<std::string> Execution::getTrack() const {
return track_;
}

#endif