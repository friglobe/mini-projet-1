#include <stdio.h>
#include <math.h>
#include"mandelbrot.h"

#define largeur 900
#define hauteur 600
#define MAX_ITER 85
#define X1 -2.0
#define Y1  1.0
#define X2  1.0
#define Y2 -1.0

int convergence(complexe z)
{
    complexe u =z;
    double temp;
    for (int i = 0; i < MAX_ITER; i++)
    {
        if (u.re *u.re +u.im*u.im >= 4.0)
        {
            return i;
        }
        temp = u.re*u.re -u.im*u.im+z.re;
        u.im = 2 *u.re*u.im+z.im;
        u.re =temp;
    }
    return 0;
}

couleur calcCouleur(int c)
{
    couleur col;
    col.r = 0;
    col.g = 3*c;
    if (col.g > 255)
    {
        col.g =255;
    }
    col.b = 255;
    return col;
    
}

void genererImage(image im, const char *nomFichier)
{
    FILE *f=fopen(nomFichier, "w");
    if (!f)
    {
        printf("impossible de créer le fichier.\n");
        return;
    }
    fprintf(f, "P3\n");           // <-- format texte
    fprintf(f, "%d %d\n", im.l, im.h);
    fprintf(f, "255\n");
    for (int j = 0; j < im.h; j++)
    {
        for (int i = 0; i < im.l; i++)
        {
            double x = im.x1+i*(im.x2-im.x1)/(im.l -1);
            double y = im.y1+j*(im.y2-im.y1)/(im.h-1);

            complexe z = {x, y};
            int c = convergence(z);
            couleur col = calcCouleur(c);

            fprintf(f,"%d %d %d",col.r,col.g,col.b);
        }
        fprintf(f,"\n");
    }
    fclose(f);
    printf("Image générée : %s\n",nomFichier);
}
void main()
{
    image im;

    im.l =largeur;
    im.h = hauteur;
    im.x1 = X1;
    im.x2 = X2;
    im.y1 = Y1;
    im.y2 = Y2;

    genererImage(im,"mandelbrot.ppm");
}