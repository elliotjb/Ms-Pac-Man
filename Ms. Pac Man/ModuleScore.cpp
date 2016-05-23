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
#include "ModuleScore.h"


ModuleScore::ModuleScore()
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

ModuleScore::~ModuleScore()
{
}

// Load assets
bool ModuleScore::Start()
{
	bool ret = true;
	LOG("Loading Numbers textures");
	graphics = App->textures->Load("Sprite_Numbers.png"); // Sprites
	number_pos1 = 0;
	number_pos2 = 0;
	number_pos3 = 0;
	number_pos4 = 0;
	puntuation = 0;
	p_1 = false;
	p_2 = false;
	return ret;
}

// Update: draw background
update_status ModuleScore::Update()
{
	p_1 = false;
	p_2 = false;

	App->render->Blit(graphics, 49, 9, &number0);

	if (puntuation > 90)
	{
		puntuation = 0;
		number_pos2;
	}


	if (puntuation == 0)
	{
		number_pos1 = 0;
		App->render->Blit(graphics, 41, 9, &number0);
	}
	if (puntuation == 10)
	{
		number_pos1 = 1;
		App->render->Blit(graphics, 41, 9, &number1);
	}
	if (puntuation == 20)
	{
		number_pos1 = 2;
		App->render->Blit(graphics, 41, 9, &number2);
	}
	if (puntuation == 30)
	{
		number_pos1 = 3;
		App->render->Blit(graphics, 41, 9, &number3);
	}
	if (puntuation == 40)
	{
		number_pos1 = 4;
		App->render->Blit(graphics, 41, 9, &number4);
	}
	if (puntuation == 50)
	{
		number_pos1 = 5;
		App->render->Blit(graphics, 41, 9, &number5);
	}
	if (puntuation == 60)
	{
		number_pos1 = 6;
		App->render->Blit(graphics, 41, 9, &number6);
	}
	if (puntuation == 70)
	{
		number_pos1 = 7;
		App->render->Blit(graphics, 41, 9, &number7);
	}
	if (puntuation == 80)
	{
		number_pos1 = 8;
		App->render->Blit(graphics, 41, 9, &number8);
	}
	if (puntuation == 90)
	{
		number_pos1 = 9;
		App->render->Blit(graphics, 41, 9, &number9);
	}



	return UPDATE_CONTINUE;
}