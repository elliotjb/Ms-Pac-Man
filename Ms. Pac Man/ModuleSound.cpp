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

// Load
bool ModuleSound::Start()
{
	int flags = MIX_INIT_OGG;
	int start = Mix_Init(flags);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
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


_Mix_Music* const ModuleSound::LoadMUS(const char* path)
{
	_Mix_Music* music = NULL;

	_Mix_Music* music_2 = Mix_LoadMUS(path);
	Mix_PlayMusic(music_2, -1);
}
/*update_status ModuleSound::Update()
{

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	music = Mix_LoadMUS("mspacmanStart.ogg");
	Mix_PlayMusic(music, -1);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, (Module*)App->welcome, 5.0f);
	}

	return UPDATE_CONTINUE;
}