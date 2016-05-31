#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleSound.h"
#include "ModuleWelcome.h"
#include "ModuleLevel_3.h"
#include "ModuleLevel_4.h"
#include "ModuleCongratulation.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGhostRed.h"
#include "ModuleGhostPink.h"
#include "ModuleGhostBlue.h"
#include "ModuleGhostOrange.h"
#include "ModuleCollision.h"
#include "ModuleScore.h"

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = welcome = new ModuleWelcome();
	modules[5] = level3 = new ModuleLevel3();
	modules[6] = level4 = new ModuleLevel4();
	modules[7] = win = new ModuleCongratulation();
	modules[8] = ghost_r = new ModuleGhostRed();
	modules[9] = ghost_b = new ModuleGhostBlue();
	modules[10] = ghost_o = new ModuleGhostOrange();
	modules[11] = ghost_p = new ModuleGhostPink();
	modules[12] = player = new ModulePlayer();
	modules[13] = sound = new ModuleSound();
	modules[14] = collision = new ModuleCollision();
	modules[15] = score = new ModuleScore();
	modules[16] = fade = new ModuleFadeToBlack();

}

Application::~Application()
{
	for (int i = NUM_MODULES - 1; i >= 0; --i)
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
	collision->Disable();
	score->Disable();
	player->Disable();
	level3->Disable();
	level4->Disable();
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