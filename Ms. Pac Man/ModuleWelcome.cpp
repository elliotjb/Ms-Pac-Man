#include "Globals.h"
#include "Application.h"
#include "ModuleWelcome.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleWelcome::ModuleWelcome()
{
	//Welcome
	welcome = {0, 0, 224, 288};
	// ground
	//ground = { 8, 376, 848, 64 };


	// flag animation
	/*water.PushBack({ 8, 447, 283, 9 });
	water.PushBack({ 296, 447, 283, 12 });
	water.PushBack({ 588, 447, 283, 18 });
	water.speed = 0.02f;*/
}

ModuleWelcome::~ModuleWelcome()
{}

// Load assets
bool ModuleWelcome::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("MsPacman_Welcome.png");

	// TODO 1: Enable (and properly disable) the player module

	return ret;
}

// Load assets
bool ModuleWelcome::CleanUp()
{
	LOG("Unloading honda stage");
	App->player->CleanUp();
	return true;
}

// Update: draw background
update_status ModuleWelcome::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, 0, &welcome);

	//App->render->Blit(graphics, 305, 136, &(water.GetCurrentFrame())); // water animation

	// TODO 3: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, (Module*)App->level1, 5.0f);
	}

	return UPDATE_CONTINUE;
}