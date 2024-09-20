#include "Fish.h"

Fish::Fish(int game_level, int id)
{
	lvl = 1 + rand() % (game_level + 1);

	switch(lvl)
	{
	case 1:
		size = 20;
		speed = 225;
		points = 25;
		break;
	
	case 2:
		size = 35;
		speed = 150;
		points = 45;
		break;

	case 3:
		size = 50;
		speed = 125;
		points = 60;
		break;

	case 4:
		size = 75;
		speed = 100;
		points = 100;
		break;

	case 5:
		size = 100;
		speed = 50;
		points = 200;
		break;

	case 6:
		size = 150;
		speed = 25;
		points = 0;     //player will never eat this fish
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
	ID = id;

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
	int Position_x_rounded;  //we need to round Position.x value
	if (Goal.x >= Position.x)       //if Goal.x is bigger we round it up, otherwise we round it down.
	{
		Position_x_rounded = int(Position.x + 0.5);
	}
	else
	{
		Position_x_rounded = int(Position.x);
	}
	
	//We need to provide rounded value of Position.x, cause when fish goes straight down/up (Position.x and Goal.x difference was really small while Goal.y and Position.y difference was big)
	//fish rapidly turn left and right. Position_x_rounded solve that problem.

	if (Goal.x > Position_x_rounded)
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

int Fish::getPoints()
{
	return points;
}

double NextFishSpawnTime = 0;
std::vector<Fish> fishes;