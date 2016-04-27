#ifndef __MODULESOUND_H__
#define __MODULESOUND_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#define MAX_AUDIO 15
typedef unsigned int uint;

struct _Mix_Music;

//struct _Mix_Chunk;

class ModuleSound : public Module
{
public:

	ModuleSound();
	~ModuleSound();

	bool Init();
	//update_status Update();
	bool CleanUp();

	_Mix_Music* music[MAX_AUDIO];
	uint last_music = 0;
	_Mix_Music* const LoadMUS(const char* path);

public:
	Mix_Music* start_mspacman;
	Mix_Chunk* eat_ms;
	Mix_Chunk* mov_ms;


};

#endif // __MODULESOUND_H__


