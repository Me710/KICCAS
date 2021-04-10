#ifndef ennemi_H_INCLUDED
#define ennemi_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

typedef struct 
{
	SDL_Surface *image[2][8];
	int speed;
	int dir;
	int num;
	SDL_Rect pos;
}ennemi;

typedef struct
{
	SDL_Surface *image;
	SDL_Rect pos;
	
}personne;

void initEnnemi(ennemi *e);
void afficherEnnemi(ennemi e, SDL_Surface *screen);
void deplacerEnnemi(ennemi *e);
void animerEnnemi(ennemi *e);
int collisionBb(personne p, ennemi e);
int collisionBB(SDL_Rect posp, SDL_Rect pose);


#endif
