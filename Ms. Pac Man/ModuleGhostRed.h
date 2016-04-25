/*#ifndef __ModuleGhostRED_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include <time.h>
#include <stdlib.h> 

struct SDL_Texture;

class ModuleGhostRed : public Module
{
public:
	ModuleGhostRed();
	~ModuleGhostRed();

	bool Start();
	update_status Update();

public:

	Animation* current_animation_r = &left_r;
	SDL_Texture* graphics = nullptr;

	int direc_r;
	int con_r, con2_r;
	

	int repeat_r;
	int time_ghost;

	//ghost red
	Animation right_r;
	Animation left_r;
	Animation up_r;
	Animation down_r;
	fPoint position_r;


};

#endif*/