//Main game file
// 
//Some libraries and their versions which I use in this project:
//glfw version 3.4
//imgui version 1.90.9

#pragma once
#include "Textures.h"
#include "Includes.h"
#include "Display.h"
#include "Plant.h"

void EatThread(bool& PlayerFish, int i, bool& isOpen)
{
	PlayerFish = true;   //stop player's fish

	std::this_thread::sleep_for(std::chrono::milliseconds(25));

	isOpen = true;   //open player's fish's mouth

	std::this_thread::sleep_for(std::chrono::milliseconds(25));

	plants.erase(plants.begin() + i);    //remove plant

	std::this_thread::sleep_for(std::chrono::milliseconds(25));

	isOpen = false;       //move player's fish and close it's mouth
	PlayerFish = false;
}

int main()
{
	//INITIALIZE ImGui AND GLFW AND CREATE WINDOW
	// 
	//Initialization GLFW
	if (!glfwInit())
	{
		exit(1);
	}

	//Open window GLFW
	GLFWwindow* window = glfwCreateWindow(ScreenSizeX, ScreenSizeY, "Fish The Game", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(window);

	//Initialization ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	//Imgui color
	ImGuiStyle* style = &ImGui::GetStyle();
	style->Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
	//
	//END INITIALIZATION

	//Load Textures
	LoadAllTextures();

    ImVec2 previous_pos = ImGui::GetMousePos(); //fish control variables
	ImVec2 Mouse_pos;
	ImVec2 Fish_pos;
	bool PlayerFishEat = false;   //for not moving
	bool PlayerFishOpen = false;   //for open mouth

	double LastFrameTime = 0;    //time variables
	double CurrentTime = 0;
	double PassedTime = 0;

	int Points = 0;  //Points

	srand(time(NULL));   //for rand() function

	while (!glfwWindowShouldClose(window))    //process inputs() update state() display state()
	{
		//Process inputs()
		CurrentTime = glfwGetTime();
		Mouse_pos = ImGui::GetMousePos();
		
		//Update state()
		PassedTime = CurrentTime - LastFrameTime;

		//Change mouse position, so mouse cursor will be in the middle of the player's fish image
		Mouse_pos.x = Mouse_pos.x - 25 / 2;   //!!!!!
		Mouse_pos.y = Mouse_pos.y - 25 / 2;

		//mouse can't go out of background image (it is limited to 0 - 1280 x and 0 - 720 y)
		if (Mouse_pos.x <= 0)
		{
			Mouse_pos.x = 0;
		}

		if (Mouse_pos.x >= ScreenSizeX - 25)   //!!!!!
		{
			Mouse_pos.x = ScreenSizeX - 25;
		}

		if (Mouse_pos.y <= 0)
		{
			Mouse_pos.y = 0;
		}

		if (Mouse_pos.y >= ScreenSizeY - 25)
		{
			Mouse_pos.y = ScreenSizeY - 25;
		}

		//update fish position
		if (PlayerFishEat == false)
		{
			Fish_pos.x = Fish_pos.x + ((Mouse_pos.x - Fish_pos.x) * 5 * PassedTime);
			Fish_pos.y = Fish_pos.y + ((Mouse_pos.y - Fish_pos.y) * 5 * PassedTime);
		}

		if (CurrentTime >= NextPlantSpawnTime)    //NextPlantSpawnTime controls how often new plant appears
		{
			if (rand() % 3 == 0)   //probability if plant spawns when it's time
			{
				plants.emplace_back();   //create a new instance of plant class

				NextPlantSpawnTime = CurrentTime + 0.5 + rand() % 2;   //random value for NextPlantSpawnTime
			}
			else    //if plant don't spawn we'll wait for half second for next try (only half second)
			{
				NextPlantSpawnTime = CurrentTime + 0.5;
			}
		}

		//update plant
		for (int i = 0; i < plants.size(); i++)
		{
			ImVec2 objectPosition = plants[i].getPlantPosition();   //help variable (we need x and y)
			if (abs(Fish_pos.x - objectPosition.x) < (plants[i].getSize() + 25)/3 and abs(Fish_pos.y - objectPosition.y) < (plants[i].getSize() + 25) / 3)   //if player get close enough
			{
				if (plants[i].isMoving == true)  //we can't call the same thread twice
				{
					plants[i].isMoving = false;  //block
					Points = Points + 10;                //increase points
					std::thread Eating(EatThread, std::ref(PlayerFishEat), i, std::ref(PlayerFishOpen));    //it is necessary to use thread, because that "animation" is parallel for game loop (it can't stop main loop)
					Eating.detach();   //create thread
				}
			}
			else
			{
				if (plants[i].isMoving == true)  //if player is not eating plant than it can move
				{
					plants[i].Move(PassedTime);   //update plants position
				}
			}
		}

		//update last frame time value
		LastFrameTime = CurrentTime;

		//Display()
		ColorAndNewFrame();

		//show image
		ShowBackground();

		//Show player fish
		if (previous_pos.x < Mouse_pos.x)
		{
			ShowPlayerFish(Fish_pos, false, PlayerFishOpen);
		}
		else
		{
			ShowPlayerFish(Fish_pos, true, PlayerFishOpen);
		}

		//update previous position (it has to be after show player fish)
		previous_pos.x = Fish_pos.x;
		previous_pos.y = Fish_pos.y;

		//Plant display
		for (int i = 0; i < plants.size(); i++)
		{
			std::string Name = "Plant " + std::to_string(i);

			ShowPlant(Name, plants, i);
		}

		ShowPoints(Points);

		ImGuiRender();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}
