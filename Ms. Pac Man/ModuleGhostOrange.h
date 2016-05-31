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
	bool CleanUp();

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
	SDL_Rect puntuation;
	Animation superpow_combination;

	iPoint position_blue;
	iPoint right_blue;
	iPoint left_blue;
	iPoint up_blue;
	iPoint down_blue;
	iPoint center_blue;

	int change_b;
	int new_direction_b; // 0-w 1-a 2-s 3-d

	bool ghost_up_blue;
	bool ghost_down_blue;
	bool ghost_left_blue;
	bool ghost_right_blue;

	bool can_right_b;
	bool can_down_b;
	bool can_left_b;
	bool can_up_b;
	bool m;
	bool change_com_b;
	bool change_direction_blue;
	bool dead;
	bool finish;

	void OnCollision(Collider* c1, Collider* c2);
	bool dead_blue;
	bool GhostBlue_ispow;

	bool Isinmid;
	int time_blue;
	int i;
	int distance;
	int t;
	int map_ghost[31][28];

	bool super;
};

#endif