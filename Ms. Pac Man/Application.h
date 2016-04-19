#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 12

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModulePlayer;
class Module;
class ModuleWelcome;
class ModuleLevel1;
class ModuleLevel2;
class ModuleCongratulation;
class ModuleFadeToBlack;
class ModuleSound;
class ModuleGhost;

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
	ModuleCongratulation* win;
	ModuleFadeToBlack* fade;
	ModuleSound* sound;
	ModuleGhost* ghost;

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