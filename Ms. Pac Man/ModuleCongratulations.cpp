#include "Globals.h"
#include "Application.h"
#include "ModuleCongratulation.h"
#include "ModuleWelcome.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLevel_4.h"
#include "ModuleLevel_3.h"
#include "ModuleCollision.h"

ModuleCongratulation::ModuleCongratulation()
{
	//Welcome
	congratulations = { 0, 0, 224, 288 };
	credit = { 528 , 133 , 7, 7 };
	p = 0;
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
	graphics = App->textures->Load("Sprites/Mspacman_congratu.png");
	graphics_2 = App->textures->Load("Sprites/MsPacMan_Sprites.png");
	App->welcome->Disable();
	App->level3->Disable();
	App->level4->Disable();
	return ret;
}

// Load assets
bool ModuleCongratulation::CleanUp()
{
	LOG("Unloading honda stage");
	App->textures->Unload(graphics);
	App->textures->Unload(graphics_2);
	return true;
}

// Update: draw background
update_status ModuleCongratulation::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, 0, &congratulations);
	if (p > 70 ){
		App->render->Blit(graphics_2, 81, 280, &credit);
	}
	App->fade->FadeToBlack(this, (Module*)App->level3, 2.0f);
	if (p > 70){
		if (App->input->keyboard[SDL_SCANCODE_1] == KEY_STATE::KEY_UP ||
			App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_UP)
		{
			App->fade->FadeToBlack(this, (Module*)App->level3, 2.0f);
		}
	}
	p++;


	return UPDATE_CONTINUE;
}