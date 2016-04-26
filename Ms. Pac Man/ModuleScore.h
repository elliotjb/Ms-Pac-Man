#ifndef _SCORE_
#define _SCORE_
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleScore : public Module
{
public:
	ModuleScore();
	bool Start();
	update_status Update();
	bool CleanUp();
	~ModuleScore();
public:
	char Maplvl[3][28];
	int score[5];
	int s0, s1, s2, s3, s4; // score[5] = {s4,s3,s2,s1,s0}
	SDL_Texture* graphics;
	SDL_Texture* graphicstxt;

	SDL_Rect Space;
	SDL_Rect One;
	SDL_Rect U;
	SDL_Rect P;
	SDL_Rect H;
	SDL_Rect I;
	SDL_Rect G;
	SDL_Rect S;
	SDL_Rect C;
	SDL_Rect O;
	SDL_Rect R;
	SDL_Rect E;
	SDL_Rect SC0;
	SDL_Rect SC1;
	SDL_Rect SC2;
	SDL_Rect SC3;
	SDL_Rect SC4;
	SDL_Rect SC5;
	SDL_Rect SC6;
	SDL_Rect SC7;
	SDL_Rect SC8;
	SDL_Rect SC9;
};


#endif