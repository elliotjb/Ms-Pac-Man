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

	LOG("Loading Sounds");

	start_mspacman = Mix_LoadMUS("Sounds/Start_MsPacman.ogg");
	eat_big_pills = Mix_LoadWAV("Sounds/Sound_Eat_Bonus.wav");
	eat_ms = Mix_LoadWAV("Sounds/Sound_Moviment_with_Eatting_Coins.wav");
	sound_mov = Mix_LoadWAV("Sounds/Sound_eat_ghost.wav");
	sound_dead = Mix_LoadWAV("Sounds/Sound_Death.wav");

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
	Mix_FreeChunk(sound_mov);
	Mix_FreeChunk(sound_dead);
	Mix_FreeChunk(eat_big_pills);
	Mix_Quit();

	return true;
}


_Mix_Music* const ModuleSound::LoadMUS(const char* path)
{
	_Mix_Music* audio = Mix_LoadMUS(path);
	LOG("Loading Music\n");
	return audio;
}
