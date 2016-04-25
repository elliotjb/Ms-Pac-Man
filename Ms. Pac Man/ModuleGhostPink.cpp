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
	position_p.y = 145;




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
	

	direc_p = 2;
	con_p = 20;
	con2_p = 0;


	return ret;
}

// Update
update_status ModuleGhostPink::Update()
{

	

	if (con2_p == con_p)
	{
		con2_p = 0;
		direc_p = rand() % 4;
		con_p = rand() % 240;
	}
	repeat_p = direc_p;

	
	

	float speed = 1;
	//RED
	

	//Pink
	if (time_ghost > 100)
	{
		if (repeat_p == 0)
		{
			if (con2_p <= con_p)
			{
				if (position_p.x <= 204)
				{
					current_animation_p = &right_p;
					position_p.x += speed;
					con2_p++;
				}
				else
				{
					con2_p = con_p;
				}
			}
		}
		if (repeat_p == 1)
		{
			if (con2_p <= con_p)
			{
				if (position_p.x > 5)
				{
					current_animation_p = &left_p;
					position_p.x -= speed;
					con2_p++;
				}
				else
				{
					con2_p = con_p;
				}
			}
		}
		if (repeat_p == 2)
		{
			if (con2_p <= con_p)
			{
				if (position_p.y > 43)
				{
					current_animation_p = &up_p;
					position_p.y -= speed;
					con2_p++;
				}
				else
				{
					con2_p = con_p;
				}
			}
		}
		if (repeat_p == 3)
		{
			if (con2_p <= con_p)
			{
				if (position_p.y < 267)
				{
					current_animation_p = &down_p;
					position_p.y += speed;
					con2_p++;
				}
				else
				{
					con2_p = con_p;
				}
			}
		}
	}

	

	// Draw everything --------------------------------------
	
	SDL_Rect r_p = current_animation_p->GetCurrentFrame();
	

	//EDIT FOR NEXT UPDATE!!! (Elliot)
	
	App->render->Blit(graphics, position_p.x, position_p.y - r_p.h, &r_p);

	
	if (time_ghost < 210)
	{
		time_ghost++;
	}

	return UPDATE_CONTINUE;
}