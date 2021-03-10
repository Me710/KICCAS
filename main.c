#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include "option.h"
#include "fonctions.h"
#include "intro.h"



int main()
{
    int hauteur_fenetre = 768,
        largeur_fenetre = 1366;
	
	SDL_Surface *ecran = NULL;	
	intro(&ecran);
	
	
    SDL_Init(SDL_INIT_VIDEO);

    //FENETRE PRINCIPALE
    SDL_Surface *screen = NULL;
    screen = SDL_SetVideoMode(largeur_fenetre, hauteur_fenetre, 32, SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("KICCAS", NULL);
    //afficher le menu
    int menu=-1;

    do
    {
	menu=afficher_menu(screen);
    switch (menu)
	{
		case 1:
			//ecran_jeu(screen);
		break;
		case 2 :
			afficher_option(screen);
		break;

	}

    }
    while (menu!=0);

    SDL_Quit();





    return 0;
}
