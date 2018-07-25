
#include "stdafx.h"

#include "../include/defines.h"
#include "../include/container.h"
#include "../include/draw.h"

int R=0;
int G=255;
int B=0;

UCHAR letters[11][11][128];

int loadfont()
{
	FILE *font;
	int count=0;
	int y=0;
	int x=0;
	int eol=0;

// LOAD FONT ARRAYS

	if ((font = fopen("C:\Users\Alienware X51 R42.16\Desktop\GitProjects\SDL2-Test\font.txt", "rb")) == NULL)
	{
		printf("No Font Found\n");
		SDL_Quit();
		exit(-35);
	}
	else {
		printf("Font File Found, Loading...\n");
	}

	while ( count < 70  ) // -4
	{
		for(y=0; y < 10; y++)
		{
			for(x=0; x < 10; x++)
			{
				fread(&letters[y][x][count],1,1,font);
			}fread(&eol,1,1,font);fread(&eol,1,1,font);
		}fread(&eol,1,1,font);fread(&eol,1,1,font);
		count++;
	}

	printf("\n");

	fclose(font);
}

int alphabet(struct container *screen, struct colour colour, SDL_Rect area, int zoom, int update)
{
	int d=0;
	char text[128];

	for (d=0; d< 128; d++)
	{
		text[d]=d;
	}text[128]='\0';

	drawText(screen, colour, area, &text, zoom,  0, 0);

	if ( update )
		SDL_UpdateTexture(screen->image, 1, &area,NULL);
		//SDL_UpdateRects();
}

int drawLetter(struct container *screen, struct colour colour, SDL_Rect area, int letter, int zoom, int update)
{
	int b;
	int c;


	area.w=area.x+10;
	area.h=area.h+10;

	for(b=0; b < 11; b++ )
	{
		for(c=0; c < 11; c++)
		{
			if ( letter != 29 ) 
			{
				if ( letter != 32 )
				{
					if ( letters[b][c][letter] == '1' )
					{
						//DrawPixel(screen, colour,c+area.x,b+area.y,0);
						DrawBox(screen,colour,(c*zoom)+area.x,(b*zoom)+area.y,zoom,0);

					}
				}
			}
		}
		
	}

	//if ( update )
	//	SDL_UpdateTexture(screen->image, 1, &area,NULL);
}

int drawText(struct container *screen, struct colour colour, SDL_Rect area, char *text, int zoom, int truncate, int update)
{
	int d=0;
	int temp=0;
	int vert=1;

	temp=area.x;

	for(d=0; d < strlen(text); d++)
	{
		drawLetter(screen, colour, area, text[d],zoom,0);

		if ( truncate )
		{
			if ( area.x+(12*zoom) >= area.w ) 
			{
				d=strlen(text);
			}else{
				area.x=area.x+(12*zoom);
			}
		}else{

			area.x=area.x+(12*zoom); 

			if ( area.x+(12*zoom) > area.w )
			{
				area.x=temp;
				area.y=area.y+(12*zoom); 
				vert++;
			}
		}
	}
	
	//if ( update )
	//	SDL_UpdateTexture(screen->image, 1, &area,NULL);

}



