#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();

public:

	Animation* current_animation = &left;

	SDL_Texture* graphics = nullptr;
	Animation right; //Hacia derecha
	Animation left; //Hacia izqueirda
	Animation up;
	Animation down;

	SDL_Rect test;

	iPoint position;
	int up_x;
	int down_x;
	int left_x;
	int right_x;
	int center_x;

	int up_y;
	int down_y;
	int left_y;
	int right_y;
	int center_y;


	int direction = 1; // 0-w 1-a 2-s 3-d
	int cont = 0;
	int tile[31][28];

	bool key = true;
	bool superpower;
	int timer;
};

#endif