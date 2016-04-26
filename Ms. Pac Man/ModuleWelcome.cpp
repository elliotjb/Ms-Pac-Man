#include "Globals.h"
#include "Application.h"
#include "ModuleWelcome.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSound.h"
#include "SDL/include/SDL.h"


ModuleWelcome::ModuleWelcome()
{
	//Welcome
	welcome = {0, 0, 224, 288};
	Mspacman = { 473, 17, 15, 15 };
	red = { 521, 65, 14, 14 };
	pink = { 537, 81, 14, 14 };
	blue = { 521, 97, 14, 14 };
	orange = { 521, 113, 14, 14 };

	//name
	r_name = { 464, 294, 69, 32 };
	
	//MS Pac Man
	backward.PushBack({ 489, 17, 15, 15 });
	backward.PushBack({ 473, 17, 15, 15 });
	backward.PushBack({ 457, 17, 15, 15 });
	backward.PushBack({ 473, 17, 15, 15 });
	backward.speed = 0.3f;	
	position_ms.x = 290;
	position_ms.y = 171;


	//RED
	left_r.PushBack({ 489, 65, 14, 14 });
	left_r.PushBack({ 505, 65, 14, 14 });
	left_r.speed = 0.1f;
	up_r.PushBack({ 521, 65, 14, 14 });
	up_r.PushBack({ 537, 65, 14, 14 });
	up_r.speed = 0.1f;
	position_r.x = 290;
	position_r.y = 171;

	//PINK
	left_p.PushBack({ 489, 81, 14, 14 });
	left_p.PushBack({ 505, 81, 14, 14 });
	left_p.speed = 0.1f;
	up_p.PushBack({ 521, 81, 14, 14 });
	up_p.PushBack({ 537, 81, 14, 14 });
	up_p.speed = 0.1f;
	position_p.x = 290;
	position_p.y = 171;

	//BLUE
	left_b.PushBack({ 489, 97, 14, 14 });
	left_b.PushBack({ 505, 97, 14, 14 });
	left_b.speed = 0.1f;
	up_b.PushBack({ 521, 97, 14, 14 });
	up_b.PushBack({ 537, 97, 14, 14 });
	up_b.speed = 0.1f;
	position_b.x = 290;
	position_b.y = 171;

	//ORANGE
	left_o.PushBack({ 489, 113, 14, 14 });
	left_o.PushBack({ 505, 113, 14, 14 });
	left_o.speed = 0.1f;
	up_o.PushBack({ 521, 113, 14, 14 });
	up_o.PushBack({ 537, 113, 14, 14 });
	up_o.speed = 0.1f;
	position_o.x = 290;
	position_o.y = 171;
	/*
	s_balls_first.speed = 0.24f;
	s_balls_first.PushBack({ 0, 0, 134, 62 });
	s_balls_first.PushBack({ 144, 0, 134, 63 });
	s_balls_first.PushBack({ 288, 0, 134, 63 });
	s_balls.PushBack({ 0, 72, 134, 62 });
	s_balls.PushBack({ 144, 72, 134, 62 });
	s_balls.PushBack({ 288, 72, 134, 62 });
	s_balls.PushBack({ 0, 144, 134, 62});
	s_balls.PushBack({ 144, 144, 134, 62 });
	s_balls.PushBack({ 288, 144, 134, 62 });
	s_balls.PushBack({ 0, 216, 134, 62 });
	s_balls.PushBack({ 144, 216, 134, 62 });
	s_balls.PushBack({ 288, 216, 134, 62 });
	s_balls.PushBack({ 0, 288, 134, 62 });
	s_balls.PushBack({ 144, 288, 134, 62 });
	s_balls.PushBack({ 288, 288, 134, 62 });
	s_balls.speed = 0.24f;
	*/

	s_balls_first.speed = 0.2f;
	s_balls_first.PushBack({ 0, 0, 134, 62 }); //1
	s_balls_first.PushBack({ 144, 0, 134, 62 });//2
	s_balls_first.PushBack({ 288, 0, 134, 62 });//3
	s_balls_first.PushBack({ 0, 72, 134, 62 });//4
	s_balls_first.PushBack({ 144, 72, 134, 62 });//5
	s_balls_first.PushBack({ 288, 72, 134, 62 });//6
	s_balls_first.PushBack({ 0, 144, 134, 62 });//7
	s_balls_first.PushBack({ 144, 144, 134, 62 });//8
	s_balls.PushBack({ 288, 144, 134, 62 });//9
	s_balls.PushBack({ 288, 435, 134, 62 });//21
	s_balls.PushBack({ 288, 216, 134, 62 });
	s_balls.PushBack({ 288, 652, 134, 62 });//29
	s_balls.PushBack({ 144, 509, 134, 62 });
	s_balls.PushBack({ 0, 144, 134, 62 });
	s_balls.speed = 0.2f;
}


ModuleWelcome::~ModuleWelcome()
{}

// Load assets
bool ModuleWelcome::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("MsPacman_Welcome.png");
	graphics_2 = App->textures->Load("MsPacMan_Sprites.png"); //Sprites
	graphics_Balls = App->textures->Load("MsPacman_Welcome_S.png");
	music_sound = App->sound->LoadMUS("music.ogg");//This not correctly music!


	if (Mix_PlayMusic(music_sound, -1) == -1) {
		LOG("Mix_PlayMusic: %s\n", Mix_GetError());

	}
	time_welcome = 0;
	return ret;
}

// Load assets
bool ModuleWelcome::CleanUp()
{
	LOG("Unloading honda stage");
	App->player->CleanUp();
	while (!Mix_FadeOutMusic(1000) && Mix_PlayingMusic())
		SDL_Delay(1000);

	return true;
}

// Update: draw background
update_status ModuleWelcome::Update()
{
	// Draw everything --------------------------------------	
	float speed = 1;


	//red
	if (time_welcome > 100)
	{
		if (position_r.x == 41 && position_r.y > 100)
		{
			current_animation_r = &up_r;
			position_r.y -= speed;
		}

		else if (position_r.x > 41)
		{
			current_animation_r = &left_r;
			position_r.x -= speed;
		}
	}


	//Pink.
	if (time_welcome > 350)
	{
		if (position_p.x == 41 && position_p.y > 116)
		{
			current_animation_p = &up_p;
			position_p.y -= speed;
		}

		else if (position_p.x > 41)
		{
			current_animation_p = &left_p;
			position_p.x -= speed;
		}


	}


	//Blue
	if (time_welcome > 580)
	{
		if (position_b.x == 41 && position_b.y > 132)
		{
			current_animation_b = &up_b;
			position_b.y -= speed;
		}

		else if (position_b.x > 41)
		{
			current_animation_b = &left_b;
			position_b.x -= speed;
		}


	}


	//orange
	if (time_welcome > 800)
	{
		if (position_o.x == 41 && position_o.y > 148)
		{
			current_animation_o = &up_o;
			position_o.y -= speed;
		}
		else if (position_o.x > 41)
		{
			current_animation_o = &left_o;
			position_o.x -= speed;
		}


	}

	//Ms Pac Man
	if (time_welcome > 1000)
	{
		if (position_ms.x > 120)
		{
			current_animation_ms = &backward;
			position_ms.x -= speed;
		}
	}


	SDL_Rect r = current_animation_ms->GetCurrentFrame();

	SDL_Rect balls_first = current_animation_balls_first->GetCurrentFrame();
	SDL_Rect balls = current_animation_balls->GetCurrentFrame();

	

	SDL_Rect r_r = current_animation_r->GetCurrentFrame();
	SDL_Rect r_p = current_animation_p->GetCurrentFrame();
	SDL_Rect r_o = current_animation_o->GetCurrentFrame();
	SDL_Rect r_b = current_animation_b->GetCurrentFrame();

	//background
	App->render->Blit(graphics, 0, 0, &welcome);
	
	//MS Pac Man
	if (position_ms.x == 120)
	{
		App->render->Blit(graphics_2, position_ms.x, position_ms.y - r.h, &Mspacman);
	}
	else if (position_ms.x > 120)
	{
		App->render->Blit(graphics_2, position_ms.x, position_ms.y - r.h, &r);
	}


	//Ghosts
	//Red
	if (position_r.y == 100)
	{
		App->render->Blit(graphics_2, position_r.x, position_r.y - r_r.h, &red);
	}
	else if (position_r.y > 100)
	{
		App->render->Blit(graphics_2, position_r.x, position_r.y - r_r.h, &r_r);
	}
	//Pink
	if (position_p.y == 116)
	{
		App->render->Blit(graphics_2, position_p.x, position_p.y - r_p.h, &pink);
	}
	else if (position_p.y > 116)
	{
		App->render->Blit(graphics_2, position_p.x, position_p.y - r_p.h, &r_p);
	}
	//Blue
	if (position_b.y == 132)
	{
		App->render->Blit(graphics_2, position_b.x, position_b.y - r_b.h, &blue);
	}
	else if (position_b.y > 132)
	{
		App->render->Blit(graphics_2, position_b.x, position_b.y - r_b.h, &r_b);
	}
	//ORANGE
	if (position_o.y == 148)
	{
		App->render->Blit(graphics_2, position_o.x, position_o.y - r_o.h, &orange);
	}
	else if (position_o.y > 148)
	{
		App->render->Blit(graphics_2, position_o.x, position_o.y - r_o.h, &r_o);
	}

	if (time_welcome <= 40)
	{
		App->render->Blit(graphics_Balls, 60, 88, &balls_first);
	}
	else if (time_welcome > 40)
	{
		App->render->Blit(graphics_Balls, 60, 88, &balls);
	}

	if (time_welcome < 1100)
	{
		time_welcome++;
	}


	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, (Module*)App->level1, 2.0f);
	}
	//NOM Ghosts
	if (time_welcome >= 90)
	{
		App->render->Blit(graphics_2, 80, 103, &r_name);
	else if (time_welcome >= 340)
		{
			App->render->Blit(graphics_2, 80, 103, &r_name);
		}
	}
	else if (time_welcome >= 90)
	{
		App->render->Blit(graphics_2, 80, 103, &r_name);
	}
	}
		else if (time_welcome >= 90)
		{
			App->render->Blit(graphics_2, 80, 103, &r_name);
		}
	}


	return UPDATE_CONTINUE;
}
