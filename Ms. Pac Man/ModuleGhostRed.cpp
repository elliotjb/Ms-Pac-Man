#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleGhostRed.h"
#include "ModuleCollision.h"
#include "ModuleLevel_3.h"
#include "ModuleLevel_4.h"
#include "ModuleScore.h"
#include "ModuleSound.h"
#include <cmath>

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
	puntuation = { 456, 133, 15, 7 };
	superpow_combination.PushBack({ 585, 65, 14, 14 });
	superpow_combination.PushBack({ 617, 65, 14, 14 });
	superpow_combination.speed = 0.05f;

	superpow_blue = { 585, 65, 14, 14 };

}

ModuleGhostRed::~ModuleGhostRed()
{}

// Load assets
bool ModuleGhostRed::Start()
{
	LOG("Loading Ghost textures");
	bool ret = true;
	graphics = App->textures->Load("Sprites/MsPacMan_Sprites.png"); // Sprites
	srand(time(NULL));
	Time_change_direction = 0;
	position.x = 105;
	position.y = 99;
	current_animation = &left_r;
	s = 0;
	superfristmoviment = false;
	dead = false;
	finish = false;
	super = false;
	new_direction_r = 1;
	time_blue = 0;
	ghost_up_r = false;
	ghost_down_r = false;
	ghost_left_r = false;
	ghost_right_r = false;

	can_right_r = false;
	can_down_r = false;
	can_left_r = false;
	can_up_r = false;

	if (App->level3->islevel3)
	{
		for (int i = 0; i < 31; i++)
		{
			for (int j = 0; j < 28; j++)
			{
				map_ghost[i][j] = App->level3->map[i][j];
			}
		}
	}

	if (App->level4->islevel4)
	{
		for (int i = 0; i < 31; i++)
		{
			for (int j = 0; j < 28; j++)
			{
				map_ghost[i][j] = App->level4->map[i][j];
			}
		}
	}

	//red
	collision = App->collision->AddCollider({ 0, 0, 10, 10 }, COLLIDER_ENEMY, this);
	new_direction_r = 1;
	return ret;
}

bool ModuleGhostRed::CleanUp()
{
	App->textures->Unload(graphics);
		return true;
}

// Update
update_status ModuleGhostRed::Update()
{

	if (App->player->time_to_start > 240)
	{
		finish = true;
		if (App->player->stop >= 50)
		{
			srand(time(NULL));
			//RED

			//checking possibilities

			//right


			if (map_ghost[right_y_r][right_x_r + 1] != 0)
			{
				if ((position.x + 7) == (center_x_r * 8) + 4 && (position.y - 7) == (center_y_r * 8) + 4) can_right_r = true;
			}
			else can_right_r = false;

			//left
			if (map_ghost[left_y_r][left_x_r - 1] != 0)
			{
				if ((position.x + 7) == (center_x_r * 8) + 4 && (position.y - 7) == (center_y_r * 8) + 4) can_left_r = true;
			}
			else can_left_r = false;

			//up
			if (map_ghost[up_y_r - 1][up_x_r] != 0)
			{
				if ((position.x + 7) == (center_x_r * 8) + 4 && (position.y - 7) == (center_y_r * 8) + 4) can_up_r = true;
			}
			else can_up_r = false;

			// down
			if (map_ghost[down_y_r + 1][down_x_r] != 0)
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


			if (change_direction_r && super == false)
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
					Time_change_direction++;
					if (Time_change_direction > 5)
					{
						Time_change_direction = 0;
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
					}
					look_wherePacman = false;
				}
			}

			if (super == true)
			{
				if (superfristmoviment == false)
				{
					if (new_direction_r == 0)
					{
						new_direction_r = 2; ghost_down_r = true; ghost_right_r = false; ghost_left_r = false; ghost_up_r = false;
					}
					if (new_direction_r == 1)
					{
						new_direction_r = 3; ghost_right_r = true; ghost_down_r = false; ghost_left_r = false; ghost_up_r = false;
					}
					if (new_direction_r == 2)
					{
						new_direction_r = 0; ghost_up_r = true; ghost_right_r = false; ghost_left_r = false; ghost_down_r = false;
					}
					if (new_direction_r == 3)
					{
						new_direction_r = 1; ghost_left_r = true; ghost_right_r = false; ghost_up_r = false; ghost_down_r = false;
					}
				}
				if (change_direction_r && superfristmoviment == true)
				{
					isup = 0;
					isdown = 0;
					isleft = 0;
					isright = 0;
					look_wherePacman = true;
					if (look_wherePacman)
					{
						if (can_up_r)
						{
							up.x = ((center_x_r - App->player->center.x)*(center_x_r - App->player->center.x));
							up.y = (((center_y_r - 1) - App->player->center.y)*((center_y_r - 1) - App->player->center.y));
							isup = sqrt(up.x + up.y);
						}

						if (can_left_r)
						{
							left.x = (((center_x_r - 1) - App->player->center.x)*((center_x_r - 1) - App->player->center.x));
							left.y = ((center_y_r - App->player->center.y)*(center_y_r - App->player->center.y));
							isleft = sqrt(left.x + left.y);
						}

						if (can_down_r)
						{
							down.x = ((center_x_r - App->player->center.x)*(center_x_r - App->player->center.x));
							down.y = (((center_y_r + 1) - App->player->center.y)*((center_y_r + 1) - App->player->center.y));
							isdown = sqrt(down.x + down.y);
						}

						if (can_right_r)
						{
							right.x = (((center_x_r + 1) - App->player->center.x)*((center_x_r + 1) - App->player->center.x));
							right.y = ((center_y_r - App->player->center.y)*(center_y_r - App->player->center.y));
							isright = sqrt(right.x + right.y);
						}

						Time_change_direction++;
						if (Time_change_direction > 5)
						{
							Time_change_direction = 0;
							//Check which direction to go, the shortest
							if (isup >= isleft && isup >= isdown && isup >= isright)
							{
								ghost_up_r = true; ghost_right_r = false; ghost_left_r = false; ghost_down_r = false;
							}
							if (isleft >= isup && isleft >= isdown && isleft >= isright)
							{
								ghost_left_r = true; ghost_right_r = false; ghost_up_r = false; ghost_down_r = false;
							}
							if (isdown >= isup && isdown >= isleft && isdown >= isright)
							{
								ghost_down_r = true; ghost_right_r = false; ghost_left_r = false; ghost_up_r = false;
							}
							if (isright >= isup && isright >= isleft && isright >= isdown)
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
						}
						look_wherePacman = false;
					}
				}
				superfristmoviment = true;
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

			if (dead == true)
			{
				super = false;
				if (position.y > 99)
				{
					position.y--;
				}
				else if (position.y = 99)
				{
					dead = false;
				}
			}
			int speed = 1;
			if (time_blue < 240)
			{
				time_blue++;
			}
			if (time_blue > 239)
			{
				//decided direction
				//TODO ELLIOT BUG ATRAVESAR PORTAL
				if (map_ghost[up_y_r - 1][up_x_r] != 0 && position.x < 210 && position.x > 0)
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

				if (map_ghost[left_y_r][left_x_r - 1] != 0 || position.x <= 0 || position.x >= 220 && position.x <= 239)
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

					if (position.x == -15 && new_direction_r == 1)
					{
						position.x = 239;
					}
				}

				if (map_ghost[down_y_r + 1][down_x_r] != 0 && position.x < 210 && position.x > 0)
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

				if (map_ghost[right_y_r][right_x_r + 1] != 0 || position.x > 210)
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

					if (position.x >= 239 && new_direction_r == 3)
					{
						position.x = -15;
					}
				}
			}
		}



		collision->SetPos(position.x + 2, position.y + 12);
		// Draw everything --------------------------------------

		SDL_Rect r_r = current_animation->GetCurrentFrame();


		//EDIT FOR NEXT UPDATE!!! (Elliot)
		if (super == true && App->player->timer < 5)
		{
			GhostBlue_ispow = true;
		}
		if (super == false)
		{
			GhostBlue_ispow = false;
		}
		// Draw everything --------------------------------------

		SDL_Rect r_b = current_animation->GetCurrentFrame();
		SDL_Rect r_pow = current_superpow_combination->GetCurrentFrame();

		//EDIT FOR NEXT UPDATE!!! (Elliot)
		if (App->player->time_to_start > 70)
		{
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
				App->render->Blit(graphics, position.x, position.y + 24 - r_r.h, &r_r);
			}
		}
		if (App->player->isdead == true && finish == true){
			position.x = 105;
			position.y = 121;
			dead = true;
			new_direction_r = 1;
			current_animation = &left_r;
			GhostBlue_ispow = false;

			ghost_up_r = false;
			ghost_down_r = false;
			ghost_left_r = false;
			ghost_right_r = false;

			collision->SetPos(position.x + 2, position.y + 12);
			can_right_r = false;
			can_down_r = false;
			can_left_r = false;
			can_up_r = false;



		}


		return UPDATE_CONTINUE;
	}
}

void ModuleGhostRed::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collision && c2->type == COLLIDER_PLAYER && App->player->superpower == true && super == true ||
		c1 == collision && c2->type == COLLIDER_PLAYER && App->player->SUPER_GOD == true )
	{
		App->render->Blit(graphics, position.x, position.y, &puntuation);
		position.x = 105;		
		position.y = 121;
		dead = true;
		new_direction_r = 1;
		current_animation = &left_r;
		GhostBlue_ispow = false;
		ghost_up_r = false;
		ghost_down_r = false;
		ghost_left_r = false;
		ghost_right_r = false;
		App->score->puntuation += 200;
		Mix_PlayChannel(-1, App->sound->sound_mov, 0);
		//super = false;
		collision->SetPos(position.x + 2, position.y + 12);
		can_right_r = false;
		can_down_r = false;
		can_left_r = false;
		can_up_r = false;

		change_comp_r = false;
		App->player->stop = 0;
	}
}