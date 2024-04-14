#include "background.h"


void initBackg(background *b)
{
    char *nom[] = {"mainback.png", "play.png", "options.png","credits.png"};
    int i;
    for (i = 0; i < 4; i++)
    {
        b->image[i] = IMG_Load(nom[i]);
        if (b->image[i] == NULL)
        {
            fprintf(stderr, "Echec de chargement de l'image : %s.\n", IMG_GetError());
            exit(1);
        }
    }
    b->posimg.x = 0;
    b->posimg.y = 0;
    b->posimg.w = b->image[0]->w;
    b->posimg.h = b->image[0]->h;
    b->niveau=0;
}

void initimgs(image* im[], int nbi, char* nom[],  int x[], int y[])
{
    int i;
    for (i = 0; i < nbi; i++)
    {
        im[i] =(image*)malloc(sizeof(image));
        if (im[i] == NULL)
        {
            fprintf(stderr, "Erreur d'allocation de mémoire pour l'image.\n");
            exit(1);
        }
        im[i]->image = IMG_Load(nom[i]);
        if (im[i]->image == NULL)
        {
            fprintf(stderr, "Echec de chargement de l'image : %s.\n", IMG_GetError());
            exit(1);
        }
        im[i]->posimg.x = x[i];
        im[i]->posimg.y = y[i];
        im[i]->posimg.w = im[i]->image->w;
        im[i]->posimg.h = im[i]->image->h;
    }
}

void afficherimgs(image* im[], int nbi, SDL_Surface *ecran)
{
    int i;
    for (i = 0; i < nbi; i++)
    {
       SDL_BlitSurface(im[i]->image, NULL, ecran, &im[i]->posimg);
    }
}

void afficherBack(background *b, SDL_Surface *ecran)
{
    if (b->niveau<4)
    {
    SDL_BlitSurface(b->image[b->niveau], NULL, ecran, &b->posimg);
    }
}

void freeBack (background *b)
{
    int i;

    for (i = 0; i < 4; i++)
    {
        SDL_FreeSurface(b->image[i]);
    }
    free(b);

}

void initanim (image* anim[], char nom[20], int taille, int x, int y)
{
    int i;
    char animnom[15];
    for (i=0; i<taille; i++)
    {
        sprintf(animnom,"%s%d.png",nom,i);
        anim[i]=(image*)malloc(sizeof(image));
        anim[i]->image=IMG_Load(animnom);
        if (anim[i]->image == NULL)
        {
            fprintf(stderr, "Echec de chargement de l'image pour animation %d.\n", i);
            exit(1);
        }
        anim[i]->posimg.x = x;
        anim[i]->posimg.y = y;
        anim[i]->posimg.w = anim[i]->image->w;
        anim[i]->posimg.h = anim[i]->image->h;
    }
}

void affichermusicbar(SDL_Surface *ecran, image* anim[], int vol)
{
    SDL_BlitSurface(anim[vol]->image, NULL, ecran, &anim[vol]->posimg);
}

void freeanim (image* anim[], int taille)
{
    int i;
    for (i = 0; i < taille; i++)
    {
        SDL_FreeSurface(anim[i]->image);
        free(anim[i]);
    }
}

void freeimgs(image* im[], int nbi, SDL_Surface *ecran)
{
    int i;
    for (i = 0; i < nbi; i++)
    {
        SDL_FreeSurface(im[i]->image);
        free(im[i]);
    }
}













