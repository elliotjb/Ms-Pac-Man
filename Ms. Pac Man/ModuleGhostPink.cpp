#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleGhostPink.h"
#include "ModuleCollision.h"
#include "ModuleLevel_3.h"
#include "ModuleScore.h"
#include <cmath>


ModuleGhostPink::ModuleGhostPink()
{
	right_b.PushBack({ 457, 81, 14, 14 });
	right_b.PushBack({ 473, 81, 14, 14 });
	right_b.speed = 0.1f;
	left_b.PushBack({ 489, 81, 14, 14 });
	left_b.PushBack({ 505, 81, 14, 14 });
	left_b.speed = 0.1f;
	up_b.PushBack({ 521, 81, 14, 14 });
	up_b.PushBack({ 537, 81, 14, 14 });
	up_b.speed = 0.1f;
	down_b.PushBack({ 553, 81, 14, 14 });
	down_b.PushBack({ 569, 81, 14, 14 });
	down_b.speed = 0.1f;

	superpow_combination.PushBack({ 585, 65, 14, 14 });
	superpow_combination.PushBack({ 617, 65, 14, 14 });
	superpow_combination.speed = 0.05f;

	superpow_blue = { 585, 65, 14, 14 };
	puntuation = { 456, 133, 15, 7 };


	position_blue.x = 105;
	position_blue.y = 121;

	test = { 488, 201, 8, 8 };

}

ModuleGhostPink::~ModuleGhostPink()
{
}

// Load assets
bool ModuleGhostPink::Start()
{
	LOG("Loading Ghost textures");
	bool ret = true;
	graphics = App->textures->Load("MsPacMan_Sprites.png"); // Sprites
	test_num_UP.x = 0;
	test_num_UP.y = 0;
	super = false;
	ghost_up_r = false;
	ghost_down_r = false;
	ghost_left_r = false;
	ghost_right_r = false;
	dead_blue = false;
	can_right_r = false;
	can_down_r = false;
	can_left_r = false;
	can_up_r = false;
	GhostBlue_ispow = false;
	new_direction_b = 0;
	time_blue = 0;
	look_wherePacman = false;
	isleft = 0;
	isright = 0;
	isup = 0;
	isdown = 0;
	finish = false;
	Time_change_direction = 0;
	collision_blue = App->collision->AddCollider({ 0, 0, 10, 10 }, COLLIDER_ENEMY, this);
	srand(time(NULL));
	return ret;
}
bool ModuleGhostPink::CleanUp()
{
	App->textures->Unload(graphics);
	return true;
}

// Update
update_status ModuleGhostPink::Update()
{
	if (App->player->time_to_start > 240)
	{
		if (App->player->stop >= 50)
		{
			int speed = 1;
			//BLUE
			if (time_blue < 330 && Isinmid == true)
			{
				time_blue++;
			}
			if (Isinmid == false)
			{
				time_blue = 240;
			}

			if (Isinmid == true && time_blue > 329)
			{
				position_blue.y -= 1;
				if (position_blue.y == 99)
				{
					new_direction_b = 3;
					Isinmid = false;
					finish = true;
				}
			}

			//check possibilities
			//lefy
			if (App->level3->map[left_blue.y][left_blue.x - 1] != 0)
			{
				if ((position_blue.x + 7) == (center_blue.x * 8) + 4 &&
					(position_blue.y - 7) == (center_blue.y * 8) + 4)
				{
					can_left_r = true;
				}
			}
			else
			{
				can_left_r = false;
			}

			//up
			if (App->level3->map[up_blue.y - 1][up_blue.x] != 0)
			{
				if ((position_blue.x + 7) == (center_blue.x * 8) + 4 &&
					(position_blue.y - 7) == (center_blue.y * 8) + 4)
				{
					can_up_r = true;
				}
			}
			else
			{
				can_up_r = false;
			}

			// down
			if (App->level3->map[down_blue.y + 1][down_blue.x] != 0)
			{
				if ((position_blue.x + 7) == (center_blue.x * 8) + 4 &&
					(position_blue.y - 7) == (center_blue.y * 8) + 4)
				{
					can_down_r = true;
				}
			}
			else
			{
				can_down_r = false;
			}

			//left
			if (can_left_r == true || can_right_r == true)
			{
				if (can_up_r == false && can_down_r == false)
				{
					change_direction_r = false;
				}
				else
				{
					change_direction_r = true;
				}
			}
			if (can_up_r == true || can_down_r == true)
			{
				if (can_left_r == false && can_right_r == false)
				{
					change_direction_r = false;
				}
				else
				{
					change_direction_r = true;
				}
			}
			else{ change_direction_r = false; }


			if (App->player->direction == 0)
			{
				test_num_UP.y = App->player->center.y;
				while (App->level3->map[test_num_UP.y - 1][App->player->center.x] != 0)
				{
					test_num_UP.y -= 1;
				}
				test_num_UP.x = App->player->center.x;
				if (App->player->SUPER_GOD)
				{
					App->render->Blit(graphics, (test_num_UP.x * 8), (test_num_UP.y*8) + 24, &test);
				}
			}
			if (App->player->direction == 1)
			{
				test_num_UP.x = App->player->center.x;
				while (App->level3->map[App->player->center.y][test_num_UP.x - 1] != 0)
				{
					test_num_UP.x -= 1;
				}
				test_num_UP.y = App->player->center.y;
				if (App->player->SUPER_GOD)
				{
					App->render->Blit(graphics, test_num_UP.x * 8, (test_num_UP.y * 8) + 24, &test);
				}
			}
			if (App->player->direction == 2)
			{
				test_num_UP.y = App->player->center.y;
				while (App->level3->map[test_num_UP.y + 1][App->player->center.x] != 0)
				{
					test_num_UP.y += 1;
				}
				test_num_UP.x = App->player->center.x;
				if (App->player->SUPER_GOD)
				{
					App->render->Blit(graphics, test_num_UP.x * 8, (test_num_UP.y * 8) + 24, &test);
				}
			}
			if (App->player->direction == 3)
			{
				test_num_UP.x = App->player->center.x;
				while (App->level3->map[App->player->center.y][test_num_UP.x + 1] != 0)
				{
					test_num_UP.x += 1;
				}
				test_num_UP.y = App->player->center.y;
				if (App->player->SUPER_GOD)
				{
					App->render->Blit(graphics, test_num_UP.x * 8, (test_num_UP.y * 8) + 24, &test);
				}
			}

			//
			if (change_direction_r && super == false)
			{
				look_wherePacman = true;
				if (look_wherePacman)
				{
					if (can_up_r)
					{
						up_blue.x = ((center_blue.x - test_num_UP.x)*(center_blue.x - test_num_UP.x));
						up_blue.y = (((center_blue.y - 1) - test_num_UP.y)*((center_blue.y - 1) - test_num_UP.y));
						isup = sqrt(up_blue.x + up_blue.y);
						//No change direction in the opposite direction
						if (new_direction_b == 2)
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
						left_blue.x = (((center_blue.x - 1) - test_num_UP.x)*((center_blue.x - 1) - test_num_UP.x));
						left_blue.y = ((center_blue.y - test_num_UP.y)*(center_blue.y - test_num_UP.y));
						isleft = sqrt(left_blue.x + left_blue.y);
						//No change direction in the opposite direction
						if (new_direction_b == 3)
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
						down_blue.x = ((center_blue.x - test_num_UP.x)*(center_blue.x - test_num_UP.x));
						down_blue.y = (((center_blue.y + 1) - test_num_UP.y)*((center_blue.y + 1) - test_num_UP.y));
						isdown = sqrt(down_blue.x + down_blue.y);
						//No change direction in the opposite direction
						if (new_direction_b == 0)
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
						right_blue.x = (((center_blue.x + 1) - test_num_UP.x)*((center_blue.x + 1) - test_num_UP.x));
						right_blue.y = ((center_blue.y - test_num_UP.y)*(center_blue.y - test_num_UP.y));
						isright = sqrt(right_blue.x + right_blue.y);
						//No change direction in the opposite direction
						if (new_direction_b == 1)
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
						if (isup <= isleft && isup <= isdown && isup <= isright && new_direction_b != 2)
						{
							ghost_up_r = true; ghost_right_r = false; ghost_left_r = false; ghost_down_r = false;
						}
						if (isleft <= isup && isleft <= isdown && isleft <= isright && new_direction_b != 3)
						{
							ghost_left_r = true; ghost_right_r = false; ghost_up_r = false; ghost_down_r = false;
						}
						if (isdown <= isup && isdown <= isleft && isdown <= isright && new_direction_b != 0)
						{
							ghost_down_r = true; ghost_right_r = false; ghost_left_r = false; ghost_up_r = false;
						}
						if (isright <= isup && isright <= isleft && isright <= isdown && new_direction_b != 1)
						{
							ghost_right_r = true; ghost_down_r = false; ghost_left_r = false; ghost_up_r = false;
						}


						//This is for the corners
						if (can_right_r && can_down_r && can_left_r == false && can_up_r == false)
						{
							if (new_direction_b == 1)//Pacman is moving to left
							{
								ghost_down_r = true; ghost_right_r = false; ghost_left_r = false; ghost_up_r = false;
							}
							if (new_direction_b == 0)//Pacman is moving to up
							{
								ghost_right_r = true; ghost_down_r = false; ghost_left_r = false; ghost_up_r = false;
							}
						}

						if (can_left_r && can_up_r && can_right_r == false && can_down_r == false)
						{
							if (new_direction_b == 3)//Pacman is moving to down
							{
								ghost_up_r = true; ghost_right_r = false; ghost_left_r = false; ghost_down_r = false;
							}
							if (new_direction_b == 2)
							{
								ghost_left_r = true; ghost_right_r = false; ghost_up_r = false; ghost_down_r = false;
							}
						}
						if (can_left_r && can_down_r && can_right_r == false && can_down_r == false)
						{
							if (new_direction_b == 3)
							{
								ghost_down_r = true; ghost_right_r = false; ghost_left_r = false; ghost_up_r = false;
							}
							if (new_direction_b == 0)
							{
								ghost_left_r = true; ghost_right_r = false; ghost_up_r = false; ghost_down_r = false;
							}
						}
						if (can_right_r && can_up_r && can_left_r == false && can_down_r == false)
						{
							if (new_direction_b == 1)
							{
								ghost_up_r = true; ghost_right_r = false; ghost_left_r = false; ghost_down_r = false;
							}
							if (new_direction_b == 2)
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
					if (new_direction_b == 0)
					{
						new_direction_b = 2; ghost_down_r = true; ghost_right_r = false; ghost_left_r = false; ghost_up_r = false;
					}
					if (new_direction_b == 1)
					{
						new_direction_b = 3; ghost_right_r = true; ghost_down_r = false; ghost_left_r = false; ghost_up_r = false;
					}
					if (new_direction_b == 2)
					{
						new_direction_b = 0; ghost_up_r = true; ghost_right_r = false; ghost_left_r = false; ghost_down_r = false;
					}
					if (new_direction_b == 3)
					{
						new_direction_b = 1; ghost_left_r = true; ghost_right_r = false; ghost_up_r = false; ghost_down_r = false;
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
							up_blue.x = (center_blue.x - App->player->center.x)*(center_blue.x - App->player->center.x);
							up_blue.y = (((center_blue.y - 1) - App->player->center.y)*((center_blue.y - 1) - App->player->center.y));
							isup = sqrt(up_blue.x + up_blue.y);
						}

						if (can_left_r)
						{
							left_blue.x = (((center_blue.x - 1) - App->player->center.x)*((center_blue.x - 1) - App->player->center.x));
							left_blue.y = ((center_blue.y - App->player->center.y)*(center_blue.y - App->player->center.y));
							isleft = sqrt(left_blue.x + left_blue.y);
						}

						if (can_down_r)
						{
							down_blue.x = ((center_blue.x - App->player->center.x)*(center_blue.x - App->player->center.x));
							down_blue.y = (((center_blue.y + 1) - App->player->center.y)*((center_blue.y + 1) - App->player->center.y));
							isdown = sqrt(down_blue.x + down_blue.y);
						}

						if (can_right_r)
						{
							right_blue.x = (((center_blue.x + 1) - App->player->center.x)*((center_blue.x + 1) - App->player->center.x));
							right_blue.y = ((center_blue.y - App->player->center.y)*(center_blue.y - App->player->center.y));
							isright = sqrt(right_blue.x + right_blue.y);
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
								if (new_direction_b == 1)//Pacman is moving to left
								{
									ghost_down_r = true; ghost_right_r = false; ghost_left_r = false; ghost_up_r = false;
								}
								if (new_direction_b == 0)//Pacman is moving to up
								{
									ghost_right_r = true; ghost_down_r = false; ghost_left_r = false; ghost_up_r = false;
								}
							}

							if (can_left_r && can_up_r && can_right_r == false && can_down_r == false)
							{
								if (new_direction_b == 3)//Pacman is moving to down
								{
									ghost_up_r = true; ghost_right_r = false; ghost_left_r = false; ghost_down_r = false;
								}
								if (new_direction_b == 2)
								{
									ghost_left_r = true; ghost_right_r = false; ghost_up_r = false; ghost_down_r = false;
								}
							}
							if (can_left_r && can_down_r && can_right_r == false && can_down_r == false)
							{
								if (new_direction_b == 3)
								{
									ghost_down_r = true; ghost_right_r = false; ghost_left_r = false; ghost_up_r = false;
								}
								if (new_direction_b == 0)
								{
									ghost_left_r = true; ghost_right_r = false; ghost_up_r = false; ghost_down_r = false;
								}
							}
							if (can_right_r && can_up_r && can_left_r == false && can_down_r == false)
							{
								if (new_direction_b == 1)
								{
									ghost_up_r = true; ghost_right_r = false; ghost_left_r = false; ghost_down_r = false;
								}
								if (new_direction_b == 2)
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


			right_blue.x = (position_blue.x + 3) / PIX_TILE;
			right_blue.y = (position_blue.y - 7) / PIX_TILE;
			left_blue.x = (position_blue.x + 10) / PIX_TILE;
			left_blue.y = (position_blue.y - 7) / PIX_TILE;
			up_blue.x = (position_blue.x + 7) / PIX_TILE;
			up_blue.y = (position_blue.y - 4) / PIX_TILE;
			down_blue.x = (position_blue.x + 7) / PIX_TILE;
			down_blue.y = (position_blue.y - 11) / PIX_TILE;
			center_blue.x = (position_blue.x + 6) / PIX_TILE;
			center_blue.y = (position_blue.y - 7) / PIX_TILE;


			//decided direction
			if (App->level3->map[up_blue.y - 1][up_blue.x] != 0 && position_blue.x < 210 && position_blue.x > 0)
			{
				if (ghost_up_r)
				{
					if ((position_blue.x + 7) == (center_blue.x * PIX_TILE) + 4 || (position_blue.x + 7) == (center_blue.x * PIX_TILE) + 3 ||
						(position_blue.x + 7) == (center_blue.x * PIX_TILE) + 5 || (position_blue.x + 7) == (center_blue.x * PIX_TILE) + 2 ||
						(position_blue.x + 7) == (center_blue.x * PIX_TILE) + 6 && (position_blue.y - 7) == (center_blue.y * PIX_TILE) + 4 ||
						new_direction_b == 2)
					{
						position_blue.x = (center_blue.x * PIX_TILE) + 4 - 7;
						new_direction_b = 0;
					}
				}
				if (new_direction_b == 0)
				{
					up_b.speed = 0.3f;
					animation_blue = &up_b;
					position_blue.y -= speed;
				}
			}
			else
			{
				up_b.speed = 0.0f;
			}
			if (App->level3->map[left_blue.y][left_blue.x - 1] != 0 || position_blue.x <= 0 || position_blue.x >= 220 && position_blue.x <= 239)
			{
				if (ghost_left_r)
				{
					if ((position_blue.x + 7) == (center_blue.x * PIX_TILE) + 4 && (position_blue.y - 7) == (center_blue.y * PIX_TILE) + 4 ||
						(position_blue.y - 7) == (center_blue.y * PIX_TILE) + 3 || (position_blue.y - 7) == (center_blue.y * PIX_TILE) + 5 ||
						(position_blue.y - 7) == (center_blue.y * PIX_TILE) + 2 || (position_blue.y - 7) == (center_blue.y * PIX_TILE) + 6 ||
						new_direction_b == 3)
					{
						position_blue.y = (center_blue.y * PIX_TILE) + 4 + 7;
						new_direction_b = 1;
					}
				}
				if (new_direction_b == 1)
				{
					left_b.speed = 0.3f;
					animation_blue = &left_b;
					position_blue.x -= speed;
				}
				if (position_blue.x == -10 && new_direction_b == 1)
				{
					position_blue.x = 220;
				}
			}
			else
			{
				left_b.speed = 0.0f;
			}

			if (App->level3->map[down_blue.y + 1][down_blue.x] != 0 && position_blue.x < 210 && position_blue.x > 0)
			{
				if (ghost_down_r)
				{
					if ((position_blue.x + 7) == (center_blue.x * PIX_TILE) + 4 || (position_blue.x + 7) == (center_blue.x * PIX_TILE) + 3 ||
						(position_blue.x + 7) == (center_blue.x * PIX_TILE) + 5 || (position_blue.x + 7) == (center_blue.x * PIX_TILE) + 2 ||
						(position_blue.x + 7) == (center_blue.x * PIX_TILE) + 6 && (position_blue.y - 7) == (center_blue.y * PIX_TILE) + 4 ||
						new_direction_b == 0)
					{
						position_blue.x = (center_blue.x * PIX_TILE) + 4 - 7;
						new_direction_b = 2;
					}
				}
				if (new_direction_b == 2)
				{
					down_b.speed = 0.3f;
					animation_blue = &down_b;
					position_blue.y += speed;
				}
			}
			else
			{
				down_b.speed = 0.0f;
			}

			if (App->level3->map[right_blue.y][right_blue.x + 1] != 0 || position_blue.x > 210)
			{
				if ((position_blue.x + 7) == (center_blue.x * 8) + 4 &&
					(position_blue.y - 7) == (center_blue.y * 8) + 4)
				{
					can_right_r = true;
				}
				if (ghost_right_r)
				{
					if ((position_blue.x + 7) == (center_blue.x * PIX_TILE) + 4 && (position_blue.y - 7) == (center_blue.y * PIX_TILE) + 4 ||
						(position_blue.y - 7) == (center_blue.y * PIX_TILE) + 3 || (position_blue.y - 7) == (center_blue.y * PIX_TILE) + 5 ||
						(position_blue.y - 7) == (center_blue.y * PIX_TILE) + 2 || (position_blue.y - 7) == (center_blue.y * PIX_TILE) + 6 ||
						new_direction_b == 1)
					{
						position_blue.y = (center_blue.y * PIX_TILE) + 4 + 7;
						new_direction_b = 3;
					}
				}
				if (new_direction_b == 3)
				{
					right_b.speed = 0.3f;
					animation_blue = &right_b;
					position_blue.x += speed;
				}

				if (position_blue.x >= 220 && new_direction_b == 3)
				{
					position_blue.x = -10;
				}
			}
			else
			{
				right_b.speed = 0.0f;
			}
			if (App->level3->map[right_blue.y][right_blue.x + 1] == 0)
			{
				can_right_r = false;
			}

			collision_blue->SetPos(position_blue.x + 2, position_blue.y + 12);

			if (super == true && App->player->timer < 5)
			{
				GhostBlue_ispow = true;
			}
			if (super == false)
			{
				GhostBlue_ispow = false;
			}
		}
	}

	// Draw everything --------------------------------------

	SDL_Rect r_b = animation_blue->GetCurrentFrame();
	SDL_Rect r_pow = current_superpow_combination->GetCurrentFrame();

	//EDIT FOR NEXT UPDATE!!! (Elliot)
	if (App->player->time_to_start > 60)
	{
		if (GhostBlue_ispow == true)
		{
			if (App->player->timer > 280)
			{
				superpow_combination.speed = 0.06f;
				App->render->Blit(graphics, position_blue.x, position_blue.y + 24 - r_b.h, &r_pow);
			}
			else
			{
				App->render->Blit(graphics, position_blue.x, position_blue.y + 24 - r_b.h, &superpow_blue);
			}

		}
		else
		{
			App->render->Blit(graphics, position_blue.x, position_blue.y + 24 - r_b.h, &r_b);
		}
	}
	if (App->player->isdead == true && finish == true){
		position_blue.x = 105;
		position_blue.y = 121;
		Isinmid = true;
		new_direction_b = 0;
		animation_blue = &up_b;
		GhostBlue_ispow = false;
		dead_blue = false;
		super = false;
		collision_blue->SetPos(position_blue.x + 2, position_blue.y + 12);
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


void ModuleGhostPink::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collision_blue && c2->type == COLLIDER_PLAYER && App->player->superpower == true && super == true ||
		c1 == collision_blue && c2->type == COLLIDER_PLAYER && App->player->SUPER_GOD == true)
	{
		App->render->Blit(graphics, position_blue.x, position_blue.y, &puntuation);
		position_blue.x = 105;
		position_blue.y = 121;
		Isinmid = true;
		new_direction_b = 0;
		animation_blue = &up_b;
		GhostBlue_ispow = false;
		dead_blue = false;
		super = false;
		App->score->puntuation += 200;

		collision_blue->SetPos(position_blue.x + 2, position_blue.y + 12);
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
