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
#include "Fish.h"

void PlayerEatPlant(bool& PlayerFish, int plant_number, bool& isOpen)
{
	PlayerFish = true;   //stop player's fish

	std::this_thread::sleep_for(std::chrono::milliseconds(25));

	isOpen = true;   //open player's fish's mouth

	std::this_thread::sleep_for(std::chrono::milliseconds(25));

	plants.erase(plants.begin() + plant_number);    //remove plant

	std::this_thread::sleep_for(std::chrono::milliseconds(25));

	isOpen = false;       //move player's fish and close it's mouth
	PlayerFish = false;
}

void FishEatPlant(bool& IsEating, bool& IsOpen, int plant_number)
{
	IsEating = true;

	std::this_thread::sleep_for(std::chrono::milliseconds(25));

	IsOpen = true;

	std::this_thread::sleep_for(std::chrono::milliseconds(25));

	plants.erase(plants.begin() + plant_number);

	std::this_thread::sleep_for(std::chrono::milliseconds(25));

	IsOpen = false;
	IsEating = false;
}

void PlayerEatFish(bool& PlayerFishEat, int fish_number, bool& isOpen)
{
	PlayerFishEat = true;  //stop player's fish

	std::this_thread::sleep_for(std::chrono::milliseconds(25));

	isOpen = true;  //open player's fish's mouth

	std::this_thread::sleep_for(std::chrono::milliseconds(25));

	fishes.erase(fishes.begin() + fish_number);

	std::this_thread::sleep_for(std::chrono::milliseconds(25));

	isOpen = false;        //move player's fish and close it's mouth
	PlayerFishEat = false;
}

void FishEatFish(int EatingFish, int EatenFish)
{
	fishes[EatingFish].IsEating = true;   //stop fish

	std::this_thread::sleep_for(std::chrono::microseconds(25));

	fishes[EatingFish].IsOpen = true;    //open mouth

	std::this_thread::sleep_for(std::chrono::microseconds(25));

	fishes.erase(fishes.begin() + EatenFish);     //remove fish

	std::this_thread::sleep_for(std::chrono::microseconds(25));

	if (EatenFish < EatingFish)    //if we remove fish that is on lower position on vector then fish with higher position will have position lower by 1
	{
		EatingFish--;
	}

	fishes[EatingFish].IsOpen = false;
	fishes[EatingFish].IsEating = false;
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

	//Player fish variables
    ImVec2 previous_pos = ImGui::GetMousePos(); //fish control variables
	ImVec2 Mouse_pos;
	ImVec2 Fish_pos;
	bool PlayerFishEat = false;   //for not moving
	bool PlayerFishOpen = false;   //for open mouth
	int PlayerFishSize = 25;

	double LastFrameTime = 0;    //time variables
	double CurrentTime = 0;
	double PassedTime = 0;

	int Points = 0;  //Points

	bool test = false;

	srand(time(NULL));   //for rand() function

	while (!glfwWindowShouldClose(window))    //process inputs() update state() display state()
	{
		//Process inputs()
		CurrentTime = glfwGetTime();
		Mouse_pos = ImGui::GetMousePos();
		
		//Update state()
		PassedTime = CurrentTime - LastFrameTime;

		//Change mouse position, so mouse cursor will be in the middle of the player's fish image
		Mouse_pos.x = Mouse_pos.x - PlayerFishSize / 2;
		Mouse_pos.y = Mouse_pos.y - PlayerFishSize / 2;

		//mouse can't go out of background image (it is limited to 0 - 1280 x and 0 - 720 y)
		if (Mouse_pos.x <= 0)
		{
			Mouse_pos.x = 0;
		}

		if (Mouse_pos.x >= ScreenSizeX - PlayerFishSize)
		{
			Mouse_pos.x = ScreenSizeX - PlayerFishSize;
		}

		if (Mouse_pos.y <= 0)
		{
			Mouse_pos.y = 0;
		}

		if (Mouse_pos.y >= ScreenSizeY - PlayerFishSize)
		{
			Mouse_pos.y = ScreenSizeY - PlayerFishSize;
		}

		//check collisions
		for (int i = 0; i < plants.size(); i++)   //player fish and plants collision
		{
			if (pow(plants[i].getPlantPosition().x - Fish_pos.x, 2) + pow(plants[i].getPlantPosition().y - Fish_pos.y, 2) < pow(PlayerFishSize/2, 2))   //we check if player fish is close enough (radius). To detect it we use (x1 - x2)^2 + (y1 - y2)^2 < radius^2 
			{
				if (plants[i].isMoving == true and PlayerFishEat == false)  //we can't call the same thread twice (and we can't eat the same plant twice) and we can't eat 2 things at once
				{
					plants[i].isMoving = false;  //block
					Points = Points + 10;                //increase points
					std::thread Eating(PlayerEatPlant, std::ref(PlayerFishEat), i, std::ref(PlayerFishOpen));    //it is necessary to use thread, because that "animation" is parallel for game loop (it can't stop main loop)
					Eating.detach();   //create thread
				}
			}
		}

		for (int i = 0; i < plants.size(); i++)  //fishes and plants collision
		{
			for (int a = 0; a < fishes.size(); a++)
			{
				if (pow(fishes[a].getPosition().x - plants[i].getPlantPosition().x, 2) + pow(fishes[a].getPosition().y - plants[i].getPlantPosition().y, 2) < pow(fishes[a].getSize()/2, 2))
				{
					if (plants[i].isMoving == true and fishes[a].IsMoving == true and fishes[a].IsEating == false)  //check if plants and fish are moving (nothing is eating them) and if fish is not eating something else
					{
						plants[i].isMoving = false;   //block
						fishes[a].IsEating = true;    //fish is eating
						std::thread Eating(FishEatPlant, std::ref(fishes[a].IsEating), std::ref(fishes[a].IsOpen), i);   //thread
						Eating.detach();
					}
				}
			}
		}

		for (int i = 0; i < fishes.size(); i++)    //player fish and other fishes
		{
			if(pow(fishes[i].getPosition().x - Fish_pos.x,2) + pow(fishes[i].getPosition().y - Fish_pos.y,2) < pow(fishes[i].getSize()/2.5 + PlayerFishSize /2.5, 2))
			{
				if (fishes[i].getSize() <= PlayerFishSize)    //if fish is smaller than player's fish then player's fish eat that fish
				{
					if (fishes[i].IsMoving == true and fishes[i].IsEating == false and PlayerFishEat == false)   //check if something is not eating this fish, if fish is not eating something and if player is not eating something
					{
						fishes[i].IsMoving = false;  //block
						Points = Points + fishes[i].getPoints();
						std::thread Eating(PlayerEatFish, std::ref(PlayerFishEat), i, std::ref(PlayerFishOpen));
						Eating.detach();
					}
				}
				else
				{
					std::cout << "loser" << std::endl;
					//break loop - u lose
				}
			}
		}

		//fish eat fish
		for (int i = 0; i < fishes.size(); i++)   //we check every fish with each other
		{
			for (int a = i+1; a < fishes.size() - i; a++)
			{
				if (pow(fishes[i].getPosition().x - fishes[a].getPosition().x, 2) + pow(fishes[i].getPosition().y - fishes[a].getPosition().y, 2) < pow(fishes[i].getSize() / 2.5 + fishes[a].getSize() / 2.5, 2))  //collision
				{
					//check lvl - fish with higher level eats fish with smaller level; if levels are equal do nothing (we could compare fish with size - results would be the same)
					if (fishes[i].getlvl() < fishes[a].getlvl())
					{
						if (fishes[i].IsMoving == true and fishes[i].IsEating == false and fishes[a].IsMoving == true and fishes[a].IsEating == false)  //check if fishes aren't eating and something doesn't eat them
						{
							fishes[i].IsMoving = false;  //block
							std::thread Eating(FishEatFish, a, i);
							Eating.detach();
						}
					}
					else if(fishes[i].getlvl() > fishes[a].getlvl())
					{
						if (fishes[i].IsMoving == true and fishes[i].IsEating == false and fishes[a].IsMoving == true and fishes[a].IsEating == false)
						{
							fishes[a].IsMoving = false;  //block
							std::thread Eating(FishEatFish, i, a);
							Eating.detach();
						}
					}
				}
			}
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

		if (CurrentTime >= NextFishSpawnTime)
		{
			fishes.emplace_back();

			NextFishSpawnTime = CurrentTime + 1 + rand() % 7;
		}

		for (int i = 0; i < plants.size(); i++) //update plants position
		{
			if (plants[i].isMoving == true)
			{
				plants[i].Move(PassedTime);
			}
		}

		for (int i = 0; i < fishes.size(); i++)  //update fish position
		{
			if (fishes[i].IsEating == false and fishes[i].IsMoving == true)
			{
				fishes[i].Move(PassedTime);
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

		for (int i = 0; i < fishes.size(); i++)
		{
			std::string Name = "Fish " + std::to_string(i);

			ShowFish(Name, fishes, i);
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
