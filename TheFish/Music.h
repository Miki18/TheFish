#pragma once

void PlayMusic()
{
	while (true)   //we put  PlaySound in loop, so when music ends it will start again
	{
		PlaySound(TEXT("MoonlightBeach.wav"), NULL, SND_FILENAME);    //play music
	}
}