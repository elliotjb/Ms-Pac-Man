#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScore.h"
#include "ModulePlayer.h"


ModuleScore::ModuleScore(){
	s4 = 0;
	s3 = 0;
	s2 = 0;
	s1 = 0;
	s0 = 0;
	One = { 26, 0, 6, 6 };
	U = { 33, 0, 6, 6 };
	P = { 41, 0, 6, 6 };
	H = { 73, 0, 6, 6 };
	I = { 82, 0, 6, 6 };
	G = { 89, 0, 6, 6 };
	S = { 113, 0, 6, 6 };
	C = { 121, 0, 6, 6 };
	O = { 129, 0, 6, 6 };
	R = { 137, 0, 6, 6 };
	E = { 145, 0, 6, 6 };
	SC0 = { 17, 186, 6, 6 };
	SC1 = { 29, 186, 6, 6 };
	SC2 = { 37, 186, 6, 6 };
	SC3 = { 47, 186, 6, 6 };
	SC4 = { 57, 186, 6, 6 };
	SC5 = { 67, 186, 6, 6 };
	SC6 = { 77, 186, 6, 6 };
	SC7 = { 87, 186, 6, 6 };
	SC8 = { 97, 186, 6, 6 };
	SC9 = { 107, 186, 6, 6 };
	Space = { 0, 0, 8, 8 };

}

ModuleScore::~ModuleScore(){

}
bool ModuleScore::Start(){
	LOG(" SCORE MAP");
	bool ret = true;

	graphics = App->textures->Load("MsPacman.png");
	graphicstxt = App->textures->Load("google-pacman-logo-sprites.png");

	char SCOREMAP[3][28] = {
		{ ' ', ' ', ' ', 'o', 'U', 'P', ' ', ' ', ' ', 'H', 'I', 'G', 'H', ' ', 'S', 'C', 'O', 'R', 'E', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }, 
		{ ' ', ' ', ' ', 'n', 'n', 'n', 'n', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }, 
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }, 
		};

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 28; j++){
			Maplvl[i][j] = SCOREMAP[i][j];
		}

	}
	return ret;
}


bool ModuleScore::CleanUp(){

	return true;
}

update_status ModuleScore::Update()
{
	for (int x = 0; x < 28; ++x){
		for (int y = 0; y < 3; y++){
			switch (Maplvl[y][x]){
			case ' ':
				App->render->Blit(graphics,x * 8, y * 8, &Space);
				break;
			case 'H':
				App->render->Blit(graphics, x * 8, y * 8, &H);
				break;
			case 'I':
				App->render->Blit(graphics, x * 8, y * 8, &I);
				break;
			case 'G':
				App->render->Blit(graphics, x * 8, y * 8, &G);
				break;
			case 'S':
				App->render->Blit(graphics, x * 8, y * 8, &S);
				break;
			case 'C':
				App->render->Blit(graphics, x * 8, y * 8, &C);
				break;
			case 'O':
				App->render->Blit(graphics, x * 8, y * 8, &O);
				break;
			case 'R':
				App->render->Blit(graphics, x * 8, y * 8, &R);
				break;
			case 'E':
				App->render->Blit(graphics, x * 8, y * 8, &E);
				break;
			case 'U':
				App->render->Blit(graphics, x * 8, y * 8, &U);
				break;
			case 'P':
				App->render->Blit(graphics, x * 8, y * 8, &P);
				break;
			case 1:
				App->render->Blit(graphics, x * 8, y * 8, &One);
				break;
			case 'n':
				for (int x = 0; x < 4; ++x){
					switch (score[x]){
					case 0:
						App->render->Blit(graphicstxt, x * 8, y * 8, &SC0);
						break;
					case 'o':
						App->render->Blit(graphicstxt, x * 8, y * 8, &SC1);
						break;
					case 2:
						App->render->Blit(graphicstxt, x * 8, y * 8, &SC2);
						break;
					case 3:
						App->render->Blit(graphicstxt, x * 8, y * 8, &SC3);
						break;
					case 4:
						App->render->Blit(graphicstxt, x * 8, y * 8, &SC4);
						break;
					case 5:
						App->render->Blit(graphicstxt, x * 8, y * 8, &SC5);
						break;
					case 6:
						App->render->Blit(graphicstxt, x * 8, y * 8, &SC6);
						break;
					case 7:
						App->render->Blit(graphicstxt, x * 8, y * 8, &SC7);
						break;
					case 8:
						App->render->Blit(graphicstxt, x * 8, y * 8, &SC8);
						break;
					case 9:
						App->render->Blit(graphicstxt, x * 8, y * 8, &SC9);
						break;

					}
				}
			}

		}

	}
	
	



	return UPDATE_CONTINUE;

}