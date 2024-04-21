prog: main.o background.o bouton.o texte.o entity.o
	gcc main.o background.o bouton.o texte.o entity.o -o prog -lSDL -g -lSDL_image -lSDL_ttf -lSDL_mixer -lm

main.o: main.c
	gcc -c main.c -o main.o -lSDL -g -lSDL_image -lSDL_ttf -lSDL_mixer -lm

background.o: background.c
	gcc -c background.c -o background.o -g -lSDL -g -lSDL_image -lSDL_ttf -lSDL_mixer -lm

bouton.o: bouton.c
	gcc -c bouton.c -o bouton.o -lSDL -g -lSDL_image -lSDL_ttf -lSDL_mixer -lm

texte.o: texte.c
	gcc -c texte.c -o texte.o -lSDL -g -lSDL_image -lSDL_ttf -lSDL_mixer -lm

entity.o: entity.c
	gcc -c entity.c -o entity.o -lSDL -g -lSDL_image -lSDL_ttf -lSDL_mixer -lm
