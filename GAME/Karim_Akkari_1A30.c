#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

#include "Karim_Akkari_1A30.h"


void initmap(minimap *m)
{
    m->position_mini.x = 0;
    m->position_mini.y = 0;
    m->sprite = NULL;
    m->sprite = IMG_Load("resources/image/minimap1.png");
    m->dot = IMG_Load("resources/image/Dot.png");
    m->posdot.x = 58;
    m->posdot.y = 38;
    m->deplacement=0;
}

void afficherminimap(minimap m, SDL_Surface *screen)
{
    SDL_BlitSurface(m.sprite, NULL, screen, &m.position_mini);
    SDL_BlitSurface(m.dot,NULL,screen,&m.posdot);
}
void free_minimap(minimap m)
{
    SDL_FreeSurface(m.sprite);
    SDL_FreeSurface(m.dot);
}

void initialiser_temps(temps *t)
{
    t->texte = NULL;
    t->position.x = 1000;
    t->position.y = 30;
    t->police = NULL;
    t->police = TTF_OpenFont("resources/avocado.ttf", 40);
    strcpy(t->entree, "");
    (t->secondesEcoulees) = 0;
    time(&(t->t1)); //temps du debut
}

void afficher_temps(temps *t, SDL_Surface *screen)
{
    SDL_Color couleurnoir = {0, 0, 0};
    
    time(&(t->t2)); // temps actuel

    t->secondesEcoulees = t->t2 - t->t1;

    t->min = ((t->secondesEcoulees / 60) % 60);
    t->sec = ((t->secondesEcoulees) % 60);
    int millisecondes=SDL_GetTicks()%60;
    
    sprintf(t->entree, "%02d:%02d:%02d", t->min, t->sec, millisecondes);

    t->texte = TTF_RenderText_Blended(t->police, t->entree, couleurnoir);

    SDL_BlitSurface(t->texte, NULL, screen, &(t->position)); /* Blit du texte */
}

void free_temps(temps *t, SDL_Surface *screen)
{
    SDL_FreeSurface(t->texte);
    TTF_CloseFont(t->police);
}

SDL_Color GetPixel(SDL_Surface *Background, int x, int y)
{

    SDL_Color color;
    Uint32 col = 0;
    //Determine position

    char *pixelPosition = (char *)Background->pixels;
    //Offset by Y
    pixelPosition += (Background->pitch * y);
    //Offset by X
    pixelPosition += (Background->format->BytesPerPixel * x);
    //Copy pixel data
    memcpy(&col, pixelPosition, Background->format->BytesPerPixel);
    //Convert to color
    SDL_GetRGB(col, Background->format, &color.r, &color.g, &color.b);

    return (color);
}

int collisionPP(Personne p, SDL_Surface *Masque)
{
    SDL_Color test, couleurnoir = {0, 0, 0};

    SDL_Rect pos[8];
    pos[0].x = p.pos.x;
    pos[0].y = p.pos.y;
    pos[1].x = p.pos.x + p.pos.w / 2;
    pos[1].y = p.pos.y;
    pos[2].x = p.pos.x + p.pos.w;
    pos[2].y = p.pos.y;
    pos[3].x = p.pos.x;
    pos[3].y = p.pos.y + p.pos.h / 2;
    pos[4].x = p.pos.x;
    pos[4].y = p.pos.y + p.pos.h;
    pos[5].x = p.pos.x + p.pos.w / 2;
    pos[5].y = p.pos.y + p.pos.h;
    pos[6].x = p.pos.x + p.pos.w;
    pos[6].y = p.pos.y + p.pos.h;
    pos[7].x = p.pos.x + p.pos.w;
    pos[7].y = p.pos.y + p.pos.h / 2;
    int collision = 0, x, y;

    for (int i = 0; i < 8 && collision == 0; i++)
    {
        x = pos[i].x;
        y = pos[i].y;
        test = GetPixel(Masque, x, y);
        if (test.r == 0 && test.g == 0 && test.b == 0)
            collision = 1;
    }
    return collision;
}
void majminimap (Personne *p, minimap *m ,int camera ,int redimensionnement)
{
    if(camera != -1)
    {
        if (camera==0)
        m->posdot.x+=redimensionnement;

        else if (camera==1)
        m->posdot.x-=redimensionnement;

        else if(camera==2)
        m->posdot.y-=redimensionnement;

        //si on arrive a la fin de l'ecran
        if(m->posdot.x>=814)
            m->posdot.x=814;
        if(m->posdot.x<=58)
            m->posdot.x=58;

        if(m->posdot.x<=0)
          m->posdot.x=0;
        if(m->posdot.y>=890)
          m->posdot.y=890;
    }
}

/*



  if(m->posdot.x>=814 && p->key==0)
  {
    //m->posdot.x=814;
    p->key=1;
    camera=0;
  }

  if(m->posdot.x <= 58 || m->posdot.x >= 813)
    m->deplacement = 1;
  else
    m->deplacement = 0;*/