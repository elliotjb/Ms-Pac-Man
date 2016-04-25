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
	position_o.x = 121;
	position_o.y = 145;


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
	

	direc_o = 2;
	con_o = 20;
	con2_o = 0;
	time_ghost = 0;
	return ret;
}

// Update
update_status ModuleGhostOrange::Update()
{

	

	if (con2_o == con_o)
	{
		con2_o = 0;
		direc_o = rand() % 4;
		con_o = rand() % 240;
	}
	repeat_o = direc_o;

	float speed = 1;
	//RED
	

	//ORANGE
	if (time_ghost > 200)
	{
		if (repeat_o == 0)
		{
			if (con2_o <= con_o)
			{
				if (position_o.x <= 204)
				{
					current_animation_o = &right_o;
					position_o.x += speed;
					con2_o++;
				}
				else
				{
					con2_o = con_o;
				}
			}
		}
		if (repeat_o == 1)
		{
			if (con2_o <= con_o)
			{
				if (position_o.x > 5)
				{
					current_animation_o = &left_o;
					position_o.x -= speed;
					con2_o++;
				}
				else
				{
					con2_o = con_o;
				}
			}
		}
		if (repeat_o == 2)
		{
			if (con2_o <= con_o)
			{
				if (position_o.y > 43)
				{
					current_animation_o = &up_o;
					position_o.y -= speed;
					con2_o++;
				}
				else
				{
					con2_o = con_o;
				}
			}
		}
		if (repeat_o == 3)
		{
			if (con2_o <= con_o)
			{
				if (position_o.y < 267)
				{
					current_animation_o = &down_o;
					position_o.y += speed;
					con2_o++;
				}
				else
				{
					con2_o = con_o;
				}
			}
		}
	}


	// Draw everything --------------------------------------

	SDL_Rect r_o = current_animation_o->GetCurrentFrame();
	


	//EDIT FOR NEXT UPDATE!!! (Elliot)
	

	App->render->Blit(graphics, position_o.x, position_o.y - r_o.h, &r_o);

	if (time_ghost < 210)
	{
		time_ghost++;
	}

	return UPDATE_CONTINUE;
}