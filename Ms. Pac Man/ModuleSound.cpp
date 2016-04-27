#include "Globals.h"
#include "Application.h"
#include "ModuleSound.h"

ModuleSound::ModuleSound()
{}
ModuleSound::~ModuleSound(){}

// Load
bool ModuleSound::Init()
{
	bool ret = true;
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	LOG("Loading background assets");

	start_mspacman = Mix_LoadMUS("Start_MsPacman.ogg");
	eat_ms = Mix_LoadWAV("Sound_Moviment_with_Eatting_Coins.wav");

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

	Mix_CloseAudio();
	Mix_FreeMusic(start_mspacman);
	Mix_FreeChunk(eat_ms);
	Mix_Quit();

	return true;
}


_Mix_Music* const ModuleSound::LoadMUS(const char* path)
{
	_Mix_Music* audio = Mix_LoadMUS(path);
	LOG("Loading Music\n");
	return audio;
}
