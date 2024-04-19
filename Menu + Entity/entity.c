#include "entity.h"

void initEntity(entity *e, char nom[], int x, int y, char sfxnom[], int column, int line, int leftLine, int dir)
{

    e->spsheet = malloc(sizeof(spritesheet));
    if (e->spsheet == NULL)
    {
        fprintf(stderr, "Erreur d'allocation de mémoire pour spritesheet de l'entité.\n");
        exit(1);
    }
    e->spsheet->sheet = IMG_Load(nom);
    if (e->spsheet->sheet == NULL)
    {
        fprintf(stderr, "Echec de chargement du sheet: %s.\n", IMG_GetError());
        exit(1);
    }
    e->dirpre = -1;
    e->dir = dir;
    e->leftLine = leftLine;
    e->spsheet->column = column;
    e->spsheet->line = line;

    e->spsheet->width = (float)e->spsheet->sheet->w / e->spsheet->column;
    e->spsheet->height = (float)e->spsheet->sheet->h / e->spsheet->line;

    e->spsheet->posEcran.x = x;
    e->spsheet->posEcran.y = y;
    e->spsheet->posEcran.w = e->spsheet->width;
    e->spsheet->posEcran.h = e->spsheet->height;

    e->spsheet->posSheet.x = 0;
    e->spsheet->posSheet.y = 0;
    e->spsheet->posSheet.w = e->spsheet->width;
    e->spsheet->posSheet.h = e->spsheet->height;

    e->rayon = sqrt(pow(e->spsheet->width / 2.0, 2) + pow(e->spsheet->height / 2.0, 2));

    e->sfx = Mix_LoadWAV(sfxnom);
    if (e->sfx == NULL)
    {
        fprintf(stderr, "Echec de chargement du son bref : %s.\n", Mix_GetError());
        exit(1);
    }
}

void animerEntity(entity *e, int *currcol, int *currline)
{
    if (((e->dir != e->dirpre) || (*currcol < 1)) || (*currline < 1))
    {
        if (e->dir == 0)
        {
            *currline = 1;
            *currcol = 1;
        }
        else
        {
            *currline = e->leftLine;
            *currcol = 1;
        }
    }

    if (e->dir == 0)
    {
        if (*currcol > e->spsheet->column)
        {
            *currcol = 1;
            if (*currline == e->leftLine - 1)
            {
                *currline = 1;
            }
            else
            {
                (*currline)++;
            }
        }
    }
    else
    {
        if (*currcol > e->spsheet->column)
        {
            *currcol = 1;
            if (*currline == e->spsheet->line)
            {
                *currline = e->leftLine;
            }
            else
            {
                (*currline)++;
            }
        }
    }
    /*printf("Sprite sheet width: %f, height: %f\n", e->spsheet->width, e->spsheet->height);
    printf("Current column: %d, Current line: %d\n", *currcol, *currline);
    printf("Sprite position on screen (x, y): (%d, %d)\n", e->spsheet->posEcran.x, e->spsheet->posEcran.y);
    printf("Sprite clipping position (x, y): (%d, %d)\n", e->spsheet->posSheet.x, e->spsheet->posSheet.y);*/

    e->spsheet->posSheet.x = e->spsheet->width * (*currcol - 1);
    e->spsheet->posSheet.y = e->spsheet->height * (*currline - 1);

    (*currcol)++;
}

void afficherEntity(entity *e, SDL_Surface *ecran)
{
    SDL_BlitSurface(e->spsheet->sheet, &e->spsheet->posSheet, ecran, &e->spsheet->posEcran);
    Mix_PlayChannel(-1, e->sfx, 0);
}

int collisionTri(entity *e, SDL_Rect pose)
{
    float ehalfWidth = e->spsheet->width / 2;
    float ehalfHeight = e->spsheet->height / 2;
    float ecenterX = e->spsheet->posEcran.x + ehalfWidth;
    float ecenterY = e->spsheet->posEcran.y + ehalfHeight;
    float pradius = sqrt(pow(pose.w / 2.0, 2) + pow(pose.h / 2.0, 2));
    float pcenterX = pose.x + pose.w / 2;
    float pcenterY = pose.y + pose.h / 2;

    float distanceX = fabs(ecenterX - pcenterX);
    float distanceY = fabs(ecenterY - pcenterY);

    if (distanceX <= ehalfWidth + pradius && distanceY <= ehalfHeight + pradius)
    {
        float actualDistance = sqrt(pow(distanceX, 2) + pow(distanceY, 2));
        if (actualDistance <= e->rayon + pradius)
        {
            return 1;
        }
    }
    return 0;
}

/*void move(entity *e, int level, SDL_Surface *ecran, SDL_Rect pose)
{

    float minX, maxX, deltaX;
    int PosMax, PosMin, ecranWidth = ecran->w;
    srand((unsigned int)time(NULL));
    if (level == 1)
    {
        minX = 0;
        maxX = 5;
    }
    else if (level == 2)
    {
        minX = 0;
        maxX = 10;
    }
    PosMax = ecranWidth - e->spsheet->width;
    PosMin = 0;
    deltaX = ((maxX - minX) * ((float)rand() / RAND_MAX) + minX); //* (rand() % 2 == 0 ? 1 : -1);
    if (e->spsheet->posEcran.x > pose.x)
    {
        deltaX = -deltaX;
    }
    e->dirpre = e->dir;
    if (deltaX > 0)
    {
        e->dir = 0;
    }
    else if (deltaX < 0)
    {
        e->dir = 1;
    }
    e->spsheet->posEcran.x = e->spsheet->posEcran.x + deltaX;

    if (e->spsheet->posEcran.x < PosMin)
    {
        e->spsheet->posEcran.x = PosMin;
    }
    else if (e->spsheet->posEcran.x > PosMax)
    {
        e->spsheet->posEcran.x = PosMax;
    }
}*/

void move(entity *e, int level, SDL_Surface *ecran, SDL_Rect pose)
{
    float min, max;
    int PosMax, PosMin, ecranWidth = ecran->w, pas;
    if (level == 1)
    {
        pas = 3;
        min = e->spsheet->posEcran.x - 100;
        max = e->spsheet->posEcran.x + 100;
    }
    else if (level == 2)
    {
        pas = 5;
        min = e->spsheet->posEcran.x - 180;
        max = e->spsheet->posEcran.x + 180;
    }
    PosMax = ecranWidth - e->spsheet->width;
    PosMin = 0;

    if (PosMax < max)
    {
        max = PosMax;
    }
    if (PosMin > min)
    {
        min = PosMin;
    }
    e->dirpre = e->dir;
    if (pose.x >= min && pose.x <= max)
    {
        if (e->spsheet->posEcran.x > pose.x)
        {
            e->dir = 1;
            e->spsheet->posEcran.x -= pas;
        }
        else
        {
            e->dir = 0;
            e->spsheet->posEcran.x += pas;
        }
    }
    else
    {
        if (e->dir == 0)
        {
            if (e->spsheet->posEcran.x >= PosMax)
            {
                e->dir = 1;
                e->spsheet->posEcran.x -= pas;
            }
            else
            {
                e->spsheet->posEcran.x += pas;
            }
        }
        else
        {
            if (e->spsheet->posEcran.x <= PosMin)
            {
                e->dir = 0;
                e->spsheet->posEcran.x += pas;
            }
            else
            {
                e->spsheet->posEcran.x -= pas;
            }
        }
    }
}

int collisionBB(entity *e, SDL_Rect pose)
{
    if (pose.x + pose.w < e->spsheet->posEcran.x || pose.x > e->spsheet->posEcran.x + e->spsheet->posEcran.w || pose.y + pose.h < e->spsheet->posEcran.y || pose.y > e->spsheet->posEcran.y + e->spsheet->posEcran.h)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void freeEntity(entity *e)
{
    SDL_FreeSurface(e->spsheet->sheet);
    Mix_FreeChunk(e->sfx);
    free(e->spsheet);
    free(e);
}