#include "Plant.h"
#include "Includes.h"

double NextPlantSpawnTime = 0;

Plant::Plant()
{
	PlantPosition.x = rand() % ScreenSizeX;
	PlantPosition.y = ScreenSizeY - 40 - (rand() % 120);
	SelectNextGoal();
	isMoving = true;
}

int Plant::getSize()
{
	return size;
}

ImVec2 Plant::getPlantPosition()
{
	return PlantPosition;
}

void Plant::Move(double PassedTime)
{
	if (Goal > PlantPosition.y)
	{
		PlantPosition.y = PlantPosition.y + 1.0f * PassedTime;
		if (Goal <= PlantPosition.y)
		{
			SelectNextGoal();
		}
	}
	else
	{
		PlantPosition.y = PlantPosition.y - 1.0f * PassedTime;
		if (Goal >= PlantPosition.y)
		{
			SelectNextGoal();
		}
	}
}

void Plant::SelectNextGoal()
{
	if (PlantPosition.y >= ScreenSizeY)
	{
		Goal = PlantPosition.y - 15 - (rand() % 120);
	}
	else
	{
		if (rand() % 2 == 0)
		{
			Goal = PlantPosition.y - 15 - (rand() % 120);
			if (Goal < 0)
			{
				Goal = 0;
			}
		}
		else
		{
			Goal = PlantPosition.y + 15 + (rand() % 120);
			if (Goal > 720)
			{
				Goal = 720;
			}
		}
	}
}

std::vector<Plant> plants;