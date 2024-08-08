//Main game file
// 
//Some libraries and their versions which I use in this project:
//glfw version 3.4
//imgui version 1.90.9

#pragma once
#include "Textures.h"
#include "Includes.h"

int main()
{
	//Initialization GLFW
	if (!glfwInit())
	{
		exit(1);
	}

	//Open window GLFW
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Fish The Game", NULL, NULL);
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

	//Load Textures
	LoadAllTextures();

    ImVec2 previous_pos = ImGui::GetMousePos();
	ImVec2 Mouse_pos;
	ImVec2 Fish_pos;

	double LastFrameTime = 0;
	double CurrentTime = 0;
	double PassedTime = 0;

	double LastSpawnTime = 0;

	int Points = 0;

	ImGuiStyle* style = &ImGui::GetStyle();
	style->Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

	srand(time(NULL));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Ustawia kolor t³a na bia³y
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//show image
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::Begin("Background", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize);
		ImGui::Image((void*)(intptr_t)Background, ImVec2(1300, 750));
		ImGui::End();

		CurrentTime = glfwGetTime();
		PassedTime = CurrentTime - LastFrameTime;

		Mouse_pos = ImGui::GetMousePos();
		Mouse_pos.x = Mouse_pos.x - 25 / 2;
		Mouse_pos.y = Mouse_pos.y - 25 / 2;

		if (Mouse_pos.x <= 0)
		{
			Mouse_pos.x = 0;
		}

		if (Mouse_pos.x >= 1280 - 25)
		{
			Mouse_pos.x = 1280 - 25;
		}

		if (Mouse_pos.y <= 0)
		{
			Mouse_pos.y = 0;
		}

		if (Mouse_pos.y >= 720 - 25)
		{
			Mouse_pos.y = 720 - 25;
		}

		Fish_pos.x = Fish_pos.x + ((Mouse_pos.x - Fish_pos.x) * 5 * PassedTime);
		Fish_pos.y = Fish_pos.y + ((Mouse_pos.y - Fish_pos.y) * 5 * PassedTime);

		LastFrameTime = CurrentTime;

        ImGui::SetNextWindowPos(Fish_pos);
        ImGui::Begin("Player", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);   //Player fish
		//show image - use ImVec2 to rotate (every level we go *2 -> 1 lvl = 25, 2 lvl = 50, 3lvl = 100 etc)
		if (previous_pos.x < Mouse_pos.x)
		{
			ImGui::Image((void*)(intptr_t)Fishes[0][0], ImVec2(25, 25), ImVec2(1, 0), ImVec2(0, 1)); //texture name, size, mirror
		}
		else
		{
			ImGui::Image((void*)(intptr_t)Fishes[0][0], ImVec2(25, 25), ImVec2(0, 0), ImVec2(1, 1));

		}
        ImGui::End();

		previous_pos.x = Fish_pos.x;
		previous_pos.y = Fish_pos.y;

		ImGui::SetNextWindowPos(ImVec2(100, 100));
		ImGui::SetNextWindowSize(ImVec2(15, 15));
		ImGui::Begin("Plant", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
		ImGui::Image((void*)(intptr_t)Plant, ImVec2(15, 15));
		ImGui::End();

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(180, 40));
		ImGui::Begin("Points", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
		ImGui::SetWindowFontScale(1.5f);
		ImGui::SetCursorPos(ImVec2(8, 10));
		ImGui::Text("Points: %d", Points);
		ImGui::End();
		
		if (glfwGetTime() - LastSpawnTime > 2)
		{
			if (rand() % 25 == 0)     //fix this shit
			{
				//std::cout << "Yes" << std::endl;
				LastSpawnTime = glfwGetTime();
			}
		}

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}
