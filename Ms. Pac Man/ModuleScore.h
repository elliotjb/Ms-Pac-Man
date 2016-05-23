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

public:

	SDL_Texture* graphics = nullptr;

	SDL_Rect number0;
	SDL_Rect number1;
	SDL_Rect number2;
	SDL_Rect number3;
	SDL_Rect number4;
	SDL_Rect number5;
	SDL_Rect number6;
	SDL_Rect number7;
	SDL_Rect number8;
	SDL_Rect number9;

	int number_pos1;
	int number_pos2;
	int number_pos3;
	int number_pos4;

	bool p_1;
	bool p_2;
	int puntuation;





};

#endif