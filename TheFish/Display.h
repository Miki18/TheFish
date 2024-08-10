//Display.h and Display.cpp display everything what should be visible on screen. In 'Game Loop' schemat it does the render part

#pragma once
#include "Includes.h"
#include "Plant.h"

void ShowBackground();   //Show Background

void ShowPoints(int Points);  //Show Points

void ShowPlayerFish(ImVec2 Fish_pos, bool turn, bool IsOpen);  //Show player fish. Fish_pos - fish's position; it has x and y value
//turn - determines if fish is swimming from left to right or vice versa        IsOpen sets it's mouth open or close

void ShowPlant(std::string Name, std::vector<Plant>& plants, int i);    //Show plants; name is window name, vector contains all plants' instances, i is instance number

void ColorAndNewFrame(); //we need to do this every time in main loop (at start)

void ImGuiRender();  //we need to do this every time in main loop (at end)