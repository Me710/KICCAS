#include "header.h"
#include "quitter.h"

void quitter(SDL_Surface *screen, int *menu)
{
	SDL_Surface *image = NULL;
	SDL_Surface *yes[2];
	SDL_Surface *no[2];
	SDL_Rect pos,posyes,posno;
	SDL_Event event;
	int continuer = 1;
	int i;
	int y = 0;
	int n = 0;

    //mouse click sound
    Mix_Chunk *music1, *music2;
    Mix_AllocateChannels(1);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s", Mix_GetError());
    }
    music1 = Mix_LoadWAV("resources/sound/ClicDeSouris.wav");
    music2 = Mix_LoadWAV("resources/sound/ClicDeSouris2.wav");

	image = IMG_Load("resources/image/backgroundquit.png");
	yes[0] = IMG_Load("resources/image/oui_nonclique.png");
	yes[1] = IMG_Load("resources/image/oui_clique.png");
	no[0] = IMG_Load("resources/image/non_nonclique.png");
	no[1] = IMG_Load("resources/image/non_clique.png");

    pos.x = 0;
    pos.y = 0;
    posyes.x = 150;
    posyes.y = 400;
    posno.x = posyes.x+400;
    posno.y = posyes.y;

    while(continuer)
    {

    	if(SDL_PollEvent(&event))
    	{
    		switch(event.type)
    		{
    			case SDL_QUIT:
                continuer = 0;
                *menu = -1;
                break;
                case SDL_KEYDOWN:   //keyboard buttons
                switch (event.key.keysym.sym) 
                {
                	case SDLK_q:
                	continuer = 0;
                	*menu = 0;
                	break;
                	case SDLK_n:
                	continuer = 0;
                	*menu = -1;
                	break;
                	case SDLK_RIGHT: //upper arrow
                    if (y == 0 && n == 0)
                    {
                        y = 1;
                        Mix_PlayChannel(-1, music1, 0);
                        SDL_Delay(100);
                    }
                    else if (y == 1)
                    {
                        n = 1;
                        y = 0;
                        Mix_PlayChannel(-1, music1, 0);
                        SDL_Delay(100);
                    }
                    else if (n == 1)
                    {
                        n = 0;
                        y = 1;
                        Mix_PlayChannel(-1, music1, 0);
                        SDL_Delay(100);
                    }
                    break;
			/*****************************************************************************************************/
                case SDLK_LEFT: //lower arrow
                    if (y == 0 && n == 0)
                    {
                        y = 1;
                        Mix_PlayChannel(-1, music1, 0);
                        SDL_Delay(100);
                    }
                    else if (y == 1)
                    {
                        n = 1;
                        y = 0;
                        Mix_PlayChannel(-1, music1, 0);
                        SDL_Delay(100);
                    }
                    else if (n == 1)
                    {
                        n = 0;
                        y = 1;
                        Mix_PlayChannel(-1, music1, 0);
                        SDL_Delay(100);
                    }
                    break;
			/*****************************************************************************************************/
                case SDLK_RETURN: //enter
                    if (y == 1)
                    	*menu = 0;
                    if (n == 1)
                        *menu = -1;

                        Mix_PlayChannel(-1, music2, 0);

                    SDL_Delay(200);
                    continuer = 0;
                    break;
                }

    		}
    	}

    	SDL_BlitSurface(image,NULL,screen,&pos);
    	SDL_BlitSurface(yes[y],NULL,screen,&posyes);
    	SDL_BlitSurface(no[n],NULL,screen,&posno);
    	SDL_Flip(screen);

    }
    Mix_FreeChunk(music1);
    Mix_FreeChunk(music2);
    SDL_FreeSurface(image);
    for(i=0;i<2;i++)
    {
    	SDL_FreeSurface(yes[i]);
    	SDL_FreeSurface(no[i]);
    }
}
