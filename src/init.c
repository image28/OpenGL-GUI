#ifdef __APPLE__
	#include <SDL\SDL.h>
	#include <SDL\SDL_mixer.h>
#else
	//#if SDL_VERSION_ATLEAST(2,0,0)
		/* SDL 2.0 code */
		#include <SDL\SDL.h>
		#include <SDL\SDL_mixer.h>
	//#else
		/* SDL 1.2 code */
	//	#include <SDL/SDL.h>
	//	#include <SDL/SDL_mixer.h>
	//#endif
#endif

#include "stdafx.h"

#ifdef _WIN32 
	#include <windows.h>
#endif



#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	//#if SDL_VERSION_ATLEAST(2,0,0)
		/* SDL 2.0 code */
		//#include <SDL_opengl.h>
	//#else
		/* SDL 1.2 code */
	//	#include <SDL/SDL_opengl.h>
	//#endif
	//#include <GL\gl.h>
	#include <GL\gl.h>
	#include <GL/glu.h>
#endif
#include "../include/container.h"
#include "../include/init.h"

int startup(struct container *screen, int *windowed, const GLubyte *vendor, const GLubyte *renderer, const GLubyte *version, const GLubyte *extensions)
{
	int d=0;
	int bpp=32;

// SDL INIT
	if ( (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) == -1 ) ) 
	{
		printf("Could not initialize SDL: %s.\n", SDL_GetError()); 
		exit(-1);
	}
	
	//SDL_WM_SetCaption("Silverspeed","Silverspeed"); 
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(0);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,     32);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,  8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);

	if ( *(windowed) == 1 )
	{
		//screen->image = SDL_SetVideoMode(screen->area.w, screen->area.h, bpp, SDL_OPENGL|SDL_SWSURFACE|SDL_GL_DOUBLEBUFFER); 
		screen->image = SDL_CreateWindow("Launcher", 0, 0, screen->area.w, screen->area.h, SDL_WINDOW_SKIP_TASKBAR|SDL_WINDOW_BORDERLESS|SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
	}else{
		screen->image = SDL_CreateWindow("Launcher", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen->area.w, screen->area.h, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL|SDL_WINDOW_FULLSCREEN);
	}
	
	SDL_GLContext glcontext = SDL_GL_CreateContext(screen->image);
// SDL INIT	
	

	vendor=glGetString(GL_VENDOR);
	renderer=glGetString(GL_RENDERER);
	version=glGetString(GL_VERSION);
	extensions=glGetString(GL_EXTENSIONS);
	printf("VENDOR: %s\nRENDERER: %s\nVERSION: %s\n\n",vendor,renderer,version);

	printf("Availible Extensions:\n");
	for(d=0;d<strlen((const char*)(extensions));d++)
	{
		if ( *(extensions+d) == 32 )	
			printf("\n");
		else
			printf("%c",*(extensions+d));

	}printf("\n");

	/*
	if ( ! checkExt("GL_ARB_texture_non_power_of_two") )
	{
		printf("Required Graphics Card Extension Not Found\n");
		printf("GL_ARB_texture_non_power_of_two\n");
		exit(-1);
	}*/

	glViewport(0,0,screen->area.w,(int)screen->area.h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0,screen->area.w,screen->area.h,0);
	//glOrthox(0, screen->area.w, screen->area.h, 0,  -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

	return(0);
}

int isWin(SDL_Window *surface)
{
	if (SDL_GetWindowFlags(surface) & SDL_WINDOW_FULLSCREEN) 		
		return 0; 
	else
		return 1;
} 

int reload(struct container *screen, int *windowed, int win32)
{
	int bpp=32;
	int mode=0;

	printf("%dx%d %dbpp\n",screen->area.w,screen->area.h,bpp);

	if ( isWin(screen->image) )
	{
		SDL_SetWindowFullscreen(screen->image, 1);
		*(windowed)=0;
	}else{
		SDL_SetWindowFullscreen(screen->image, 0);
		*(windowed)=1;
	}

// SDL INIT	
	if ( win32 )
	{
		glViewport(0,0,screen->area.w,screen->area.h);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluOrtho2D(0,screen->area.w,screen->area.h,0);
		//glOrthox(0, screen->area.w, screen->area.h, 0, -1, 1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
	}
}
/*
int checkExt(char* name)
{
	char *list = (char*) glGetString(GL_EXTENSIONS);
	unsigned int first=0;
	
	if ( !name || !list )
		return 0;

	while(*list)
	{
		first = strcspn(list," ");

		if ( strlen(name) == first && strncmp(name,list, first) == 0 )
		{
			return 1;
		}

		list += first + 1;
	}

	return 0;
}*/
