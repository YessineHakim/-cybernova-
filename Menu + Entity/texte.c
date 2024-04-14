#include "texte.h"
#include <string.h>

void inittexte(texte *t,char message[40], int x, int y, int taille)
{
    t->postxt.x = x;
    t->postxt.y = y;
    t->font = TTF_OpenFont("Before-Modern.ttf", taille);
    if (t->font == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir la police de caractères : %s\n", TTF_GetError());
        exit(1);
    }
    t->color.r = 251;
    t->color.g = 170;
    t->color.b = 25;
    strcpy(t->texte,message);
    t->txtsurface=NULL;
}

void affichertexte(texte* t, SDL_Surface *ecran)
{
    t->txtsurface = TTF_RenderText_Solid(t->font, t->texte, t->color);
    if (t->txtsurface == NULL)
    {
        fprintf(stderr, "Impossible de rendre le texte : %s\n", TTF_GetError());
        exit(1);
    }
    SDL_BlitSurface(t->txtsurface, NULL, ecran, &t->postxt);
}

void freetexte(texte* t)
{
    if (t->txtsurface != NULL)
    {
        SDL_FreeSurface(t->txtsurface);
        t->txtsurface = NULL;
    }
    TTF_Quit();
}

void inittabtexte(texte *t[], int ntxt, int x[], int y[])
{
    int i=0;
    for (i=0; i<ntxt; i++)
    {
        t[i]=(texte*)malloc(sizeof(texte));
        inittexte(t[i],"selected",x[i],y[i],16);
    }
}

void affichermotiontexte(texte* t[], SDL_Surface *ecran, bouton *b[], int nbout)
{
    int i=0;
    for (i=0; i<nbout; i++)
    {
        if (b[i]->actif==1)
        {
            affichertexte(t[i],ecran);
        }
    }
}

void freetabtexte(texte* t[], int ntxt)
{
    int i=0;
    for (i=0; i<ntxt; i++)
    {
        if (t[i]->txtsurface != NULL)
        {
            SDL_FreeSurface(t[i]->txtsurface);
            t[i]->txtsurface = NULL;
        }
    }
    TTF_Quit();
}

