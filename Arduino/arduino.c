#include <stdio.h>
#include <stdlib.h>
#include "arduino.h"

int arduinoWriteData(int x)
{
    char chemin[]="/dev/ttyACM0";
    FILE*f;

    f=fopen(chemin,"w");
    if(f == NULL)
        return(-1);

    fprintf(f,"%d",x);
    fclose(f);

    return(0);
}

int arduinoReadData(int *x)
{
    char chemin[]="/dev/ttyACM0";
    FILE*f;
    char c;
    f=fopen(chemin,"r");

    if(f == NULL)
        return(-1);

    fscanf(f,"%d",x);

    fclose(f);

    return(0);
}

void arduino_update(Personnage *p,buttonArduino b)
{
	/*Pour les directions:
	  buttonArduino.dir = 0: Avance (a droit)
	  buttonArduino.dir = 1: Retourne(a gauche)
	  buttonArduino.dir = 2: Saut(haut)

	  Pour l'attaque:
	  buttonArduino.attack = 0: Pas d'Attaque
	  buttonArduino.attack = 1: Attaque*/

	if(buttonArduino.dir == 0)//Button droit active
	{
		p.dir = 0;
		p.pos.x+=p.speed;
	}
	if(buttonArduino.dir == 1)//Button gauche active
	{
		p.dir = 1;
		p.pos.x+=p.speed;
	}
	if(buttonArduino.dir == 2)//Button haut active
	{
		p.dir = 2;
		p.pos.x+=p.speed;
	}
	if(buttonArduino.attack == 1)//Button attaque active
	{
		p.attack = 1;
	}
	else
	{
        p.attack = 0;
	}

}