#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleLevel_1.h"
#include "ModuleCollision.h"
#include "ModuleGhostBlue.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGhostOrange.h"
#include "ModuleGhostPink.h"
#include "ModuleGhostRed.h"
#include "ModuleRating.h"


ModuleRating::ModuleRating()
{

	number0 = { 3, 4, 7, 10 };
	number1 = { 14, 4, 7, 10 };
	number2 = { 23, 4, 7, 10 };
	number3 = { 33, 4, 7, 10 };
	number4 = { 43, 4, 7, 10 };
	number5 = { 53, 4, 7, 10 };
	number6 = { 63, 4, 7, 10 };
	number7 = { 73, 4, 7, 10 };
	number8 = { 83, 4, 7, 10 };
	number9 = { 93, 4, 7, 10 };

}

ModuleRating::~ModuleRating()
{
}

// Load assets
bool ModuleRating::Start()
{
	bool ret = true;
	LOG("Loading Numbers textures");
	graphics = App->textures->Load("Sprite_Numbers.png"); // Sprites
	return ret;
}

// Update: draw background
update_status ModuleRating::Update()
{
	App->render->Blit(graphics, 49, 9, &number0);
	return UPDATE_CONTINUE;
}