#ifndef __MODULELEVEL1_H__
#define __MODULELEVEL1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleLevel1 : public Module
{
public:
	ModuleLevel1();
	~ModuleLevel1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Animation big_point;
	Animation* actual_animation = &big_point;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics_2 = nullptr;
	SDL_Rect level1;
	SDL_Rect level1_2;
	SDL_Rect level1_center;
	Animation water;
};

#endif // __MODULELEVEL1_H__