#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleGhostRed.h"
#include "ModuleCollision.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleGhostRed::ModuleGhostRed()
{
	//Red
	right_r.PushBack({ 457, 65, 14, 14 });
	right_r.PushBack({ 473, 65, 14, 14 });
	right_r.speed = 0.1f;
	left_r.PushBack({ 489, 65, 14, 14 });
	left_r.PushBack({ 505, 65, 14, 14 });
	left_r.speed = 0.1f;
	up_r.PushBack({ 521, 65, 14, 14 });
	up_r.PushBack({ 537, 65, 14, 14 });
	up_r.speed = 0.1f;
	down_r.PushBack({ 553, 65, 14, 14 });
	down_r.PushBack({ 569, 65, 14, 14 });
	down_r.speed = 0.1f;
	position.x = 81;
	position.y = 99;

	superpow_combination.PushBack({ 585, 65, 14, 14 });
	superpow_combination.PushBack({ 617, 65, 14, 14 });
	superpow_combination.speed = 0.05f;

	superpow_blue = { 585, 65, 14, 14 };

}

ModuleGhostRed::~ModuleGhostRed()
{}

// Load assets
bool ModuleGhostRed::Start()
{
	LOG("Loading Ghost textures");
	bool ret = true;
	graphics = App->textures->Load("MsPacMan_Sprites.png"); // Sprites
	srand(time(NULL));
	//red
	collision = App->collision->AddCollider({ 0, 0, 10, 10 }, COLLIDER_ENEMY, this);
	new_direction_r = 3;
	return ret;
}

// Update
update_status ModuleGhostRed::Update()
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
		/*10*/{ 0, 0, 0, 3, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 3, 0, 0, 0 },
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
	//RED

	//checking possibilities

	//right
	if (tile[right_y_r][right_x_r + 1] != 0)
	{
		if ((position.x + 7) == (center_x_r * 8) + 4 && (position.y - 7) == (center_y_r * 8) + 4) can_right_r = true;
	}
	else can_right_r = false;

	//left
	if (tile[left_y_r][left_x_r - 1] != 0)
	{
		if ((position.x + 7) == (center_x_r * 8) + 4 && (position.y - 7) == (center_y_r * 8) + 4) can_left_r = true;
	}
	else can_left_r = false;

	//up
	if (tile[up_y_r - 1][up_x_r] != 0)
	{
		if ((position.x + 7) == (center_x_r * 8) + 4 && (position.y - 7) == (center_y_r * 8) + 4) can_up_r = true;
	}
	else can_up_r = false;

	// down
	if (tile[down_y_r + 1][down_x_r] != 0)
	{
		if ((position.x + 7) == (center_x_r * 8) + 4 && (position.y - 7) == (center_y_r * 8) + 4) can_down_r = true;
	}
	else can_down_r = false;


	//deciding if changing direction makes sense

	if (can_left_r == true || can_right_r == true)
	{
		if (can_up_r == false && can_down_r == false) change_direction_r = false;
		else change_direction_r = true;
	}
	if (can_up_r == true || can_down_r == true)
	{
		if (can_left_r == false && can_right_r == false) change_direction_r = false;
		else change_direction_r = true;
	}
	else change_direction_r = false;


	//changing direction

	if (change_direction_r)
	{
		change_comp_r = false;
		while (change_comp_r == false)
		{
			change_r = rand() % 4;
			if (can_right_r && change_r == 0)
			{
				position.y = (center_y_r * 8) + 4 + 7;
				ghost_right_r = true;
				change_comp_r = true;
			}
			else{ ghost_right_r = false; }


			if (can_left_r && change_r == 1)
			{
				position.y = (center_y_r * 8) + 4 + 7;
				ghost_left_r = true;
				change_comp_r = true;
			}
			else{ ghost_left_r = false; }


			if (can_up_r && change_r == 2)
			{
				position.x = (center_x_r * 8) + 4 - 7;
				ghost_up_r = true;
				change_comp_r = true;
			}
			else{ ghost_up_r = false; }


			if (can_down_r && change_r == 3)
			{
				position.x = (center_x_r * 8) + 4 - 7;
				ghost_down_r = true;
				change_comp_r = true;
			}
			else{ ghost_down_r = false; }
		}
	}

	right_x_r = (position.x + 3) / PIX_TILE;
	right_y_r = (position.y - 7) / PIX_TILE;
	left_x_r = (position.x + 10) / PIX_TILE;
	left_y_r = (position.y - 7) / PIX_TILE;
	up_x_r = (position.x + 7) / PIX_TILE;
	up_y_r = (position.y - 4) / PIX_TILE;
	down_x_r = (position.x + 7) / PIX_TILE;
	down_y_r = (position.y - 11) / PIX_TILE;
	center_x_r = (position.x + 6) / PIX_TILE;
	center_y_r = (position.y - 7) / PIX_TILE;


	//decided direction
	if (tile[up_y_r - 1][up_x_r] == 3 || tile[up_y_r - 1][up_x_r] == 4 || tile[up_y_r - 1][up_x_r] == 5)
	{
		if (ghost_up_r)
		{
			if ((position.x + 7) == (center_x_r * PIX_TILE) + 4 || (position.x + 7) == (center_x_r * PIX_TILE) + 3 || (position.x + 7) == (center_x_r * PIX_TILE) + 5 ||
				(position.x + 7) == (center_x_r * PIX_TILE) + 2 || (position.x + 7) == (center_x_r * PIX_TILE) + 6 && (position.y - 7) == (center_y_r * PIX_TILE) + 4 ||
				new_direction_r == 2)
			{
				position.x = (center_x_r * PIX_TILE) + 4 - 7;
				new_direction_r = 0;
			}
		}
		if (new_direction_r == 0)
		{
			up_r.speed = 0.3f;
			current_animation = &up_r;
			position.y -= speed;
		}
		else
		{
			up_r.speed = 0.0f;
		}

	}

	if (tile[left_y_r][left_x_r - 1] == 3 || tile[left_y_r][left_x_r - 1] == 4 || tile[left_y_r][left_x_r - 1] == 5 || tile[left_y_r][left_x_r - 1] == 8 || position.x == 0)
	{
		if (ghost_left_r)
		{

			if ((position.x + 7) == (center_x_r * PIX_TILE) + 4 && (position.y - 7) == (center_y_r * PIX_TILE) + 4 || (position.y - 7) == (center_y_r * PIX_TILE) + 3 ||
				(position.y - 7) == (center_y_r * PIX_TILE) + 5 || (position.y - 7) == (center_y_r * PIX_TILE) + 2 || (position.y - 7) == (center_y_r * PIX_TILE) + 6 ||
				new_direction_r == 3)
			{
				position.y = (center_y_r * PIX_TILE) + 4 + 7;
				new_direction_r = 1;
			}
		}
		if (new_direction_r == 1)
		{
			left_r.speed = 0.3f;
			current_animation = &left_r;
			position.x -= speed;
		}
		else
		{
			left_r.speed = 0.0f;
		}

		if (position.x == 0)//tile[left_y][left_x-1] == 8)
		{
			for (int i = 0; i >= 25; i++){
				position.x--;
			}
			position.x += 204;
		}
	}

	if (tile[down_y_r + 1][down_x_r] == 3 || tile[down_y_r + 1][down_x_r] == 4 || tile[down_y_r + 1][down_x_r] == 5)
	{
		if (ghost_down_r)
		{
			if ((position.x + 7) == (center_x_r * PIX_TILE) + 4 || (position.x + 7) == (center_x_r * PIX_TILE) + 3 || (position.x + 7) == (center_x_r * PIX_TILE) + 5 ||
				(position.x + 7) == (center_x_r * PIX_TILE) + 2 || (position.x + 7) == (center_x_r * PIX_TILE) + 6 && (position.y - 7) == (center_y_r * PIX_TILE) + 4 ||
				new_direction_r == 0)
			{
				position.x = (center_x_r * PIX_TILE) + 4 - 7;
				new_direction_r = 2;
			}
		}
		if (new_direction_r == 2)
		{
			down_r.speed = 0.3f;
			current_animation = &down_r;
			position.y += speed;

		}
		else
		{
			down_r.speed = 0.0f;
		}

	}

	if (tile[right_y_r][right_x_r + 1] == 3 || tile[right_y_r][right_x_r + 1] == 5 || tile[right_y_r][right_x_r + 1] == 4 || tile[right_y_r][right_x_r + 1] == 9)
	{
		if (ghost_right_r)
		{
			if ((position.x + 7) == (center_x_r * PIX_TILE) + 4 && (position.y - 7) == (center_y_r * PIX_TILE) + 4 || (position.y - 7) == (center_y_r * PIX_TILE) + 3 ||
				(position.y - 7) == (center_y_r * PIX_TILE) + 5 || (position.y - 7) == (center_y_r * PIX_TILE) + 2 || (position.y - 7) == (center_y_r * PIX_TILE) + 6 ||
				new_direction_r == 1)
			{
				position.y = (center_y_r * PIX_TILE) + 4 + 7;
				new_direction_r = 3;
			}
		}
		if (new_direction_r == 3)
		{
			right_r.speed = 0.3f;
			current_animation = &right_r;
			position.x += speed;
		}
		else
		{
			right_r.speed = 0.0f;
		}

		if (tile[right_y_r][right_x_r + 1] == 9)
		{

			position.x -= 204;
		}
	}


	collision->SetPos(position.x + 2, position.y + 12);
	// Draw everything --------------------------------------

	SDL_Rect r_r = current_animation->GetCurrentFrame();


	//EDIT FOR NEXT UPDATE!!! (Elliot)
	if (App->player->superpower == true && App->player->timer < 5)
	{
		GhostBlue_ispow = true;
	}
	if (App->player->superpower == false)
	{
		GhostBlue_ispow = false;
	}
	// Draw everything --------------------------------------

	SDL_Rect r_b = current_animation->GetCurrentFrame();
	SDL_Rect r_pow = current_superpow_combination->GetCurrentFrame();

	//EDIT FOR NEXT UPDATE!!! (Elliot)
	if (GhostBlue_ispow == true)
	{
		if (App->player->timer > 280)
		{
			superpow_combination.speed = 0.06f;
			App->render->Blit(graphics, position.x, position.y + 24 - r_b.h, &r_pow);
		}
		else
		{
			App->render->Blit(graphics, position.x, position.y + 24 - r_b.h, &superpow_blue);
		}

	}
	else
	{
		App->render->Blit(graphics, position.x, position.y + 24 - r_r.h, &r_r);
	}

	return UPDATE_CONTINUE;
}

void ModuleGhostRed::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collision && c2->type == COLLIDER_PLAYER && App->player->superpower == true)
	{

		position.x = 81;
		position.y = 99;
		new_direction_r = 1;
		current_animation = &left_r;
		GhostBlue_ispow = false;

		ghost_up_r = false;
		ghost_down_r = false;
		ghost_left_r = false;
		ghost_right_r = false;

		can_right_r = false;
		can_down_r = false;
		can_left_r = false;
		can_up_r = false;

		change_comp_r = false;

	}
}