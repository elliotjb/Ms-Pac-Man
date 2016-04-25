/*#ifndef __ModuleGhostOrange_H__
#define __ModuleGhostOrange_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include <time.h>
#include <stdlib.h> 

struct SDL_Texture;

class ModuleGhostOrange : public Module
{
public:
	ModuleGhostOrange();
	~ModuleGhostOrange();

	bool Start();
	update_status Update();

public:


	Animation* current_animation_o = &up_o;
	SDL_Texture* graphics = nullptr;

	int  direc_o;
	
	int con_o, con2_o;
	int  repeat_o;
	int time_ghost;

	//ghost orange
	Animation right_o;
	Animation left_o;
	Animation up_o;
	Animation down_o;
	fPoint position_o;

};

#endif*/