#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleGhostOrange.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleGhostOrange::ModuleGhostOrange()
{
	

	//orange
	right_o.PushBack({ 457, 113, 14, 14 });
	right_o.PushBack({ 473, 113, 14, 14 });
	right_o.speed = 0.1f;
	left_o.PushBack({ 489, 113, 14, 14 });
	left_o.PushBack({ 505, 113, 14, 14 });
	left_o.speed = 0.1f;
	up_o.PushBack({ 521, 113, 14, 14 });
	up_o.PushBack({ 537, 113, 14, 14 });
	up_o.speed = 0.1f;
	down_o.PushBack({ 553, 113, 14, 14 });
	down_o.PushBack({ 569, 113, 14, 14 });
	down_o.speed = 0.1f;

	position_o.x = 129;
	position_o.y = 99;


}

ModuleGhostOrange::~ModuleGhostOrange()
{}

// Load assets
bool ModuleGhostOrange::Start()
{
	LOG("Loading Ghost textures");
	bool ret = true;
	graphics = App->textures->Load("MsPacMan_Sprites.png"); // Sprites
	srand(time(NULL));
	new_direction_o = 1;
	return ret;
}

// Update
update_status ModuleGhostOrange::Update()
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



	//ORANGE

	//check possibilities
	if (tile[right_y_o][right_x_o + 1] != 0)
	{
		if ((position_o.x + 7) == (center_x_o * 8) + 4 && (position_o.y - 7) == (center_y_o * 8) + 4)
		{
			can_right_o = true;
		}
	}
	else{ can_right_o = false; }

	//lefy
	if (tile[left_y_o][left_x_o - 1] != 0)
	{
		if ((position_o.x + 7) == (center_x_o * 8) + 4 && (position_o.y - 7) == (center_y_o * 8) + 4)
		{
			can_left_o = true;
		}
	}
	else{ can_left_o = false; }

	//up
	if (tile[up_y_o - 1][up_x_o] != 0)
	{
		if ((position_o.x + 7) == (center_x_o * 8) + 4 && (position_o.y - 7) == (center_y_o * 8) + 4)
		{
			can_up_o = true;
		}
	}
	else{ can_up_o = false; }

	// down
	if (tile[down_y_o + 1][down_x_o] != 0)
	{
		if ((position_o.x + 7) == (center_x_o * 8) + 4 && (position_o.y - 7) == (center_y_o * 8) + 4)
		{
			can_down_o = true;
		}
	}
	else{ can_down_o = false; }

	//left
	if (can_left_o == true || can_right_o == true)
	{
		if (can_up_o == false && can_down_o == false)
		{
			change_direction_o = false;
		}
		else
		{
			change_direction_o = true;
		}
	}
	if (can_up_o == true || can_down_o == true)
	{
		if (can_left_o == false && can_right_o == false)
		{
			change_direction_o = false;
		}
		else
		{
			change_direction_o = true;
		}
	}
	else{ change_direction_o = false; }

	//
	if (change_direction_o)
	{
		change_comp_o = false;
		while (change_comp_o == false)
		{
			change_o = rand() % 4;
			if (can_right_o && change_o == 1)
			{
				position_o.y = (center_y_o * 8) + 4 + 7;
				ghost_right_o = true;
				change_comp_o = true;
			}
			else{ ghost_right_o = false; }


			if (can_left_o && change_o == 2)
			{
				position_o.y = (center_y_o * 8) + 4 + 7;
				ghost_left_o = true;
				change_comp_o = true;
			}
			else{ ghost_left_o = false; }


			if (can_up_o && change_o == 3)
			{
				position_o.x = (center_x_o * 8) + 4 - 7;
				ghost_up_o = true;
				change_comp_o = true;
			}
			else{ ghost_up_o = false; }


			if (can_down_o && change_o == 0)
			{
				position_o.x = (center_x_o * 8) + 4 - 7;
				ghost_down_o = true;
				change_comp_o = true;
			}
			else{ ghost_down_o = false; }
		}
	}


	right_x_o = (position_o.x + 3) / PIX_TILE;
	right_y_o = (position_o.y - 7) / PIX_TILE;
	left_x_o = (position_o.x + 10) / PIX_TILE;
	left_y_o = (position_o.y - 7) / PIX_TILE;
	up_x_o = (position_o.x + 7) / PIX_TILE;
	up_y_o = (position_o.y - 4) / PIX_TILE;
	down_x_o = (position_o.x + 7) / PIX_TILE;
	down_y_o = (position_o.y - 11) / PIX_TILE;
	center_x_o = (position_o.x + 6) / PIX_TILE;
	center_y_o= (position_o.y - 7) / PIX_TILE;


	//decided direction
	if (tile[up_y_o - 1][up_x_o] == 3 || tile[up_y_o - 1][up_x_o] == 4 || tile[up_y_o - 1][up_x_o] == 5)
	{
		if (ghost_up_o)
		{
			if ((position_o.x + 7) == (center_x_o * PIX_TILE) + 4 || (position_o.x + 7) == (center_x_o * PIX_TILE) + 3 || (position_o.x + 7) == (center_x_o * PIX_TILE) + 5 ||
				(position_o.x + 7) == (center_x_o * PIX_TILE) + 2 || (position_o.x + 7) == (center_x_o * PIX_TILE) + 6 && (position_o.y - 7) == (center_y_o * PIX_TILE) + 4 ||
				new_direction_o == 2)
			{
				position_o.x = (center_x_o * PIX_TILE) + 4 - 7;
				new_direction_o = 0;
			}
		}
		if (new_direction_o == 0)
		{
			up_o.speed = 0.3f;
			current_animation = &up_o;
			position_o.y -= speed;
		}
		else
		{
			up_o.speed = 0.0f;
		}

	}

	if (tile[left_y_o][left_x_o - 1] == 3 || tile[left_y_o][left_x_o - 1] == 4 || tile[left_y_o][left_x_o - 1] == 5 || tile[left_y_o][left_x_o - 1] == 8 || position_o.x == 0)
	{
		if (ghost_left_o)
		{

			if ((position_o.x + 7) == (center_x_o * PIX_TILE) + 4 && (position_o.y - 7) == (center_y_o * PIX_TILE) + 4 || (position_o.y - 7) == (center_y_o * PIX_TILE) + 3 ||
				(position_o.y - 7) == (center_y_o * PIX_TILE) + 5 || (position_o.y - 7) == (center_y_o * PIX_TILE) + 2 || (position_o.y - 7) == (center_y_o * PIX_TILE) + 6 ||
				new_direction_o == 3)
			{
				position_o.y = (center_y_o * PIX_TILE) + 4 + 7;
				new_direction_o = 1;
			}
		}
		if (new_direction_o == 1)
		{
			left_o.speed = 0.3f;
			current_animation = &left_o;
			position_o.x -= speed;
		}
		else
		{
			left_o.speed = 0.0f;
		}

		if (position_o.x == 0)//tile[left_y][left_x-1] == 8)
		{
			for (int i = 0; i >= 25; i++){
				position_o.x--;
			}
			position_o.x += 204;
		}
	}

	if (tile[down_y_o + 1][down_x_o] == 3 || tile[down_y_o + 1][down_x_o] == 4 || tile[down_y_o + 1][down_x_o] == 5)
	{
		if (ghost_down_o)
		{
			if ((position_o.x + 7) == (center_x_o * PIX_TILE) + 4 || (position_o.x + 7) == (center_x_o * PIX_TILE) + 3 || (position_o.x + 7) == (center_x_o * PIX_TILE) + 5 ||
				(position_o.x + 7) == (center_x_o * PIX_TILE) + 2 || (position_o.x + 7) == (center_x_o * PIX_TILE) + 6 && (position_o.y - 7) == (center_y_o * PIX_TILE) + 4 ||
				new_direction_o == 0)
			{
				position_o.x = (center_x_o * PIX_TILE) + 4 - 7;
				new_direction_o = 2;
			}
		}
		if (new_direction_o == 2)
		{
			down_o.speed = 0.3f;
			current_animation = &down_o;
			position_o.y += speed;

		}
		else
		{
			down_o.speed = 0.0f;
		}

	}

	if (tile[right_y_o][right_x_o + 1] == 3 || tile[right_y_o][right_x_o + 1] == 5 || tile[right_y_o][right_x_o + 1] == 4 || tile[right_y_o][right_x_o + 1] == 9)
	{
		if (ghost_right_o)
		{
			if ((position_o.x + 7) == (center_x_o * PIX_TILE) + 4 && (position_o.y - 7) == (center_y_o * PIX_TILE) + 4 || (position_o.y - 7) == (center_y_o * PIX_TILE) + 3 ||
				(position_o.y - 7) == (center_y_o * PIX_TILE) + 5 || (position_o.y - 7) == (center_y_o * PIX_TILE) + 2 || (position_o.y - 7) == (center_y_o * PIX_TILE) + 6 ||
				new_direction_o == 1)
			{
				position_o.y = (center_y_o * PIX_TILE) + 4 + 7;
				new_direction_o = 3;
			}
		}
		if (new_direction_o == 3)
		{
			right_o.speed = 0.3f;
			current_animation = &right_o;
			position_o.x += speed;
		}
		else
		{
			right_o.speed = 0.0f;
		}

		if (tile[right_y_o][right_x_o + 1] == 9)
		{

			position_o.x -= 204;
		}
	}



	// Draw everything --------------------------------------

	SDL_Rect r_o = current_animation->GetCurrentFrame();


	//EDIT FOR NEXT UPDATE!!! (Elliot)

	App->render->Blit(graphics, position_o.x, position_o.y + 24 - r_o.h, &r_o);

	return UPDATE_CONTINUE;
}