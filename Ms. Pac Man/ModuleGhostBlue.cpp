#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleGhostBlue.h"
#include "ModuleCollision.h"
#include "ModuleLevel_1.h"

ModuleGhostBlue::ModuleGhostBlue()
{

	right_b.PushBack({ 457, 97, 14, 14 });
	right_b.PushBack({ 473, 97, 14, 14 });
	right_b.speed = 0.1f;
	left_b.PushBack({ 489, 97, 14, 14 });
	left_b.PushBack({ 505, 97, 14, 14 });
	left_b.speed = 0.1f;
	up_b.PushBack({ 521, 97, 14, 14 });
	up_b.PushBack({ 537, 97, 14, 14 });
	up_b.speed = 0.1f;
	down_b.PushBack({ 553, 97, 14, 14 });
	down_b.PushBack({ 569, 97, 14, 14 });
	down_b.speed = 0.1f;

	superpow_combination.PushBack({ 585, 65, 14, 14 });
	superpow_combination.PushBack({ 617, 65, 14, 14 });
	superpow_combination.speed = 0.05f;

	superpow_blue = { 585, 65, 14, 14 };



	position_blue.x = 89;
	position_blue.y = 121;

	test = { 11, 11, 1, 1 };
	i = 0;

}

ModuleGhostBlue::~ModuleGhostBlue()
{
}

// Load assets
bool ModuleGhostBlue::Start()
{
	LOG("Loading Ghost textures");
	bool ret = true;
	graphics = App->textures->Load("MsPacMan_Sprites.png"); // Sprites

	new_direction_b = 0;
	collision_blue = App->collision->AddCollider({ 50, 50, 10, 10 }, COLLIDER_ENEMY, this);
	srand(time(NULL));
	return ret;
}

// Update
update_status ModuleGhostBlue::Update()
{
	//new_direction = rand() % 4;

	int speed = 1;
	//BLUE
	if (time_blue < 500 && Isinmid == true)
	{
		time_blue++;

		if (i == 5) {
			
			position_blue.y = 123;
			
		}
		else if (i == 10) {
			position_blue.y = 121;
			
		}
		else if (i == 15) {
			
		position_blue.y = 119;
			i = 0;
		}
		i++;
	}
	if (Isinmid == false)
	{
		time_blue = 0;
	}

	if (Isinmid == true && time_blue > 499)
	{
		if (position_blue.x <= 105 && Isinmid == true){
			position_blue.x++;
		}
		if (position_blue.x >= 104){
			position_blue.y -= 1;
			if (position_blue.y == 99)
			{
				new_direction_b = 1;
				Isinmid = false;
			}
		}
	}


	//check possibilities
	/*if (App->level1->map[right_blue.y][right_blue.x + 1] != 0)
	{
		if ((position_blue.x + 7) == (center_blue.x * 8) + 4 &&
			(position_blue.y - 7) == (center_blue.y * 8) + 4)
		{
			can_right_b = true;
		}
	}
	else
	{ 
		can_right_b = false; 
	}*/

	//lefy
	if (App->level1->map[left_blue.y][left_blue.x - 1] != 0)
	{
		if ((position_blue.x + 7) == (center_blue.x * 8) + 4 && 
			(position_blue.y - 7) == (center_blue.y * 8) + 4)
		{
			can_left_b = true;
		}
	}
	else
	{ 
		can_left_b = false; 
	}

	//up
	if (App->level1->map[up_blue.y - 1][up_blue.x] != 0)
	{
		if ((position_blue.x + 7) == (center_blue.x * 8) + 4 && 
			(position_blue.y - 7) == (center_blue.y * 8) + 4)
		{
			can_up_b = true;
		}
	}
	else
	{ 
		can_up_b = false; 
	}

	// down
	if (App->level1->map[down_blue.y + 1][down_blue.x] != 0)
	{
		if ((position_blue.x + 7) == (center_blue.x * 8) + 4 && 
			(position_blue.y - 7) == (center_blue.y * 8) + 4)
		{
			can_down_b = true;
		}
	}
	else
	{ 
		can_down_b = false; 
	}

	//left
	if (can_left_b == true || can_right_b == true)
	{
		if (can_up_b == false && can_down_b == false)
		{
			change_direction_blue = false;
		}
		else
		{
			change_direction_blue = true;
		}
	}
	if (can_up_b == true || can_down_b == true)
	{
		if (can_left_b == false && can_right_b == false)
		{
			change_direction_blue = false;
		}
		else
		{
			change_direction_blue = true;
		}
	}
	else{ change_direction_blue = false; }

	//
	if (change_direction_blue)
	{
		change_com_b = false;
		while (change_com_b == false)
		{
			change_b = rand() % 4;
			if (can_right_b && change_b == 2)
			{
				position_blue.y = (center_blue.y * 8) + 4 + 7;
				ghost_right_blue = true;
				change_com_b = true;
			}
			else{ ghost_right_blue = false; }


			if (can_left_b && change_b == 3)
			{
				position_blue.y = (center_blue.y * 8) + 4 + 7;
				ghost_left_blue = true;
				change_com_b = true;
			}
			else{ ghost_left_blue = false; }


			if (can_up_b && change_b == 0)
			{
				position_blue.x = (center_blue.x * 8) + 4 - 7;
				ghost_up_blue = true;
				change_com_b = true;
			}
			else{ ghost_up_blue = false; }


			if (can_down_b && change_b == 1)
			{
				position_blue.x = (center_blue.x * 8) + 4 - 7;
				ghost_down_blue = true;
				change_com_b = true;
			}
			else{ ghost_down_blue = false; }
		}
	}


	right_blue.x = (position_blue.x + 3) / PIX_TILE;
	right_blue.y = (position_blue.y - 7) / PIX_TILE;
	left_blue.x = (position_blue.x + 10) / PIX_TILE;
	left_blue.y = (position_blue.y - 7) / PIX_TILE;
	up_blue.x = (position_blue.x + 7) / PIX_TILE;
	up_blue.y = (position_blue.y - 4) / PIX_TILE;
	down_blue.x = (position_blue.x + 7) / PIX_TILE;
	down_blue.y = (position_blue.y - 11) / PIX_TILE;
	center_blue.x = (position_blue.x + 6) / PIX_TILE;
	center_blue.y = (position_blue.y - 7) / PIX_TILE;


	//decided direction
	if (App->level1->map[up_blue.y - 1][up_blue.x] != 0)
	{
		if (ghost_up_blue)
		{
			if ((position_blue.x + 7) == (center_blue.x * PIX_TILE) + 4 || (position_blue.x + 7) == (center_blue.x * PIX_TILE) + 3 ||
				(position_blue.x + 7) == (center_blue.x * PIX_TILE) + 5 || (position_blue.x + 7) == (center_blue.x * PIX_TILE) + 2 ||
				(position_blue.x + 7) == (center_blue.x * PIX_TILE) + 6 && (position_blue.y - 7) == (center_blue.y * PIX_TILE) + 4 ||
				new_direction_b == 2)
			{
				position_blue.x = (center_blue.x * PIX_TILE) + 4 - 7;
				new_direction_b = 0;
			}
		}
		if (new_direction_b == 0)
		{
			up_b.speed = 0.3f;
			animation_blue = &up_b;
			position_blue.y -= speed;
		}
	}
	else
	{
		up_b.speed = 0.0f;
	}



	if (App->level1->map[left_blue.y][left_blue.x - 1] != 0 || position_blue.x <= 0 || position_blue.x >= 220 && position_blue.x <= 239)
	{
		if (ghost_left_blue)
		{
			if ((position_blue.x + 7) == (center_blue.x * PIX_TILE) + 4 && (position_blue.y - 7) == (center_blue.y * PIX_TILE) + 4 ||
				(position_blue.y - 7) == (center_blue.y * PIX_TILE) + 3 || (position_blue.y - 7) == (center_blue.y * PIX_TILE) + 5 ||
				(position_blue.y - 7) == (center_blue.y * PIX_TILE) + 2 || (position_blue.y - 7) == (center_blue.y * PIX_TILE) + 6 ||
				new_direction_b == 3)
			{
				position_blue.y = (center_blue.y * PIX_TILE) + 4 + 7;
				new_direction_b = 1;
			}
		}
		if (new_direction_b == 1)
		{
			left_b.speed = 0.3f;
			animation_blue = &left_b;
			position_blue.x -= speed;
		}
		if (position_blue.x == -10 && new_direction_b == 1)
		{
			position_blue.x = 220;
		}
	}
	else
	{
		left_b.speed = 0.0f;
	}

	if (App->level1->map[down_blue.y + 1][down_blue.x] != 0)
	{
		if (ghost_down_blue)
		{
			if ((position_blue.x + 7) == (center_blue.x * PIX_TILE) + 4 || (position_blue.x + 7) == (center_blue.x * PIX_TILE) + 3 ||
				(position_blue.x + 7) == (center_blue.x * PIX_TILE) + 5 || (position_blue.x + 7) == (center_blue.x * PIX_TILE) + 2 ||
				(position_blue.x + 7) == (center_blue.x * PIX_TILE) + 6 && (position_blue.y - 7) == (center_blue.y * PIX_TILE) + 4 ||
				new_direction_b == 0)
			{
				position_blue.x = (center_blue.x * PIX_TILE) + 4 - 7;
				new_direction_b = 2;
			}
		}
		if (new_direction_b == 2)
		{
			down_b.speed = 0.3f;
			animation_blue = &down_b;
			position_blue.y += speed;
		}
	}
	else
	{
		down_b.speed = 0.0f;
	}

	if (App->level1->map[right_blue.y][right_blue.x + 1] != 0 || position_blue.x > 210)
	{
		if ((position_blue.x + 7) == (center_blue.x * 8) + 4 &&
			(position_blue.y - 7) == (center_blue.y * 8) + 4)
		{
			can_right_b = true;
		}
		if (ghost_right_blue)
		{
			if ((position_blue.x + 7) == (center_blue.x * PIX_TILE) + 4 && (position_blue.y - 7) == (center_blue.y * PIX_TILE) + 4 ||
				(position_blue.y - 7) == (center_blue.y * PIX_TILE) + 3 || (position_blue.y - 7) == (center_blue.y * PIX_TILE) + 5 ||
				(position_blue.y - 7) == (center_blue.y * PIX_TILE) + 2 || (position_blue.y - 7) == (center_blue.y * PIX_TILE) + 6 ||
				new_direction_b == 1)
			{
				position_blue.y = (center_blue.y * PIX_TILE) + 4 + 7;
				new_direction_b = 3;
			}
		}
		if (new_direction_b == 3)
		{
			right_b.speed = 0.3f;
			animation_blue = &right_b;
			position_blue.x += speed;
		}

		if (position_blue.x >= 220 && new_direction_b == 3)
		{
			position_blue.x = -10;
		}
	}
	else
	{
		right_b.speed = 0.0f;
	}
	if(App->level1->map[right_blue.y][right_blue.x + 1] == 0)
	{
		can_right_b = false;
	}

	collision_blue->SetPos(position_blue.x + 2, position_blue.y + 12);

	if (App->player->superpower == true && App->player->timer < 5)
	{
		GhostBlue_ispow = true;
	}
	if (App->player->superpower == false)
	{
		GhostBlue_ispow = false;
	}
	// Draw everything --------------------------------------

	SDL_Rect r_b = animation_blue->GetCurrentFrame();
	SDL_Rect r_pow = current_superpow_combination->GetCurrentFrame();

	//EDIT FOR NEXT UPDATE!!! (Elliot)
	if (GhostBlue_ispow == true)
	{
		if (App->player->timer > 280)
		{
			superpow_combination.speed = 0.06f;
			App->render->Blit(graphics, position_blue.x, position_blue.y + 24 - r_b.h, &r_pow);
		}
		else
		{
			App->render->Blit(graphics, position_blue.x, position_blue.y + 24 - r_b.h, &superpow_blue);
		}

	}
	else
	{
		App->render->Blit(graphics, position_blue.x, position_blue.y + 24 - r_b.h, &r_b);
	}


	return UPDATE_CONTINUE;
}


void ModuleGhostBlue::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collision_blue && c2->type == COLLIDER_PLAYER && App->player->superpower == true)
	{

		position_blue.x = 105;
		position_blue.y = 121;
		Isinmid = true;
		new_direction_b = 0;
		animation_blue = &up_b;
		GhostBlue_ispow = false;
		dead_blue = false;


		ghost_up_blue = false;
		ghost_down_blue = false;
		ghost_left_blue = false;
		ghost_right_blue = false;

		can_right_b = false;
		can_down_b = false;
		can_left_b = false;
		can_up_b = false;

		change_com_b = false;

	}
}

