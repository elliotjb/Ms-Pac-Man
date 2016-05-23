#include "Globals.h"
#include "Application.h"
#include "ModuleLevel_1.h"
#include "ModuleLevel_2.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGhostRed.h"
#include "ModuleGhostOrange.h"
#include "ModuleGhostBlue.h"
#include "ModuleGhostPink.h"
#include "ModuleSound.h"
#include "ModuleCollision.h"

ModuleLevel1::ModuleLevel1()
{
	//Welcome
	level1 = { 0, 0, 224, 288 };
	level1_2 = { 0, 272, 224, 16 };
	level1_center = { 228, 0, 224, 288 };
	pills = { 8, 8, 8, 8 };

	big_pill.PushBack({ 208, 16, 8, 8 });
	big_pill.PushBack({ 235, 16, 8, 8 });
	big_pill.speed = 0.1f;
}

ModuleLevel1::~ModuleLevel1()
{}

// Load assets
bool ModuleLevel1::Start()
{
	bool ret = true;
	eatenpills = 0;
	victory = false;

	int tile[31][28] = {
		/*      0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22  23 24 25 26 27*/
		/*0 */{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		/*1 */{ 0, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 0 },
		/*2 */{ 0, 4, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 4, 0 },
		/*3 */{ 0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0 },
		/*4 */{ 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0 },
		/*5 */{ 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0 },
		/*6 */{ 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0 },
		/*7 */{ 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0 },
		/*8 */{ 5, 5, 5, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 5, 5, 5 },
		/*9 */{ 0, 0, 0, 3, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 3, 0, 0, 0 },
		/*19*/{ 0, 0, 0, 3, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 3, 0, 0, 0 },
		/*11*/{ 0, 0, 0, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 0, 0, 0 },
		/*12*/{ 0, 0, 0, 3, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 3, 0, 0, 0 },
		/*13*/{ 0, 0, 0, 3, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 3, 0, 0, 0 },
		/*14*/{ 0, 0, 0, 3, 0, 0, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0, 3, 0, 0, 0 },
		/*15*/{ 0, 0, 0, 3, 0, 0, 5, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 5, 0, 0, 3, 0, 0, 0 },
		/*16*/{ 0, 0, 0, 3, 0, 0, 5, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 5, 0, 0, 3, 0, 0, 0 },
		/*17*/{ 5, 5, 5, 3, 5, 5, 5, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 5, 5, 5, 3, 5, 5, 5 },
		/*18*/{ 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0 },
		/*19*/{ 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0 },
		/*20*/{ 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 0, 0, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0 },
		/*21*/{ 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0 },
		/*22*/{ 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0 },
		/*23*/{ 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0 },
		/*24*/{ 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0 },
		/*25*/{ 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0 },
		/*26*/{ 0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0 },
		/*27*/{ 0, 4, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 4, 0 },
		/*28*/{ 0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0 },
		/*29*/{ 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0 },
		/*30*/{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	};

	//public map

	for (int i = 0; i < 31; i++)
	{
		for (int j = 0; j < 28; j++)
		{
			map[i][j] = tile[i][j];
		}
	}


	LOG("Loading background assets");

	graphics = App->textures->Load("Mspacman.png");
	graphics_2 = App->textures->Load("MsPacMan_Sprites.png");

	App->ghost_r->Enable();
	App->ghost_b->Enable();
	App->ghost_p->Enable();
	App->ghost_o->Enable();
	App->player->Enable();
	App->player->position.x = 1050;
	App->player->position.y = 1950;
	App->ghost_b->position_blue.x = 89;
	App->ghost_b->position_blue.y = 121;
	App->ghost_o->position_blue.x = 121;
	App->ghost_o->position_blue.y = 121;
	App->ghost_p->position_blue.x = 105;
	App->ghost_p->position_blue.y = 121;
	App->ghost_r->position.x = 105;
	App->ghost_r->position.y = 99 ;
	App->ghost_b->Isinmid = true;
	App->ghost_o->Isinmid = true;
	App->ghost_p->Isinmid = true;
	App->collision->Enable();

	//orange

	App->ghost_o->new_direction_b = 0;
	App->ghost_o->GhostBlue_ispow = false;
	App->ghost_o->dead_blue = false;
	App->ghost_o->ghost_up_blue = false;
	App->ghost_o->ghost_down_blue = false;
	App->ghost_o->ghost_left_blue = false;
	App->ghost_o->ghost_right_blue = false;
	App->ghost_o->can_right_b = false;
	App->ghost_o->can_down_b = false;
	App->ghost_o->can_left_b = false;
	App->ghost_o->can_up_b = false;
	App->ghost_o->change_com_b = false;
	//pink
	App->ghost_p->new_direction_b = 0;
	App->ghost_p->GhostBlue_ispow = false;
	App->ghost_p->dead_blue = false;
	App->ghost_p->ghost_up_blue = false;
	App->ghost_p->ghost_down_blue = false;
	App->ghost_p->ghost_left_blue = false;
	App->ghost_p->ghost_right_blue = false;
	App->ghost_p->can_right_b = false;
	App->ghost_p->can_down_b = false;
	App->ghost_p->can_left_b = false;
	App->ghost_p->can_up_b = false;
	App->ghost_p->change_com_b = false;
	//blue
	App->ghost_b->new_direction_b = 0;
	App->ghost_b->GhostBlue_ispow = false;
	App->ghost_b->dead_blue = false;
	App->ghost_b->ghost_up_blue = false;
	App->ghost_b->ghost_down_blue = false;
	App->ghost_b->ghost_left_blue = false;
	App->ghost_b->ghost_right_blue = false;
	App->ghost_b->can_right_b = false;
	App->ghost_b->can_down_b = false;
	App->ghost_b->can_left_b = false;
	App->ghost_b->can_up_b = false;
	App->ghost_b->change_com_b = false;

	sound_big_pill = false;

	return ret;
}

bool ModuleLevel1::CleanUp()
{
	LOG("Unloading Level1 stage");
	App->ghost_o->CleanUp();
	App->ghost_p->CleanUp();
	App->ghost_b->CleanUp();
	App->ghost_r->CleanUp();
	App->player->CleanUp();
	App->collision->CleanUp();
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


	//printing elements

	for (int i = 0; i < 31; i++)
	{
		for (int j = 0; j < 28; j++)
		{
			switch (map[i][j])
			{
			case 3:
				App->render->Blit(graphics_2, j * PIX_TILE, (i * PIX_TILE) + 24, &pills);
				break;
			case 4:
				App->render->Blit(graphics_2, j * PIX_TILE, (i * PIX_TILE) + 24, &r);
				break;
			}
		}
	}

	switch (map[App->player->center.y][App->player->center.x])
	{
	case 3:
		map[App->player->center.y][App->player->center.x] = 5;
		if (sound_big_pill == false)
		{
			Mix_PlayChannel(-1, App->sound->eat_ms, 0);

		}
		eatenpills++;
		break;
	case 4:
		map[App->player->center.y][App->player->center.x] = 5;
		App->player->superpower = true;
		if (Mix_PlayChannel(-1, App->sound->eat_big_pills, 0))
		{
			sound_big_pill = true;
		}
		else
		{
			sound_big_pill = false;
		}
		eatenpills++;
		break;
	}

	//TODO, S'ha de ficar el so de moviment sense menjar!

	//win condition

	if (eatenpills == 224)
	{
		victory = true;
	}

	//App->render->Blit(graphics, 305, 136, &(water.GetCurrentFrame())); // water animation

	if (victory)
	{
		App->fade->FadeToBlack(this, (Module*)App->win, 2.0f);
		App->player->Disable();
		App->ghost_b->Disable();
		App->ghost_r->Disable();
		App->ghost_o->Disable();
		App->ghost_p->Disable();
	}

	return UPDATE_CONTINUE;
}