#include "Fish.h"

Fish::Fish()
{
	lvl = 1 + rand() % 2;

	switch(lvl)
	{
	case 1:
		size = 20;
		speed = 150;
		break;
	
	case 2:
		size = 35;
		speed = 75;
		break;
	}

	if (rand() % 2 == 0)
	{
		Position.x = 0;
		Position.y = rand() % ScreenSizeY;
	}
	else
	{
		Position.x = ScreenSizeX;
		Position.y = rand() % ScreenSizeY;
	}

	IsMoving = true;
	IsEating = false;
	IsOpen = false;

	ChooseNextDestination();
}

void Fish::ChooseNextDestination()
{
	Goal.x = rand() % ScreenSizeX;
	Goal.y = rand() % ScreenSizeY;
}

void Fish::Move(double PassedTime)
{
	if (Position.x < Goal.x)
	{
		Position.x = Position.x + (speed * PassedTime);
	}
	else
	{
		Position.x = Position.x - (speed * PassedTime);
	}
	
	if (Position.y < Goal.y)
	{
		Position.y = Position.y + (speed * PassedTime);
	}
	else
	{
		Position.y = Position.y - (speed * PassedTime);
	}

	if (abs(Position.x - Goal.x) < 5 and abs(Position.y - Goal.y) < 5)
	{
		ChooseNextDestination();
	}
}

bool Fish::getTurn()
{
	if (Goal.x > Position.x)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ImVec2 Fish::getPosition()
{
	return Position;
}

int Fish::getSize()
{
	return size;
}

int Fish::getlvl()
{
	return lvl;
}

double NextFishSpawnTime = 0;
std::vector<Fish> fishes;