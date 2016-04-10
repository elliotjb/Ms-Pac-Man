#ifndef __MODULECONGRATULATIONS_H__
#define __MODULECONGRATULATIONS_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

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
	SDL_Rect congratulations;
	Animation water;
};

#endif // __MODULECONGRATULATIONS_H__