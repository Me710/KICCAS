#ifndef ARDUINO_H_INCLUDED
#define ARDUINO_H_INCLUDED


typedef struct 
{
	int dir;
	int attack;
	
}buttonArduino;

int arduinoWriteData(int x);
int arduinoReadData(int *x);
void arduino_update(Personnage p,buttonArduino b);

#endif