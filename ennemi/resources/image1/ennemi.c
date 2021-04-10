#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "ennemi.h"

/***********-------------- ENNEMI 1------------------**************/


void initialiser_ennemi1(ennemi *en1)
{
en1->position_entite.x=2500;
en1->position_entite.y=200;
en1->position_entite.w=448;
en1->position_entite.h=373;
en1->direction=0;
	char entites[20];
	int i;
  for ( i = 0; i < 20; i++)
  {
      sprintf(entites,"ennemi/en1/%d.png",i);
    en1->affichage_secondaire[i]=IMG_Load(entites);
  }
en1->Frame=0;
en1->speed=35;
}

void initialiser_ennemi2(ennemi *en2)
{
en2->position_entite.x=3325;
en2->position_entite.y=50;
en2->position_entite.w=448;
en2->position_entite.h=373;
  char entites[20];
  int i;
  for ( i = 0; i < 20; i++)
  {
      sprintf(entites,"ennemi/en2/%d.png",i);
    en2->affichage_secondaire[i]=IMG_Load(entites);
  }
en2->Frame=0;en2->speed=35;
}

void afficher_ennemi1(ennemi en1, SDL_Surface *ecran)
{
SDL_BlitSurface(en1.affichage_secondaire[en1.Frame],NULL,ecran ,&(en1.position_entite));
} 


void afficher_ennemi2(ennemi en2, SDL_Surface *ecran)
{
SDL_BlitSurface(en2.affichage_secondaire[en2.Frame],NULL,ecran ,&(en2.position_entite));
} 


/*-- animation gauche/droite -- */

void animation_droite (ennemi *en1)
{
	if(en1->Frame<=0 || en1->Frame>=9)
	{
	//printf("hello!");
	en1->Frame=1;
	}
	en1->Frame++;
	}

/*--SCROLL--*/


void scroll_ennemi(int clic, ennemi *en1)
{


if(clic==2)//walk droite
	{
		
		en1->position_entite.x-=en1->speed;
		
	}
	else if ((clic==1)&&(en1->position_entite.x<6500))//walk gauche
	{ 
		en1->position_entite.x+=en1->speed;
		
	}
if(clic==5)//walk droite
	{
		
		en1->position_entite.x-=en1->speed+2;
		
	}
	else if ((clic==6)&&(en1->position_entite.x<6500))//walk gauche
	{ 
		en1->position_entite.x+=en1->speed+2;
		
	}

if(clic==3)
	{
		
		en1->position_entite.x-=en1->speed;
		
	}

}




int collision_enn(personnage *p, ennemi en)
{
if (((p->position_personnage.x+p->position_personnage.w>=en.position_entite.x)&&(p->position_personnage.x+p->position_personnage.w<=en.position_entite.x+en.position_entite.w))||((p->position_personnage.x>=en.position_entite.x)&&(p->position_personnage.x<=en.position_entite.x+en.position_entite.w)))
{if ((p->position_personnage.y+p->position_personnage.h>=en.position_entite.y-en.position_entite.h)&&(p->position_personnage.y<=en.position_entite.y+en.position_entite.h))
return 1;}
return 0;
}
int collision_enn2(personnage *p, ennemi en2)
{
if (((p->position_personnage.x+p->position_personnage.w>=en2.position_entite.x)&&(p->position_personnage.x+p->position_personnage.w<=en2.position_entite.x+en2.position_entite.w))||((p->position_personnage.x>=en2.position_entite.x)&&(p->position_personnage.x<=en2.position_entite.x+en2.position_entite.w)))
{if ((p->position_personnage.y+p->position_personnage.h>=en2.position_entite.y-en2.position_entite.h)&&(p->position_personnage.y<=en2.position_entite.y+en2.position_entite.h))
return 1;}
return 0;
}
/***********-------------- ENNEMI 2 ------------------**************/


/*-- animation gauche/droite -- */

void animation_droite2(ennemi *en2)
{
	if(en2->Frame<=0 || en2->Frame>=9)
	{
	//printf("hello!");
	en2->Frame=1;
	}
	en2->Frame++;

	}

/*-- SCROLL --*/

void scroll_ennemi2(int clic, ennemi *en2)
{


if(clic==2)//walk droite
	{
		
		en2->position_entite.x-=en2->speed;
		
	}
	else if ((clic==1)&&(en2->position_entite.x<6500))//walk gauche
	{ 
		en2->position_entite.x+=en2->speed;
		
	}
if(clic==5)//walk droite
	{
		
		en2->position_entite.x-=en2->speed+2;
		
	}
	else if ((clic==6)&&(en2->position_entite.x<6500))//walk gauche
	{ 
		en2->position_entite.x+=en2->speed+2;
		
	}

if(clic==3)
	{
		
		en2->position_entite.x-=en2->speed;
		
	}

}
/*
void animation_up_down (ennemi *en1)
{

  if (en1->direction==0)
  {
	if(en1->Frame<=11 || en1->Frame>=21)
		en1->Frame=12;

	en1->Frame++;
  }
else if (en1->direction==1)
  {

if(en1->Frame<=22 || en1->Frame>=30)
  en1->Frame=23;
en1->Frame++;
  }

}*/


