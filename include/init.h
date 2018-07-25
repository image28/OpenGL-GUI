#include "stdafx.h"

#ifdef __APPLE__
	#include <SDL\SDL.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <SDL\SDL.h>
	#include <GL\gl.h>
	
#endif

int startup(struct container *screen, int *windowed, const GLubyte *vendor, const GLubyte *renderer, const GLubyte *version, const GLubyte *extensions);
int reload(struct container *screen, int *windowed, int win32);
int checkExt(char *name);
int isWin(SDL_Window *);

