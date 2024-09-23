# The Fish

# Short introduction
You are fish and you need to eat fishes smaller than you and plant to collect enough points to finish level. There are 5 levels and in every level there is that one type of fish that is bigger than you therefore you have to avoid it. If it catch you, the level restarts.
# Libraries
This simple game was made in C++. I used Visual Studio 2022 and ISO C++ 14 standard.

I also used external libraries such as:
  - glfw version 3.4
  - imgui version 1.90.9
# Description
  - Project Structure: <br>
    Game.cpp is the main file. Music.h is for music and Includes.h contains the most of includes that are needed in the most of .cpp files. Those two .h files doesn't have .cpp file related to them. <br>
    Textures.h loads textures while Display.h display windows on the screen (and also loaded textures if they are needed). We also have two classes: Plant.h and Fish.h. Those four .h files have .cpp file related to them. <br>
  - Game Loop: <br>
    When game starts it loads all textures to variables. In main loop (game loop) game first processes all inputs from player than updates the game (for example move fish) and in the end it displays everything. <br>
  - Levels: <br>
    All levels are in the same file. The only thing that changes are variables' values. However game have GameScreen variable that determines where player is right now. It has values from 0 to 3: <br>
    * 0 - actual game where player moves fish
    * 1 - you lose where player can restart level or exit
    * 2 - go to next level where player gets info that he finished level
    * 3 - finished game where player can choose whether he wants to restarts the whole game or exit <br>
    
Game is avaible on itchio for free.<br>
Game was created by Miki18
