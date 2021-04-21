#include "autre.h"
#define droite 0
#define gauche 1
#define haut 2

void initObstacle(obstacle *ob)
{
    ob->image = IMG_Load("resources/image/ligne.png");
	ob->pos.x = 700;
	ob->pos.y = 250; 
	ob->pos.w = ob->image->w;
	ob->pos.h = ob->image->h;
}
void initmusic( Mix_Music **music,Mix_Chunk  **music1)
{
	Mix_AllocateChannels(2);
	*music1 = Mix_LoadWAV("resources/sound/ClicDeSouris.wav");
    *music = Mix_LoadMUS("resources/sound/cinematic music.mp3");
}

int Get_EventDirection(SDL_Event *event,int *continuer,Personne *p)
{
	int dir=-1;

	if(SDL_PollEvent(event))
		{
			switch(event->type)
			{
				case SDL_QUIT:
				*continuer = 0;
				break;
		        case SDL_KEYDOWN:
		            switch (event->key.keysym.sym) 
                    {
                    	case SDLK_RIGHT:
                    		 p->dir=0;
                    	     dir = 0; 
                    	break;
                    	case SDLK_LEFT:
                    	     p->dir=1;
                    	     dir = 1;
                    	break;
                    	case SDLK_UP:
                    	     dir = 2;
                    	break;
                    	case SDLK_ESCAPE:
                    	     *continuer=0;
                    	   break;
                    }
				break;
			}
		}

	return dir;
}