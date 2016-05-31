#ifndef __MODULELEVEL4_H__
#define __MODULELEVEL4_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleLevel4 : public Module
{
public:
	ModuleLevel4();
	~ModuleLevel4();

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
	SDL_Rect level4;
	SDL_Rect level4_2;
	SDL_Rect level4_center;
	SDL_Rect next;
	SDL_Rect next2;
	SDL_Rect pills;

	int map[31][28];
	int eatenpills;
	bool victory;
	bool sound_big_pill;
	bool islevel4;
	int p;
};

#endif