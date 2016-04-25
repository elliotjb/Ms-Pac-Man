#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleGhostBlue.h"

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
	position_b.x = 89;
	position_b.y = 145;


}

ModuleGhostBlue::~ModuleGhostBlue()
{}

// Load assets
bool ModuleGhostBlue::Start()
{
	LOG("Loading Ghost textures");
	bool ret = true;
	graphics = App->textures->Load("MsPacMan_Sprites.png"); // Sprites
	srand(time(NULL));
	

	direc_b = 2;
	con_b = 20;
	con2_b = 0;

	
	return ret;
}

// Update
update_status ModuleGhostBlue::Update()
{

	

	if (con2_b == con_b)
	{
		con2_b = 0;
		direc_b = rand() % 4;
		con_b = rand() % 240;
	}
	repeat_b = direc_b;

	
	float speed = 1;
	//RED
	
	//BLUE
	if (time_ghost > 150)
	{
		if (repeat_b == 0)
		{
			if (con2_b <= con_b)
			{
				if (position_b.x <= 204)
				{
					current_animation_b = &right_b;
					position_b.x += speed;
					con2_b++;
				}
				else
				{
					con2_b = con_b;
				}
			}
		}
		if (repeat_b == 1)
		{
			if (con2_b <= con_b)
			{
				if (position_b.x > 5)
				{
					current_animation_b = &left_b;
					position_b.x -= speed;
					con2_b++;
				}
				else
				{
					con2_b = con_b;
				}
			}
		}
		if (repeat_b == 2)
		{
			if (con2_b <= con_b)
			{
				if (position_b.y > 43)
				{
					current_animation_b = &up_b;
					position_b.y -= speed;
					con2_b++;
				}
				else
				{
					con2_b = con_b;
				}
			}
		}
		if (repeat_b == 3)
		{
			if (con2_b <= con_b)
			{
				if (position_b.y < 267)
				{
					current_animation_b = &down_b;
					position_b.y += speed;
					con2_b++;
				}
				else
				{
					con2_b = con_b;
				}
			}
		}
	}

	


	// Draw everything --------------------------------------
	
	SDL_Rect r_b = current_animation_b->GetCurrentFrame();


	//EDIT FOR NEXT UPDATE!!! (Elliot)

	App->render->Blit(graphics, position_b.x, position_b.y - r_b.h, &r_b);


	if (time_ghost < 210)
	{
		time_ghost++;
	}

	return UPDATE_CONTINUE;
}