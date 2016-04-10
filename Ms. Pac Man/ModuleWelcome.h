#ifndef __MODULEWELCOME_H__
#define __MODULEWELCOME_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;
struct _Mix_Music;

class ModuleWelcome : public Module
{
public:
	ModuleWelcome();
	~ModuleWelcome();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	_Mix_Music* music_sound = nullptr;
	SDL_Rect welcome;
};

#endif // __MODULEWELCOME_H__