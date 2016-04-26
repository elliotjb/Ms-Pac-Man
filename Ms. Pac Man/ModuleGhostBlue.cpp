#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleGhostBlue.h"
#include "ModuleCollision.h"

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



	position_b.x = 105;
	position_b.y = 121;

	test = { 11, 11, 1, 1 };

}

ModuleGhostBlue::~ModuleGhostBlue()
{
	collision_blue = nullptr;
}

// Load assets
bool ModuleGhostBlue::Start()
{
	LOG("Loading Ghost textures");
	bool ret = true;
	graphics = App->textures->Load("MsPacMan_Sprites.png"); // Sprites
	
	new_direction_b = 0;
	collision_blue = App->collision->AddCollider({ 50, 50, 10, 10 }, COLLIDER_ENEMY, this);
	return ret;
}

// Update
update_status ModuleGhostBlue::Update()
{

	int tile[31][28] = { //Mover en otra entrega a level1
		/*      0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22  23 24 25 26 27*/
		/*0 */{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		/*1 */{ 0, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 0 },
		/*2 */{ 0, 4, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 4, 0 },
		/*3 */{ 0, 3, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0 },
		/*4 */{ 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0 },
		/*5 */{ 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0 },
		/*6 */{ 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0 },
		/*7 */{ 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0 },
		/*8 */{ 8, 5, 5, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 5, 5, 9 },
		/*9 */{ 0, 0, 0, 3, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 3, 0, 0, 0 },
		/*19*/{ 0, 0, 0, 3, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 3, 0, 0, 0 },
		/*11*/{ 0, 0, 0, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 0, 0, 0 },
		/*12*/{ 0, 0, 0, 3, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 3, 0, 0, 0 },
		/*13*/{ 0, 0, 0, 3, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 3, 0, 0, 0 },
		/*14*/{ 0, 0, 0, 3, 0, 0, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0, 3, 0, 0, 0 },
		/*15*/{ 0, 0, 0, 3, 0, 0, 5, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 5, 0, 0, 3, 0, 0, 0 },
		/*16*/{ 0, 0, 0, 3, 0, 0, 5, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 5, 0, 0, 3, 0, 0, 0 },
		/*17*/{ 8, 5, 5, 3, 5, 5, 5, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 5, 5, 5, 3, 5, 5, 9 },
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
	//new_direction = rand() % 4;
	srand(time(NULL));
	int speed = 1;
	//BLUE
	if (time_blue < 111)
	{
		time_blue++;
	}
	if (Isinmid == false)
	{
		time_blue = 0;
	}

	if (Isinmid == true && time_blue > 100)
	{
		position_b.y -= 1;
		if (position_b.y == 99)
		{
			new_direction_b = 1;
			Isinmid = false;
		}
	}

	//check possibilities
	if (tile[right_y_b][right_x_b + 1] != 0)
	{
		if ((position_b.x + 7) == (center_x_b * 8) + 4 && (position_b.y - 7) == (center_y_b * 8) + 4)
		{
			can_right_b = true;
		}
	}
	else{ can_right_b = false; }

	//lefy
	if (tile[left_y_b][left_x_b - 1] != 0)
	{
		if ((position_b.x + 7) == (center_x_b * 8) + 4 && (position_b.y - 7) == (center_y_b * 8) + 4)
		{
			can_left_b = true;
		}
	}
	else{ can_left_b = false; }

	//up
	if (tile[up_y_b - 1][up_x_b] != 0)
	{
		if ((position_b.x + 7) == (center_x_b * 8) + 4 && (position_b.y - 7) == (center_y_b * 8) + 4)
		{
			can_up_b = true;
		}
	}
	else{ can_up_b = false; }

	// down
	if (tile[down_y_b + 1][down_x_b] != 0)
	{
		if ((position_b.x + 7) == (center_x_b * 8) + 4 && (position_b.y - 7) == (center_y_b * 8) + 4)
		{
			can_down_b = true;
		}
	}
	else{ can_down_b = false; }

	//left
	if (can_left_b == true || can_right_b == true)
	{
		if (can_up_b == false && can_down_b == false)
		{
			change_direction_b = false;
		}
		else
		{
			change_direction_b = true;
		}
	}
	if (can_up_b == true || can_down_b == true)
	{
		if (can_left_b == false && can_right_b == false)
		{
			change_direction_b = false;
		}
		else
		{
			change_direction_b = true;
		}
	}
	else{ change_direction_b = false; }

	//
	if (change_direction_b)
	{
		change_com_b = false;
		while (change_com_b == false)
		{
			change_b = rand() % 4;
			if (can_right_b && change_b == 2)
			{
				position_b.y = (center_y_b * 8) + 4 + 7;
				ghost_right_b = true;
				change_com_b = true;
			}
			else{ ghost_right_b = false; }


			if (can_left_b && change_b == 3)
			{
				position_b.y = (center_y_b * 8) + 4 + 7;
				ghost_left_b = true;
				change_com_b = true;
			}
			else{ ghost_left_b = false; }


			if (can_up_b && change_b == 0)
			{
				position_b.x = (center_x_b * 8) + 4 - 7;
				ghost_up_b = true;
				change_com_b = true;
			}
			else{ ghost_up_b = false; }


			if (can_down_b && change_b == 1)
			{
				position_b.x = (center_x_b * 8) + 4 - 7;
				ghost_down_b = true;
				change_com_b = true;
			}
			else{ ghost_down_b = false; }
		}
	}
	

	right_x_b = (position_b.x + 3) / PIX_TILE;
	right_y_b = (position_b.y - 7) / PIX_TILE;
	left_x_b = (position_b.x + 10) / PIX_TILE;
	left_y_b = (position_b.y - 7) / PIX_TILE;
	up_x_b = (position_b.x + 7) / PIX_TILE;
	up_y_b = (position_b.y - 4) / PIX_TILE;
	down_x_b = (position_b.x + 7) / PIX_TILE;
	down_y_b = (position_b.y - 11) / PIX_TILE;
	center_x_b = (position_b.x + 6) / PIX_TILE;
	center_y_b = (position_b.y - 7) / PIX_TILE;


	//decided direction
	if (tile[up_y_b - 1][up_x_b] == 3 || tile[up_y_b - 1][up_x_b] == 4 || tile[up_y_b - 1][up_x_b] == 5)
	{
		if (ghost_up_b)
		{
			if ((position_b.x + 7) == (center_x_b * PIX_TILE) + 4 || (position_b.x + 7) == (center_x_b * PIX_TILE) + 3 || (position_b.x + 7) == (center_x_b * PIX_TILE) + 5 ||
				(position_b.x + 7) == (center_x_b * PIX_TILE) + 2 || (position_b.x + 7) == (center_x_b * PIX_TILE) + 6 && (position_b.y - 7) == (center_y_b * PIX_TILE) + 4 ||
				new_direction_b == 2)
			{
				position_b.x = (center_x_b * PIX_TILE) + 4 - 7;
				new_direction_b = 0;
			}
		}
		if (new_direction_b == 0)
		{
			up_b.speed = 0.3f;
			current_animation_b = &up_b;
			position_b.y -= speed;
		}
		else
		{
			up_b.speed = 0.0f;
		}

	}

	if (tile[left_y_b][left_x_b - 1] == 3 || tile[left_y_b][left_x_b - 1] == 4 || tile[left_y_b][left_x_b - 1] == 5 || tile[left_y_b][left_x_b - 1] == 8 || position_b.x == 0)
	{
		if (ghost_left_b)
		{

			if ((position_b.x + 7) == (center_x_b * PIX_TILE) + 4 && (position_b.y - 7) == (center_y_b * PIX_TILE) + 4 || (position_b.y - 7) == (center_y_b * PIX_TILE) + 3 ||
				(position_b.y - 7) == (center_y_b * PIX_TILE) + 5 || (position_b.y - 7) == (center_y_b * PIX_TILE) + 2 || (position_b.y - 7) == (center_y_b * PIX_TILE) + 6 ||
				new_direction_b == 3)
			{
				position_b.y = (center_y_b * PIX_TILE) + 4 + 7;
				new_direction_b = 1;
			}
		}
		if (new_direction_b == 1)
		{
			left_b.speed = 0.3f;
			current_animation_b = &left_b;
			position_b.x -= speed;
		}
		else
		{
			left_b.speed = 0.0f;
		}

		if (position_b.x == 0)//tile[left_y][left_x-1] == 8)
		{
			for (int i = 0; i >= 25; i++){
				position_b.x--;
			}
			position_b.x += 204;
		}
	}

	if (tile[down_y_b + 1][down_x_b] == 3 || tile[down_y_b + 1][down_x_b] == 4 || tile[down_y_b + 1][down_x_b] == 5)
	{
		if (ghost_down_b)
		{
			if ((position_b.x + 7) == (center_x_b * PIX_TILE) + 4 || (position_b.x + 7) == (center_x_b * PIX_TILE) + 3 || (position_b.x + 7) == (center_x_b * PIX_TILE) + 5 ||
				(position_b.x + 7) == (center_x_b * PIX_TILE) + 2 || (position_b.x + 7) == (center_x_b * PIX_TILE) + 6 && (position_b.y - 7) == (center_y_b * PIX_TILE) + 4 ||
				new_direction_b == 0)
			{
				position_b.x = (center_x_b * PIX_TILE) + 4 - 7;
				new_direction_b = 2;
			}
		}
		if (new_direction_b == 2)
		{
			down_b.speed = 0.3f;
			current_animation_b = &down_b;
			position_b.y += speed;

		}
		else
		{
			down_b.speed = 0.0f;
		}

	}

	if (tile[right_y_b][right_x_b + 1] == 3 || tile[right_y_b][right_x_b + 1] == 5 || tile[right_y_b][right_x_b + 1] == 4 || tile[right_y_b][right_x_b + 1] == 9)
	{
		if (ghost_right_b)
		{
			if ((position_b.x + 7) == (center_x_b * PIX_TILE) + 4 && (position_b.y - 7) == (center_y_b * PIX_TILE) + 4 || (position_b.y - 7) == (center_y_b * PIX_TILE) + 3 ||
				(position_b.y - 7) == (center_y_b * PIX_TILE) + 5 || (position_b.y - 7) == (center_y_b * PIX_TILE) + 2 || (position_b.y - 7) == (center_y_b * PIX_TILE) + 6 ||
				new_direction_b == 1)
			{
				position_b.y = (center_y_b * PIX_TILE) + 4 + 7;
				new_direction_b = 3;
			}
		}
		if (new_direction_b == 3)
		{
			right_b.speed = 0.3f;
			current_animation_b = &right_b;
			position_b.x += speed;
		}
		else
		{
			right_b.speed = 0.0f;
		}

		if (tile[right_y_b][right_x_b + 1] == 9)
		{

			position_b.x -= 204;
		}
	}
	
	collision_blue->SetPos(position_b.x + 2, position_b.y + 12);
	if (App->player->superpower == true && App->player->timer < 5)
	{
		GhostBlue_ispow = true;
	}
	if (App->player->superpower == false)
	{
		GhostBlue_ispow = false;
	}
	// Draw everything --------------------------------------
	
	SDL_Rect r_b = current_animation_b->GetCurrentFrame();
	SDL_Rect r_pow = current_superpow_combination->GetCurrentFrame();

	//EDIT FOR NEXT UPDATE!!! (Elliot)
	if (GhostBlue_ispow == true)
	{
		if (App->player->timer > 280)
		{
			superpow_combination.speed = 0.06f;
			App->render->Blit(graphics, position_b.x, position_b.y + 24 - r_b.h, &r_pow);
		}
		else
		{
			App->render->Blit(graphics, position_b.x, position_b.y + 24 - r_b.h, &superpow_blue);
		}

	}
	else
	{
		App->render->Blit(graphics, position_b.x, position_b.y + 24 - r_b.h, &r_b);
	}


	return UPDATE_CONTINUE;
}


void ModuleGhostBlue::OnCollision(Collider* c1, Collider* c2)
{

}
