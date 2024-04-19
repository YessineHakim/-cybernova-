#include "background.h"
#include "bouton.h"
#include "entity.h"
#include "texte.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int quitter = 1;
    int i = 0, j = 0, vol = 5, volre, niveaure, boutpos = 0, mu[2] = {0, 0}, encurrcol = -1, encurrline = -1, boncurrcol = -1, boncurrline = -1;
    int x, y;
    background *bg = malloc(sizeof(background));
    entity *en = malloc(sizeof(entity));
    entity *bonus = malloc(sizeof(entity));
    bouton *b[4], *bo[7], *bc[1], *bq[2];
    image *musicbar[11], *mbganim[19], *obganim[36], *qt[1], *perso[1];
    SDL_Surface *ecran;
    SDL_Event event;
    SDL_Rect poseperso = {100, 400, 57, 102};
    Mix_Music *music;
    Uint32 mbgstartTime, mbgendTime, obgstartTime, obgendTime, entstartTime, entendTime, bonstartTime, bonendTime;
    texte *c = malloc(sizeof(texte));
    texte *sel[4];
    char *mbgnom[] = {"playoff.png", "playon.png", "optionsoff.png", "optionson.png", "creditsoff.png", "creditson.png", "quitoff.png", "quiton.png"};
    int mbgx[] = {20, 210, 400, 590};
    int mbgy[] = {498, 498, 498, 498};
    int mbgtxtx[] = {20, 210, 400, 590};
    int mbgtxty[] = {460, 460, 460, 460};
    char *obgnom[] = {"backoff.png", "backon.png", "-off.png", "-on.png", "+off.png", "+on.png", "fullscreenoff.png", "fullscreenon.png", "windowedoff.png", "windowedon.png", "volumeunmuted.png", "volumemuted.png", "musicunmuted.png", "musicmuted.png"};
    int obgx[] = {45, 318, 719, 50, 570, 300, 450};
    int obgy[] = {30, 250, 262, 498, 498, 498, 498};
    char *cbgnom[] = {"backoff.png", "backon.png"};
    int cbgx[] = {25};
    int cbgy[] = {30};
    char *qbg[] = {"quit.png"};
    int qimgx[] = {170};
    int qimgy[] = {140};
    char *qbgnom[] = {"qquitoff.png", "qquiton.png", "qplayoff.png", "qplayon.png"};
    int qbgx[] = {230, 420};
    int qbgy[] = {320, 320};
    char *pers[] = {"perso.png"};
    int persimgx[] = {100};
    int persimgy[] = {400};

    // Initialisation

    if (en == NULL)
    {
        fprintf(stderr, "Erreur d'allocation de mémoire pour entité.\n");
        exit(1);
    }
    TTF_Init();
    if (TTF_Init() != 0)
    {
        printf("Echec d'initialisation de SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("Echec d'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }
    else
    {
        printf("SDL est initialise avec succes.\n");
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
        ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
        if (ecran == NULL)
        {
            fprintf(stderr, "Echec de creation de la fenetre : %s.\n", SDL_GetError());
            exit(1);
        }
        inittexte(c, "cybernova", 30, 10, 32);
        inittabtexte(sel, 4, mbgtxtx, mbgtxty);
        initBackg(bg);
        initimgs(qt, 1, qbg, qimgx, qimgy);
        initanim(musicbar, "mb", 11, 357, 260);
        initanim(mbganim, "mani", 18, 0, 0);
        initanim(obganim, "opani", 36, 0, 0);
        initbouton(b, 4, mbgnom, mbgx, mbgy);
        initbouton(bc, 1, cbgnom, cbgx, cbgy);
        initbouton(bo, 7, obgnom, obgx, obgy);
        initbouton(bq, 2, qbgnom, qbgx, qbgy);
        initEntity(en, "enemy.png", 500, 375, "enemysfx.wav", 3, 8, 5, 0);
        initEntity(bonus, "bonus.png", 600, 400, "sfx.wav", 3, 4, 3, 0);
        initimgs(perso, 1, pers, persimgx, persimgy);
        music = Mix_LoadMUS("soncontinue.mp3");
        if (music == NULL)
        {
            fprintf(stderr, "Erreur de chargement de music: %s\n", Mix_GetError());
            exit(1);
        }
        Mix_PlayMusic(music, -1);
        Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
        i = 0;
        while (quitter)
        {
            mbgstartTime = SDL_GetTicks();
            obgstartTime = SDL_GetTicks();
            entstartTime = SDL_GetTicks();
            bonstartTime = SDL_GetTicks();
            afficherBack(bg, ecran);
            switch (bg->niveau)
            {
            case 0:
                SDL_BlitSurface(mbganim[i]->image, NULL, ecran, NULL);
                affichertexte(c, ecran);
                afficherbouton(b, ecran, 4);
                affichermotiontexte(sel, ecran, b, 4);
                SDL_Flip(ecran);
                mbgendTime = SDL_GetTicks();
                if (mbgendTime - mbgstartTime < 0)
                {
                    SDL_Delay(0 - (mbgendTime - mbgstartTime));
                }
                i++;
                if (i >= 18)
                {
                    i = 0;
                }
                break;
            case 1:
                /* if (collisionBB(bonus, en->spsheet->posEcran) == 1)
                 {
                     if (bonus->dir == 0)
                     {
                         bonus->spsheet->posEcran.x = en->spsheet->posEcran.x - (bonus->spsheet->width + 5);
                     }
                     if (bonus->dir == 1)
                     {
                         bonus->spsheet->posEcran.x = en->spsheet->posEcran.x + en->spsheet->posEcran.w + 5;
                     }
                 }*/
                if (collisionBB(en, poseperso) == 1)
                {
                    if (en->dir == 0)
                    {
                        en->spsheet->posEcran.x = poseperso.x - (en->spsheet->width + 5);
                    }
                    if (en->dir == 1)
                    {
                        en->spsheet->posEcran.x = poseperso.x + poseperso.w + 5;
                    }
                }
                else
                {
                    move(en, 2, ecran, poseperso);
                    // perso[0]->posimg.x += 3;
                    // poseperso.x += 3;
                }
                animerEntity(en, &encurrcol, &encurrline);
                afficherEntity(en, ecran);
                if (collisionTri(bonus, poseperso) == 1)
                {
                    if (bonus->dir == 0)
                    {
                        bonus->spsheet->posEcran.x = poseperso.x - bonus->spsheet->width;
                    }
                    if (en->dir == 1)
                    {
                        bonus->spsheet->posEcran.x = poseperso.x + poseperso.w;
                    }
                }
                else
                {
                    move(bonus, 1, ecran, poseperso);
                }
                animerEntity(bonus, &boncurrcol, &boncurrline);
                afficherEntity(bonus, ecran);
                afficherimgs(perso, 1, ecran);
                SDL_Flip(ecran);
                entendTime = SDL_GetTicks();
                if (entendTime - entstartTime < 250)
                {
                    SDL_Delay(250 - (entendTime - entstartTime));
                }
                bonendTime = SDL_GetTicks();
                if (bonendTime - bonstartTime < 200)
                {
                    SDL_Delay(200 - (bonendTime - bonstartTime));
                }
                break;
            case 2:
                SDL_BlitSurface(obganim[j]->image, NULL, ecran, NULL);
                afficherbouton(bo, ecran, 7);
                affichermusicbar(ecran, musicbar, vol);
                SDL_Flip(ecran);
                obgendTime = SDL_GetTicks();
                if (obgendTime - obgstartTime < 50)
                {
                    SDL_Delay(50 - (obgendTime - obgstartTime));
                }
                j++;
                if (j >= 36)
                {
                    j = 0;
                }
                break;
            case 3:
                afficherbouton(bc, ecran, 1);
                break;
            case 4:
                afficherimgs(qt, 1, ecran);
                afficherbouton(bq, ecran, 2);
                break;
            }
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    niveaure = bg->niveau;
                    bg->niveau = 4;
                }
                switch (bg->niveau)
                {
                case 0:
                    switch (event.type)
                    {
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                        {
                        case SDLK_ESCAPE:
                            niveaure = bg->niveau;
                            bg->niveau = 4;
                            break;
                        case SDLK_p:
                            bg->niveau = 1;
                            break;
                        case SDLK_o:
                            bg->niveau = 2;
                            break;
                        case SDLK_c:
                            bg->niveau = 3;
                            break;
                        case SDLK_q:
                            niveaure = bg->niveau;
                            bg->niveau = 4;
                            break;
                        case SDLK_RIGHT:
                            if (boutpos < 3)
                            {
                                boutpos++;
                            }
                            else
                            {
                                boutpos = 0;
                            }
                            for (i = 0; i < 4; i++)
                            {
                                b[i]->actif = 0;
                            }
                            b[boutpos]->actif = 1;
                            break;
                        case SDLK_LEFT:
                            if (boutpos > 0)
                            {
                                boutpos--;
                            }
                            else
                            {
                                boutpos = 3;
                            }
                            for (i = 0; i < 4; i++)
                            {
                                b[i]->actif = 0;
                            }
                            b[boutpos]->actif = 1;
                            break;
                        case SDLK_RETURN:
                            if (boutpos < 3)
                            {
                                bg->niveau = boutpos + 1;
                            }
                            else
                            {
                                niveaure = bg->niveau;
                                bg->niveau = 4;
                            }
                            break;
                        }
                        break;
                    }
                    boutonmotion(b, 4, &event);
                    mbgboutonaction(b, &event, bg, &niveaure);
                    break;
                case 1:
                    switch (event.type)
                    {
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                        {
                        case SDLK_ESCAPE:
                            bg->niveau = 0;
                            break;
                        }
                        break;
                    }
                    break;
                case 2:
                    obgkeydown(&ecran, &event, bo, bg, &vol, &volre, mu);
                    boutonmotion(bo, 5, &event);
                    obgboutonaction(&ecran, bo, &event, &vol, &volre, mu, bg);
                    break;
                case 3:
                    switch (event.type)
                    {
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                        {
                        case SDLK_ESCAPE:
                            bg->niveau = 0;
                            break;
                        }
                        break;
                    }
                    boutonmotion(bc, 1, &event);
                    cbgboutonaction(bc, &event, bg);
                    break;
                case 4:
                    switch (event.type)
                    {
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                        {
                        case SDLK_ESCAPE:
                            bg->niveau = niveaure;
                            break;
                        case SDLK_y:
                            quitter = 0;
                            break;
                        case SDLK_n:
                            bg->niveau = niveaure;
                            break;
                        }
                        break;
                    }
                    boutonmotion(bq, 2, &event);
                    qbgboutonaction(qt, bq, &event, bg, &niveaure, &quitter);
                    break;
                }
            }
            SDL_Flip(ecran);
        }
    }
    freetexte(c);
    freetabtexte(sel, 4);
    freeBack(bg);
    freebouton(b, 4);
    freebouton(bo, 7);
    freebouton(bc, 1);
    freeanim(musicbar, 11);
    freeanim(mbganim, 18);
    freeanim(obganim, 36);
    freeanim(qt, 1);
    freeimgs(qt, 1, ecran);
    freeimgs(perso, 1, ecran);
    freeEntity(en);
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}
