#include <stdio.h>
#include <math.h>
#include "mandelbrot.h"

#define largeur 900
#define hauteur 600
#define MAX_ITER 85
#define X1 -2.0
#define Y1 1.0
#define X2 1.0
#define Y2 -1.0

int convergence(complexe z)
{
    complexe u = z;
    double temp;
    for (int i = 0; i < MAX_ITER; i++)
    {
        if (u.re * u.re + u.im * u.im >= 4.0)
        {
            return i;
        }
        temp = u.re * u.re - u.im * u.im + z.re;
        u.im = 2 * u.re * u.im + z.im;
        u.re = temp;
    }
    return MAX_ITER;
}

couleur calcCouleur(int c)
{
    couleur col;
    col.r = 0;
    col.g = 3*c;
    col.b = 255;
    if (col.g >255)
    {
        col.g = 255;
    }
    
    if (c == MAX_ITER)
    {
        col.g =col.r = col.b = 255;
        return col;
    }
    return col;
}

void genererImage(image im, const char *nomFichier)
{
    FILE *f = fopen(nomFichier, "w");
    if (!f)
    {
        printf("impossible de créer le fichier.\n");
        return;
    }
    fprintf(f, "P3\n"); // <-- format texte
    fprintf(f, "%d %d\n", im.l, im.h);
    fprintf(f, "255\n");
    for (int j = 0; j < im.h; j++)
    {
        for (int i = 0; i < im.l; i++)
        {
            double x = im.x1 + i * (im.x2 - im.x1) / (im.l - 1);
            double y = im.y1 + j * (im.y2 - im.y1) / (im.h - 1);

            complexe z = {x, y};
            int c = convergence(z);
            couleur col = calcCouleur(c);

            fprintf(f, "%d %d %d ", col.r, col.g, col.b);
        }
        fprintf(f, "\n");
    }
    fclose(f);
    printf("Image générée : %s\n", nomFichier);
}
void main()
{
    image im;
    double cibleX = -0.99;
    double cibleY = 0.30;
    double zoom = 0.90;
    double x1 =X1 ,x2=X2 ,y1=Y1 ,y2=Y2;

    for (int i = 0; i < 10; i++)
    {
        im.l = largeur;
        im.h = hauteur;
        im.x1 = x1;
        im.x2 = x2;
        im.y1 = y1;
        im.y2 = y2;

        char nom[20];
        sprintf(nom,"im%d.ppm",i);
        genererImage(im,nom);


        double centreX = (x1+x2)/2;
        double centreY = (y1+y2)/2;

        centreX = centreX + (cibleX-centreX) * 0.20;
        centreY = centreY + (cibleY-centreY) * 0.20;

        double largeurX = (x2-x1)*zoom;
        double hauteurY = (y2-y1)*zoom;

        hauteurY =largeurX * (hauteur / largeur);
        
        x1 = centreX - largeurX /2;
        x2 = centreX + largeurX /2;

        y2 =centreY + hauteurY /2;
        y1 = centreY - hauteurY /2;

    }

}