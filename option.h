#ifndef option_H_INCLUDED
#define option_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

void save_volume(int volume);
int get_volume();
int afficher_option(SDL_Surface *screen);


#endif
