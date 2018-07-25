
#include "stdafx.h"

#include "../include/container.h"
#include "../include/draw.h"
#include "../include/progressbar.h"
#include "../include/frame.h"

int progress(struct container *screen, struct progressDef box)
{
	struct frameDef box2;

	int d=0;
	int e=0;
	int done=0;

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


	int x,y,h,w;

	x=box.pos+5+box.area.x;
	y=box.area.y+5;
	w=box.area.w-2;
	h=box.area.h-2;

	DrawFrame(screen, box2);

	for ( d = box.area.x+5; d < x; d++ )
	{
		for(e=y; e < h; e++)
		{	
			if ( d < w )
			{
					DrawPixel(screen, box.bar_colour, d, e,0);
			}else{
				done=1;
			}
		}
	}

	if ( box.update )
		SDL_UpdateTexture(screen->image, 1, &box.area,NULL);

	if ( done )
		return(1);
	else
		return(0);

}

