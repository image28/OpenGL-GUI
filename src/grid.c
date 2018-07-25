
#include "stdafx.h"

#include "../include/container.h"
#include "../include/draw.h"
#include "../include/grid.h"
#include "../include/frame.h"

int drawGrid(struct container *screen, struct gridDef box)
{
	struct frameDef box2;

	int R=0;
	int G=255;
	int B=0;

	int x,y;
	int yoccured=0;
	int xoccured=0;

	box2.update=0;	
	box2.zoom=1;
	box2.frametype=0;

	box2.frame_colour.R=box.frame_colour.R;
	box2.frame_colour.G=box.frame_colour.G;
	box2.frame_colour.B=box.frame_colour.B;

	box2.area.x=box.area.x;
	box2.area.w=box.area.w;
	box2.area.y=box.area.y;
	box2.area.h=box.area.h;

	if ( box.frame )
		DrawFrame(screen, box2);

	for(y=box.area.y; y < box.area.h; y++ )
	{
		for(x=box.area.x; x < box.area.w; x++ )
		{
			if ( box.lines )
			{
				if ( ( (y-box.area.y)-(box.ydivide*yoccured) ) == box.ydivide )
				{
					DrawPixel(screen, box.grid_colour, x, y,0);	
					if ( x == (box.area.w-1) )
						yoccured++;
				}
				else if ( ( (x-box.area.x) - (box.xdivide*xoccured) ) == box.xdivide )
				{
					DrawPixel(screen, box.grid_colour, x, y,0);
					xoccured++;
				
				}
			}else{
				if ( ( ( (y-box.area.y)-(box.ydivide*yoccured) ) == box.ydivide ) &&  ( ( (x-box.area.x) - (box.xdivide*xoccured) ) == box.xdivide ) )
				{
					DrawPixel(screen, box.grid_colour, x, y,0);	
					xoccured++;
				}				
				else if ( ( (y-box.area.y)-(box.ydivide*yoccured) ) == box.ydivide )
				{
					if ( x == (box.area.w-1) )
						yoccured++;
				}
				else if ( ( (x-box.area.x) - (box.xdivide*xoccured) ) == box.xdivide )
				{
					xoccured++;
				}
			}

		}xoccured=0;
	}

	if ( box.update )	
		SDL_UpdateTexture(screen->image, 1, &box.area,NULL);

	return(0);
}
/*
int draw3dGrid(struct container *screen, struct colour colour, SDL_Rect area, int xdivide, int ydivide, int lines, int vertrot, int update)
{
	int R=0;
	int G=255;
	int B=0;

	int x,y;
	int yoccured=0;
	int xoccured=0;

	DrawFrame(screen, colour, area,0,1,0);

	for(y=area.y; y < area.h; y++ )
	{
		for(x=area.x; x < area.w; x++ )
		{
			if ( lines )
			{
				if ( ( (y-area.y)-(ydivide*yoccured) ) == ydivide )
				{
					DrawPixel(screen, colour, x, y,0);	
					if ( x == (area.w-1) )
						yoccured++;
				}
				else if ( ( (x-area.x) - (xdivide*xoccured) ) == xdivide )
				{
					DrawPixel(screen, colour, x, y,0);
					xoccured++;
				
				}
			}else{
				if ( ( ( (y-area.y)-(ydivide*yoccured) ) == ydivide ) &&  ( ( (x-area.x) - (xdivide*xoccured) ) == xdivide ) )
				{
					DrawPixel(screen, colour, x, y,0);	
					xoccured++;
				}				
				else if ( ( (y-area.y)-(ydivide*yoccured) ) == ydivide )
				{
					if ( x == (area.w-1) )
						yoccured++;
				}
				else if ( ( (x-area.x) - (xdivide*xoccured) ) == xdivide )
				{
					xoccured++;
				}
			}

		}xoccured=0;
	}

	if ( update )	
		SDL_UpdateTexture(screen->image, 1, &area,NULL);

	return(0);
}
*/
