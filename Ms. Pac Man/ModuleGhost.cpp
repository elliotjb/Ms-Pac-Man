#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleGhost.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleGhost::ModuleGhost()
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

	//blue
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

ModuleGhost::~ModuleGhost()
{}

// Load assets
bool ModuleGhost::Start()
{
	LOG("Loading Ghost textures");
	bool ret = true;
	graphics = App->textures->Load("MsPacMan_Sprites.png"); // Sprites
	srand(time(NULL));
	//red
	direc_r = 1;
	con_r = 20;
	con2_r = 0;

	direc_p = 2;
	con_p = 20;
	con2_p = 0;

	direc_b = 2;
	con_b = 20;
	con2_b = 0;

	direc_o = 2;
	con_o = 20;
	con2_o = 0;
	time_ghost = 0;
	return ret;
}

// Update
update_status ModuleGhost::Update()
{

	if (con2_r == con_r)
	{
		con2_r = 0;
		direc_r = rand() % 4;
		con_r = rand() % 240;
	}
	repeat_r = direc_r;

	if (con2_p == con_p)
	{
		con2_p = 0;
		direc_p = rand() % 4;
		con_p = rand() % 240;
	}
	repeat_p = direc_p;

	if (con2_b == con_b)
	{
		con2_b = 0;
		direc_b = rand() % 4;
		con_b = rand() % 240;
	}
	repeat_b = direc_b;

	if (con2_o == con_o)
	{
		con2_o = 0;
		direc_o = rand() % 4;
		con_o = rand() % 240;
	}
	repeat_o = direc_o;

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
	SDL_Rect r_r = current_animation_r->GetCurrentFrame();
	SDL_Rect r_p = current_animation_p->GetCurrentFrame();
	SDL_Rect r_o = current_animation_o->GetCurrentFrame();
	SDL_Rect r_b = current_animation_b->GetCurrentFrame();


//EDIT FOR NEXT UPDATE!!! (Elliot)
	App->render->Blit(graphics, position_r.x, position_r.y - r_r.h, &r_r);

	App->render->Blit(graphics, position_p.x, position_p.y - r_p.h, &r_p);

	App->render->Blit(graphics, position_b.x, position_b.y - r_b.h, &r_b);

	App->render->Blit(graphics, position_o.x, position_o.y - r_o.h, &r_o);

	if (time_ghost < 210)
	{
		time_ghost++;
	}

	return UPDATE_CONTINUE;
}