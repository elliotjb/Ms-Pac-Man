#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleSound.h"
#include "ModuleWelcome.h"
#include "ModuleLevel_1.h"
#include "ModuleLevel_2.h"
#include "ModuleCongratulation.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGhostRed.h"
#include "ModuleGhostPink.h"
#include "ModuleGhostBlue.h"
#include "ModuleGhostOrange.h"

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = welcome = new ModuleWelcome();
	modules[5] = level1 = new ModuleLevel1();
	modules[6] = level2 = new ModuleLevel2();
	modules[7] = win = new ModuleCongratulation();
	modules[8] = ghost_r = new ModuleGhostRed();
	modules[9] = ghost_b = new ModuleGhostBlue();
	modules[10] = ghost_o = new ModuleGhostOrange();
	modules[11] = ghost_p = new ModuleGhostPink();
	modules[12] = player = new ModulePlayer();
	modules[13] = sound = new ModuleSound();
	modules[14] = fade = new ModuleFadeToBlack();
	modules[15] = menu = new ModuleLevel1();
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Player will be enabled on the first update of a new scene
	ghost_r->Disable();
	ghost_b->Disable();
	ghost_o->Disable();
	ghost_p->Disable();
	player->Disable();
	level1->Disable();
	level2->Disable();
	win->Disable();
	
	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}