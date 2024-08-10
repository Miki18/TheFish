//Textures.h and Textures.cpp load images and create textures. We can find all texture variables (GLuint) here.

#pragma once
#include "Includes.h"

//Variables
extern GLuint BackgroundTex;
extern GLuint PlantTex;
extern GLuint FishesTex[1][2];     //Fish[0][x] is player's fish
//First parameter is for different fish, while second tell us if fish has close or open mouth.

void LoadBackgroundTexture();    //load background texture
void LoadObjectTexture(GLuint& Tex, std::string File_name);   //load objects texture
void LoadAllTextures();  //When we start game all textures will load