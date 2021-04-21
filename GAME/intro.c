#include "header.h"
#include "intro.h"


void intro (SDL_Surface **ecran)
{
	*ecran = SDL_SetVideoMode (1366,768,32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("KICCAS", NULL);

	SDL_Surface *logo=NULL, *embleme=NULL;
	SDL_Rect poslogo;
	poslogo.x=0;
	poslogo.y=0;
	int i=0;
	SDL_Event event;
	logo=IMG_Load ("resources/image/logo.png");
	embleme=IMG_Load ("resources/image/embleme.png");

	SDL_FillRect(*ecran, NULL, SDL_MapRGB((*ecran)->format, 0, 0, 0));

	
	while (i!=128)
	{
		SDL_SetAlpha (logo, SDL_SRCALPHA, i);
		SDL_BlitSurface(logo, NULL, (*ecran), &poslogo);
		SDL_Flip(*ecran);
		i++;
		while (SDL_PollEvent(&event))
		switch(event.type)
		 {
		 	case SDL_KEYDOWN:
		 	switch (event.key.keysym.sym)
		 	{
		 		case SDLK_ESCAPE:
		 		i=128;
		 		break;
		 	}
		 }
	}
	
	i=0;
		while (i!=128)
	{
		SDL_SetAlpha (embleme, SDL_SRCALPHA, i);
		SDL_BlitSurface(embleme, NULL,(*ecran), &poslogo);
		SDL_Flip(*ecran);
		i++;
		while (SDL_PollEvent(&event))
		switch(event.type)
		{
		 	case SDL_KEYDOWN:
		 	switch (event.key.keysym.sym)
		 	{
		 		case SDLK_ESCAPE:
		 		i=128;
		 		break;
		 	}
		 }
	}

	SDL_FreeSurface(logo);
	SDL_FreeSurface(embleme);

}
