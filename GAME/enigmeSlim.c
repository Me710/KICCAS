#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>  //celle de la fonction random
#include <math.h> /* déclare des fonctions mathématiques. Tous les paramètres et résultats sont du type double; les angles sont indiqués en radians. */


#include "enigmeSlim.h"

enigme generer()
{

    enigme e;
    int x, y;
    float s,w,a;
    char opera[4]="+-/*";  //tableau d'operateurs
    srand(time(NULL));  // initialize random seed
    int i=rand()%4;
    e.numrep=rand()%3;
    int z=1+rand()%4; /* 1 lel 4 */ 
    int n=1+rand()%4;	
    x=rand()%101;
    y=1+rand()%101;    

   if(i==0)
    {
        s=(x)+(y); //correcte
        w=s-z; //fausse 1 
        a=s+n; //fausse 2
        sprintf(e.question,"Quelle est la reponse de cette operation %d %c %d : ",x,opera[i],y);
    }
    if(i==1)
    {
        s=(x)-(y);
        w=s-n;
        a=s+z;
        sprintf(e.question,"Quelle est la reponse de cette operation %d %c %d : ",x,opera[i],y);
    }
    if(i==2)
    {

        s=(float)x/y;
        w=s-1;
        a=s+1;
        sprintf(e.question,"Quelle est la reponse de cette operation %d %c %d : ",x,opera[i],y);

    }
    if(i==3)
    {
        s=x*y;
        w=s-n;
        a=s+z;
        sprintf(e.question,"Quelle est la reponse de cette operation %d %c %d : ",x,opera[i],y);
    }

    switch (e.numrep)   //changement de l'ordre de toutes les reponses
    {
    case 0:
        sprintf(e.reponse1,"Reponse 1 : %.1f",s);
        sprintf(e.reponse2,"Reponse 2 : %.1f",w);
        sprintf(e.reponse3,"Reponse 3 : %.1f",a);
        break;
    case 1:
        sprintf(e.reponse1,"Reponse 1 : %.1f",w);
        sprintf(e.reponse2,"Reponse 2 : %.1f",s);
        sprintf(e.reponse3,"Reponse 3 : %.1f",a);
        break;
    case 2:
        sprintf(e.reponse1,"Reponse 1 : %.1f",a);
        sprintf(e.reponse2,"Reponse 2 : %.1f",w);
        sprintf(e.reponse3,"Reponse 3 : %.1f",s);
        break;
    }

    return e;
}

int afficherenigme(enigme e, SDL_Surface*ecran){

	SDL_Surface *menu=NULL, *question=NULL, *resultat1=NULL, *resultat1a=NULL, *resultat2=NULL, *resultat2a=NULL, *resultat3=NULL, *resultat3a=NULL, *reponsef=NULL, *reponsev=NULL;
	SDL_Rect positionmenu, positionenigme, positionresultat1, positionresultat2, positionresultat3, positionvrai, positionfaux, positionrep, positionreponsef, positionreponsev, positioncasevide1, positioncasevide2, positioncasevide3;
	SDL_Event event;
        SDL_Surface *couche[2], *casevide=NULL;
	TTF_Font *policetexte=NULL;
	SDL_Color couleurnoire={0,0,0};
	int continuer=1;
	e=generer();
	int choix, v;
	int score=100;
	TTF_Init();
	SDL_Init(SDL_INIT_VIDEO);
	//ecran=SDL_SetVideoMode(600,399,32,SDL_HWSURFACE | SDL_DOUBLEBUF);

        couche[0] = IMG_Load("resources/image/casevrai.png");
        couche[1] = IMG_Load("resources/image/casefaux.png");
	casevide = IMG_Load("resources/image/casevide.png");
		
		

	policetexte=TTF_OpenFont("resources/KaushanScript-Regular.ttf",23);
	question=TTF_RenderText_Blended(policetexte,e.question,couleurnoire);

	resultat1=TTF_RenderText_Blended(policetexte,e.reponse1,couleurnoire);
	
	resultat2=TTF_RenderText_Blended(policetexte,e.reponse2,couleurnoire);
	
	resultat3=TTF_RenderText_Blended(policetexte,e.reponse3,couleurnoire);
	
	reponsef=TTF_RenderText_Blended(policetexte,"Mauvaise Reponse :(",couleurnoire);	
	reponsev=TTF_RenderText_Blended(policetexte,"Bonne Reponse !",couleurnoire);

	menu=IMG_Load("resources/image/tache.png");

	positionmenu.x=0;
	positionmenu.y=0;
	SDL_BlitSurface(menu,NULL,ecran,&positionmenu);
    //disposition
	positioncasevide1.x=125;
	positioncasevide1.y=135;

	positioncasevide2.x=125;
	positioncasevide2.y=185;
	
	positioncasevide3.x=125;
	positioncasevide3.y=235;

	positionvrai.x = 125;  //tick
    positionfaux.x = 125;   //croix rouge

	positionenigme.x=80;  //question
	positionenigme.y=100;
	
	positionresultat1.x=205;
	positionresultat1.y=150;

	positionresultat2.x=205;
	positionresultat2.y=200;

	positionresultat3.x=205;
	positionresultat3.y=250;

	positionreponsef.x=180;   //mauvaise reponse :(
	positionreponsef.y=300;
 
	positionreponsev.x=195;   //bonne reponse !
	positionreponsev.y=300;
 
        
         switch(e.numrep)
         {
            case 0:
             positionvrai.y = positionresultat1.y-15;   //tick est lié a la reponse juste et -15 car il faut dans le carré vide exacte
            break;
            case 1:
             positionvrai.y = positionresultat2.y-15;
            break;
            case 2:
             positionvrai.y = positionresultat3.y-15;   
	    break;	
         }

	//while(continuer!=0){
	
	if(SDL_PollEvent(&event)){
	switch(event.type){
		case SDL_QUIT:
            	continuer = 0;
              	break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
				case SDLK_KP1: case SDLK_a:
				choix=0;
                                positionfaux.y =positionresultat1.y-15;

				if(choix!=e.numrep){
				score--;
                		v = 1;
                		positionrep = positionfaux;
				SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);
					return 0;
				}
				else{
                		v = 0;  
				score++;
                		positionrep = positionvrai;
				SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);
				SDL_BlitSurface(reponsev,NULL,ecran,&positionreponsev);
				SDL_Flip(ecran);    //mise a jour de l'ecran
				SDL_Delay(1000);
						return 1;
        			}
			if(v!=0){

				SDL_BlitSurface(reponsef,NULL,ecran,&positionreponsef);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				 v=0;				// si rep fausse on affiche tick sur la bonne reponse
				SDL_BlitSurface(couche[v],NULL,ecran,&positionvrai);
				SDL_Flip(ecran);
				SDL_Delay(1000);  
				}

				 continuer=0;
				
				break;
				case SDLK_KP2: case SDLK_b:
				choix=1;
                                positionfaux.y =positionresultat2.y-15;


				if(choix!=e.numrep){
				score--;
                		v = 1;
                		positionrep = positionfaux;
				SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);
					return 0;
				}
				else{
               			 v = 0;
				score++;
                		positionrep = positionvrai;
				SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);
				
				
				SDL_BlitSurface(reponsev,NULL,ecran,&positionreponsev);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				   			return 1;
        			}
			if(v!=0){

				SDL_BlitSurface(reponsef,NULL,ecran,&positionreponsef);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				v=0;				
				SDL_BlitSurface(couche[v],NULL,ecran,&positionvrai);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				}

				continuer=0;

				break;
				case SDLK_KP3: case SDLK_c:
				choix=2;
                                positionfaux.y =positionresultat3.y-15;

				if(choix!=e.numrep){
				score--;
                		v = 1;
                		positionrep = positionfaux;
				SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);
					return 0;
				}
				else{
                		v = 0;
				score++;
                		positionrep = positionvrai;
				SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);
				
				SDL_BlitSurface(reponsev,NULL,ecran,&positionreponsev);
				SDL_Flip(ecran);
				SDL_Delay(1000);
						return 1;
        			}
			if(v!=0){

				
				SDL_BlitSurface(reponsef,NULL,ecran,&positionreponsef);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				v=0;				
				SDL_BlitSurface(couche[v],NULL,ecran,&positionvrai);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				}
				
				continuer=0;
				
				break;		
			} 
		break;
		case SDL_MOUSEBUTTONDOWN:
		if(event.button.button == SDL_BUTTON_LEFT){
			if((event.button.x >= 125 && event.button.x <= 170) && (event.button.y >= 135 && event.button.y <= 184))
                 	{
				choix=0;
                                positionfaux.y =positionresultat1.y-15;


				if(choix!=e.numrep){
				score--;
                		v = 1;
                		positionrep = positionfaux;
				SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);
					return 0;
				}
				else{
                		v = 0;
				score++;
                		positionrep = positionvrai;
				SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);
				
				SDL_BlitSurface(reponsev,NULL,ecran,&positionreponsev);
				SDL_Flip(ecran);
				SDL_Delay(1000);
							return 1;
        			}
				if(v!=0){

				
				SDL_BlitSurface(reponsef,NULL,ecran,&positionreponsef);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				v=0;				
				SDL_BlitSurface(couche[v],NULL,ecran,&positionvrai);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				}
			continuer=0;
				
			}
			if((event.button.x >= 125 && event.button.x <= 170) && (event.button.y >= 185 && event.button.y <= 234))
                 	{
				choix=1;
                                positionfaux.y =positionresultat2.y-15;


				if(choix!=e.numrep){
				score--;
                		v = 1;
                		positionrep = positionfaux;
				SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);
					return 0;
				}
				else{
               			 v = 0;
				score++;
                		positionrep = positionvrai;
				SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);
				
				SDL_BlitSurface(reponsev,NULL,ecran,&positionreponsev);
				SDL_Flip(ecran);
				SDL_Delay(1000);
						return 1;
        			}
				if(v!=0){

				
				SDL_BlitSurface(reponsef,NULL,ecran,&positionreponsef);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				v=0;				
				SDL_BlitSurface(couche[v],NULL,ecran,&positionvrai);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				}
			continuer=0;
				
			}
			if((event.button.x >= 125 && event.button.x <= 170) && (event.button.y >= 235 && event.button.y <= 285))
                 	{
				choix=2;
                                positionfaux.y =positionresultat3.y-15;


				if(choix!=e.numrep){
				score--;
                		v = 1;
                		positionrep = positionfaux;
				SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);
						return 0;
				}
				else{
                		v = 0;
				score++;
                		positionrep = positionvrai;
				SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);
				
				
				SDL_BlitSurface(reponsev,NULL,ecran,&positionreponsev);
				SDL_Flip(ecran);
				SDL_Delay(1000);
							return 1;
        			}
				if(v!=0){

				
				SDL_BlitSurface(reponsef,NULL,ecran,&positionreponsef);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				v=0;				
				SDL_BlitSurface(couche[v],NULL,ecran,&positionvrai);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				}
			     continuer=0;
			}


		}
		break;
	}
	}


	SDL_BlitSurface(casevide,NULL,ecran,&positioncasevide1);
	SDL_BlitSurface(casevide,NULL,ecran,&positioncasevide2);
	SDL_BlitSurface(casevide,NULL,ecran,&positioncasevide3);
	SDL_BlitSurface(question,NULL,ecran,&positionenigme);
	SDL_BlitSurface(resultat1,NULL,ecran,&positionresultat1);
	SDL_BlitSurface(resultat2,NULL,ecran,&positionresultat2);
	SDL_BlitSurface(resultat3,NULL,ecran,&positionresultat3);
	SDL_Flip(ecran);
	return -1;
		

TTF_CloseFont(policetexte);
TTF_Quit;
SDL_FreeSurface(couche[0]);
SDL_FreeSurface(couche[1]);
SDL_FreeSurface(question);
SDL_FreeSurface(resultat1);
SDL_FreeSurface(resultat2);
SDL_FreeSurface(resultat3);
//SDL_Quit();
}


