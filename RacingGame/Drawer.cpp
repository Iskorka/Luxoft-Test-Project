#include "stdafx.h"
#include "Drawer.h"
#include "Constants.h"
#include <iostream>
#include <vector>
#include <string>

using namespace Constants;

Drawer::Drawer()
{
}

void Drawer::drawTrack(std::vector<std::string> track)
{
	for (int i = 0; i < MAX_Y; i++) {
		std::cout << track[i] << std::endl;
	}
}

Drawer::~Drawer()
{
}
