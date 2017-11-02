#ifndef CALCULATIONS_H
#define CALCULATIONS_H

class Calculations
{
public:
	Calculations();

	//generate random X 
	int computeX(int min, int max);

	int getTime(int startTime, int endTime);

	~Calculations();
};

#endif
