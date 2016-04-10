#include "Globals.h"
#include "Application.h"
#include "ModuleCongratulation.h"
#include "ModuleLevel_2.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleLevel2::ModuleLevel2()
{
	//Welcome
	level2 = { 0, 0, 224, 288 };
	// ground
	//ground = { 8, 376, 848, 64 };


	// flag animation
	/*water.PushBack({ 8, 447, 283, 9 });
	water.PushBack({ 296, 447, 283, 12 });
	water.PushBack({ 588, 447, 283, 18 });
	water.speed = 0.02f;*/
}

ModuleLevel2::~ModuleLevel2()
{}

// Load assets
bool ModuleLevel2::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("MsPacman_Level2.png");

	// TODO 1: Enable (and properly disable) the player module
	App->player->Enable();

	return ret;
}

// Load assets
bool ModuleLevel2::CleanUp()
{
	LOG("Unloading honda stage");
	App->player->CleanUp();
	return true;
}

// Update: draw background
update_status ModuleLevel2::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, 0, &level2);

	//App->render->Blit(graphics, 305, 136, &(water.GetCurrentFrame())); // water animation

	// TODO 3: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, (Module*)App->win, 5.0f);
	}

	return UPDATE_CONTINUE;
}