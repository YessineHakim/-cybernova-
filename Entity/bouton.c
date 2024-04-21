#include "bouton.h"
#include "background.h"

void initbouton(bouton *b[], int nbout, char *nom[],  int x[], int y[])
{

    int i;

    for (i = 0; i < nbout; i++)
    {
        b[i] = malloc(sizeof(bouton));
        if (b[i] == NULL)
        {
            fprintf(stderr, "Echec d'allocation mémoire pour le bouton %d.\n", i);
            exit(1);
        }
        b[i]->image[0] = IMG_Load(nom[2 * i]);
        b[i]->image[1] = IMG_Load(nom[2 * i + 1]);

        if (b[i]->image[0] == NULL || b[i]->image[1] == NULL)
        {
            fprintf(stderr, "Echec de chargement de l'image pour le bouton %d.\n", i);
            exit(1);
        }
        b[i]->posimg.x = x[i];
        b[i]->posimg.y = y[i];
        b[i]->posimg.w = b[i]->image[0]->w;
        b[i]->posimg.h = b[i]->image[0]->h;
        b[i]->actif = 0;
        b[i]->sfx = Mix_LoadWAV("sfx.wav");
        if (b[i]->sfx == NULL)
        {
            fprintf(stderr, "Echec de chargement du son bref : %s.\n", Mix_GetError());
            exit(1);
        }
    }
}

void afficherbouton(bouton *b[], SDL_Surface *ecran, int nbout)
{
    int i=0;

    for (i = 0; i < nbout; i++)
    {
        SDL_BlitSurface(b[i]->image[b[i]->actif], NULL, ecran, &b[i]->posimg);
    }

}
void freebouton(bouton *b[], int nbout)
{
    int i;
    for (i = 0; i < nbout; i++)
    {
        SDL_FreeSurface(b[i]->image[0]);
        SDL_FreeSurface(b[i]->image[1]);
        Mix_FreeChunk(b[i]->sfx);
        free(b[i]);
    }
}

void boutonmotion(bouton *b[], int nbout, SDL_Event *event)
{
    int x,y,j;
    switch (event->type)
    {
    case SDL_MOUSEMOTION:
        x = event->motion.x;
        y = event->motion.y;

        for (j = 0; j < nbout; j++)
        {
            if ((x >= b[j]->posimg.x) && (x <= b[j]->posimg.x + b[j]->posimg.w) && (y >= b[j]->posimg.y) && (y <= b[j]->posimg.y + b[j]->posimg.h))
            {
                if (b[j]->actif==0)
                {
                    b[j]->actif = 1;
                    Mix_PlayChannel(-1, b[j]->sfx, 0);
                }
            }
            else
            {
                b[j]->actif = 0;
            }
        }
        break;
    }
}
void mbgboutonaction(bouton *b[], SDL_Event *event, background *bg, int* niveaure)
{
    int x,y,j;
    switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:
        x = event->button.x;
        y = event->button.y;
        if (event->button.button == SDL_BUTTON_LEFT)
        {
            for (j = 0; j < 4; j++)
            {
                if ((x >= b[j]->posimg.x) && (x <= b[j]->posimg.x + b[j]->posimg.w) && (y >= b[j]->posimg.y) && (y <= b[j]->posimg.y + b[j]->posimg.h) && (bg->niveau == 0))
                {
                    if (j == 0)
                    {
                        bg->niveau = 1;
                    }
                    else if (j == 1)
                    {
                        bg->niveau = 2;
                    }
                    else if (j == 2)
                    {
                        bg->niveau = 3;
                    }
                    else if (j == 3)
                    { 
                        *niveaure=bg->niveau;
                        bg->niveau=4;
                    }
                }
            }
        }
        break;
    default:
        break;
    }
}

void obgboutonaction(SDL_Surface **ecran, bouton *b[], SDL_Event *event, int* vol, int* volre, int mu[], background *bg)
{

    int x,y,j,i;
    switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:
        x = event->button.x;
        y = event->button.y;
        if (event->button.button == SDL_BUTTON_LEFT)
        {
            for (j = 0; j < 7; j++)
            {
                if ((x >= b[j]->posimg.x) && (x <= b[j]->posimg.x + b[j]->posimg.w) && (y >= b[j]->posimg.y) && (y <= b[j]->posimg.y + b[j]->posimg.h) && (bg->niveau == 2))
                {
                    switch (j)
                    {
                    case 0:
                        bg->niveau = 0;
                        break;
                    case 1:
                        if(*vol>1)
                        {
                            Mix_VolumeMusic(Mix_VolumeMusic(-1) - (int)(0.1 * MIX_MAX_VOLUME));
                            (*vol)--;
                        }
                        else if (*vol==1)
                        {
                            Mix_VolumeMusic(0);
                            *vol=0;
                            mu[1]=1;
                        }
                        Mix_PlayChannel(-1, b[0]->sfx, 0);
                        break;
                    case 2:
                        if ((*vol==0)&&(mu[0]==1))
                        {       
                            system("amixer -D pulse sset Master 100%+ > /dev/null");
                            *vol=*volre;
                        }
                        if(*vol<10)
                        {
                            Mix_VolumeMusic(Mix_VolumeMusic(-1) + (int)(0.1 * MIX_MAX_VOLUME));
                            (*vol)++;
                            mu[1]=0;
                            mu[0]=0;
                        }
                        Mix_PlayChannel(-1, b[0]->sfx, 0);
                        break;
                    case 3:
                        if((*ecran) == SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF))
                        {
                            (*ecran) = SDL_SetVideoMode(1208, 896, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                        }
                        break;
                    case 4:
                        if((*ecran) == SDL_SetVideoMode(1208, 896, 32, SDL_HWSURFACE | SDL_DOUBLEBUF))
                        {
                            (*ecran) = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                        }
                        break;
                    case 5:
                        if (*vol!=0)
                        {
                            *volre=*vol;
                            *vol=0;
                            system("amixer -D pulse sset Master 100%- > /dev/null");
                            Mix_PlayChannel( -1,b[0]->sfx, 0 );
                            mu[0]=1;
                        }
                        else
                        {
                            if (*vol==0)
                            {
                                *vol=*volre;
                            }
                            system("amixer -D pulse sset Master 100%+ > /dev/null");
                            Mix_PlayChannel( -1,b[0]->sfx, 0 );
                            mu[0]=0;
                        }
                        break;
                    case 6:
                        if (*vol!=0)
                        {
                            *volre=*vol;
                            *vol=0;
                            Mix_VolumeMusic(0);
                            Mix_PlayChannel( -1,b[0]->sfx, 0 );
                            mu[1]=1;
                        }
                        else
                        {
                            if (*vol==0)
                            {
                                *vol=*volre;
                            }
                            Mix_VolumeMusic((int)(0.1 *(*vol)* MIX_MAX_VOLUME));
                            Mix_PlayChannel( -1,b[0]->sfx, 0 );
                            mu[1]=0;
                        }
                        break;
                    }
                }
            }
        }
        break;
    case SDL_MOUSEMOTION:
        x = event->motion.x;
        y = event->motion.y;
        for (j = 5; j < 7; j++)
        {
            if (((x >= b[j]->posimg.x) && (x <= b[j]->posimg.x + b[j]->posimg.w) && (y >= b[j]->posimg.y) && (y <= b[j]->posimg.y + b[j]->posimg.h))||(mu[j-5]==1))
            {
                if (b[j]->actif==0)
                {
                    b[j]->actif = 1;
                    Mix_PlayChannel(-1, b[j]->sfx, 0);
                }
            }
            else
            {
                b[j]->actif = 0;
            }
        }
        break;
    default:
        break;
    }
}

void cbgboutonaction(bouton *b[], SDL_Event *event, background* bg)
{
    int x,y,j;
    switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:
        x = event->button.x;
        y = event->button.y;
        if (event->button.button == SDL_BUTTON_LEFT)
        {
            for (j = 0; j < 1; j++)
            {
                if ((x >= b[j]->posimg.x) && (x <= b[j]->posimg.x + b[j]->posimg.w) && (y >= b[j]->posimg.y) && (y <= b[j]->posimg.y + b[j]->posimg.h))
                {
                    switch (j)
                    {
                    case 0:
                        bg->niveau = 0;
                        break;
                    }
                }
            }
        }
        break;
    default:
        break;
    }
}
void obgkeydown(SDL_Surface **ecran, SDL_Event *event, bouton *bo[], background *bg, int* vol, int* volre, int mu[])
{
    switch (event->type)
    {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym)
        {
        case SDLK_ESCAPE:
            bg->niveau = 0;
            break;
        case SDLK_RIGHT:
            if ((*vol==0)&&(mu[0]==1))
            {  
                system("amixer -D pulse sset Master 100%+ > /dev/null");
                *vol=*volre;
            }
            if(*vol<10)
            {
                Mix_VolumeMusic(Mix_VolumeMusic(-1) + (int)(0.1 * MIX_MAX_VOLUME));
                (*vol)++;
                mu[1]=0;
                mu[0]=0;
            }
            Mix_PlayChannel(-1, bo[0]->sfx, 0);
            break;
        case SDLK_LEFT:
            if(*vol>1)
            {
                Mix_VolumeMusic(Mix_VolumeMusic(-1) - (int)(0.1 * MIX_MAX_VOLUME));
                (*vol)--;             
            }
            else if (*vol==1)
            {
                Mix_VolumeMusic(0);
                *vol=0;
                mu[1]=1;
            }
            Mix_PlayChannel(-1, bo[0]->sfx, 0);
            break;
        case SDLK_m:
            *volre=*vol;
            *vol=0;
            system("amixer -D pulse sset Master 100%- > /dev/null");
            Mix_PlayChannel( -1,bo[0]->sfx, 0 );
            break;
        case SDLK_u:
            if (*vol==0)
            {
                *vol=*volre;
            }
            system("amixer -D pulse sset Master 100%+ > /dev/null");
            Mix_PlayChannel( -1,bo[0]->sfx, 0 );
            break;
        case SDLK_f:
            if((*ecran) == SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF))
            {
                (*ecran) = SDL_SetVideoMode(1208, 896, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
            }
            break;
        case SDLK_w:
            if((*ecran) == SDL_SetVideoMode(1208, 896, 32, SDL_HWSURFACE | SDL_DOUBLEBUF))
            {
                (*ecran) = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
            }
            break;
        }
    }
}

void qbgboutonaction(image* qt[], bouton *bq[], SDL_Event *event, background* bg, int* niveaure, int* quitter)
{
    int x,y,j;
    switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:
        x = event->button.x;
        y = event->button.y;
        if (event->button.button == SDL_BUTTON_LEFT)
        {
            for (j = 0; j < 2; j++)
            {
                if ((x >= bq[j]->posimg.x) && (x <= bq[j]->posimg.x + bq[j]->posimg.w) && (y >= bq[j]->posimg.y) && (y <= bq[j]->posimg.y + bq[j]->posimg.h))
                {
                    switch (j)
                    {
                    case 0:
                        *quitter = 0;
                        break;
                    case 1:
                        bg->niveau=*niveaure;
                        break;    
                    }
                }
            }
        }
        break;
    default:
        break;
    }
}
