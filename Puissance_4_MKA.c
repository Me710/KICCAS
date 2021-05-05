
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>

#define LARGEURG 50
#define HAUTEURG 50
#define LARGEURP 50
#define HAUTEURP 50
#define BORD 5

#define VIDE ' '
#define ROUGE 'x'
#define JAUNE 'o'

#define NB_COLONNES 7
#define NB_LIGNES 6

#define TRUE 1
#define FALSE 0

typedef struct
{
    int dg;
    int vert;
    int dd;
    int horz;
} Case;

SDL_Surface *ecran = NULL,
            *Sblanche = NULL,
            *prouge = NULL,
            *pjaune = NULL,
            *bouton[7] = {NULL};

typedef struct
{
    char blanche[NB_COLONNES][NB_LIGNES];
    int joueur;
    int G_O;
    int nbcoups;
    int humainOK;
} Jeu;

void InitSDL()
{
    int i;

    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(LARGEURG * NB_COLONNES + BORD * (NB_COLONNES - 1), 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    Sblanche = SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEURG, HAUTEURG, 32, 0, 0, 0, 0);
    SDL_FillRect(Sblanche, NULL, SDL_MapRGB(Sblanche->format, 255, 255, 255));

    prouge = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA, LARGEURP, HAUTEURP, 32, 0, 0, 0, 0);
    SDL_FillRect(prouge, NULL, SDL_MapRGB(prouge->format, 255, 0, 0));

    pjaune = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA, LARGEURP, HAUTEURP, 32, 0, 0, 0, 0);
    SDL_FillRect(pjaune, NULL, SDL_MapRGB(pjaune->format, 255, 255, 0));

    for (i = 0; i < 7; i++)
    {
        bouton[i] = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA, LARGEURG, HAUTEURG, 32, 0, 0, 0, 0);
        SDL_FillRect(bouton[i], NULL, SDL_MapRGB(bouton[i]->format, 128 - i, 128 - i, 128 - i));
    }
}

void charge_Jeu(Jeu *j)
{
    int w, h;

    for (w = 0; w < NB_COLONNES; w++)
    {
        for (h = 0; h < NB_LIGNES; h++)
        {
            j->blanche[w][h] = VIDE;
        }
    }
    j->joueur = TRUE;
    j->G_O = FALSE;
    j->nbcoups = 0;
    j->humainOK = FALSE;
    printf("Initialisation du jeu.\n");
}

int coupvalide(char blanche[NB_COLONNES][NB_LIGNES], int colonne)
{
    int y;
    int lignefree = -1;

    colonne -= 1;

    if (colonne < 0 || colonne >= NB_COLONNES)
    {
        return FALSE;
    }

    for (y = NB_LIGNES - 1; y >= 0; y--)
    {
        if (blanche[colonne][y] == VIDE)
            lignefree = y;
    }

    if (lignefree == -1)
    {
        return FALSE;
    }
    return TRUE;
}

int traiter(char blanche[NB_COLONNES][NB_LIGNES])

{
    Case game[NB_COLONNES][NB_LIGNES];
    int ligne, colonne;
    for (ligne = 0; ligne < NB_LIGNES; ligne++)
    {
        for (colonne = 0; colonne < NB_COLONNES; colonne++)
        {

            game[colonne][ligne].horz = 1;
            game[colonne][ligne].vert = 1;
            game[colonne][ligne].dg = 1;
            game[colonne][ligne].dd = 1;
        }
    }

    for (ligne = 0; ligne < NB_LIGNES; ligne++)
    {
        for (colonne = 1; colonne < NB_COLONNES; colonne++)
        {
            if ((blanche[colonne][ligne] == blanche[colonne - 1][ligne]) && (blanche[colonne][ligne] != VIDE))

            {
                game[colonne][ligne].horz = game[colonne - 1][ligne].horz + 1;
                if (game[colonne][ligne].horz == 4)
                    return TRUE;
            }
        }
    }

    for (ligne = 1; ligne < NB_LIGNES; ligne++)
    {
        for (colonne = 0; colonne < NB_COLONNES; colonne++)
        {
            if ((blanche[colonne][ligne] == blanche[colonne][ligne - 1]) && (blanche[colonne][ligne] != VIDE))

            {
                game[colonne][ligne].vert = game[colonne][ligne - 1].vert + 1;
                if (game[colonne][ligne].vert == 4)

                    return TRUE;
            }
        }
    }

    for (ligne = 1; ligne < NB_LIGNES; ligne++)
    {
        for (colonne = 0; colonne < NB_COLONNES - 1; colonne++)
        {
            if ((blanche[colonne][ligne] == blanche[colonne + 1][ligne - 1]) && (blanche[colonne][ligne] != VIDE))

            {
                game[colonne][ligne].dg = game[colonne + 1][ligne - 1].dg + 1;
                if (game[colonne][ligne].dg == 4)
                    return TRUE;
            }
        }
    }

    for (ligne = 1; ligne < NB_LIGNES; ligne++)
    {
        for (colonne = 1; colonne < NB_COLONNES; colonne++)
        {
            if ((blanche[colonne][ligne] == blanche[colonne - 1][ligne - 1]) && (blanche[colonne][ligne] != VIDE))

            {
                game[colonne][ligne].dd = game[colonne - 1][ligne - 1].dd + 1;
                if (game[colonne][ligne].dd == 4)
                    return TRUE;
            }
        }
    }
    return FALSE;
}

void joue(Jeu *j, int colonne)

{
    int lignefree = -1;
    int y;

    colonne -= 1;
    if (colonne < 0 || colonne >= NB_COLONNES)
    {
        return;
    }
    for (y = NB_LIGNES - 1; y >= 0; y--)
    {
        if (j->blanche[colonne][y] == VIDE)
            lignefree = y;
    }
    if (lignefree == -1)
    {
        return;
    }

    j->blanche[colonne][lignefree] = (j->joueur == FALSE) ? JAUNE : ROUGE;
    printf("%s a joue blanche[%d][%d]\n", (j->joueur == FALSE) ? "JAUNE" : "ROUGE", colonne + 1, lignefree + 1);
}

int joueur2IA(int quisuisje, const char blanche[NB_COLONNES][NB_LIGNES])
{
    int col;
     int once = FALSE;
    if (once == FALSE)
    {
        srand(time(NULL));
        once = TRUE;
    }
    col = (rand() % NB_COLONNES) + 1;
    return col;
}

void afficheblanche(char blanche[NB_COLONNES][NB_LIGNES])
{
    int i = 0, x, y;
    SDL_Rect position;
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    for (i = 0; i < NB_COLONNES; i++)
    {
        position.x = (LARGEURG + BORD) * i;
        position.y = 0;
        SDL_BlitSurface(bouton[i], NULL, ecran, &position);
    }

    for (x = 0; x < NB_COLONNES; x++)
    {
        for (y = 0; y < NB_LIGNES; y++)
        {
            position.x = (LARGEURG + BORD) * x;
            position.y = 480 + (HAUTEURG + BORD + (HAUTEURG + BORD) * y) * -1;
            if (blanche[x][y] != VIDE)
            {
                if (blanche[x][y] == ROUGE)
                    SDL_BlitSurface(prouge, NULL, ecran, &position);
                else
                    SDL_BlitSurface(pjaune, NULL, ecran, &position);
            }
            else
                SDL_BlitSurface(Sblanche, NULL, ecran, &position);
        }
    }
    SDL_Flip(ecran);
}

void optimasion()
{
    int i;
    printf("Cleaning...");
    SDL_FreeSurface(Sblanche);
    SDL_FreeSurface(prouge);
    SDL_FreeSurface(pjaune);
    for (i = 0; i < 7; i++)
        SDL_FreeSurface(bouton[i]);

    SDL_Quit();
    printf("Done\n");
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)

{
    int bpp = surface->format->BytesPerPixel;

    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;
    }
}

int puissance4()
{

    SDL_Event event1;
    int continuer = TRUE;
    Uint8 r, g, b, a;

    Jeu puissance4;
    int colonne;
    InitSDL();
    charge_Jeu(&puissance4);
    while (continuer)
    {
        SDL_WaitEvent(&event1);
        switch (event1.type)
        {
        case SDL_QUIT:
            continuer = FALSE;
            break;

        case SDL_KEYDOWN:
            switch (event1.key.keysym.sym)
            {
            case SDLK_F1:
                charge_Jeu(&puissance4);
                break;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            r = g = b = a = 0;
            SDL_GetRGB(getpixel(ecran, event1.button.x, event1.button.y), ecran->format, &r, &g, &b);
            if (r == g && g == b && b != 0)
            {

                if (coupvalide(puissance4.blanche, 128 - r + 1))
                {
                    colonne = 128 - r + 1;
                    puissance4.humainOK = TRUE;
                }
                else
                    printf("Coup NON Valide: %d\n", 128 - r + 1);
            }
            break;
        }
        if (puissance4.humainOK && puissance4.G_O != TRUE)
        {
            if (puissance4.joueur != TRUE)
            {
                do
                {
                    colonne = joueur2IA(puissance4.joueur, puissance4.blanche);
                } while (coupvalide(puissance4.blanche, colonne) == FALSE);
                puissance4.humainOK = FALSE;
            }
            joue(&puissance4, colonne);
            puissance4.nbcoups++;
            if (traiter(puissance4.blanche) == TRUE)
            {
                puissance4.G_O = TRUE;
                printf("Victoire de %s au %dieme coups!\n", puissance4.joueur == FALSE ? "JAUNE" : "ROUGE", puissance4.nbcoups);
            }
            else if (puissance4.nbcoups == NB_COLONNES * NB_LIGNES)
            {
                puissance4.G_O = TRUE;
                printf("Match NUL (%d coups)\n", puissance4.nbcoups);
            }
            puissance4.joueur = !puissance4.joueur;
        }
        afficheblanche(puissance4.blanche);
    }
    optimasion();
    return 0;
}

int main()
{
    puissance4();
    return 0;
}