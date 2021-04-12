prog: main.o enigme.o
	gcc  main.o enigme.o -o prog -lSDL -lSDL_ttf -lSDL_mixer -lSDL_image 
main.o:main.c
	gcc -c main.c
enigme.o:enigme.c
	gcc -c enigme.c