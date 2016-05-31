#include "Globals.h"
#include "Application.h"
#include "ModuleLevel_3.h"
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
#include "ModuleScore.h"
#include "ModuleLevel_4.h"

ModuleLevel3::ModuleLevel3()
{
	//Welcome
	level3 = { 0, 0, 224, 288 };
	level3_2 = { 0, 272, 224, 16 };
	level3_center = { 228, 248, 224, 288 };
	next = { 0, 0, 224, 288 };
	next2 = { 0, 0, 224, 288 };
	pills = { 8, 8, 8, 8 };

	big_pill.PushBack({ 208, 16, 8, 8 });
	big_pill.PushBack({ 235, 16, 8, 8 });
	big_pill.speed = 0.1f;
}
ModuleLevel3::~ModuleLevel3()
{}

bool ModuleLevel3::Start()
{
	bool ret = true;
	eatenpills = 0;
	victory = false;

	int tile[31][28] = {
		/*      0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22  23 24 25 26 27*/
		/*0 */{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		/*1 */{ 5, 5, 5, 5, 5, 5, 5, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 5, 5, 5, 5, 5, 5, 5 },
		/*2 */{ 0, 0, 0, 0, 0, 0, 5, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 5, 0, 0, 0, 0, 0, 0 },
		/*3 */{ 0, 0, 0, 0, 0, 0, 5, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 5, 0, 0, 0, 0, 0, 0 },
		/*4 */{ 0, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0 },
		/*5 */{ 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0 },
		/*6 */{ 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0 },
		/*7 */{ 0, 3, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 3, 0, 0, 3, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 3, 0 },
		/*8 */{ 0, 3, 0, 0, 3, 0, 0, 0, 0, 5, 0, 0, 3, 3, 3, 3, 0, 0, 5, 0, 0, 0, 0, 3, 0, 0, 3, 0 },
		/*9 */{ 0, 3, 0, 0, 3, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 3, 0, 0, 3, 0 },
		/*10*/{ 0, 3, 3, 3, 3, 3, 3, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 3, 3, 3, 3, 3, 3, 0 },
		/*11*/{ 0, 0, 0, 0, 0, 0, 3, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 3, 0, 0, 0, 0, 0, 0 },
		/*12*/{ 0, 0, 0, 0, 0, 0, 3, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 3, 0, 0, 0, 0, 0, 0 },
		/*13*/{ 0, 3, 3, 3, 3, 3, 3, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 3, 3, 3, 3, 3, 3, 0 },
		/*14*/{ 0, 3, 0, 0, 0, 0, 3, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 3, 0, 0, 0, 0, 3, 0 },
		/*15*/{ 0, 3, 0, 0, 0, 0, 3, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 3, 0, 0, 0, 0, 3, 0 },
		/*16*/{ 0, 3, 3, 3, 0, 0, 3, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 3, 0, 0, 3, 3, 3, 0 },
		/*17*/{ 0, 0, 0, 3, 0, 0, 3, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 3, 0, 0, 3, 0, 0, 0 },
		/*18*/{ 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0 },
		/*19*/{ 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0 },
		/*20*/{ 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0 },
		/*21*/{ 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0 },
		/*22*/{ 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0 },
		/*23*/{ 5, 5, 5, 3, 3, 3, 3, 0, 0, 3, 3, 3, 5, 5, 5, 5, 3, 3, 3, 0, 0, 3, 3, 3, 3, 5, 5, 5 },
		/*24*/{ 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0 },
		/*25*/{ 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0 },
		/*26*/{ 0, 4, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 4, 0 },
		/*27*/{ 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0 },
		/*28*/{ 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0 },
		/*29*/{ 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0 },
		/*30*/{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	};

	for (int i = 0; i < 31; i++)
	{
		for (int j = 0; j < 28; j++)
		{
			map[i][j] = tile[i][j];
		}
	}
	islevel3 = true;

	LOG("Loading background assets");

	graphics = App->textures->Load("Sprites/Mspacman.png");
	graphics_2 = App->textures->Load("Sprites/MsPacMan_Sprites.png");
	graphics_3 = App->textures->Load("Sprites/MsPacMan_next.png");
	graphics_4 = App->textures->Load("Sprites/MsPacMan_next2.png");

	App->ghost_r->Enable();
	App->ghost_b->Enable();
	App->ghost_p->Enable();
	App->ghost_o->Enable();
	App->player->Enable();
	App->player->position.x = 105;
	App->player->position.y = 195;
	App->ghost_b->position.x = 89;
	App->ghost_b->position.y = 121;
	App->ghost_o->position_blue.x = 121;
	App->ghost_o->position_blue.y = 121;
	App->ghost_p->position_blue.x = 105;
	App->ghost_p->position_blue.y = 121;
	App->ghost_r->position.x = 105;
	App->ghost_r->position.y = 99;
	App->ghost_b->Isinmid = true;
	App->ghost_o->Isinmid = true;
	App->ghost_p->Isinmid = true;
	App->collision->Enable();
	//App->score->Enable();

	p = 0;
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
	App->ghost_p->ghost_up_r = false;
	App->ghost_p->ghost_down_r = false;
	App->ghost_p->ghost_left_r = false;
	App->ghost_p->ghost_right_r = false;
	App->ghost_p->can_right_r = false;
	App->ghost_p->can_down_r = false;
	App->ghost_p->can_left_r = false;
	App->ghost_p->can_up_r = false;
	//blue
	App->ghost_b->new_direction_r = 0;
	App->ghost_b->GhostBlue_ispow = false;
	App->ghost_b->dead_blue = false;
	App->ghost_b->ghost_up_r = false;
	App->ghost_b->ghost_down_r = false;
	App->ghost_b->ghost_left_r = false;
	App->ghost_b->ghost_right_r = false;
	App->ghost_b->can_right_r = false;
	App->ghost_b->can_down_r = false;
	App->ghost_b->can_left_r = false;
	App->ghost_b->can_up_r = false;


	sound_big_pill = false;
	return ret;
}

bool ModuleLevel3::CleanUp()
{
	LOG("Unloading Level3 stage");
	App->textures->Unload(graphics);
	App->textures->Unload(graphics_2);
	App->textures->Unload(graphics_3);
	App->textures->Unload(graphics_4);
	islevel3 = false;
	return true;
}

update_status ModuleLevel3::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &level3);
	App->render->Blit(graphics_2, 0, 24, &level3_center);
	App->render->Blit(graphics, 0, 272, &level3_2);

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

	if (App->player->time_to_start < 60)
	{
		App->player->time_to_start++;
	}
	if (App->player->time_to_start < 245 && App->player->time_to_start > 59)
	{
		App->player->time_to_start++;
	}

	switch (map[App->player->center.y][App->player->center.x])
	{
	case 3:
		map[App->player->center.y][App->player->center.x] = 5;
		App->score->puntuation += 10;
		if (sound_big_pill == false)
		{
			Mix_PlayChannel(-1, App->sound->eat_ms, 0);
		}
		eatenpills++;
		break;
	case 4:
		map[App->player->center.y][App->player->center.x] = 5;
		App->player->timer = 0;
		App->player->superpower = true;
		App->ghost_o->super = true;
		App->ghost_r->super = true;
		App->ghost_p->super = true;
		App->ghost_b->super = true;
		App->score->puntuation += 50;
		if (Mix_PlayChannel(-1, App->sound->eat_big_pills, 0))
		{
			sound_big_pill = false;
		}
		eatenpills++;
		break;
	}

	//lose condition
	if (App->player->playerlives == 0){
		if (App->player->t < 160)
		{

			App->ghost_b->Disable();
			App->ghost_r->Disable();
			App->ghost_o->Disable();
			App->ghost_p->Disable();
		}
		else if (App->player->t == 160)
		{
			App->collision->Disable();
			App->player->Disable();
			App->score->puntuation = 0;
			App->fade->FadeToBlack(this, (Module*)App->win, 2.0f);
		}
		App->player->t++;
	}

	//win condition
	if (eatenpills == 244)
	{

		victory = true;
	}

	if (victory)
	{

		App->ghost_b->Disable();
		App->ghost_r->Disable();
		App->ghost_o->Disable();
		App->ghost_p->Disable();
		App->collision->Disable();
		App->player->Disable();
		if (p <= 10 || p >= 21 && p <= 31 || p >= 43 && p <= 53)
		{
			App->render->Blit(graphics_3, 0, 0, &next);

		}
		else if (p <= 11 || p >= 32 && p <= 42 || p >= 54 && p <= 64){
			App->render->Blit(graphics_3, 0, 0, &next2);

		}
		else if (p > 64) {
			App->fade->FadeToBlack(this, (Module*)App->level4, 2.0f);
			App->player->Disable();
		}
		p++;
	}
	return UPDATE_CONTINUE;
}
















