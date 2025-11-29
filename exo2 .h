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
    int centreX;
    int centreY;
    int rayon;
    struct pixel *pix;
} pixmap;

int pixmap_init(pixmap *mp, int l, int h);
int pixmap_release(pixmap *mp);
void pixmap_setpixel(pixmap *mp, int x,int y, unsigned char r,unsigned char g,unsigned char b);
int pixmap_dump(pixmap *mp, char* path);