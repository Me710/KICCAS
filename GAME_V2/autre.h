#ifndef AUTRE_H_INCLUDED
#define AUTRE_H_INCLUDED

#include "perso.h"

typedef struct 
{
	SDL_Surface* image;
	SDL_Rect pos;

}obstacle;

void initObstacle(obstacle *ob);
void initmusic( Mix_Music **music,Mix_Chunk  **music1);
int Get_EventDirection(SDL_Event *event);

#endif