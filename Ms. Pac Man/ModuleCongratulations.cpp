#include "Globals.h"
#include "Application.h"
#include "ModuleCongratulation.h"
#include "ModuleWelcome.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLevel_1.h"
#include "ModuleCollision.h"

ModuleCongratulation::ModuleCongratulation()
{
	//Welcome
	congratulations = { 0, 0, 224, 288 };
	// ground
	//ground = { 8, 376, 848, 64 };


	// flag animation
	/*water.PushBack({ 8, 447, 283, 9 });
	water.PushBack({ 296, 447, 283, 12 });
	water.PushBack({ 588, 447, 283, 18 });
	water.speed = 0.02f;*/
}

ModuleCongratulation::~ModuleCongratulation()
{}

// Load assets
bool ModuleCongratulation::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Mspacman_congratu.png");
	App->welcome->Disable();

	// TODO 1: Enable (and properly disable) the player module
	/*App->player->Disable();
	App->ghost_b->Disable();
	App->ghost_o->Disable();
	App->ghost_p->Disable();
	App->ghost_r->Disable();
	App->collision->Disable();*/
	App->level1->Disable();


	return ret;
}

// Load assets
bool ModuleCongratulation::CleanUp()
{
	LOG("Unloading honda stage");
	App->player->CleanUp();
	return true;
}

// Update: draw background
update_status ModuleCongratulation::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, 0, &congratulations);

	if (App->input->keyboard[SDL_SCANCODE_1] == KEY_STATE::KEY_UP || 
		App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_UP)
	{
		App->fade->FadeToBlack(this, (Module*)App->level1, 1.0f);
	}


	return UPDATE_CONTINUE;
}