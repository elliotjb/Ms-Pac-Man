#include "Globals.h"
#include "Application.h"
#include "ModuleLevel_1.h"
#include "ModuleLevel_2.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleLevel1::ModuleLevel1()
{
	//Welcome
	level1 = { 0, 0, 224, 288 };
	big_point.PushBack({ 208, 16, 7, 7 });
	big_point.PushBack({ 235, 16, 7, 7 });
}

ModuleLevel1::~ModuleLevel1()
{}

// Load assets
bool ModuleLevel1::Start()
{
	bool ret = true;

	LOG("Loading background assets");

	graphics = App->textures->Load("Mspacman.png");

	App->player->Enable();

	return ret;
}

bool ModuleLevel1::CleanUp()
{
	LOG("Unloading Level1 stage");
	App->player->CleanUp();
	return true;
}

// Update
update_status ModuleLevel1::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, 0, &level1);

	//App->render->Blit(graphics, 305, 136, &(water.GetCurrentFrame())); // water animation

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, (Module*)App->level2, 2.0f);
	}

	return UPDATE_CONTINUE;
}