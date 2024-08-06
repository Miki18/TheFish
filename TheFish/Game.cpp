#include <iostream>
#include <fstream>
#include <vector>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

//glfw version 3.4
//imgui version 1.90.9

int main()
{
    //Initialization GLFW
    if (!glfwInit())
        return 1;

    //Open window GLFW
    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui BMP Example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    //Initialization ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    GLuint Background;
    glGenTextures(1, &Background);
    glBindTexture(GL_TEXTURE_2D, Background);

    //texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //load a picture
    std::ifstream file("Background.bmp", std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file: " << "Background.bmp" << std::endl;
        return 0;
    }

    char header[54];
    file.read(header, 54);
    int width = 1280;
    int height = 720;

    //Load pixels' data
    int size = 3 * width * height;
    std::vector<char> pixels(size);
    file.read(pixels.data(), size);

    //Change pixels
    for (int i = 0; i < width * height; ++i)
    {
        unsigned char temp = pixels[i * 3]; // B
        pixels[i * 3] = pixels[i * 3 + 2]; // R
        pixels[i * 3 + 2] = temp; // B
    }

    //Create a texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
    file.close();

    GLuint Player_Fish;
    glGenTextures(1, &Player_Fish);
    glBindTexture(GL_TEXTURE_2D, Player_Fish);

    //texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //load a picture
    file.open("PlayerFish.bmp", std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file: " << "PlayerFish.bmp" << std::endl;
        return 1;
    }

    file.read(header, 54);
    width = 50;
    height = 50;

    //Load pixels' data
    size = 4 * width * height;
    file.read(pixels.data(), size);

    std::vector<char> rgbaPixels(size);

    for (int i = 0; i < width * height; ++i) {
        rgbaPixels[4 * i] = pixels[4 * i + 2];     // R
        rgbaPixels[4 * i + 1] = pixels[4 * i + 1]; // G
        rgbaPixels[4 * i + 2] = pixels[4 * i]; // B
        rgbaPixels[4 * i + 3] = pixels[4 * i + 3];     // A
    }

    //Create a texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaPixels.data());

    ImVec2 previous_pos = ImGui::GetMousePos();
	ImVec2 Mouse_pos;
	ImVec2 Fish_pos;
    
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Ustawia kolor t³a na bia³y
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //show image
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::Begin("Background", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
        ImGui::Image((void*)(intptr_t)Background, ImVec2(1300, 750));
        ImGui::End();

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

		if (abs(Mouse_pos.x - Fish_pos.x) < 25)
		{
			Fish_pos.x = Mouse_pos.x;
		}
		else
		{
			if (Mouse_pos.x > Fish_pos.x)
			{
				Fish_pos.x += 25;
			}
			else
			{
				Fish_pos.x -= 25;
			}
		}

		if (abs(Mouse_pos.y - Fish_pos.y) < 25)
		{
			Fish_pos.y = Mouse_pos.y;
		}
		else
		{
			if (Mouse_pos.y > Fish_pos.y)
			{
				Fish_pos.y += 25;
			}
			else
			{
				Fish_pos.y -= 25;
			}
		}

        ImGui::SetNextWindowPos(Mouse_pos);
        ImGui::Begin("Fish", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);   //Player fish
		//show image - use ImVec2 to rotate (every level we go *2 -> 1 lvl = 25, 2 lvl = 50, 3lvl = 100 etc)
		if (previous_pos.x < Mouse_pos.x)
		{
			ImGui::Image((void*)(intptr_t)Player_Fish, ImVec2(25, 25), ImVec2(1, 0), ImVec2(0, 1));
		}
		else
		{
			ImGui::Image((void*)(intptr_t)Player_Fish, ImVec2(25, 25), ImVec2(0, 0), ImVec2(1, 1));

		}
        ImGui::End();

		previous_pos.x = Fish_pos.x;
		previous_pos.y = Fish_pos.y;

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
