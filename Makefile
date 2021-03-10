game : main.o intro.o fonctions.o option.o
	gcc -o game main.o fonctions.o option.o -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf


main.o : main.c
	gcc -o main.o -c main.c -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf

fonctions.o : fonctions.c
	gcc -o fonctions.o -c fonctions.c -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf

option.o : option.c
	gcc -o option.o -c option.c -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf

intro.o : intro.c
	gcc -o intro.o -c intro.c -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf

