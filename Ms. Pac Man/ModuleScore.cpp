#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleLevel_3.h"
#include "ModuleCollision.h"
#include "ModuleGhostBlue.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGhostOrange.h"
#include "ModuleGhostPink.h"
#include "ModuleGhostRed.h"
#include "ModuleScore.h"
#include "ModuleCongratulation.h"


ModuleScore::ModuleScore()
{
	test0 = { 3, 4, 7, 10 };
	test = { 3, 4, 7, 10 };
	test2 = { 3, 4, 7, 10 };
	test3 = { 3, 4, 7, 10 };

	coins_test = { 3, 4, 7, 10 };
	coins_test1 = { 3, 4, 7, 10 };

	MAX_test0 = { 3, 4, 7, 10 };
	MAX_test = { 3, 4, 7, 10 };
	MAX_test2 = { 3, 4, 7, 10 };
	MAX_test3 = { 3, 4, 7, 10 };
}

ModuleScore::~ModuleScore()
{
}

// Load assets
bool ModuleScore::Start()
{
	bool ret = true;
	LOG("Loading Numbers textures");
	graphics = App->textures->Load("Sprites/Sprite_Numbers.png"); // Sprites
	number_pos1 = 0;
	number_pos2 = 0;
	number_pos3 = 0;
	coin_number_pos1 = 0;
	coin_number_pos2 = 0;
	puntuation = 0;
	NUM_coins = 0;
	MAX_puntuation = 0;
	return ret;
}

bool ModuleScore::CleanUp()
{
	App->textures->Unload(graphics);
	NUM_coins -= 1;
	return true;
}

// Update: draw background
update_status ModuleScore::Update()
{
	if (puntuation >= MAX_puntuation)
	{
		MAX_puntuation = puntuation;
	}
	int j = 0;

	//PUNTUATION
	if (puntuation == 0)
	{
		test0 = { 3, 4, 7, 10 };
		test = { 3, 4, 7, 10 };
		test2 = { 3, 4, 7, 10 };
		test3 = { 3, 4, 7, 10 };
		App->render->Blit(graphics, 49, 9, &test0);
	}

	if (puntuation <= 90)
	{
		for (int i = 0; i <= puntuation; i += 10)
		{
			if (i == puntuation)
			{
				j = i + 3;
				test = { j, 4, 7, 10 };
				if (puntuation >= MAX_puntuation)
				{
					MAX_test = { j, 4, 7, 10 };
				}
			}
		}
		App->render->Blit(graphics, 41, 9, &test);
		App->render->Blit(graphics, 49, 9, &test0);
	}

	if (puntuation > 90 && puntuation <= 990)
	{
		j = 0;
		int number_pos2 = (puntuation / 100);
		for (int i = 0; i <= number_pos2; i++)
		{
			if (i == number_pos2)
			{
				j = (i * 10) + 3;
				test2 = { j, 4, 7, 10 };
				if (puntuation >= MAX_puntuation)
				{
					MAX_test2 = { j, 4, 7, 10 };
				}
			}
		}
		number_pos1 = puntuation - (number_pos2 * 100);
		for (int i = 0; i <= number_pos1; i += 10)
		{
			if (i == number_pos1)
			{
				j = i + 3;
				test = { j, 4, 7, 10 };
				if (puntuation >= MAX_puntuation)
				{
					MAX_test = { j, 4, 7, 10 };
				}
			}
		}
		App->render->Blit(graphics, 33, 9, &test2);
		App->render->Blit(graphics, 41, 9, &test);
		App->render->Blit(graphics, 49, 9, &test0);
	}

	if (puntuation > 990 && puntuation <= 9990)
	{
		j = 0;
		number_pos1 = puntuation - ((puntuation / 100) * 100);
		number_pos3 = (puntuation / 1000);
		number_pos2 = puntuation - (number_pos3 * 1000) - number_pos1;
		for (int i = 0; i <= number_pos3; i++)
		{
			if (i == number_pos3)
			{
				j = (i * 10) + 3;
				test3 = { j, 4, 7, 10 };
				if (puntuation >= MAX_puntuation)
				{
					MAX_test3 = { j, 4, 7, 10 };
				}
			}
		}
		for (int i = 0; i <= (number_pos2 /100); i++)
		{
			if (i == (number_pos2 / 100))
			{
				j = (i * 10) + 3;
				test2 = { j, 4, 7, 10 };
				if (puntuation >= MAX_puntuation)
				{
					MAX_test2 = { j, 4, 7, 10 };
				}
			}
		}
		for (int i = 0; i <= number_pos1; i += 10)
		{
			if (i == number_pos1)
			{
				j = i + 3;
				test = { j, 4, 7, 10 };
				if (puntuation >= MAX_puntuation)
				{
					MAX_test = { j, 4, 7, 10 };
				}
			}
		}
		App->render->Blit(graphics, 25, 9, &test3);
		App->render->Blit(graphics, 33, 9, &test2);
		App->render->Blit(graphics, 41, 9, &test);
		App->render->Blit(graphics, 49, 9, &test0);
	}

	App->render->Blit(graphics, 105, 9, &MAX_test3);
	App->render->Blit(graphics, 113, 9, &MAX_test2);
	App->render->Blit(graphics, 121, 9, &MAX_test);
	App->render->Blit(graphics, 129, 9, &MAX_test0);

	if (App->win->issceen == true)
	{
		//COINS
		if (NUM_coins == 0)
		{
			coins_test = { 3, 4, 7, 10 };
		}

		if (NUM_coins <= 9)
		{
			for (int i = 0; i <= NUM_coins; i += 1)
			{
				if (i == NUM_coins)
				{
					j = 3 + 10*i;
					coins_test = { j, 4, 7, 10 };
				}
			}
			App->render->Blit(graphics, 81, 280, &coins_test);
		}

		if (NUM_coins > 9 && NUM_coins <= 99)
		{
			coins_test1 = { 3, 4, 7, 10 };
			j = 0;
			int coin_number_pos2 = (NUM_coins / 10);
			for (int i = 0; i <= coin_number_pos2; i++)
			{
				if (i == coin_number_pos2)
				{
					j = (i * 10) + 3;
					coins_test1 = { j, 4, 7, 10 };
				}
			}
			coin_number_pos1 = NUM_coins - (coin_number_pos2 * 10);
			for (int i = 0; i <= coin_number_pos1; i += 1)
			{
				if (i == coin_number_pos1)
				{
					j = 3 + 10 * i;
					coins_test = { j, 4, 7, 10 };
				}
			}
			App->render->Blit(graphics, 81, 280, &coins_test);
			App->render->Blit(graphics, 73, 280, &coins_test1);
		}
	}




	return UPDATE_CONTINUE;
}