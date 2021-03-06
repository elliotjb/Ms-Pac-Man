#ifndef __ModuleRating_H__
#define __ModuleRating_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleScore : public Module
{
public:
	ModuleScore();
	~ModuleScore();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect test0;
	SDL_Rect test;
	SDL_Rect test2;
	SDL_Rect test3;

	SDL_Rect coins_test;
	SDL_Rect coins_test1;

	SDL_Rect MAX_test0;
	SDL_Rect MAX_test;
	SDL_Rect MAX_test2;
	SDL_Rect MAX_test3;

	int coin_number_pos1;
	int coin_number_pos2;

	int number_pos1;
	int number_pos2;
	int number_pos3;
	int number_pos4;

	int puntuation;
	int NUM_coins;
	int MAX_puntuation;





};

#endif