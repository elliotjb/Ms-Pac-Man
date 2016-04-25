#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleGhostRed.h"

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
	position_r.x = 105;
	position_r.y = 123;

	

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
	direc_r = 1;
	con_r = 20;
	con2_r = 0;

	return ret;
}

// Update
update_status ModuleGhostRed::Update()
{

	if (con2_r == con_r)
	{
		con2_r = 0;
		direc_r = rand() % 4;
		con_r = rand() % 240;
	}
	repeat_r = direc_r;

	

	float speed = 1;
	//RED
	if (time_ghost > 50)
	{
		if (repeat_r == 0)//right
		{
			if (con2_r <= con_r)
			{
				if (position_r.x <= 204)
				{
					current_animation_r = &right_r;
					position_r.x += speed;
					con2_r++;
				}
				else
				{
					con2_r = con_r;
				}
			}
		}
		if (repeat_r == 1)//left
		{
			if (con2_r <= con_r)
			{
				if (position_r.x > 5)
				{
					current_animation_r = &left_r;
					position_r.x -= speed;
					con2_r++;
				}
				else
				{
					con2_r = con_r;
				}
			}
		}
		if (repeat_r == 2)//up
		{
			if (con2_r <= con_r)
			{
				if (position_r.y > 43)
				{
					current_animation_r = &up_r;
					position_r.y -= speed;
					con2_r++;
				}
				else
				{
					con2_r = con_r;
				}
			}
		}
		if (repeat_r == 3)//down
		{
			if (con2_r <= con_r)
			{
				if (position_r.y < 267)
				{
					current_animation_r = &down_r;
					position_r.y += speed;
					con2_r++;
				}
				else
				{
					con2_r = con_r;
				}
			}
		}
	}

	

	// Draw everything --------------------------------------
	SDL_Rect r_r = current_animation_r->GetCurrentFrame();
	


	//EDIT FOR NEXT UPDATE!!! (Elliot)
	App->render->Blit(graphics, position_r.x, position_r.y - r_r.h, &r_r);

	

	if (time_ghost < 210)
	{
		time_ghost++;
	}

	return UPDATE_CONTINUE;
}