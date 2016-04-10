#ifndef __MODULESOUND_H__
#define __MODULESOUND_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleSound : public Module
{
public:
	ModuleSound();
	~ModuleSound();

	bool Start();
	//update_status Update();
	bool CleanUp();

public:
	_Mix_Music* const LoadMUS(const char* path);

public:
	_Mix_Music* music;
	_Mix_Music* music_2;
};

#endif // __MODULESOUND_H__


