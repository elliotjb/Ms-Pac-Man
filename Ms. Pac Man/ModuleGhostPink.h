#ifndef __ModuleGhostPink_H__
#define __ModuleGhostPink_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include <time.h>
#include <stdlib.h> 

struct SDL_Texture;

class ModuleGhostPink : public Module
{
public:
	ModuleGhostPink();
	~ModuleGhostPink();

	bool Start();
	update_status Update();

public:

	
	Animation* current_animation_p = &up_p;

	SDL_Texture* graphics = nullptr;

	int  direc_p;
	
	int con_p, con2_p;
	
	int repeat_p;
	int time_ghost;



	//ghost pink
	Animation right_p;
	Animation left_p;
	Animation up_p;
	Animation down_p;
	fPoint position_p;

	

};

#endif