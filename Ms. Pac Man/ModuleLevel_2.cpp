#include "Globals.h"
#include "Application.h"
#include "ModuleCongratulation.h"
#include "ModuleLevel_2.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleGhostRed.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGhostBlue.h"
#include "ModuleGhostOrange.h"
#include "ModuleGhostPink.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleLevel2::ModuleLevel2()
{
	//Welcome
	level2 = { 0, 0, 224, 288 };
	big_point.PushBack({ 208, 280, 8, 8 });
	big_point.PushBack({ 235, 280, 8, 8 });
	big_point.speed = 0.1f;
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
	graphics_2 = App->textures->Load("MsPacMan_Sprites.png");

	App->ghost_r->Enable();
	App->ghost_b->Enable();
	App->ghost_p->Enable();
	App->ghost_o->Enable();
	App->player->Enable();

	return ret;
}

// Load assets
bool ModuleLevel2::CleanUp()
{
	LOG("Unloading Level2 stage");
	App->player->CleanUp();
	return true;
}

// Update: draw background
update_status ModuleLevel2::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, 0, &level2);
	

	SDL_Rect r = actual_animation->GetCurrentFrame();
	App->render->Blit(graphics_2, 8, 56, &r);
	App->render->Blit(graphics_2, 208, 56, &r);
	App->render->Blit(graphics_2, 8, 232, &r);
	App->render->Blit(graphics_2, 208, 232, &r);

	//App->render->Blit(graphics, 305, 136, &(water.GetCurrentFrame())); // water animation

	// TODO 3: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, (Module*)App->win, 2.0f);
	}

	return UPDATE_CONTINUE;
}