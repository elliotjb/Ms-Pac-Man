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

	
	Animation* current_animation = &up_p;
	SDL_Texture* graphics = nullptr;
	SDL_Rect test;

	//ghost blue
	Animation right_p;
	Animation left_p;
	Animation up_p;
	Animation down_p;
	iPoint position_p;

	int up_x_p;
	int down_x_p;
	int left_x_p;
	int right_x_p;
	int center_x_p;

	int up_y_p;
	int down_y_p;
	int left_y_p;
	int right_y_p;
	int center_y_p;

	int change_p = 1;
	int new_direction_p = 1; // 0-w 1-a 2-s 3-d

	bool ghost_up_p = false;
	bool ghost_down_p = false;
	bool ghost_left_p = false;
	bool ghost_right_p = false;

	bool can_right_p = false;
	bool can_down_p = false;
	bool can_left_p = false;
	bool can_up_p = false;

	bool change_comp_p = false;
	bool change_direction_p;

	

};

#endif