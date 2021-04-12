prog : main.o fonction.o option.o intro.o quitter.o gfxutils.o 
	gcc -o prog main.o fonction.o option.o intro.o quitter.o gfxutils.o -lm -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g
main.o : main.c
	gcc -o main.o -c main.c -lm -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g
fonction.o : fonction.c
	gcc -o fonction.o -c fonction.c -lm -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g
option.o : option.c
	gcc -o option.o -c option.c -lm -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g
intro.o : intro.c
	gcc -o intro.o -c intro.c -lm -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g
quitter.o : quitter.c
	gcc -o quitter.o -c quitter.c -lm -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g
gfxutils.o : gfxutils.c
	gcc -o gfxutils.o -c gfxutils.c -lm -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g

