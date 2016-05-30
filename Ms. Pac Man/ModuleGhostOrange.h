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


	Animation* animation_blue = &up_b;
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

	iPoint position_blue;
	iPoint right_blue;
	iPoint left_blue;
	iPoint up_blue;
	iPoint down_blue;
	iPoint center_blue;

	int change_b = 1;
	int new_direction_b = 1; // 0-w 1-a 2-s 3-d

	bool ghost_up_blue = false;
	bool ghost_down_blue = false;
	bool ghost_left_blue = false;
	bool ghost_right_blue = false;

	bool can_right_b = false;
	bool can_down_b = false;
	bool can_left_b = false;
	bool can_up_b = false;

	bool change_com_b = false;
	bool change_direction_blue;
	bool dead;
	bool finish;

	void OnCollision(Collider* c1, Collider* c2);
	bool dead_blue = false;
	bool GhostBlue_ispow = false;

	bool Isinmid = true;
	int time_blue = 0;
	int i = 0;
	int distance;
	int t = 0;

	bool super;
};

#endif