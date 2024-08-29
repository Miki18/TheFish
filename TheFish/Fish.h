#pragma once
#include "Includes.h"

class Fish
{
private:
	ImVec2 Position;
	ImVec2 Goal;
	int lvl;
	int size;
	float speed;
public:
	Fish();
	void ChooseNextDestination();
	void Move(double PassedTime);
	ImVec2 getPosition();
	int getSize();
	bool getTurn();
	int getlvl();
	bool IsEating;   //when fish eat something
	bool IsMoving;   //when fish is eating
	bool IsOpen;      //open/close mouth
};

extern double NextFishSpawnTime;
extern std::vector<Fish> fishes;