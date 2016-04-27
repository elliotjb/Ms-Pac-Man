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
	Collider* collision_player;
	SDL_Texture* graphics = nullptr;
	Animation right; //Hacia derecha
	Animation left; //Hacia izqueirda
	Animation up;
	Animation down;
	iPoint position;
	int playerlives;
	iPoint direction_right;
	iPoint direction_left;
	iPoint direction_up;
	iPoint direction_down;
	iPoint center;
	SDL_Rect test;

	bool destroyed = false;


	int direction = 1; // 0-w 1-a 2-s 3-d
	int cont = 0;
	//int tile[31][28];

	int time_to_start = 0;
	bool superpower;
	int timer;

	void OnCollision(Collider* c1, Collider* c2);
};

#endif