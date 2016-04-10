#include "Globals.h"
#include "Application.h"
#include "ModuleSound.h"
#include "ModuleWelcome.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SDL_mixer\include\SDL_mixer.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSound::ModuleSound()
{

}

ModuleSound::~ModuleSound()
{

}

// Load assets
bool ModuleSound::Start()
{
	Mix_Init(MIX_INIT_OGG | MIX_INIT_MOD);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	music = Mix_LoadMUS("mspacmanStart.ogg");
	Mix_PlayMusic(music, -1);
	LOG("Loading background assets");
	bool ret = true;


	return ret;
}

// Load assets
bool ModuleSound::CleanUp()
{
	LOG("Unloading honda stage");
	Mix_FreeMusic(music);
	return true;
}

// Update: draw background
update_status ModuleSound::Update()
{
	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, (Module*)App->welcome, 5.0f);
	}

	return UPDATE_CONTINUE;
}