#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "Karim_Akkari_1A30.h"

int main()
{
    int collision, distance = 100;
    SDL_Event event;
    minimap m;
    Personne p, pM, pMprochaine;
    temps t;
    SDL_Surface *screen = NULL, *imageDeFond = NULL, *masked = NULL, *chiffres[30];
    SDL_Rect position_BG, position_chiffres , position_camera;
    int longueurM = 8000, largeurM = 800, longueur = 800, largeur = 80, i = 0;
    int redimensionnement =  distance * longueur / longueurM;
    screen = SDL_SetVideoMode(1600, 800, 32, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
    TTF_Init();
    if (screen == NULL)
    {
        printf("ERREUR: %s\n", SDL_GetError());
        return 1;
    }

    position_BG.x = 0;
    position_BG.y = 0;

    imageDeFond = IMG_Load("map1.png");
    int continuer = 1;
    initmap(&m);
    initialiser_temps(&t);
    
    masked = IMG_Load("map1_masked.png");

    p.sprite = IMG_Load("Dot.png");
    p.position_perso.x = 0;
    p.position_perso.y = 40;

    pM.sprite = IMG_Load("karim.png");
    pM.position_perso.x = 0;
    pM.position_perso.y = 550;

    pMprochaine.position_perso.x = pM.position_perso.x;
    pMprochaine.position_perso.y = pM.position_perso.y;

    chiffres[1] = IMG_Load("img/1.png");
    chiffres[2] = IMG_Load("img/2.png");
    chiffres[3] = IMG_Load("img/3.png");
    chiffres[4] = IMG_Load("img/4.png");
    chiffres[5] = IMG_Load("img/5.png");
    chiffres[6] = IMG_Load("img/6.png");
    chiffres[7] = IMG_Load("img/7.png");
    chiffres[8] = IMG_Load("img/8.png");
    chiffres[9] = IMG_Load("img/9.png");
    chiffres[10] = IMG_Load("img/10.png");
    chiffres[11] = IMG_Load("img/11.png");
    chiffres[12] = IMG_Load("img/12.png");
    chiffres[13] = IMG_Load("img/13.png");

    while (continuer)
    {

        SDL_BlitSurface(imageDeFond, NULL, screen, &position_BG);
        afficherminimap(m, screen);
        SDL_BlitSurface(p.sprite, NULL, screen, &p.position_perso);
        SDL_BlitSurface(pM.sprite, NULL, screen, &pM.position_perso);
        afficher_temps(&t, screen);

        //mapCollision(Hero *entity);
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    continuer = 0;
                    break;
                case SDLK_RIGHT:
                    pMprochaine.position_perso.x += distance;
                    if (collisionPP(pMprochaine, masked) == 0)
                    { position_camera.x=0;
 
                        pM.position_perso.x = pMprochaine.position_perso.x;
                        
                        majminimap(&p,&m,position_camera,redimensionnement);
                    }
                    else
                    {  if (i==13)
                          i=0; 
                        i++;
                        pMprochaine.position_perso.x = pM.position_perso.x;
                        SDL_BlitSurface(chiffres[i], NULL, screen, &pM.position_perso);
                        SDL_Delay(300);
                    }
                    break;

                case SDLK_LEFT:
                    pMprochaine.position_perso.x -= distance;
                    if (collisionPP(pMprochaine, masked) == 0)
                    {   position_camera.x=1;
                        pM.position_perso.x = pMprochaine.position_perso.x;
                        majminimap(&p,&m,position_camera,redimensionnement);
                    }
                    else
                    {  if (i==13)
                          i=0;
                        i++;
                        pMprochaine.position_perso.x = pM.position_perso.x;
                        SDL_BlitSurface(chiffres[i], NULL, screen, &pM.position_perso);
                        SDL_Delay(300);
                    }
                break;


                    case SDLK_DOWN:
                    pMprochaine.position_perso.y += distance;
                    if (collisionPP(pMprochaine, masked) == 0)
                    {
                        position_camera.x=2;
                        pM.position_perso.y = pMprochaine.position_perso.y;
                        majminimap(&p,&m,position_camera,redimensionnement);
                    }
                    else
                    {  if (i==13)
                          i=0;
                        i++;
                        pMprochaine.position_perso.y = pM.position_perso.y;
                        SDL_BlitSurface(chiffres[i], NULL, screen, &pM.position_perso);
                        SDL_Delay(300);
                    }
                    break;



                case SDLK_UP:
                    pMprochaine.position_perso.y -= distance;
                    if (collisionPP(pMprochaine, masked) == 0)
                    {   position_camera.x=3;
                        pM.position_perso.y = pMprochaine.position_perso.y;
                        majminimap(&p,&m,position_camera,redimensionnement);
                    }
                    else
                    {   if (i==13)
                          i=0;
                        i++;
                        pMprochaine.position_perso.y = pM.position_perso.y;
                        SDL_BlitSurface(chiffres[i], NULL, screen, &pM.position_perso);
                        SDL_Delay(300);
                    }

                    break;

                case SDLK_p:
                    imageDeFond = IMG_Load("map1_masked.png");
                    break;
                case SDLK_o:
                  imageDeFond = IMG_Load("map1.png");

                }
                
            }
        }
        SDL_Flip(screen);
    }
    free_minimap(&m);
    SDL_FreeSurface(p.sprite);
    SDL_FreeSurface(chiffres[1]);
    SDL_FreeSurface(chiffres[2]);
    SDL_FreeSurface(chiffres[3]);
    SDL_FreeSurface(chiffres[4]);
    SDL_FreeSurface(chiffres[5]);
    SDL_FreeSurface(chiffres[6]);
    SDL_FreeSurface(chiffres[7]);
    SDL_FreeSurface(chiffres[8]);
    SDL_FreeSurface(chiffres[9]);
    SDL_FreeSurface(chiffres[10]);
    SDL_FreeSurface(chiffres[11]);
    SDL_FreeSurface(chiffres[12]);
    SDL_FreeSurface(chiffres[13]);
    free_temps(&t, screen);
    SDL_FreeSurface(screen);
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}
