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
	bool CleanUp();

public:

	

	Animation* animation_blue = &up_b;
	Animation* current_superpow_combination = &superpow_combination;
	SDL_Texture* graphics = nullptr;
	SDL_Rect test;
	SDL_Rect puntuation;
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


	iPoint test_num_UP;
	//iPoint test_num_DOWN;
	//iPoint test_num_LEFT;
	//iPoint test_num_RIGHT;

	int change_b = 1;
	int new_direction_b = 1; // 0-w 1-a 2-s 3-d

	bool ghost_up_r;
	bool ghost_down_r;
	bool ghost_left_r;
	bool ghost_right_r;

	bool can_right_r;
	bool can_down_r;
	bool can_left_r;
	bool can_up_r;
	bool change_direction_r;

	void OnCollision(Collider* c1, Collider* c2);
	bool dead_blue;
	bool GhostBlue_ispow;
	bool look_wherePacman;

	bool finish;

	bool super;

	bool Isinmid = true;
	int time_blue;

	int isleft;
	int isright;
	int isup;
	int isdown;
	int Time_change_direction;
	bool superfristmoviment;
	

};

#endif