#include <stdio.h>
#include <stdlib.h>
#include "exo2.h"

// INITIALISE UNE IMAGE
int pixmap_initIM(pixmap *pm, int l, int h)
{
    pm->largeur = l;
    pm->hauteur = h;

    pm->pix = malloc(l * h * sizeof(pixel));
    if (!pm->pix)
    {
        printf("echec de l'allocation de memoire\n");
        return 1;
    }

    return 0;   // <-- important !
}

// Libere l'espace
void pixmap_effacer(pixmap *pm)
{
    if (!pm) return;
    free(pm->pix);
    pm->pix = NULL;
}

// récupérer un pixel
pixel *pixmap_recupPixel(pixmap *pm, int x, int y)
{
    return &pm->pix[y * pm->largeur + x];
}

// Mettre une couleur à un pixel
void pixmap_couleurPixel(pixmap *pm, int x, int y,
                         unsigned char r,unsigned char g,unsigned char b)
{
    pixel *p = pixmap_recupPixel(pm, x, y);  // <-- corrigé
    p->r = r;
    p->g = g;
    p->b = b;
}

//creation de l'image ppm (format texte P3)
int pixmap_Image(pixmap *pm, char *path)
{
    FILE *f = fopen(path, "w");   // <-- corrigé
    if (!f)
    {
        printf("impossible de créer le fichier.\n");
        return 1;
    }

    fprintf(f, "P3\n");           // <-- format texte
    fprintf(f, "%d %d\n", pm->largeur, pm->hauteur);
    fprintf(f, "255\n");

    for (int y = 0; y < pm->hauteur; y++)
    {
        for (int x = 0; x < pm->largeur; x++)
        {
            pixel *p = pixmap_recupPixel(pm,x,y);
            fprintf(f,"%d %d %d ", p->r, p->g, p->b);  // <-- espace !
        }
        fprintf(f,"\n");
    }
    fclose(f);
    return 0;
}

//dessin du cercle
void cercle(pixmap *pm, int cx,int cy,int r, pixel couleur, pixel fond)
{
    for (int y = 0; y < pm->hauteur; y++)
    {
        for (int x = 0; x < pm->largeur; x++)
        {
            int dx = x - cx;
            int dy = y - cy;

            if(dx*dx + dy*dy <= r*r)
                pixmap_couleurPixel(pm, x, y, couleur.r, couleur.g, couleur.b);
            else
                pixmap_couleurPixel(pm, x, y, fond.r, fond.g, fond.b);
        }
    }
}

int main()
{
    pixmap pm;
    int l = 600, h = 400;

    if(pixmap_initIM(&pm, l, h))
    {
        printf("impossible d'allouer l'image \n");
        return 1;
    }

    pixel color = {255, 0, 0};
    pixel fond = {0, 0, 0};

    cercle(&pm, l/2, h/2, 100, color, fond);
    pixmap_Image(&pm, "cercle.ppm");
    pixmap_effacer(&pm);

    printf("image créée : cercle.ppm\n");
    return 0;
}
