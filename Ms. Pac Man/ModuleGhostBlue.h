/*#ifndef __ModuleGhostBlue_H__
#define __ModuleGhostBlue_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include <time.h>
#include <stdlib.h> 

struct SDL_Texture;

class ModuleGhostBlue : public Module
{
public:
	ModuleGhostBlue();
	~ModuleGhostBlue();

	bool Start();
	update_status Update();

public:


	Animation* current_animation_b = &up_b;
	
	SDL_Texture* graphics = nullptr;


	int con_b, con2_b;
	int repeat_b;
	int time_ghost;


	//ghost blue
	Animation right_b;
	Animation left_b;
	Animation up_b;
	Animation down_b;
	fPoint position_b;

};

#endif*/