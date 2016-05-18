#include "Globals.h"
#include "Application.h"
#include "ModuleLevel_1.h"
#include "ModuleLevel_2.h"
#include "ModuleLevel_3.h"
#include "ModuleLevel_4.h"
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

ModuleLevel4::ModuleLevel4()
{
	//Welcome
	level4 = { 0, 0, 224, 288 };
	level4_2 = { 0, 272, 224, 16 };
	level4_center = { 228, 0, 224, 288 };
	pills = { 8, 8, 8, 8 };

	big_pill.PushBack({ 208, 16, 8, 8 });
	big_pill.PushBack({ 235, 16, 8, 8 });
	big_pill.speed = 0.1f;
}
ModuleLevel4::~ModuleLevel4()
{}

bool ModuleLevel4::Start()
{
	bool ret = true;
	eatenpills = 0;
	victory = false;
	int tile[31][28] = {
		/*      0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22  23 24 25 26 27*/
		/*0 */{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		/*1 */{ 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0 },
		/*2 */{ 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0 },
		/*3 */{ 0, 4, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0 },
		/*4 */{ 0, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 0 },
		/*5 */{ 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0 },
		/*6 */{ 0, 3, 3, 3, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 3, 3, 3, 0 },
		/*7 */{ 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0 },
		/*8 */{ 0, 0, 0, 0, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 0, 0, 0, 0 },
		/*9 */{ 5, 3, 3, 3, 3, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 3, 3, 3, 3, 5 },
		/*10*/{ 0, 3, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 3, 0 },
		/*11*/{ 0, 3, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 3, 0 },
		/*12*/{ 0, 3, 0, 0, 0, 0, 5, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 5, 0, 0, 0, 0, 3, 0 },
		/*13*/{ 0, 3, 0, 0, 0, 0, 5, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 5, 0, 0, 0, 0, 3, 0 },
		/*14*/{ 0, 3, 5, 5, 5, 5, 5, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 5, 5, 5, 5, 5, 3, 0 },
		/*15*/{ 0, 3, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 3, 0 },
		/*16*/{ 0, 3, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 3, 0 },
		/*17*/{ 0, 3, 0, 0, 5, 5, 5, 5, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 5, 5, 0, 0, 3, 0 },
		/*18*/{ 0, 3, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5, 0, 0, 5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 3, 0 },
		/*19*/{ 0, 3, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5, 0, 0, 5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 3, 0 },
		/*20*/{ 0, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 0 },
		/*21*/{ 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0 },
		/*22*/{ 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0 },
		/*23*/{ 0, 4, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 5, 5, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 4, 0 },
		/*24*/{ 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0 },
		/*25*/{ 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0 },
		/*26*/{ 0, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 0 },
		/*27*/{ 0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0 },
		/*28*/{ 0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0 },
		/*29*/{ 0, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 0 },
		/*30*/{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	};

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

	return ret;
}



bool ModuleLevel4::CleanUp()
{
	LOG("Unloading Level4 stage");
	App->ghost_o->CleanUp();
	App->ghost_p->CleanUp();
	App->ghost_b->CleanUp();
	App->ghost_r->CleanUp();
	App->player->CleanUp();
	return true;
}

update_status ModuleLevel4::Update()
{
	// Draw everything --------------------------------------

	App->render->Blit(graphics, 0, 0, &level4);
	App->render->Blit(graphics_2, 0, 24, &level4_center);
	App->render->Blit(graphics, 0, 272, &level4_2);
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
		Mix_PlayChannel(-1, App->sound->eat_ms, 0);
		eatenpills++;
		break;
	case 4:
		map[App->player->center.y][App->player->center.x] = 5;
		App->player->superpower = true;
		Mix_PlayChannel(-1, App->sound->eat_ms, 0);
		eatenpills++;
		break;
	}

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


