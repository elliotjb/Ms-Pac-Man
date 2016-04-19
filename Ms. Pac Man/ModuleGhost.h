#ifndef __ModuleGhost_H__
#define __ModuleGhost_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include <time.h>
#include <stdlib.h> 

struct SDL_Texture;

class ModuleGhost : public Module
{
public:
	ModuleGhost();
	~ModuleGhost();

	bool Start();
	update_status Update();

public:

	Animation* current_animation_r = &left_r;
	Animation* current_animation_p = &up_p;
	Animation* current_animation_b = &up_b;
	Animation* current_animation_o = &up_o;
	SDL_Texture* graphics = nullptr;

	int direc_r, direc_p, direc_b, direc_o;
	int con_r, con2_r;
	int con_p, con2_p;
	int con_b, con2_b;
	int con_o, con2_o;
	int repeat_r, repeat_p, repeat_b, repeat_o;
	int time_ghost;

	//ghost red
	Animation right_r;
	Animation left_r;
	Animation up_r;
	Animation down_r;
	fPoint position_r;

	//ghost pink
	Animation right_p;
	Animation left_p;
	Animation up_p;
	Animation down_p;
	fPoint position_p;

	//ghost blue
	Animation right_b;
	Animation left_b;
	Animation up_b;
	Animation down_b;
	fPoint position_b;

	//ghost orange
	Animation right_o;
	Animation left_o;
	Animation up_o;
	Animation down_o;
	fPoint position_o;

};

#endif // __ModuleGhost_H__


/*	if (repeat_r == 0)
	{
		if (con2_r <= con_r)
		{
			if (position_r.x <= 204)
			{
				current_animation_r = &right_r;
				position_r.x += speed;
				con2_r++;
			}
			else
			{
				con2_r = con_r;
			}
		}
		}*/