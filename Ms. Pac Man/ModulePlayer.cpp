#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleLevel_3.h"
#include "ModuleLevel_4.h"
#include "ModuleCollision.h"
#include "ModuleGhostBlue.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGhostOrange.h"
#include "ModuleGhostPink.h"
#include "ModuleGhostRed.h"
#include "ModuleSound.h"


ModulePlayer::ModulePlayer()
{
	position.x = 105;
	position.y = 195;

	lose = { 475, 500, 81, 11 };
	ready = { 463, 371, 75, 55 };
	ready2 = { 569, 371, 75, 55 };

	right.PushBack({ 489, 1, 15, 14 });
	right.PushBack({ 473, 1, 15, 14 });
	right.PushBack({ 457, 1, 15, 14 });
	right.PushBack({ 473, 1, 15, 14 });
	right.speed = 0.3f;

	square = { 474, 471, 13, 15 };

	left.PushBack({ 488, 17, 15, 14 });
	left.PushBack({ 472, 17, 15, 14 });
	left.PushBack({ 456, 17, 15, 14 });
	left.PushBack({ 472, 17, 15, 14 });
	left.speed = 0.3f;

	up.PushBack({ 489, 31, 14, 15 });
	up.PushBack({ 473, 31, 14, 15 });
	up.PushBack({ 457, 31, 14, 15 });
	up.PushBack({ 473, 31, 14, 15 });
	up.speed = 0.3f;

	down.PushBack({ 489, 49, 14, 15 });
	down.PushBack({ 473, 49, 14, 15 });
	down.PushBack({ 457, 49, 14, 15 });
	down.PushBack({ 473, 49, 14, 15 });
	down.speed = 0.3f;

	dead.PushBack({ 473, 49, 14, 15 });
	dead.PushBack({ 472, 17, 15, 14 });
	dead.PushBack({ 473, 31, 14, 15 });
	dead.PushBack({ 473, 1, 15, 14 });
	dead.speed = 0.1f;

	test = { 11, 11, 1, 1 };

	Mode_GOD = { 511, 40, 58, 8 };
	SUPER_Mode_GOD = { 511, 40, 70, 8 };

}

ModulePlayer::~ModulePlayer()
{
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	superpower = false;
	timer = 0;
	graphics = App->textures->Load("Sprites/MsPacMan_Sprites.png"); // Sprites
	isdead = false;
	direction = 1;
	current_animation = &left;
	time_to_start = 0;
	time_to_player = 0;
	t = 0;
	timetorespawn = 0;
	time_change_direction = 0;
	playerlives = 3;
	GOD = false;
	SUPER_GOD = false;
	stop = 50;
	Mix_PlayMusic(App->sound->start_mspacman, 1);

	if (App->level3->islevel3)
	{
		for (int i = 0; i < 31; i++)
		{
			for (int j = 0; j < 28; j++)
			{
				map_player[i][j] = App->level3->map[i][j];
			}
		}
	}

	if (App->level4->islevel4)
	{
		for (int i = 0; i < 31; i++)
		{
			for (int j = 0; j < 28; j++)
			{
				map_player[i][j] = App->level4->map[i][j];
			}
		}
	}


	collision_player = App->collision->AddCollider({ position.x+6, position.y + 6, 9, 8 }, COLLIDER_PLAYER, this);
	return ret;
}
bool ModulePlayer::CleanUp()
{
	App->textures->Unload(graphics);
	center.x = 0;
	center.y = 0;
	key_A = false; key_S = false; key_D = false; key_W = false;
	return true;
}
// Update: draw background
update_status ModulePlayer::Update()
{
	if (isdead == false)
	{
		if (stop >= 50)
		{
			if (time_to_player < 250)
			{
				time_to_player++;
			}
			direction_right.x = (position.x + 3) / PIX_TILE;
			direction_right.y = (position.y - 10) / PIX_TILE;
			direction_left.x = (position.x + 10) / PIX_TILE;
			direction_left.y = (position.y - 7) / PIX_TILE;
			direction_up.x = (position.x + 7) / PIX_TILE;
			direction_up.y = (position.y - 4) / PIX_TILE;
			direction_down.x = (position.x + 7) / PIX_TILE;
			direction_down.y = (position.y - 11) / PIX_TILE;
			center.x = (position.x + 6) / PIX_TILE;
			center.y = (position.y - 7) / PIX_TILE;

			if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT &&  position.x < 210 && position.x > 0)
			{
				key_W = true; key_A = false; key_S = false; key_D = false;
			}
			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT &&  position.x < 220 && position.x > 0)
			{
				key_A = true; key_S = false; key_D = false; key_W = false;
			}
			if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT &&  position.x < 210 && position.x > 0)
			{
				key_S = true; key_D = false; key_W = false; key_A = false;
			}
			if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT &&  position.x < 220 && position.x > 0)
			{
				key_D = true; key_W = false; key_A = false; key_S = false;
			}

			//GOD Mode
			if (App->input->keyboard[SDL_SCANCODE_G] == KEY_STATE::KEY_UP)
			{
				if (SUPER_GOD) SUPER_GOD = false;
				if (GOD) GOD = false;
				else GOD = true;
			}

			//SUPER GOD MDOE
			if (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_UP)
			{
				if (GOD) GOD = false;
				if (SUPER_GOD) SUPER_GOD = false;
				else SUPER_GOD = true;
			}

			speed = 1;

			if (time_to_player > 240)
			{
				if (map_player[direction_up.y - 1][direction_up.x] != 0 && position.x < 210 && position.x > 0)
				{
					if (key_W == true)
					{
						if ((position.x + 7) == (center.x * PIX_TILE) + 4 || (position.x + 7) == (center.x * PIX_TILE) + 3 ||
							(position.x + 7) == (center.x * PIX_TILE) + 5 || (position.x + 7) == (center.x * PIX_TILE) + 2 ||
							(position.x + 7) == (center.x * PIX_TILE) + 6 && (position.y - 7) == (center.y * PIX_TILE) + 4 ||
							direction == 2)
						{
							position.x = (center.x * PIX_TILE) + 4 - 7;
							direction = 0;
						}
					}
					if (direction == 0)
					{
						up.speed = 0.3f;
						current_animation = &up;
						position.y -= speed;
					}
				}
				else
				{
					up.speed = 0.0f;
				}

				if (map_player[direction_left.y][direction_left.x - 1] != 0 || position.x <= 0 || position.x >= 220 && position.x <= 239)
				{
					if (key_A == true)
					{
						if ((position.x + 7) == (center.x * PIX_TILE) + 4 && (position.y - 7) == (center.y * PIX_TILE) + 4 ||
							(position.y - 7) == (center.y * PIX_TILE) + 3 || (position.y - 7) == (center.y * PIX_TILE) + 5 ||
							(position.y - 7) == (center.y * PIX_TILE) + 2 || (position.y - 7) == (center.y * PIX_TILE) + 6 ||
							direction == 3)
						{
							position.y = (center.y * PIX_TILE) + 4 + 7;
							direction = 1;
						}
					}
					if (direction == 1)
					{
						left.speed = 0.3f;
						current_animation = &left;
						position.x -= speed;
					}
					if (position.x == -15 && direction == 1)
					{
						position.x = 239;
					}
				}
				else
				{
					left.speed = 0.0f;
				}

				if (map_player[direction_down.y + 1][direction_down.x] != 0 && position.x < 210 && position.x > 0)
				{
					if (key_S == true)
					{
						if ((position.x + 7) == (center.x * PIX_TILE) + 4 || (position.x + 7) == (center.x * PIX_TILE) + 3 ||
							(position.x + 7) == (center.x * PIX_TILE) + 5 || (position.x + 7) == (center.x * PIX_TILE) + 2 ||
							(position.x + 7) == (center.x * PIX_TILE) + 6 && (position.y - 7) == (center.y * PIX_TILE) + 4 ||
							direction == 0)
						{
							position.x = (center.x * PIX_TILE) + 4 - 7;
							direction = 2;
						}
					}
					if (direction == 2)
					{
						down.speed = 0.3f;
						current_animation = &down;
						position.y += speed;
					}
				}
				else
				{
					down.speed = 0.0f;
				}

				if (map_player[direction_right.y][direction_right.x + 1] != 0 || position.x > 210)
				{
					if (key_D == true)
					{
						if ((position.x + 7) == (center.x * PIX_TILE) + 4 && (position.y - 7) == (center.y * PIX_TILE) + 4 ||
							(position.y - 7) == (center.y * PIX_TILE) + 3 || (position.y - 7) == (center.y * PIX_TILE) + 5 ||
							(position.y - 7) == (center.y * PIX_TILE) + 2 || (position.y - 7) == (center.y * PIX_TILE) + 6 ||
							direction == 1)
						{
							position.y = (center.y * PIX_TILE) + 4 + 7;
							direction = 3;
						}
					}
					if (direction == 3)
					{
						right.speed = 0.3f;
						current_animation = &right;
						position.x += speed;
					}

					if (position.x >= 239 && direction == 3)
					{
						position.x = -15;
					}
				}
				else
				{
					right.speed = 0.0f;
				}

			}
			if (time_to_start < 60)
			{
				App->render->Blit(graphics, 77, 112, &ready);

			}

			if (time_to_start < 240 && time_to_start > 59)
			{
				App->render->Blit(graphics, 77, 112, &ready2);

			}
			//super power
			if (superpower)
			{
				timer++;
			}
			if (superpower == false)
			{
				App->ghost_o->super = false;
				App->ghost_r->super = false;
				App->ghost_b->super = false;
				App->ghost_p->super = false;
			}
			if (timer > 420)
			{
				superpower = false;
				timer = 0;
			}

			//Collision follow the Ms Pac Man
			collision_player->SetPos(position.x + 3, position.y + 13);

			//Draw MODE GOD
			if (GOD == true)
			{
				App->render->Blit(graphics, 150, 13, &Mode_GOD);
			}
			if (SUPER_GOD == true)
			{
				App->render->Blit(graphics, 150, 13, &SUPER_Mode_GOD);
			}
		}

		if (stop < 51)
		{
			stop++;
		}
	}
	//Sound dead Ms Pacman
	if (isdead == true)
	{
		timetorespawn++;
		if (timetorespawn < 150)
		{
			current_animation = &dead;
			SDL_Rect po = current_animation->GetCurrentFrame();
			App->render->Blit(graphics, position.x, position.y + 24 - po.h, &po);

		}
		else
		{
			// Draw everything --------------------------------------
			current_animation = &left;
			SDL_Rect r = current_animation->GetCurrentFrame();
			App->render->Blit(graphics, position.x, position.y + 24 - r.h, &r);

			position.x = 105;
			position.y = 195;
			stop = 0;
			timetorespawn = 0;
			isdead = false;
		}
	}
	else
	{
		// Draw everything --------------------------------------
		SDL_Rect r = current_animation->GetCurrentFrame();

		App->render->Blit(graphics, position.x, position.y + 24 - r.h, &r);
	}


	if (playerlives == 2)
	{
		App->render->Blit(graphics, 49, 273, &square);
	}
	else if (playerlives == 1)
	{
		App->render->Blit(graphics, 33, 273, &square);
		App->render->Blit(graphics, 49, 273, &square);
	}
	else if (playerlives == 0)
	{
		App->render->Blit(graphics, 17, 273, &square);
		App->render->Blit(graphics, 33, 273, &square);
		App->render->Blit(graphics, 49, 273, &square);
	}
	if (playerlives == 0){
		direction = 0;
		if (t < 160){
			App->render->Blit(graphics, 72, 160, &lose);
			current_animation = &dead;
		}

	}
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{

	if (c1 == collision_player && c2->type == COLLIDER_ENEMY && GOD == false && SUPER_GOD == false)
	{
		if (App->ghost_r->super == false && c1 == collision_player && c2 == App->ghost_r->collision)
		{
			current_animation = &left;
			direction = 1;
			Mix_PlayChannel(-1, App->sound->sound_dead, 0);
			isdead = true;
			key_A = false; key_S = false; key_D = false; key_W = false;
			--playerlives;
			collision_player->SetPos(105, 195 + 10);
		}
		if (App->ghost_b->super == false && c1 == collision_player && c2 == App->ghost_b->collision_blue)
		{
			current_animation = &left;
			direction = 1;
			Mix_PlayChannel(-1, App->sound->sound_dead, 0);
			isdead = true;
			key_A = false; key_S = false; key_D = false; key_W = false;
			--playerlives;
			collision_player->SetPos(105, 195 + 10);
		}
		if (App->ghost_p->super == false && c1 == collision_player && c2 == App->ghost_p->collision_blue)
		{
			current_animation = &left;
			direction = 1;
			Mix_PlayChannel(-1, App->sound->sound_dead, 0);
			isdead = true;
			key_A = false; key_S = false; key_D = false; key_W = false;
			--playerlives;
			collision_player->SetPos(105, 195 + 10);
		}
		if (App->ghost_o->super == false && c1 == collision_player && c2 == App->ghost_o->collision_blue)
		{
			current_animation = &left;
			direction = 1;
			Mix_PlayChannel(-1, App->sound->sound_dead, 0);
			isdead = true;
			key_A = false; key_S = false; key_D = false; key_W = false;
			--playerlives;
			collision_player->SetPos(105, 195 + 10);
		}

	}
}


