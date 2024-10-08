#pragma once
#include "Includes.h"

class Fish
{
private:
	ImVec2 Position;
	ImVec2 Goal;
	int lvl;
	int size;
	int points;
	float speed;
public:
	Fish(int game_level, int id);
	void ChooseNextDestination();
	void Move(double PassedTime);
	ImVec2 getPosition();
	int getSize();
	bool getTurn();
	int getlvl();
	int getPoints();
	bool IsEating;   //when fish eat something
	bool IsMoving;   //when fish is eating
	bool IsOpen;      //open/close mouth
	int ID;           //ID
};

extern double NextFishSpawnTime;
extern std::vector<Fish> fishes;