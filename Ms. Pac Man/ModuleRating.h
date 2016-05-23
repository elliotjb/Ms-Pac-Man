#ifndef __ModuleRating_H__
#define __ModuleRating_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleRating : public Module
{
public:
	ModuleRating();
	~ModuleRating();

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


};

#endif