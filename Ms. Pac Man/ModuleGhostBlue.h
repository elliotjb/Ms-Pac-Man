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
	bool CleanUp();

public:


	Animation* current_animation = &up_r;
	Animation* current_superpow_combination = &superpow_combination;
	SDL_Texture* graphics = nullptr;
	SDL_Rect test;

	Collider* collision_blue;
	//ghost blue
	Animation right_r;
	Animation left_r;
	Animation up_r;
	Animation down_r;
	iPoint position;

	SDL_Rect superpow_blue;

	SDL_Rect puntuation;
	Animation superpow_combination;

	iPoint up;
	iPoint left;
	iPoint down;
	iPoint right;

	int up_x_r;
	int down_x_r;
	int left_x_r;
	int right_x_r;
	int center_x_r;
	int r;

	int up_y_r;
	int down_y_r;
	int left_y_r;
	int right_y_r;
	int center_y_r;

	int speed;

	int new_direction_r; // 0-w 1-a 2-s 3-d

	bool ghost_up_r ;
	bool ghost_down_r ;
	bool ghost_left_r ;
	bool ghost_right_r ;

	bool can_right_r;
	bool can_down_r ;
	bool can_left_r ;
	bool can_up_r ;

	bool change_direction_r;
	bool GhostBlue_ispow;

	void OnCollision(Collider* c1, Collider* c2);
	bool dead_blue ;
	bool finish;
	bool m;
	int s;
	bool look_wherePacman;
	int Time_change_direction;
	int isleft;
	int isright;
	int isup;
	int isdown;

	bool super;

	bool Isinmid = true;
	int time_blue;
	int a;
	int t;
	int i;
	bool dead;

};

#endif
