#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 18

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModulePlayer;
class Module;
class ModuleWelcome;
class ModuleLevel1;
class ModuleLevel2;
class ModuleLevel3;
class ModuleLevel4;
class ModuleCongratulation;
class ModuleFadeToBlack;
class ModuleSound;
class ModuleGhostRed;
class ModuleGhostPink;
class ModuleGhostOrange;
class ModuleGhostBlue;
class ModuleCollision;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModulePlayer* player;
	ModuleWelcome* welcome;
	ModuleLevel1* level1;
	ModuleLevel2* level2;
	ModuleLevel3* level3;
	ModuleLevel4* level4;
	ModuleCongratulation* win;
	ModuleFadeToBlack* fade;
	ModuleSound* sound;
	ModuleGhostRed* ghost_r;
	ModuleGhostBlue* ghost_b;
	ModuleGhostOrange* ghost_o;
	ModuleGhostPink* ghost_p;

	ModuleCollision* collision;
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__