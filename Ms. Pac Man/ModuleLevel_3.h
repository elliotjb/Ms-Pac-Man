#ifndef __MODULELEVEL3_H__
#define __MODULELEVEL3_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleLevel3 : public Module
{
public:
	ModuleLevel3();
	~ModuleLevel3();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Animation big_pill;
	Animation* actual_animation = &big_pill;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics_2 = nullptr;
	SDL_Texture* graphics_3 = nullptr;
	SDL_Texture* graphics_4 = nullptr;
	SDL_Rect level3;
	SDL_Rect level3_2;
	SDL_Rect next;
	SDL_Rect next2;
	SDL_Rect level3_center;
	SDL_Rect pills;
	Animation water;

	int map[31][28];
	int eatenpills;
	int p;
	bool victory;
	bool sound_big_pill;

};

#endif