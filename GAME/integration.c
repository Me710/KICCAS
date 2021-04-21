#include "header.h"

#define  largeur_fenetre 1366
#define  hauteur_fenetre 768
#define largeur_background 8904
#define largeur_map 890

void ecran_Jeu()
{
	/************************************************************************************************************/
//initialiser 
	SDL_Surface *screengame = NULL;
	SDL_Surface *gameover=NULL;
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	screengame = SDL_SetVideoMode(largeur_fenetre, hauteur_fenetre, 32, SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("GAME OF KICCAS", NULL);
	TTF_Init();
	/**************************************************************************************************************/
//declaration de la music
	Mix_Chunk  *music1;
    Mix_Music *music;
    initmusic(&music,&music1);
	/**************************************************************************************************************/
//declaration des structures du jeu
    background b;
    Personne p, pM, pMprochaine;
    ennemi e;
    enigme En;
    obstacle ob;
    minimap m;
    temps t;
 	/**************************************************************************************************************/
	SDL_Event event;
	int volum = 128;
    int direction = -1;
    int game = 1,i,j;	
	int collision = 0;
	int redimensionnement = 20*largeur_map/largeur_background;
	Uint32 dt;
	int reponse=-1;
 	/**************************************************************************************************************/
    SDL_EnableKeyRepeat(15,15);
    Mix_VolumeMusic(volum);
    Mix_PlayMusic(music,-1);
	initEnnemi(&e);
    initBack(&b);
    initPerso(&p);
    initObstacle(&ob);
    initmap(&m);
    initialiser_temps(&t);
 	/**************************************************************************************************************/

	while(game)
	{ 
		direction = Get_EventDirection(&event,&game,&p);
		collision = collisionBB(p.pos,e.pos);
		scrolling(&b,direction);
		majminimap(&p,&m,direction,redimensionnement);
		updatePerso(&p);

		
		
             
       	if(collision == 1)
		{
			e.num = 3;
			p.collision++;
			Mix_PlayChannel(-1, music1, 0);
		}

		if(direction == -1)
			p.key=0;
		else
		{
			p.key=1;
			p.dir=direction;
		}

		
       /**************************************************************************************************************/
       //deplacer et animer l'ennemi
		deplacerEnnemi(&e);
		animerEnnemi(&e);
		/**************************************************************************************************************/
	   //MAJ du perso et animation
		//deplacerPerso (&p,dt);
		animerPerso(&p);
		
		/**************************************************************************************************************/
        
 		/**************************************************************************************************************/
        //afficher 
        afficherPerso(p,screengame);
    	afficher(b,screengame);
    	afficherEnnemi(e,screengame);
    	afficher_temps(&t, screengame);
    	afficherminimap(m, screengame);
    	if(p.etat_vie==0)
    	{
    		SDL_FillRect(screengame, NULL, SDL_MapRGB(screengame->format, 0, 0, 0));
           //reponse=afficherenigme(En,screengame);
           SDL_Flip(screengame);
    	}
    	if(reponse==0)
    	{
         	//SDL_FillRect(screengame, NULL, SDL_MapRGB(screengame->format, 0, 0, 0));
            SDL_BlitSurface(gameover,NULL,screengame,&b.pos);
            game=0;
            SDL_Delay(500);
            SDL_Flip(screengame);
    	}
    	/**************************************************************************************************************/
		//rafraichir
		//SDL_Delay(10);
    	SDL_Flip(screengame);
    	/**************************************************************************************************************/
    }
    free_minimap(m);
    free_temps(&t, screengame);
	libererennemi(e);
	SDL_FreeSurface(b.imageFond);
	SDL_FreeSurface(screengame);
	SDL_FreeSurface(gameover);
	Mix_FreeChunk(music1);
	Mix_FreeMusic(music);
	libererperso(p);
	SDL_FreeSurface(ob.image);
	TTF_Quit();
    SDL_Quit();
}



//SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));