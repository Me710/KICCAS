#include "header.h"

int main()
{
    int hauteur_fenetre = 768,
        largeur_fenetre = 1366;

	SDL_Surface *ecran = NULL;
	intro(&ecran);


    SDL_Init(SDL_INIT_VIDEO);

    //FENETRE PRINCIPALE
    SDL_Surface *screen = NULL;
    screen = SDL_SetVideoMode(largeur_fenetre, hauteur_fenetre, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("KICCAS", NULL);
    //afficher le menu
    int menu=-1;

    do
    {
	    menu=afficher_menu(screen);
     switch (menu)
	{
		case 1:
			ecran_Jeu(screen);
		break;
		case 2 :
			afficher_option(screen);
		break;
                case 4:
 			quitter(screen,&menu);
                break;

	}

    }
    while (menu!=0);

    SDL_Quit();





    return 0;
}
