#ifndef __ModuleGhostRED_H__
#define __ModuleGhostRED_H__
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

	Animation* current_animation = &up_r;
	Animation* current_superpow_combination = &superpow_combination;
	SDL_Texture* graphics = nullptr;
	SDL_Rect test;

	Collider* collision;
	SDL_Rect superpow_blue;
	Animation superpow_combination;

	//ghost blue
	Animation right_r;
	Animation left_r;
	Animation up_r;
	Animation down_r;
	iPoint position;

	iPoint up;
	iPoint left;
	iPoint down;
	iPoint right;

	int up_x_r;
	int down_x_r;
	int left_x_r;
	int right_x_r;
	int center_x_r;

	int up_y_r;
	int down_y_r;
	int left_y_r;
	int right_y_r;
	int center_y_r;

	int change_r = 1;
	int new_direction_r = 1; // 0-w 1-a 2-s 3-d

	bool ghost_up_r = false;
	bool ghost_down_r = false;
	bool ghost_left_r = false;
	bool ghost_right_r = false;

	bool can_right_r = false;
	bool can_down_r = false;
	bool can_left_r = false;
	bool can_up_r = false;

	bool change_comp_r = false;
	bool change_direction_r;
	bool GhostBlue_ispow = false;

	int isleft;
	int isright;
	int isup;
	int isdown;
	int time_blue;

	bool look_wherePacman;

	void OnCollision(Collider* c1, Collider* c2);
};

#endif