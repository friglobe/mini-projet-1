typedef struct 
{
    unsigned char r,g,b;

}pixel;

typedef struct
{
    int largeur, hauteur;
    pixel *pix;
} pixmap;

int pixmap_initIM(pixmap *pm, int l, int h);
void pixmap_effacer(pixmap *pm);
void pixmap_couleurPixel(pixmap *pm, int x, int y,unsigned char r,unsigned char g,unsigned char b);
int pixmap_Image(pixmap *pm, char *path);
void cercle(pixmap *pm, int cx,int cy,int r, pixel coulor, pixel fond);
