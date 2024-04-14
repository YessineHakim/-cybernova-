#ifndef BOUTON_H
#define BOUTON_H

#include "background.h"
#include <SDL/SDL.h>

typedef struct {
    SDL_Surface *image[2];
    SDL_Rect posimg;
    int actif;
    Mix_Chunk *sfx;  
} bouton;

void initbouton(bouton *b[], int nbout, char *nom[],  int x[], int y[]);
void freebouton(bouton *b[], int nbout) ;
void afficherbouton(bouton *b[], SDL_Surface *ecran, int nbout);
void boutonmotion(bouton *b[], int nbout, SDL_Event *event);
void mbgboutonaction(bouton *b[], SDL_Event *event, background *bg, int* niveaure);
void obgboutonaction(SDL_Surface **ecran, bouton *b[], SDL_Event *event, int* vol, int* volre, int mu[], background *bg);
void cbgboutonaction(bouton *b[], SDL_Event *event, background* bg);
void obgkeydown(SDL_Surface **ecran, SDL_Event *event, bouton *bo[], background *bg, int* vol, int* volre, int mu[]);
void qbgboutonaction(image* qt[], bouton *bq[], SDL_Event *event, background* bg, int* niveaure, int* quitter);
#endif /* BOUTON_H */

