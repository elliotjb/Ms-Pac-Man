#include "Globals.h"
#include "Application.h"
#include "ModuleSound.h"
#include "ModuleFadeToBlack.h"

#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleSound::ModuleSound() : Module(){}
ModuleSound::~ModuleSound(){}

// Load
bool ModuleSound::Init()
{
	bool ret = true;
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	LOG("Loading background assets");

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Audio lib. Mix_Init: %s\n", Mix_GetError());
		ret = false;
	}

	return ret;
}

// Load assets
bool ModuleSound::CleanUp()
{
	LOG("Unloading honda stage");

	for (int i = 0; i < last_music; i++)
		Mix_FreeMusic(music[i]);

	Mix_CloseAudio();
	Mix_Quit();

	return true;
}


_Mix_Music* const ModuleSound::LoadMUS(const char* path)
{
	_Mix_Music* audio = Mix_LoadMUS(path);
	music[last_music++] = audio;
	LOG("Loading Music\n");
	return audio;
}
