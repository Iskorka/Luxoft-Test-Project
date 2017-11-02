#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {
	const int DEFAULT_CAR_X = 8;
	const int DEFAULT_CAR_Y = 14;
	const int DEFAULT_SPEED = 150;

	const int KEY_LEFT = 75;
	const int KEY_RIGHT = 77;
	const int KEY_UP = 72;
	const int KEY_DOWN = 80;
	const int KEY_ENTER = 13;
	const int KEY_ESC = 27;

	const int MIN_CAR_X = 2;
	const int MAX_CAR_X = 14;

	const int MIN_SPEED = 50;
	const int MAX_SPEED = 150;
	const int SPEED_INCREMENT = 50;

	const int MIN_X = 0;
	const int MIN_Y = 0;
	const int MAX_X = 17;
	const int MAX_Y = 18;

	const int MIN_OBSTACLE_X = 2;
	const int MAX_OBSTACLE_X = 14;

	const int MAX_OBSTACLE_Y = 15;

	const int AXIS_SHIFT = 1;
	const int AXIS_DOUBLE_SHIFT = 2;
	const int AXIS_TRIPLE_SHIFT = 3;
	const int ONE_SECOND = 1000;

	const char OBSTACLE_SKIN = 'T';
}

#endif