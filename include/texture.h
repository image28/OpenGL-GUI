#define MAXTEXTURES 64

struct textures
{
	char name[128];
};

SDL_Surface* loadSurface(char *graphic);
int loadList(char *infile, struct textures *list, GLuint *fcount);
int SDL_GL_LoadTexture(SDL_Surface *tempSurf, GLuint *texture, GLuint *texcount, GLfloat *texcoord, int *w, int *h, int *w2, int *h2);
void makeAlpha(SDL_Surface *image1, SDL_Surface *image2);
