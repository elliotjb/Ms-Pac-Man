#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleGhostBlue.h"
#include "ModuleCollision.h"
#include "ModuleLevel_1.h"
#include <cmath>

ModuleGhostBlue::ModuleGhostBlue()
{

	right_r.PushBack({ 457, 97, 14, 14 });
	right_r.PushBack({ 473, 97, 14, 14 });
	right_r.speed = 0.1f;
	left_r.PushBack({ 489, 97, 14, 14 });
	left_r.PushBack({ 505, 97, 14, 14 });
	left_r.speed = 0.1f;
	up_r.PushBack({ 521, 97, 14, 14 });
	up_r.PushBack({ 537, 97, 14, 14 });
	up_r.speed = 0.1f;
	down_r.PushBack({ 553, 97, 14, 14 });
	down_r.PushBack({ 569, 97, 14, 14 });
	down_r.speed = 0.1f;

	superpow_combination.PushBack({ 585, 65, 14, 14 });
	superpow_combination.PushBack({ 617, 65, 14, 14 });
	superpow_combination.speed = 0.05f;

	superpow_blue = { 585, 65, 14, 14 };
	a = 0;
	t = 1;


	position.x = 89;
	position.y = 121;

	test = { 11, 11, 1, 1 };
	i = 0;

}

ModuleGhostBlue::~ModuleGhostBlue()
{
}

// Load assets
bool ModuleGhostBlue::Start()
{
	LOG("Loading Ghost textures");
	bool ret = true;
	graphics = App->textures->Load("MsPacMan_Sprites.png"); // Sprites
	speed = 0;
	dead = false;
	m = false;
	ghost_up_r = false;
	ghost_down_r = false;
	ghost_left_r = false;
	ghost_right_r = false;

	can_right_r = false;
	can_down_r = false;
	 can_left_r = false;
	 can_up_r = false;
	 dead_blue = false;
	 new_direction_r = 0;
	finish = false;
	new_direction_r = 0;
	collision_blue = App->collision->AddCollider({ 50, 50, 10, 10 }, COLLIDER_ENEMY, this);
	srand(time(NULL));
	return ret;
}
bool ModuleGhostRed::CleanUp(){
	App->textures->Unload(graphics);
	return true;
}
// Update
update_status ModuleGhostBlue::Update()
{
	if (App->player->time_to_start > 240)
	{
		if (App->player->stop >= 50)
		{
			if (time_blue < 130 && Isinmid == true && dead == false)
			{
				time_blue++;
				
				if (i == 0 ) {
					
					position.y = 118;
	

				}
				
				else if (i == 4) {

					position.y = 120;
				

				}
			
				else if (i == 8 ) {
					position.y = 122;


				}
			
				else if (i == 12) {

					position.y = 124;

				

				}
				else if (i == 16) {

					position.y = 126;


				}
				/*
				 if (position_blue.y > 118 && a == 0){
				 position_blue.y--;
				 }
				 else if (position_blue.y == 117){
				 a = 1;
				 position_blue.y++;
				 }
				 else if (position_blue.y == 124){
				 a = 0;
				 position_blue.y++;
				 }
				 else if (position_blue.y<125 && a == 1){
				 position_blue.y++;
				 }*/
				
				if (i == 16){
					t = -1;
				}
				else if (i == 0){
					t = 1;
				}
				if (t == -1){
					i--;
					current_animation = &up_r;
				}
				else if (t == 1){
					i++;
					current_animation = &down_r;
				}
			



			}
		
			if (Isinmid == false)
			{
				time_blue = 0;
			}

			if (Isinmid == true && time_blue > 129 && dead == false )
			{
				if (position.x <= 105 && Isinmid == true){
					position.x++;
				}
				if (position.x >= 104){
					position.y -= 1;
					if (position.y == 99)
					{
						new_direction_r = 1;
						Isinmid = false;
						speed = 1;
						finish = true;
					}
				}
			}
			srand(time(NULL));
			//RED
			if (dead == true && Isinmid == true && finish == true && m == false){
				dead = false;
				if (position.x <= 105){
					position.x++;
				}
				else if (position.x >= 104){

					position.y--;
					if (position.y == 99){
						dead = false;
						new_direction_r = 1;
						Isinmid = false;
						speed = 1;
					}

				}
			}
			if (dead == true && Isinmid == true && finish == true && m == true){
				if (position.x <= 105){
					position.x++;
				}
				else if (position.x >= 104){
					
						position.y--;
						if (position.y == 99){
							dead = false;
							new_direction_r = 1;
							Isinmid = false;
							speed = 1;
						}
				
				}
			}
			//checking possibilities

			//right
			if (App->level1->map[right_y_r][right_x_r + 1] != 0)
			{
				if ((position.x + 7) == (center_x_r * 8) + 4 && (position.y - 7) == (center_y_r * 8) + 4) can_right_r = true;
			}
			else can_right_r = false;

			//left
			if (App->level1->map[left_y_r][left_x_r - 1] != 0)
			{
				if ((position.x + 7) == (center_x_r * 8) + 4 && (position.y - 7) == (center_y_r * 8) + 4) can_left_r = true;
			}
			else can_left_r = false;

			//up
			if (App->level1->map[up_y_r - 1][up_x_r] != 0)
			{
				if ((position.x + 7) == (center_x_r * 8) + 4 && (position.y - 7) == (center_y_r * 8) + 4) can_up_r = true;
			}
			else can_up_r = false;

			// down
			if (App->level1->map[down_y_r + 1][down_x_r] != 0)
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


			if (change_direction_r)
			{
				look_wherePacman = true;
				if (look_wherePacman)
				{
					if (can_up_r)
					{
						up.x = ((center_x_r - App->player->center.x)*(center_x_r - App->player->center.x));
						up.y = (((center_y_r - 1) - App->player->center.y)*((center_y_r - 1) - App->player->center.y));
						isup = sqrt(up.x + up.y);
						//No change direction in the opposite direction
						if (new_direction_r == 2)
						{
							isup = 300;
						}
					}
					else
					{
						isup = 300;
					}

					if (can_left_r)
					{
						left.x = (((center_x_r - 1) - App->player->center.x)*((center_x_r - 1) - App->player->center.x));
						left.y = ((center_y_r - App->player->center.y)*(center_y_r - App->player->center.y));
						isleft = sqrt(left.x + left.y);
						//No change direction in the opposite direction
						if (new_direction_r == 3)
						{
							isleft = 300;
						}
					}
					else
					{
						isleft = 300;
					}

					if (can_down_r)
					{
						down.x = ((center_x_r - App->player->center.x)*(center_x_r - App->player->center.x));
						down.y = (((center_y_r + 1) - App->player->center.y)*((center_y_r + 1) - App->player->center.y));
						isdown = sqrt(down.x + down.y);
						//No change direction in the opposite direction
						if (new_direction_r == 0)
						{
							isdown = 300;
						}
					}
					else
					{
						isdown = 300;
					}

					if (can_right_r)
					{
						right.x = (((center_x_r + 1) - App->player->center.x)*((center_x_r + 1) - App->player->center.x));
						right.y = ((center_y_r - App->player->center.y)*(center_y_r - App->player->center.y));
						isright = sqrt(right.x + right.y);
						//No change direction in the opposite direction
						if (new_direction_r == 1)
						{
							isright = 300;
						}
					}
					else
					{
						isright = 300;
					}

					//Check which direction to go, the shortest
					if (isup <= isleft && isup <= isdown && isup <= isright && new_direction_r != 2)
					{
						ghost_up_r = true; ghost_right_r = false; ghost_left_r = false; ghost_down_r = false;
					}
					if (isleft <= isup && isleft <= isdown && isleft <= isright && new_direction_r != 3)
					{
						ghost_left_r = true; ghost_right_r = false; ghost_up_r = false; ghost_down_r = false;
					}
					if (isdown <= isup && isdown <= isleft && isdown <= isright && new_direction_r != 0)
					{
						ghost_down_r = true; ghost_right_r = false; ghost_left_r = false; ghost_up_r = false;
					}
					if (isright <= isup && isright <= isleft && isright <= isdown && new_direction_r != 1)
					{
						ghost_right_r = true; ghost_down_r = false; ghost_left_r = false; ghost_up_r = false;
					}


					//This is for the corners
					if (can_right_r && can_down_r && can_left_r == false && can_up_r == false)
					{
						if (new_direction_r == 1)//Pacman is moving to left
						{
							ghost_down_r = true; ghost_right_r = false; ghost_left_r = false; ghost_up_r = false;
						}
						if (new_direction_r == 0)//Pacman is moving to up
						{
							ghost_right_r = true; ghost_down_r = false; ghost_left_r = false; ghost_up_r = false;
						}
					}

					if (can_left_r && can_up_r && can_right_r == false && can_down_r == false)
					{
						if (new_direction_r == 3)//Pacman is moving to down
						{
							ghost_up_r = true; ghost_right_r = false; ghost_left_r = false; ghost_down_r = false;
						}
						if (new_direction_r == 2)
						{
							ghost_left_r = true; ghost_right_r = false; ghost_up_r = false; ghost_down_r = false;
						}
					}
					if (can_left_r && can_down_r && can_right_r == false && can_down_r == false)
					{
						if (new_direction_r == 3)
						{
							ghost_down_r = true; ghost_right_r = false; ghost_left_r = false; ghost_up_r = false;
						}
						if (new_direction_r == 0)
						{
							ghost_left_r = true; ghost_right_r = false; ghost_up_r = false; ghost_down_r = false;
						}
					}
					if (can_right_r && can_up_r && can_left_r == false && can_down_r == false)
					{
						if (new_direction_r == 1)
						{
							ghost_up_r = true; ghost_right_r = false; ghost_left_r = false; ghost_down_r = false;
						}
						if (new_direction_r == 2)
						{
							ghost_right_r = true; ghost_up_r = false; ghost_left_r = false; ghost_down_r = false;
						}
					}
					look_wherePacman = false;
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
			if (App->level1->map[up_y_r - 1][up_x_r] == 3 || App->level1->map[up_y_r - 1][up_x_r] == 4 || App->level1->map[up_y_r - 1][up_x_r] == 5)
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

			if (App->level1->map[left_y_r][left_x_r - 1] == 3 || App->level1->map[left_y_r][left_x_r - 1] == 4 || App->level1->map[left_y_r][left_x_r - 1] == 5 || App->level1->map[left_y_r][left_x_r - 1] == 8 || position.x == 0)
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

			if (App->level1->map[down_y_r + 1][down_x_r] == 3 || App->level1->map[down_y_r + 1][down_x_r] == 4 || App->level1->map[down_y_r + 1][down_x_r] == 5)
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

			if (App->level1->map[right_y_r][right_x_r + 1] == 3 || App->level1->map[right_y_r][right_x_r + 1] == 5 || App->level1->map[right_y_r][right_x_r + 1] == 4 || App->level1->map[right_y_r][right_x_r + 1] == 9)
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

				if (App->level1->map[right_y_r][right_x_r + 1] == 9)
				{

					position.x -= 204;
				}
			}
		}
	}

	collision_blue->SetPos(position.x + 2, position.y + 12);

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
		App->render->Blit(graphics, position.x, position.y + 24 - r_b.h, &r_b);
	}
	if (App->player->isdead == true && finish == true){
		position.x = 89;
		position.y = 121;
		m = false;
		dead = true;
	
		current_animation = &up_r;
		GhostBlue_ispow = false;
		dead_blue = false;
		Isinmid = true;

		collision_blue->SetPos(position.x + 2, position.y + 12);
		ghost_up_r = false;
		ghost_down_r = false;
		ghost_left_r = false;
		ghost_right_r = false;

		can_right_r = false;
		can_down_r = false;
		can_left_r = false;
		can_up_r = false;
		
	}

	return UPDATE_CONTINUE;
}


void ModuleGhostBlue::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collision_blue && c2->type == COLLIDER_PLAYER && App->player->superpower == true ||
		c1 == collision_blue && c2->type == COLLIDER_PLAYER && App->player->SUPER_GOD == true)
	{
		position.x = 89;
		position.y = 121;
		dead = true;
		new_direction_r = 0;
		current_animation = &up_r;
		GhostBlue_ispow = false;
		dead_blue = false;
		Isinmid = true;
		m = true;

		collision_blue->SetPos(position.x + 2, position.y + 12);
		ghost_up_r = false;
		ghost_down_r = false;
		ghost_left_r = false;
		ghost_right_r = false;

		can_right_r = false;
		can_down_r = false;
		can_left_r = false;
		can_up_r = false;

		App->player->stop = 0;

	}
}

