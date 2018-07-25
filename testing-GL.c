#include "include/defines.h"
#include "stdafx.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "include/gui.h"
#include "include/button.h"

#define BPP 32

//The frames per second
const int FRAMES_PER_SECOND = 20;

int main(int argc, char *argv)
{

// PROGRAM VARABLES : REQUIRED VARABLES
	SDL_Event event; 
	UINT quit=0;
	int d=0;

// PROGRAM VARABLES : TESTING VARS
	struct container screen;
	struct colour colour;
	colour.R=0;
	colour.G=0;
	colour.B=255;

	GLubyte *vendor;
	GLubyte *renderer;
	GLubyte *version;
	GLubyte *extensions;

	//The clock time when the timer started
	int startTicks = 0;

	//Keep track of the current frame
	int frame = 0;
	int x,y;
	int eol=0;
	int count=1;
	long pos=0;
	long pause=0;

// SCREEN RES : Set screen resolution ( have arguments for setting resolution
	screen.area.x=0;
	screen.area.y=0;
	screen.area.w=640;
	screen.area.h=480;
// SCREEN RES
	int windowed = 1;

	startup(&screen,&windowed,&vendor,&renderer,&version,&extensions);

	// Draw Title While loading
	SDL_GL_Enter2DMode();

	// Initialize the TTF library 
	if (TTF_Init() < 0) {
		printf("Couldn't initialize TTF: %s\n", SDL_GetError());
		fprintf(stderr, "Couldn't initialize TTF: %s\n", SDL_GetError());
		SDL_Quit();
		return(2);
	}

	struct colour fontColour;
	fontColour.R = 0;
	fontColour.G = 0;
	fontColour.B = 255;
	GLuint fontTexture[128];
	GLuint fontCount;
	int fontW[128];
	int fontH[128];
	TTF_Font *font;
	char tempText[2];

	font = TTF_OpenFont("c:\\Elements.ttf", 14);
	if (font == NULL) {
		printf("Failed to load font file\n");
		SDL_Quit();
		return(3);
	}
	else {
		TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
	}

	char testText[6] = "TEST";
	int x3 = 50;
	// Genorate font textures
	genTextTexture(&fontTexture, &tempText, &fontCount, font, fontColour, &fontW, &fontH);

	while ( ! quit )
	{

		while (SDL_PollEvent(&event))
		{
			//Get the current clock time
			startTicks = SDL_GetTicks();

			// Draw current screen

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glLoadIdentity();

			

			switch (event.type)
			{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{

				case SDLK_UP:

					break;
				case SDLK_DOWN:

					break;
				case SDLK_RIGHT:

					break;
				case SDLK_LEFT:

					break;
				case SDLK_ESCAPE: quit = 1; break;
				}
			break;

			case SDL_QUIT: quit = 1; break;
			}

			putText(screen.image, &testText, &fontTexture, &x3, &x3, &fontW, &fontH);

			//Increment the frame counter
			frame++;
			pos++;

			//If we want to cap the frame rate
			if ((get_ticks(startTicks) < 1000 / FRAMES_PER_SECOND))
			{
				//Sleep the remaining frame time
				SDL_Delay((1000 / FRAMES_PER_SECOND) - get_ticks(startTicks));
			}

			SDL_GL_SwapWindow(screen.image);
			SDL_Delay(2);
		}
		

	}	

	SDL_Quit();
	exit(0);

	return(0);
}

