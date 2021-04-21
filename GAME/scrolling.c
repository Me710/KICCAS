#include "scrolling.h"

void initBack(background *b)
{
  b->imageFond = IMG_Load("resources/image/ba.png");
  b->poscam.x = 0;
  b->poscam.y = 0;
  b->poscam.w = 1366;
  b->poscam.h = (b->imageFond->h);
  b->pos.x = 0;
  b->pos.y = 0;
  b->pos.w = b->imageFond->w;
  b->pos.h = b->imageFond->h;
  b->test=0;
}

void afficher(background b,SDL_Surface *screen)
{
  SDL_BlitSurface(b.imageFond,&b.poscam,screen,&b.pos);
}

void scrolling(background *b, int direction)
{
  if(direction != -1)
{
  if(direction == 0)
  {
    b->poscam.x+=10;
  }
  if(direction == 1)
  {
    b->poscam.x-=10;
  }
  if(direction == 2)
  {
    b->poscam.y-=0;
  }
  if(direction == 3)
  {
    b->poscam.y+=0;
  }
  if(b->poscam.x >= b->pos.w-b->poscam.w)
  {
    b->poscam.x = b->pos.w-b->poscam.w;
    b->test=1;
  }
  if(b->poscam.x <= 0)
  { 
    b->poscam.x = 0;
    b->test=1;
  }
}
}
