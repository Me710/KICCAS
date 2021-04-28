#include "header.h"

#define  largeur_fenetre 1366
#define  hauteur_fenetre 768
#define largeur_background 8904
#define largeur_map 890

void ecran_Jeu(SDL_Surface *screengame,int *menu)
{
	/************************************************************************************************************/
//initialiser 
	//SDL_Surface *screengame = NULL;
	SDL_Surface *gameover=NULL;
	SDL_Surface *enigmeSlim=NULL;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	//screengame = SDL_SetVideoMode(largeur_fenetre, hauteur_fenetre, 32, SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);
	//SDL_WM_SetCaption("GAME OF KICCAS", NULL);
	TTF_Init();
	/**************************************************************************************************************/
//declaration de la music
	Mix_Chunk  *music1;
    Mix_Music *music;
    initmusic(&music,&music1);
	/**************************************************************************************************************/
//declaration des structures du jeu
    background b;
    Personne p;
    ennemi e;
    obstacle ob;
    minimap m;
    temps t;
	enigme En;
 	/**************************************************************************************************************/
	SDL_Event event;
	int volum = 128;
    int direction = -1;
    int i,j;	
	int collision = 0;
	int redimensionnement = 20*largeur_map/largeur_background;
	Uint32 dt;
	int reponse=-1;
	int deplacement;
 	/**************************************************************************************************************/
    SDL_EnableKeyRepeat(10,10);
    Mix_VolumeMusic(volum);
    Mix_PlayMusic(music,-1);
	initEnnemi(&e);
    initBack(&b);
    initPerso(&p);
    initObstacle(&ob);
    initmap(&m);
    initialiser_temps(&t);
	enigmeSlim=IMG_Load("resources/image/backgroundenigme.png");
 	/**************************************************************************************************************/

	do
	{ 
		direction = Get_EventDirection(&event);
		collision = collisionBB(p.pos,e.pos);
		deplacement=majminimap(&p,&m,direction,redimensionnement);
		/**************************************************************************************************************/
		//pour verifier si une touche de direction est activer
		if(direction == -1)
			p.key=0;
		else
		{
			p.key=1;
			p.dir=direction;
			if(direction==-2)
				*menu=0;
		}
		/**************************************************************************************************************/
		//pour gerer la condition de scrolling.
		if(deplacement)
			deplacerPerso(&p,dt);
		else
			scrolling(&b,direction);
        /**************************************************************************************************************/
	if(p.reponse==0)
    {
	En=generer();
       	while(p.etat_vie==0 && p.reponse==0)
        {
            p.reponse=afficherenigme(En,screengame);
        }
    }
       	updatePerso(&p);
		updateEnnemi(&e,p);
		/**************************************************************************************************************/
       	if(collision == 1)
		{
			e.num = 3;
			p.collision++;
			Mix_PlayChannel(-1, music1, 0);
		}
       /**************************************************************************************************************/
       //deplacer et animer l'ennemi
		//deplacerEnnemi(&e);
		deplacerIA(&e);
		animerEnnemi(&e);
		/**************************************************************************************************************/
	   //MAJ du perso et animation
		animerPerso(&p);
		
		/**************************************************************************************************************/
        
 		/**************************************************************************************************************/
        //afficher 
        afficherPerso(p,screengame);
    	afficher(b,screengame);
    	afficherEnnemi(e,screengame);
    	afficher_temps(&t, screengame);
    	afficherminimap(m, screengame);

    	/**************************************************************************************************************/
		//rafraichir
	    SDL_Delay(10);
    	SDL_Flip(screengame);
    	/**************************************************************************************************************/
    }while(direction!=-2);


    free_minimap(m);
    free_temps(&t, screengame);
	libererennemi(e);
	SDL_FreeSurface(b.imageFond);
	SDL_FreeSurface(screengame);
	SDL_FreeSurface(gameover);
	SDL_FreeSurface(enigmeSlim);
	Mix_FreeChunk(music1);
	Mix_FreeMusic(music);
	libererperso(&p);
	SDL_FreeSurface(ob.image);
	TTF_Quit();
    SDL_Quit();
}



//SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
