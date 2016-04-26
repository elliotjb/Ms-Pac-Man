#ifndef __ModuleGhostOrange_H__
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


	Animation* current_animation = &up_o;
	SDL_Texture* graphics = nullptr;
	SDL_Rect test;

	//ghost blue
	Animation right_o;
	Animation left_o;
	Animation up_o;
	Animation down_o;
	iPoint position_o;

	int up_x_o;
	int down_x_o;
	int left_x_o;
	int right_x_o;
	int center_x_o;

	int up_y_o;
	int down_y_o;
	int left_y_o;
	int right_y_o;
	int center_y_o;

	int change_o = 1;
	int new_direction_o = 1; // 0-w 1-a 2-s 3-d

	bool ghost_up_o = false;
	bool ghost_down_o = false;
	bool ghost_left_o = false;
	bool ghost_right_o = false;

	bool can_right_o = false;
	bool can_down_o = false;
	bool can_left_o = false;
	bool can_up_o = false;

	bool change_comp_o = false;
	bool change_direction_o;

};

#endif