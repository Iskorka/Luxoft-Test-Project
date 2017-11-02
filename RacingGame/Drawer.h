#ifndef DRAWER_H
#define DRAWER_H
#include <vector>

class Drawer
{
public:
	Drawer();

	void drawTrack(std::vector<std::string> track);

	~Drawer();
};

#endif