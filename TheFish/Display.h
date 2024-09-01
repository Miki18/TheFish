//Display.h and Display.cpp display everything what should be visible on screen. In 'Game Loop' schemat it does the render part

#pragma once
#include "Includes.h"
#include "Plant.h"
#include "Fish.h"

void ShowBackground();   //Show Background

void ShowPoints(int Points);  //Show Points

void ShowGoal(int Goal);    //Show Goal

void ShowPlayerFish(ImVec2 Fish_pos, bool turn, bool IsOpen, int size);  //Show player fish. Fish_pos - fish's position; it has x and y value
//turn - determines if fish is swimming from left to right or vice versa        IsOpen sets it's mouth open or close      size variable is for player fish's size

void ShowPlant(std::string Name, std::vector<Plant>& plants, int i);    //Show plants; name is window name, vector contains all plants' instances, i is instance number

void ShowFish(std::string Name, std::vector<Fish>& fishes, int i);

void ColorAndNewFrame(); //we need to do this every time in main loop (at start)

void ImGuiRender();  //we need to do this every time in main loop (at end)

void ShowText(std::string text);   //Show text "You died!", "You won!" or "Level cleared!" - it depents on variable

void ShowExit();   //Show exit button - when player clicks on it, the game will be closed

void ShowPlayLevel(std::string text);   //play level button - when player clicks, it will start a level (depend on 'CurrentLevel' variable from Game.cpp).
									//This button will be used as transition between game and "You died!", "You won!" & "Level cleared!" screens (it will take player from GameScreen = {1, 2, 3} to GameScreen = 0)
									//Text on button will be different for different screens, so we have to provide it as variable

extern int GameScreen;