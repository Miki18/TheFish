//Info: Textures.h

#pragma once
#include "Textures.h"
#include "Includes.h"

GLuint BackgroundTex;
GLuint PlantTex;
GLuint FishesTex[7][2];

void LoadBackgroundTexture()
{
	//gl Gen Texture and blind texture
	glGenTextures(1, &BackgroundTex);
	glBindTexture(GL_TEXTURE_2D, BackgroundTex);

	//texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//load a picture
	std::ifstream file("Background.bmp", std::ios::binary);
	if (!file) {
		std::cerr << "Cannot open file: " << "Background.bmp" << std::endl;
	}

	//Variables
	char header[54];  //bmp header (it has 54 chars)
	file.read(header, 54);
	int width = ScreenSizeX;     //texture size (pixels)
	int height = ScreenSizeY;

	//Load pixels' data
	int size = 3 * width * height;    //width * height = total number of pixels and multiply by 3, because every pixel has R G B parameters (no alpha)
	std::vector<char> pixels(size);   //for pixels
	file.read(pixels.data(), size);   //read data

	//Change pixels
	for (int i = 0; i < width * height; ++i)   //because BMP store pictures in BGR and glTexImage2D function needs RGB we need to convert BGR to RGB
	{
		unsigned char temp = pixels[i * 3]; // B
		pixels[i * 3] = pixels[i * 3 + 2]; // R
		pixels[i * 3 + 2] = temp; // B
	}

	//Create a texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

	//close file
	file.close();
}

void LoadObjectTexture(GLuint& Tex, std::string File_name)
{
	//gl Gen Textures and Blind
	glGenTextures(1, &Tex);
	glBindTexture(GL_TEXTURE_2D, Tex);

	//texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//load a picture
	std::ifstream file(File_name, std::ios::binary);
	if (!file) {
		std::cerr << "Cannot open object texture file" << std::endl;
	}

	char header[54];    //BMP header
	file.read(header, 54);
	int width = 50;     //every objects will have 50 x 50 texture
	int height = 50;

	//Load pixels' data
	int size = 4 * width * height;     //Objects have alpha parameter therefore we need to load R G B & A (4 parameters per pixel)
	std::vector<char> pixels(size);    //store oryginal
	file.read(pixels.data(), size);     //read pixels
	std::vector<char> rgbaPixels(size);  //store RGBA

	//Because BMP store BGRA file, we need to convert BGRA to RGBA. That loop does that and save data in rgbaPixels
	for (int i = 0; i < width * height; ++i) {
		rgbaPixels[4 * i] = pixels[4 * i + 2];     // R
		rgbaPixels[4 * i + 1] = pixels[4 * i + 1]; // G
		rgbaPixels[4 * i + 2] = pixels[4 * i]; // B
		rgbaPixels[4 * i + 3] = pixels[4 * i + 3];     // A
	}

	//Create a texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaPixels.data());

	//close file
	file.close();
}

void LoadAllTextures()
{
	//Background
	LoadBackgroundTexture();

	//Plant
	LoadObjectTexture(std::ref(PlantTex), "Plant.bmp");

	//Player Fish
	LoadObjectTexture(std::ref(FishesTex[0][0]), "PlayerFish.bmp");
	LoadObjectTexture(std::ref(FishesTex[0][1]), "PlayerFishEat.bmp");

	//Fish 1 texture
	LoadObjectTexture(std::ref(FishesTex[1][0]), "fish1_close.bmp");
	LoadObjectTexture(std::ref(FishesTex[1][1]), "fish1_open.bmp");

	//Fish 2 texture
	LoadObjectTexture(std::ref(FishesTex[2][0]), "fish2_close.bmp");
	LoadObjectTexture(std::ref(FishesTex[2][1]), "fish2_open.bmp");

	//Fish 3 texture
	LoadObjectTexture(std::ref(FishesTex[3][0]), "fish3_close.bmp");
	LoadObjectTexture(std::ref(FishesTex[3][1]), "fish3_open.bmp");

	//Fish 4 texture
	LoadObjectTexture(std::ref(FishesTex[4][0]), "fish4_close.bmp");
	LoadObjectTexture(std::ref(FishesTex[4][1]), "fish4_open.bmp");

	//Fish 5 texture
	LoadObjectTexture(std::ref(FishesTex[5][0]), "fish5_close.bmp");
	LoadObjectTexture(std::ref(FishesTex[5][1]), "fish5_open.bmp");

	//Fish 6 texture
	LoadObjectTexture(std::ref(FishesTex[6][0]), "fish6_close.bmp");
	LoadObjectTexture(std::ref(FishesTex[6][1]), "fish6_open.bmp");
}