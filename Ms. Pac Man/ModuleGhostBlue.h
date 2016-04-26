#ifndef __ModuleGhostBlue_H__
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
	Animation* current_superpow_combination = &superpow_combination;
	SDL_Texture* graphics = nullptr;
	SDL_Rect test;

	Collider* collision_blue;
	//ghost blue
	Animation right_b;
	Animation left_b;
	Animation up_b;
	Animation down_b;
	SDL_Rect superpow_blue;
	Animation superpow_combination;
	iPoint position_b;

	int up_x_b;
	int down_x_b;
	int left_x_b;
	int right_x_b;
	int center_x_b;

	int up_y_b;
	int down_y_b;
	int left_y_b;
	int right_y_b;
	int center_y_b;

	int change_b = 1;
	int new_direction_b = 1; // 0-w 1-a 2-s 3-d

	bool ghost_up_b = false;
	bool ghost_down_b = false;
	bool ghost_left_b = false;
	bool ghost_right_b = false;

	bool can_right_b = false;
	bool can_down_b = false;
	bool can_left_b = false;
	bool can_up_b = false;

	bool change_com_b = false;
	bool change_direction_b;

	void OnCollision(Collider* c1, Collider* c2);
	bool dead_blue = false;
	bool GhostBlue_ispow = false;

	bool Isinmid = true;
	int time_blue = 0;

};

#endif
