#pragma once

#include "ECS.h"

class PositionComponent : public Component
{
public:
	int x() { return xPos; }
	int y() { return yPos; }
	
	void init() override
	{
		xPos = 0; yPos = 0;
	}

	void update() override
	{
		xPos++; yPos++;
	}

	void setPos(int x, int y)
	{
		xPos = x; yPos = y;
	}


private:
	int xPos, yPos;

};

