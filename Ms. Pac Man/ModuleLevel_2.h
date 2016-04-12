#ifndef __ModuleLevel2_H__
#define __ModuleLevel2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleLevel2 : public Module
{
public:
	ModuleLevel2();
	~ModuleLevel2();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Animation big_point;
	Animation* actual_animation = &big_point;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics_2 = nullptr;
	SDL_Rect level2;
	SDL_Rect background;
	Animation Ship;

};

#endif // __ModuleLevel2_H__