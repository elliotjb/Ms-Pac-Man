#include "Globals.h"
#include "Application.h"
#include "ModuleLevel_1.h"
#include "ModuleLevel_2.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGhost.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleLevel1::ModuleLevel1()
{
	//Welcome
	level1 = { 0, 0, 224, 288 };
	level1_2 = { 0, 272, 224, 16 };
	level1_center = { 228, 0, 224, 288 };

	big_point.PushBack({ 208, 16, 8, 8 });
	big_point.PushBack({ 235, 16, 8, 8 });
	big_point.speed = 0.1f;
}

ModuleLevel1::~ModuleLevel1()
{}

// Load assets
bool ModuleLevel1::Start()
{
	bool ret = true;

	LOG("Loading background assets");

	graphics = App->textures->Load("Mspacman.png");//trampetes!! No hi han les vides ni el marcador nomes es una imatge s'ha de arreglar!!!!
	graphics_2 = App->textures->Load("MsPacMan_Sprites.png");
	App->ghost->Enable();
	App->player->Enable();

	return ret;
}

bool ModuleLevel1::CleanUp()
{
	LOG("Unloading Level1 stage");
	App->ghost->CleanUp();
	App->player->CleanUp();
	return true;
}

// Update
update_status ModuleLevel1::Update()
{
	// Draw everything --------------------------------------

	App->render->Blit(graphics, 0, 0, &level1);
	App->render->Blit(graphics_2, 0, 24, &level1_center);
	App->render->Blit(graphics, 0, 272, &level1_2);
	SDL_Rect r = actual_animation->GetCurrentFrame();
	App->render->Blit(graphics_2, 208, 40, &r);
	App->render->Blit(graphics_2, 8, 40, &r);
	App->render->Blit(graphics_2, 8, 240, &r);
	App->render->Blit(graphics_2, 208, 240, &r);

	//App->render->Blit(graphics, 305, 136, &(water.GetCurrentFrame())); // water animation

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, (Module*)App->level2, 2.0f);
	}

	return UPDATE_CONTINUE;
}