#ifndef menu_H_INCLUDED
#define menu_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>


typedef struct {
SDL_Surface *galaxy ; // puts in galaxy
SDL_Rect galaxy_pos; // cursor pos on window
SDL_Rect animation[8];
int frame; // goes within all array0 cases
int show;
}curseur ;

void init_tab_anim(SDL_Rect* clip); //fill animation array
void initialiser (curseur *p, int xmouse, int ymouse) ;
void afficher_curseur(curseur  * p , SDL_Surface *screen);
void animation(curseur  *p);
void mvt_curseur_x(curseur *p, int xmouse);
void mvt_curseur_y(curseur *p, int ymouse);

int afficher_menu(SDL_Surface *screen);
int ecran_jeu (SDL_Surface *screen);






  #endif //
