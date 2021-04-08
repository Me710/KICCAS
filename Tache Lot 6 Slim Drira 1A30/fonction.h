#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


typedef struct{
    char question[100];
    char reponse1[100];
    char reponse2[100];
    char reponse3[100];
    int numrep;
}enigme;

enigme generer();
void afficherenigme(enigme e, SDL_Surface*ecran);


#endif // FONCTION_H_INCLUDED

