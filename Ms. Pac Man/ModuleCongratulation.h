#ifndef __MODULECONGRATULATIONS_H__
#define __MODULECONGRATULATIONS_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;
struct _Mix_Music;

class ModuleCongratulation : public Module
{
public:
	ModuleCongratulation();
	~ModuleCongratulation();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics_2 = nullptr;
	_Mix_Music* sounds;
	SDL_Rect congratulations;
	SDL_Rect credit;
	Animation water;
	int p;
};

#endif // __MODULECONGRATULATIONS_H__