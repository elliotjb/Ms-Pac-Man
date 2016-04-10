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


}

ModuleWelcome::~ModuleWelcome()
{}

// Load assets
bool ModuleWelcome::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("MsPacman_Welcome.png");
	music_sound = App->sound->LoadMUS("music.ogg");//This not correctly music!

	if (Mix_PlayMusic(music_sound, -1) == -1) {
		LOG("Mix_PlayMusic: %s\n", Mix_GetError());

	}

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
	
	App->render->Blit(graphics, 0, 0, &welcome);

	//App->render->Blit(graphics, 305, 136, &(water.GetCurrentFrame())); // water animation

	// TODO 3: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, (Module*)App->level1, 2.0f);
	}

	return UPDATE_CONTINUE;
}