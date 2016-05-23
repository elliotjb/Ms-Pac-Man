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
	Animation big_pill;
	Animation* actual_animation = &big_pill;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics_2 = nullptr;
	SDL_Rect level1;
	SDL_Rect level1_2;
	SDL_Rect level1_center;
	SDL_Rect pills;
	SDL_Rect blacksquare;
	Animation water;

	int map[31][28];
	int eatenpills;
	bool victory;

	bool sound_big_pill;
};

#endif // __MODULELEVEL1_H__