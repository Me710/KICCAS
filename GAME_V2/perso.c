#include "perso.h"
#include "enigmeSlim.h"

void initPerso(Personne * p)
{ 
    int j;
    char persoL[30];
    char persoR[30];
    char persoLA[30];
    char persoRA[30];

    p->dir = 0;
    p->speed = 10;
    p->num = 0;
    p->key=0;
    p->deplacement=0;
    p->reponse=0;


    for(j=0 ; j<4 ;j++)
    { 
        sprintf(persoR,"resources/image/RW%d.png",j);
        p->image[0][j] = IMG_Load(persoR);
        sprintf(persoL,"resources/image/LW%d.png",j);
        p->image[1][j] = IMG_Load(persoL);
        sprintf(persoRA,"resources/image/RA%d.png",j);
        p->image[2][j] = IMG_Load(persoRA);
        sprintf(persoLA,"resources/image/LA%d.png",j);
        p->image[3][j] = IMG_Load(persoLA);

    }

    p->pos.x = 600;
    p->pos.y = 510;
    p->pos.w = p->image[0][0]->w;
    p->pos.h = p->image[0][0]->h;

    //CHARGEMENT DES IMAGE DE VIE
    p->V[0].image=IMG_Load("resources/image/v4.png");
    p->V[1].image=IMG_Load("resources/image/v3.png");
    p->V[2].image=IMG_Load("resources/image/v2.png");
    p->V[3].image=IMG_Load("resources/image/v1.png");
    p->etat_vie=3;
    p->V[4].image=IMG_Load("resources/image/coeur.jpg");
    p->collision=0;


  //INITIALISATIONS DES POSITIONS  
    p->TEXTE[0].pos.x=5;
    p->TEXTE[0].pos.y=90;
    p->TEXTE[1].pos.x=5;
    p->TEXTE[1].pos.y=110;
    p->V[0].pos.x=5;
    p->V[0].pos.y=130;
    p->police =TTF_OpenFont("resources/p1.otf",20);    
 
  //AUTRES INITIALISATIONS
    p->acceleration=0;
    p->score=0;
    p->vie=0;
    p->sauter=-1;

}

void afficherPerso(Personne p, SDL_Surface *screen)
{
    char score[20],vie[20];
    SDL_Color couleur  = {0, 25, 255};

    sprintf(score, "SCORE:%d",p.score);
    sprintf(vie, "VIE:%d",p.vie);

p.TEXTE[0].texte=TTF_RenderText_Blended(p.police,score, couleur);
p.TEXTE[1].texte=TTF_RenderText_Blended(p.police,vie, couleur);


SDL_BlitSurface(p.TEXTE[0].texte,NULL,screen,&p.TEXTE[0].pos);
SDL_BlitSurface(p.TEXTE[1].texte,NULL,screen,&p.TEXTE[1].pos);
SDL_BlitSurface(p.image[p.dir][p.num],NULL,screen,&p.pos);
SDL_BlitSurface(p.V[p.etat_vie].image,NULL,screen,&p.V[0].pos);
SDL_Flip(screen);

}


void deplacerPerso (Personne *p,Uint32 dt)
{

//p->dx=(0.5*p->acceleration*dt*dt)+(p->vitesse*dt);//CALCUL DE LA DISTANCE ENGENDREE;
if(p->key)
{
if(p->dir==0)
p->pos.x+=p->speed;

if(p->dir==1)
p->pos.x-=p->speed;

if(p->pos.x <=0)
p->pos.x = 0;

if(p->pos.x >= 1300)
p->pos.x=1300;
}
}

void animerPerso(Personne *p)
{
if(p->key)
{
    if(p->num == 3)
    {
        p->num = 0;
    }
    else
    {
        p->num++;
    }
}
else
    p->num=0;
//SDL_Delay(20);
}

void updatePerso(Personne *p)
{
    enigme En;
    int reponse;

        if(p->collision == 30)
        {
            p->vie++;
            p->collision=0;
        }
        if(p->vie >= 5)
        {
            p->etat_vie--;
            p->vie=0;
        }
        if(p->reponse==1)
        {
            p->etat_vie++;
            p->reponse=0;
        }
}


void libererperso(Personne *p)
{
    int i, j;


    TTF_CloseFont(p->police);

    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            SDL_FreeSurface(p->image[i][j]);
        }
    }

    for(i=0;i<5;i++)
    {
        SDL_FreeSurface(p->V[i].image);
    }

        SDL_FreeSurface(p->TEXTE[0].texte);
        //SDL_FreeSurface(p->TEXTE[1].texte);

}


/*void sauter(Personne *p,SDL_Surface *screen)
{

#define SCREEN_W 800
#define SCREEN_H 400
#define POS_X 100
#define POS_Y 400

SDL_Surface *image=NULL,*obstacle=NULL;
SDL_Rect positionImage,positionObstacle;
image=IMG_Load("resources/image/b.png");
obstacle=IMG_Load("resources/image/sapin.png");
positionObstacle.x=400;
positionObstacle.y=285;

positionImage.x=0;
positionImage.y=0;

double v_x, v_y, v_grav, v_jump, v_air;
int done=1;
double b;
b=p->postion.y;
  p->postion.y=(-0.004*p->postion.x*p->postion.x)+1; ///lequation de la parabolle;
    //initialisation des vitesses 
    v_grav =0.08;//va représenter l'attraction terrestre.
    v_jump =-4;//vitesse du saut

    v_air = 1.5;//pas trop compris se que signifiait cette variable
    v_x = v_air;//vitesse de déplacement dans les airs.
    v_y = v_jump;

  
p->postion.y=b;
    while(done)
{

if(p->etat==0)
{
     v_x=v_air;
        //evolution de la position
	
	
	
        p->postion.x += v_x;
        p->postion.y += v_y;
 
        // evolution de la vitesse
        v_y += v_grav;//vitesse à la quel le personnage va latéralement monter
 
        // collisions 
        if (p->postion.y > POS_Y)//si le perso dépace une certaine hauteur alors on fait redescendre le perso
            v_y =-v_jump;
	
        if (p->postion.x < POS_X || p->postion.x > SCREEN_W - POS_X)
            v_x = -v_x;
 
 
        //dessin
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
SDL_BlitSurface(image,NULL,screen,&positionImage);
SDL_BlitSurface(obstacle,NULL,screen,&positionObstacle);
        afficherPerso(p,screen);
        SDL_Flip(screen);

if(p->postion.y==b)
{
done=0;
}
}
else if(p->etat==1)
{

v_x=-v_air;
        //evolution de la position
	
	
	
        p->postion.x += v_x;
        p->postion.y += v_y;
 
        //evolution de la vitesse
        v_y += v_grav;//vitesse à la quel le personnage va latéralement monter
 
        // collisions 
        if (p->postion.y > POS_Y)//si le perso dépace une certaine hauteur alors on fait redescendre le perso
            v_y =-v_jump;
	
        if (p->postion.x < POS_X || p->postion.x > SCREEN_W - POS_X)
            v_x = -v_x;
 
 
        // dessin
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
SDL_BlitSurface(image,NULL,screen,&positionImage);
SDL_BlitSurface(obstacle,NULL,screen,&positionObstacle);
        afficherPerso(p,screen);
        SDL_Flip(screen);
   
if(p->postion.y==b)
{
done=0;
}
}

} 
p->sauter=0;
}

*/
