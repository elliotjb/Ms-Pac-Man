#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 105;
	position.y = 219;

	// idle animation (arcade sprite sheet)

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	forward.PushBack({489, 1, 15, 14});
	forward.PushBack({473, 1, 15, 14});
	forward.PushBack({457, 1, 15, 14});
	forward.PushBack({473, 1, 15, 14});
	forward.speed = 0.1f;

	// TODO 4: Make ryu walk backwards with the correct animations
	backward.PushBack({ 488, 17, 15, 14 });
	backward.PushBack({ 473, 17, 15, 14 });
	backward.PushBack({ 457, 17, 15, 14 });
	backward.PushBack({ 473, 17, 15, 14 });
	backward.speed = 0.155f;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("MsPacMan_Sprites.png"); // Sprites
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	Animation* current_animation = &backward;
	
	if (last_key == 1){
		Animation* current_animation = &backward;
	}
	if (last_key == 2){
		Animation* current_animation = &forward;
	}


	int speed = 1;

	if(App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		current_animation = &forward;
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		current_animation = &backward;
		position.x -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == 1){
		current_animation = &backward;
		position.y += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == 1){
		current_animation = &backward;
		position.y -= speed;
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);//EDIT FOR NEXT UPDATE!!! (Elliot)
	
	return UPDATE_CONTINUE;
}