// background.h
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h> 
#include <stdlib.h> 


typedef struct {
   
    SDL_Surface *image[4];
    SDL_Rect posimg;
    int niveau ;
} background;

typedef struct 
{
    SDL_Surface *image;
    SDL_Rect posimg;

} image;

void initBackg(background *b);
void initimgs(image* im[], int nbi, char* nom[],  int x[], int y[]);
void afficherimgs(image* im[], int nbi, SDL_Surface *ecran);
void freeBack(background *b);
void afficherBack(background *b,SDL_Surface *ecran);
void initanim (image* anim[], char nom[20], int taille, int x, int y);
void freeanim (image* anim[], int taille);
void affichermusicbar(SDL_Surface *ecran, image* anim[], int vol);
void freeimgs(image* im[], int nbi, SDL_Surface *ecran);


#endif /* BACKGROUND_H */


