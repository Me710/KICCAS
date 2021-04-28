/**
 * @file ennemi.c
 * @brief Testing Program
 * @author Christian Parfait
 * @version 0.1
 * @date Apr 03, 2021
 * 
 * Testing program for Ennemi. 
 */
#include "ennemi.h"
/**
 * @brief To initialise the ennemi e
 * @param e the ennemi
 * @return Nothing
*/
void initEnnemi(ennemi *e)
{
	int j;
	char ennemiLW[30];
	char ennemiRW[30];
	char ennemiLA[30];
	char ennemiRA[30];

	e->dir = 1;
	e->speed = 6;
	e->num = 0;
	e->state=WAITING;
	e->attack=0;


	for(j=0 ; j<4 ;j++)
    { 
    	sprintf(ennemiRW,"resources/image/ER%d.png",j);
    	e->image[0][j] = IMG_Load(ennemiRW);
    	sprintf(ennemiLW,"resources/image/EL%d.png",j);
    	e->image[1][j] = IMG_Load(ennemiLW);
    	sprintf(ennemiRA,"resources/image/ERA%d.png",j);
    	e->image[2][j] = IMG_Load(ennemiRA);
    	sprintf(ennemiLA,"resources/image/ELA%d.png",j);
    	e->image[3][j] = IMG_Load(ennemiLA);
    }

    e->pos.x = 1150;
    e->pos.y = 510;
    e->pos.w = e->image[0][0]->w;
    e->pos.h = e->image[0][0]->h;
}
/**
 * @brief To show the ennemi e
 * @param e the ennemi
 * @param screen the screen
 * @return Nothing
*/
void afficherEnnemi(ennemi e, SDL_Surface *screen)
{
	if(!e.attack)
	SDL_BlitSurface(e.image[e.dir][e.num],NULL,screen,&e.pos);
    else
    {
    	if(e.dir==0)
    		SDL_BlitSurface(e.image[2][e.num],NULL,screen,&e.pos);
    	else
    		SDL_BlitSurface(e.image[3][e.num],NULL,screen,&e.pos);
    }

}
/**
 * @brief To move the ennemi e
 * @param e the ennemi
 * @return Nothing
*/
void deplacerEnnemi(ennemi *e)
{
	int limDroite = 1150;
	int limGauche = 0;

	if(e->dir == 0)
	{
		e->pos.x += e->speed;
	}
	if(e->dir == 1)
	{
		e->pos.x -= e->speed;
	}
	/*if(e->pos.x > limDroite)
	{
		e->dir = 1;
	}
	if(e->pos.x < limGauche)
	{
		e->dir = 0;
	}*/
    
}
/**
 * @brief To animate the ennemi e
 * @param e the ennemi
 * @return Nothing
*/
void animerEnnemi(ennemi *e)
{
	if(e->num == 3 /*|| e->num == 4*/)
	{
		e->num = 0;
	}
	else
	{
		e->num++;
	}
}

int collisionBb(Personne p, ennemi e)
{
        if((p.pos.x+p.pos.w < e.pos.x) || (p.pos.x > e.pos.x+e.pos.w) || (p.pos.y+p.pos.h < e.pos.y) || (p.pos.y > e.pos.y+e.pos.h))
	{
		return 0;
	}  
	else
	{
		return 1;
	}

}

int collisionBB(SDL_Rect posp, SDL_Rect pose)
{
	if((posp.x+posp.w < pose.x) || (posp.x > pose.x+pose.w) || (posp.y+posp.h < pose.y) || (posp.y > pose.y+pose.h))
	{
		return 0;
	}  
	else
	{
		return 1;
	}
}

void updateEnnemi(ennemi *e,Personne p)
{
	int d;
	int s1=800;
	int s2=100;

	//calcul de la distance qui separe l'ennemi et l'hero
	d = (e->pos.x)-(p.pos.x);

//si la distance deviens negative
if(d<0)
d=d*(-1);
	
	if(p.pos.x<e->pos.x)
	e->dir=1;
    if(p.pos.x>=e->pos.x)
    e->dir=0;

  switch(e->state)
  {
  	case WAITING:
  		if(d>=s2 && d<=s1)
  		{
  		e->state=FOLLOWING;
  		}
  	break;
  	case FOLLOWING:
  		if(0<d && d<=s2)
  		{
  			e->state=ATTACKING;
  		}
  	break;
  	case ATTACKING:
  		if(d<=10)
  		{
  			e->state=WAITING;
  			e->attack=0;
  		}

  	break;
  }

    
}

void deplacerIA(ennemi *e)
{
	switch(e->state)
	{
		case WAITING: 
		animerEnnemi(e);
		break;
		case FOLLOWING:
		animerEnnemi(e);
		deplacerEnnemi(e);
		break;
		case ATTACKING:
		e->attack=1;
		animerEnnemi(e);
		deplacerEnnemi(e); 
		break;
	}
}

void libererennemi(ennemi e)
{
	int i,j;
	for(i=0; i<4 ;i++)
	{
		for(j=0 ;j<4 ;j++)
		{
			SDL_FreeSurface(e.image[i][j]);
		}
	}
}

