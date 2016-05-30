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
	bool CleanUp();

public:

	Animation* current_animation;
	Collider* collision_player;
	SDL_Texture* graphics = nullptr;
	Animation right; //Hacia derecha
	Animation left; //Hacia izqueirda
	Animation up;
	Animation down;
	Animation dead;
	iPoint position;
	int playerlives;
	iPoint direction_right;
	iPoint direction_left;
	iPoint direction_up;
	iPoint direction_down;
	iPoint center;
	SDL_Rect test;
	SDL_Rect lose;
	SDL_Rect ready;
	SDL_Rect ready2;
	SDL_Rect square;

	//Bool to comprovated so PacMan is Dead
	bool isdead;

	//SPEED
	int speed;

	//GOD Mode
	bool GOD;
	SDL_Rect Mode_GOD;
	bool SUPER_GOD;
	SDL_Rect SUPER_Mode_GOD;

	//STOP
	int stop;

	//Bool to comprovated if u change direction
	bool key_W = false;
	bool key_A = true;
	bool key_S = false;
	bool key_D = false;

	int direction; // 0-w 1-a 2-s 3-d
	int cont = 0;
	//int tile[31][28];

	int time_to_start = 0;
	bool superpower;
	int timer;
	int t;
	int timetorespawn;


	void OnCollision(Collider* c1, Collider* c2);
};

#endif