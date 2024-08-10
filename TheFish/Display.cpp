//Info: Display.h

#pragma once
#include "Includes.h"
#include "Textures.h"
#include "Display.h"
#include "Plant.h"

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
	ImGui::Begin("Player", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);   //Title & flags
	if (turn == false)  //Use bool turn to show texture in the way it match with fish swimming direction
	{
		ImGui::Image((void*)(intptr_t)FishesTex[0][IsOpen], ImVec2(25, 25), ImVec2(1, 0), ImVec2(0, 1));  //show image: texture name, size, rotate
	}
	else
	{
		ImGui::Image((void*)(intptr_t)FishesTex[0][IsOpen], ImVec2(25, 25), ImVec2(0, 0), ImVec2(1, 1));

	}
	ImGui::End(); //end
}

void ShowPlant(std::string Name, std::vector<Plant>& plants, int i)
{
	ImVec2 HelpPos = plants[i].getPlantPosition();
	ImGui::SetNextWindowPos(ImVec2(HelpPos.x - (plants[i].getSize() / 2), HelpPos.y - (plants[i].getSize() / 2)));     //get plant position
	ImGui::SetNextWindowSize(ImVec2(plants[i].getSize(), plants[i].getSize()));      //set window size
	ImGui::Begin(Name.c_str(), nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);   //name & flags
	ImGui::Image((void*)(intptr_t)PlantTex, ImVec2(plants[i].getSize(), plants[i].getSize()));  //image - texture name and get instance's size
	ImGui::End();  //end
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