#pragma once
#include "Includes.h"

class Plant
{
private:
	double Goal;
	ImVec2 PlantPosition;
	int size = 10;
	void SelectNextGoal();

public:
	bool isMoving;
	Plant(int id);
	void Move(double PassedTime);
	int getSize();
	ImVec2 getPlantPosition();
	int ID;
};

extern double NextPlantSpawnTime;  //for plant spawn control
extern std::vector<Plant> plants;     //vector of classes