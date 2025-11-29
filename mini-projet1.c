#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mini-projet1.h"

static inline void ppm_pixel(struct pixel *px, unsigned char r, unsigned char g, unsigned char b)
{
    px->r = r;
    px->g = g;
    px->b = b;
}

int pixmap_init(pixmap *mp, int l, int h)
{
    memset(mp, 0, sizeof(pixmap));
    mp->largeur = l;
    mp->hauteur = h;
    mp->intensite = 255;

    mp->pix = calloc(l * h, sizeof(struct pixel));
    if (!mp->pix) return 1;

    return 0;
}

int pixmap_release(pixmap *mp)
{
    if (!mp) return 1;

    free(mp->pix);
    mp->pix = NULL;
    mp->largeur = 0;
    mp->hauteur = 0;

    return 0;
}

void pixmap_Carre(pixmap *mp, unsigned char r, unsigned char g, unsigned char b)
{
    int n = mp->largeur * mp->hauteur;
    for (int i = 0; i < n; ++i) {
        ppm_pixel(&mp->pix[i], r, g, b);
    }
}

int pixmap_initFichier(pixmap *mp, char *path)
{
    FILE *f = fopen(path, "wb");
    if (!f){
        printf("Impossible de créer le fichier \n");
    } return 1;

    fprintf(f, "P6\n");
    fprintf(f, "%d %d\n", mp->largeur, mp->hauteur);
    fprintf(f, "255\n");

    fwrite(mp->pix, sizeof(struct pixel), mp->largeur * mp->hauteur, f);

    fclose(f);
    return 0;
}

int main()
{
    int h,l;
    h=10;
    l=10;
    pixmap *mp = malloc(sizeof(pixmap));
    pixmap_init(mp, l, h);
    pixmap_Carre(mp,255,0,0);
    pixmap_initFichier(mp, "test.ppm");

    pixmap_release(mp);
    free(mp);

    return 0;
}
