#ifndef MANDELBROT_H
#define MANDELBROT_H

typedef struct 
{
    double re, im;
} complexe;

typedef struct 
{
    int r, g, b;
} couleur;

typedef struct 
{
    int l, h;
    double x1, y1, x2, y2;
} image;

int convergence(complexe z);
void genererImage(image im, const char *nomFichier);

#endif
