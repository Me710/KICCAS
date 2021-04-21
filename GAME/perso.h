#ifndef PERSO_H_INCLUDED
#define PERSO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

typedef struct
{
SDL_Surface *texte;
SDL_Rect pos;
char score[20];
char vie[20];
}text; //STRUCTURE PERMETTANT DE GERER LES TEXTES QUI DOIVENT ETRE AFFCIHÉS COMME "SCORE,VIE,OU TEMPS.....);

typedef struct
{
	SDL_Surface *image;
	SDL_Rect pos;

}vies; //gerer les images de vies.


typedef struct 
{
text TEXTE[3];
vies V[5]; //CONTIENT  LES IMAGES DES COEURS ET LEURS POSITIONS;
SDL_Surface *image[4][4];//LA MATRICE CONTENANT LES IMAGES DU PERSONNAGE PRINCIPAL;
SDL_Rect pos;
TTF_Font *police;
int score;
int collision;
int deplacement;
int vie;
int num;
int dir;
int attack;
int speed;
int key;
float acceleration,dx;
int etat_vie;
int sauter;
}Personne;


//FONCTION A DEVELOPPEES;
void initPerso(Personne *p);
void afficherPerso(Personne p, SDL_Surface *screengame);
void deplacerPerso (Personne *p,Uint32 dt);
void animerPerso (Personne* p);
void sauter(Personne* p,SDL_Surface* screen);
void updatePerso(Personne *p);
void libererperso(Personne p);

#endif // PERSO_H_INCLUDED

