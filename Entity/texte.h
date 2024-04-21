#ifndef Texte_H 
#define Texte_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "bouton.h"

typedef struct 
{
    SDL_Rect postxt;
    TTF_Font* font;
    SDL_Color color;
    SDL_Surface* txtsurface;
    char texte[40];
}texte;

void inittexte(texte *t,char message[40], int x, int y, int taille);
void affichertexte(texte* t, SDL_Surface *ecran);
void freetexte(texte* t);
void inittabtexte(texte *t[], int ntxt, int x[], int y[]);
void freetabtexte(texte* t[], int ntxt);
void affichermotiontexte(texte* t[], SDL_Surface *ecran, bouton *b[], int nbout);

#endif /* TEXTE_H */
