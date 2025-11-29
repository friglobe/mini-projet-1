#ifndef MINI_PROJET1_H
#define MINI_PROJET1_H

struct pixel
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

typedef struct 
{
    int largeur;
    int hauteur;
    int intensite;
    struct pixel *pix;
} pixmap;

int pixmap_initIM(pixmap *mp, int l, int h);
int pixmap_release(pixmap *mp);
void pixmap_Carre(pixmap *mp, unsigned char r, unsigned char g, unsigned char b);
int pixmap_initFichier(pixmap *mp, char* path);

#endif
