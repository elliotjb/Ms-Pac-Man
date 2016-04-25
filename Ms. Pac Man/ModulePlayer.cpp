#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleLevel_1.h"



ModulePlayer::ModulePlayer()
{
	position.x = 105;
	position.y = 195;

	right.PushBack({ 489, 1, 15, 14 });
	right.PushBack({ 473, 1, 15, 14 });
	right.PushBack({ 457, 1, 15, 14 });
	right.PushBack({ 473, 1, 15, 14 });
	right.speed = 0.3f;

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

	test = { 11, 11, 1, 1 };

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	superpower = false;
	timer = 0;
	graphics = App->textures->Load("MsPacMan_Sprites.png"); // Sprites

	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
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

	right_x = (position.x + 3)  / PIX_TILE;
	right_y = (position.y - 7)  / PIX_TILE;
	left_x = (position.x + 10)  / PIX_TILE;
	left_y = (position.y - 7)   / PIX_TILE;
	up_x = (position.x + 7)     / PIX_TILE;
	up_y = (position.y - 4)     / PIX_TILE;
	down_x = (position.x + 7)   / PIX_TILE;
	down_y = (position.y - 11)  / PIX_TILE;
	center_x = (position.x + 6) / PIX_TILE;
	center_y = (position.y - 7) / PIX_TILE;

	int speed = 1;

	if (key)
	{
		if (tile[up_y - 1][up_x] == 3 || tile[up_y - 1][up_x] == 4 || tile[up_y - 1][up_x] == 5)
		{
			if (App->input->keyboard[SDL_SCANCODE_W] == 1)
			{
				if ((position.x + 7) == (center_x * PIX_TILE) + 4 || (position.x + 7) == (center_x * PIX_TILE) + 3 || (position.x + 7) == (center_x * PIX_TILE) + 5 ||
					(position.x + 7) == (center_x * PIX_TILE) + 2 || (position.x + 7) == (center_x * PIX_TILE) + 6 && (position.y - 7) == (center_y * PIX_TILE) + 4 ||
					direction == 2)
				{
					position.x = (center_x * PIX_TILE) + 4 - 7;
					direction = 0;
				}
			}
			if (direction == 0)
			{
				up.speed = 0.3f;
				current_animation = &up;
				position.y -= speed;
			}
			else
			{
				up.speed = 0.0f;
			}
		}

		if (tile[left_y][left_x - 1] == 3 || tile[left_y][left_x - 1] == 4 || tile[left_y][left_x - 1] == 5)
		{
			if (App->input->keyboard[SDL_SCANCODE_A] == 1)
			{

				if ((position.x + 7) == (center_x * PIX_TILE) + 4 && (position.y - 7) == (center_y * PIX_TILE) + 4 || (position.y - 7) == (center_y * PIX_TILE) + 3 ||
					(position.y - 7) == (center_y * PIX_TILE) + 5 || (position.y - 7) == (center_y * PIX_TILE) + 2 || (position.y - 7) == (center_y * PIX_TILE) + 6 ||
					direction == 3)
				{
					position.y = (center_y * PIX_TILE) + 4 + 7;
					direction = 1;
				}
			}
			if (direction == 1)
			{
				left.speed = 0.3f;
				current_animation = &left;
				position.x -= speed;
			}
			else
			{
				left.speed = 0.0f;
			}
		}

		if (tile[down_y + 1][down_x] == 3 || tile[down_y + 1][down_x] == 4 || tile[down_y + 1][down_x] == 5)
		{
			if (App->input->keyboard[SDL_SCANCODE_S] == 1)
			{
				if ((position.x + 7) == (center_x * PIX_TILE) + 4 || (position.x + 7) == (center_x * PIX_TILE) + 3 || (position.x + 7) == (center_x * PIX_TILE) + 5 ||
					(position.x + 7) == (center_x * PIX_TILE) + 2 || (position.x + 7) == (center_x * PIX_TILE) + 6 && (position.y - 7) == (center_y * PIX_TILE) + 4 ||
					direction == 0)
				{
					position.x = (center_x * PIX_TILE) + 4 - 7;
					direction = 2;
				}
			}
			if (direction == 2)
			{
				down.speed = 0.3f;
				current_animation = &down;
				position.y += speed;
			}
			else
			{
				down.speed = 0.0f;
			}
		}

		if (tile[right_y][right_x + 1] == 3 || tile[right_y][right_x + 1] == 5 || tile[right_y][right_x + 1] == 4)
		{
			if (App->input->keyboard[SDL_SCANCODE_D] == 1)
			{
				if ((position.x + 7) == (center_x * PIX_TILE) + 4 && (position.y - 7) == (center_y * PIX_TILE) + 4 || (position.y - 7) == (center_y * PIX_TILE) + 3 ||
					(position.y - 7) == (center_y * PIX_TILE) + 5 || (position.y - 7) == (center_y * PIX_TILE) + 2 || (position.y - 7) == (center_y * PIX_TILE) + 6 ||
					direction == 1)
				{
					position.y = (center_y * PIX_TILE) + 4 + 7;
					direction = 3;
				}
			}
			if (direction == 3)
			{
				right.speed = 0.3f;
				current_animation = &right;
				position.x += speed;
			}
			else
			{
				right.speed = 0.0f;
			}
		}
	}	

	//super power

	if (superpower)
	{
		timer++;
	}
	if (timer > 399)
	{
		superpower = false;
		timer = 0;
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y + 24 -r.h, &r);//EDIT FOR NEXT UPDATE!!! (Elliot)

	return UPDATE_CONTINUE;
}