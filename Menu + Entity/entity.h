// entity.h
#ifndef ENTITY_H
#define ENTITY_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <time.h>

typedef struct
{
    SDL_Surface *sheet;
    SDL_Rect posEcran,posSheet;
    int column,line;
    float width,height;
}spritesheet;

typedef struct 
{
    spritesheet *spsheet;
    int rayon,dir,dirpre,leftLine;
    Mix_Chunk *sfx;

} entity;

void initEntity(entity *e, char nom[], int x, int y, char sfxnom[], int column, int line, int leftLine, int dir);
void animerEntity( entity *e, int *currcol, int *currline);
void afficherEntity(entity *e, SDL_Surface *ecran);
int collisionTri( entity *e,  SDL_Rect pose); 
void move(entity *e, int level, SDL_Surface *ecran,  SDL_Rect pose);
int collisionBB( entity *e,  SDL_Rect pose);
void freeEntity(entity *e);
#endif /* ENTITY_H */