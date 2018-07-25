
#include "stdafx.h"

//#include <SDL/SDL_image.h>
#include "../include/container.h"
#include "../include/draw.h"

#define MAX 11



int image(struct container *screen, struct colour colour, SDL_Rect area, char *image,int zoom, int update)
{
	int d,e;

	for(e=0;e < MAX; e++)
	{
		for(d=0; d < MAX; d++)
		{
			printf("%d",*(image+(e*d)+d));
			if ( *(image+(e*d)+d) == '1' )
			{

				//DrawPixel(screen, colour, d, e, 0);
				DrawBox(screen, colour, (d*zoom)+area.x, (e*zoom)+area.y, zoom,0);

			}

		}printf("\n");

	}printf("\n");


	//if ( update )
	//	SDL_UpdateTexture(screen->image, 1, &area,NULL);

	return(0);
}
