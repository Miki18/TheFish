//Info: Display.h

#pragma once
#include "Includes.h"
#include "Textures.h"
#include "Display.h"
#include "Plant.h"
#include "Fish.h"

void ShowBackground()
{
	ImGui::SetNextWindowPos(ImVec2(0, 0)); //set window position
	ImGui::Begin("Background", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize);  //title & flags
	ImGui::Image((void*)(intptr_t)BackgroundTex, ImVec2(ScreenSizeX, ScreenSizeY)); //set image size - in that case it is literally game's screen size
	ImGui::End();  //end
}

void ShowPlayerFish(ImVec2 Fish_pos, bool turn, bool IsOpen)
{
	ImGui::SetNextWindowPos(Fish_pos);   //fish positon = window position
	ImGui::SetNextWindowSize(ImVec2(25, 25));
	ImGui::Begin("Player", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);   //Title & flags

	ImVec2 windowSize = ImGui::GetWindowSize();
	ImVec2 imageSize = ImVec2(25, 25);         //!!!! player fish size
	ImVec2 cursorPos = ImVec2((windowSize.x - imageSize.x) * 0.5f - 2.5, (windowSize.y - imageSize.y) * 0.5f);
	ImGui::SetCursorPos(cursorPos);

	if (turn == false)  //Use bool turn to show texture in the way it match with fish swimming direction
	{
		ImGui::Image((void*)(intptr_t)FishesTex[0][IsOpen], imageSize, ImVec2(1, 0), ImVec2(0, 1));  //show image: texture name, size, rotate
	}
	else
	{
		ImGui::Image((void*)(intptr_t)FishesTex[0][IsOpen], imageSize, ImVec2(0, 0), ImVec2(1, 1));
	}
	ImGui::End(); //end
}

void ShowPlant(std::string Name, std::vector<Plant>& plants, int i)
{
	ImVec2 HelpPos = plants[i].getPlantPosition();
	ImGui::SetNextWindowPos(ImVec2(HelpPos.x - (plants[i].getSize() / 2), HelpPos.y - (plants[i].getSize() / 2)));     //get plant position
	ImGui::SetNextWindowSize(ImVec2(plants[i].getSize(), plants[i].getSize()));      //set window size
	ImGui::Begin(Name.c_str(), nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);   //name & flags
	ImGui::SetCursorPos(ImVec2(10, 10));                        //set cursor, so plant picture will be in the middle of the window
	ImGui::Image((void*)(intptr_t)PlantTex, ImVec2(plants[i].getSize(), plants[i].getSize()));  //image - texture name and get instance's size
	ImGui::End();  //end
}

void ShowFish(std::string Name, std::vector<Fish>& fishes, int i)
{
	ImVec2 HelpPos = fishes[i].getPosition();
	float fishSize = fishes[i].getSize();
	ImGui::SetNextWindowPos(ImVec2(HelpPos.x - (fishSize / 2), HelpPos.y - (fishSize / 2)));
	ImGui::SetNextWindowSize(ImVec2(fishes[i].getSize(), fishes[i].getSize()));
	ImGui::Begin(Name.c_str(), nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
	if (fishes[i].getlvl() == 1)   //if fish level is greater than 1 then fish size = window size, so we set cursor at point (0,0), because image cover full window.
	{								//but level 1 fish (and also plant) is so small that it's not possible to shrink window so much. That's why we need to move cursor to different position so fish image will be in the middle of the window
		ImGui::SetCursorPos(ImVec2(6, 6));
	}
	else
	{
		ImGui::SetCursorPos(ImVec2(0, 0));
	}

	if (fishes[i].getTurn())
	{
		ImGui::Image((void*)(intptr_t)FishesTex[fishes[i].getlvl()][fishes[i].IsOpen], ImVec2(fishSize, fishSize), ImVec2(1, 0), ImVec2(0, 1));
	}
	else
	{
		ImGui::Image((void*)(intptr_t)FishesTex[fishes[i].getlvl()][fishes[i].IsOpen], ImVec2(fishSize, fishSize), ImVec2(0, 0), ImVec2(1, 1));
	}

	ImGui::End();

}

void ShowPoints(int Points)
{
	ImGui::SetNextWindowPos(ImVec2(0, 0));   //set positions - points will be in top left corner
	ImGui::SetNextWindowSize(ImVec2(180, 40));    //size
	ImGui::Begin("Points", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);  //title & flags
	ImGui::SetWindowFontScale(1.5f);  //text size
	ImGui::SetCursorPos(ImVec2(8, 10));  //it sets text in the right place
	ImGui::Text("Points: %d", Points);  //text
	ImGui::End();    //end
}

void ColorAndNewFrame()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //black color
	glClear(GL_COLOR_BUFFER_BIT);  //clear color buffer

	ImGui_ImplOpenGL3_NewFrame();  //for new frame
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiRender()
{
	ImGui::Render();  //Imgui render
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}