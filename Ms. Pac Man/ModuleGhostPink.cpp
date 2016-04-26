#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleGhostPink.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleGhostPink::ModuleGhostPink()
{
	

	//pink
	right_p.PushBack({ 457, 81, 14, 14 });
	right_p.PushBack({ 473, 81, 14, 14 });
	right_p.speed = 0.1f;
	left_p.PushBack({ 489, 81, 14, 14 });
	left_p.PushBack({ 505, 81, 14, 14 });
	left_p.speed = 0.1f;
	up_p.PushBack({ 521, 81, 14, 14 });
	up_p.PushBack({ 537, 81, 14, 14 });
	up_p.speed = 0.1f;
	down_p.PushBack({ 553, 81, 14, 14 });
	down_p.PushBack({ 569, 81, 14, 14 });
	down_p.speed = 0.1f;
	position_p.x = 105;
	position_p.y = 99;



}

ModuleGhostPink::~ModuleGhostPink()
{}

// Load assets
bool ModuleGhostPink::Start()
{
	LOG("Loading Ghost textures");
	bool ret = true;
	graphics = App->textures->Load("MsPacMan_Sprites.png"); // Sprites
	srand(time(NULL));
	new_direction_p = 1;

	return ret;
}

// Update
update_status ModuleGhostPink::Update()
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
	//PINK

	//checking possibilities

	//right
	if (tile[right_y_p][right_x_p + 1] != 0)
	{
		if ((position_p.x + 7) == (center_x_p * 8) + 4 && (position_p.y - 7) == (center_y_p * 8) + 4) can_right_p = true;
	}
	else can_right_p = false;

	//left
	if (tile[left_y_p][left_x_p - 1] != 0)
	{
		if ((position_p.x + 7) == (center_x_p * 8) + 4 && (position_p.y - 7) == (center_y_p * 8) + 4) can_left_p = true;
	}
	else can_left_p = false;

	//up
	if (tile[up_y_p - 1][up_x_p] != 0)
	{
		if ((position_p.x + 7) == (center_x_p * 8) + 4 && (position_p.y - 7) == (center_y_p * 8) + 4) can_up_p = true;
	}
	else can_up_p = false;

	// down
	if (tile[down_y_p + 1][down_x_p] != 0)
	{
		if ((position_p.x + 7) == (center_x_p * 8) + 4 && (position_p.y - 7) == (center_y_p * 8) + 4) can_down_p = true;
	}
	else can_down_p = false;


	//deciding if changing direction makes sense

	if (can_left_p == true || can_right_p == true)
	{
		if (can_up_p == false && can_down_p == false) change_direction_p = false;
		else change_direction_p = true;
	}
	if (can_up_p == true || can_down_p == true)
	{
		if (can_left_p == false && can_right_p == false) change_direction_p = false;
		else change_direction_p = true;
	}
	else change_direction_p = false;


	//changing direction

	if (change_direction_p)
	{
		change_comp_p = false;
		while (change_comp_p == false)
		{
			change_p = rand() % 4;
			if (can_right_p && change_p == 1)
			{
				position_p.y = (center_y_p * 8) + 4 + 7;
				ghost_right_p = true;
				change_comp_p = true;
			}
			else ghost_right_p = false;


			if (can_left_p && change_p == 2)
			{
				position_p.y = (center_y_p * 8) + 4 + 7;
				ghost_left_p = true;
				change_comp_p = true;
			}
			else ghost_left_p = false;


			if (can_up_p && change_p == 3)
			{
				position_p.x = (center_x_p * 8) + 4 - 7;
				ghost_up_p = true;
				change_comp_p = true;
			}
			else ghost_up_p = false;


			if (can_down_p && change_p == 0)
			{
				position_p.x = (center_x_p * 8) + 4 - 7;
				ghost_down_p = true;
				change_comp_p = true;
			}
			else ghost_down_p = false;
		}
	}


	right_x_p = (position_p.x + 3) / PIX_TILE;
	right_y_p = (position_p.y - 7) / PIX_TILE;
	left_x_p = (position_p.x + 10) / PIX_TILE;
	left_y_p = (position_p.y - 7) / PIX_TILE;
	up_x_p = (position_p.x + 7) / PIX_TILE;
	up_y_p = (position_p.y - 4) / PIX_TILE;
	down_x_p = (position_p.x + 7) / PIX_TILE;
	down_y_p = (position_p.y - 11) / PIX_TILE;
	center_x_p = (position_p.x + 6) / PIX_TILE;
	center_y_p = (position_p.y - 7) / PIX_TILE;


	//decided direction
	if (tile[up_y_p - 1][up_x_p] == 3 || tile[up_y_p - 1][up_x_p] == 4 || tile[up_y_p - 1][up_x_p] == 5)
	{
		if (ghost_up_p)
		{
			if ((position_p.x + 7) == (center_x_p * PIX_TILE) + 4 || (position_p.x + 7) == (center_x_p * PIX_TILE) + 3 || (position_p.x + 7) == (center_x_p * PIX_TILE) + 5 ||
				(position_p.x + 7) == (center_x_p * PIX_TILE) + 2 || (position_p.x + 7) == (center_x_p * PIX_TILE) + 6 && (position_p.y - 7) == (center_y_p * PIX_TILE) + 4 ||
				new_direction_p == 2)
			{
				position_p.x = (center_x_p * PIX_TILE) + 4 - 7;
				new_direction_p = 0;
			}
		}
		if (new_direction_p == 0)
		{
			up_p.speed = 0.3f;
			current_animation = &up_p;
			position_p.y -= speed;
		}
		else
		{
			up_p.speed = 0.0f;
		}

	}

	if (tile[left_y_p][left_x_p - 1] == 3 || tile[left_y_p][left_x_p - 1] == 4 || tile[left_y_p][left_x_p - 1] == 5 || tile[left_y_p][left_x_p - 1] == 8 || position_p.x == 0)
	{
		if (ghost_left_p)
		{

			if ((position_p.x + 7) == (center_x_p * PIX_TILE) + 4 && (position_p.y - 7) == (center_y_p * PIX_TILE) + 4 || (position_p.y - 7) == (center_y_p * PIX_TILE) + 3 ||
				(position_p.y - 7) == (center_y_p * PIX_TILE) + 5 || (position_p.y - 7) == (center_y_p * PIX_TILE) + 2 || (position_p.y - 7) == (center_y_p * PIX_TILE) + 6 ||
				new_direction_p == 3)
			{
				position_p.y = (center_y_p * PIX_TILE) + 4 + 7;
				new_direction_p = 1;
			}
		}
		if (new_direction_p == 1)
		{
			left_p.speed = 0.3f;
			current_animation = &left_p;
			position_p.x -= speed;
		}
		else
		{
			left_p.speed = 0.0f;
		}

		if (position_p.x == 0)//tile[left_y][left_x-1] == 8)
		{
			for (int i = 0; i >= 25; i++){
				position_p.x--;
			}
			position_p.x += 204;
		}
	}

	if (tile[down_y_p + 1][down_x_p] == 3 || tile[down_y_p + 1][down_x_p] == 4 || tile[down_y_p + 1][down_x_p] == 5)
	{
		if (ghost_down_p)
		{
			if ((position_p.x + 7) == (center_x_p * PIX_TILE) + 4 || (position_p.x + 7) == (center_x_p * PIX_TILE) + 3 || (position_p.x + 7) == (center_x_p * PIX_TILE) + 5 ||
				(position_p.x + 7) == (center_x_p * PIX_TILE) + 2 || (position_p.x + 7) == (center_x_p * PIX_TILE) + 6 && (position_p.y - 7) == (center_y_p * PIX_TILE) + 4 ||
				new_direction_p == 0)
			{
				position_p.x = (center_x_p * PIX_TILE) + 4 - 7;
				new_direction_p = 2;
			}
		}
		if (new_direction_p == 2)
		{
			down_p.speed = 0.3f;
			current_animation = &down_p;
			position_p.y += speed;

		}
		else
		{
			down_p.speed = 0.0f;
		}

	}

	if (tile[right_y_p][right_x_p + 1] == 3 || tile[right_y_p][right_x_p + 1] == 5 || tile[right_y_p][right_x_p + 1] == 4 || tile[right_y_p][right_x_p + 1] == 9)
	{
		if (ghost_right_p)
		{
			if ((position_p.x + 7) == (center_x_p * PIX_TILE) + 4 && (position_p.y - 7) == (center_y_p * PIX_TILE) + 4 || (position_p.y - 7) == (center_y_p * PIX_TILE) + 3 ||
				(position_p.y - 7) == (center_y_p * PIX_TILE) + 5 || (position_p.y - 7) == (center_y_p * PIX_TILE) + 2 || (position_p.y - 7) == (center_y_p * PIX_TILE) + 6 ||
				new_direction_p == 1)
			{
				position_p.y = (center_y_p * PIX_TILE) + 4 + 7;
				new_direction_p = 3;
			}
		}
		if (new_direction_p == 3)
		{
			right_p.speed = 0.3f;
			current_animation = &right_p;
			position_p.x += speed;
		}
		else
		{
			right_p.speed = 0.0f;
		}

		if (tile[right_y_p][right_x_p + 1] == 9)
		{

			position_p.x -= 204;
		}
	}



	// Draw everything --------------------------------------

	SDL_Rect r_b = current_animation->GetCurrentFrame();


	//EDIT FOR NEXT UPDATE!!! (Elliot)

	App->render->Blit(graphics, position_p.x, position_p.y + 24 - r_b.h, &r_b);

	return UPDATE_CONTINUE;
}