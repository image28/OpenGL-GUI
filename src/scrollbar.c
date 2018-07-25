
#include "stdafx.h"

#include "../include/container.h"
#include "../include/draw.h"
#include "../include/scrollbar.h"
#include "../include/frame.h"

int DrawScrollBar(struct container *screen,struct scrollDef box)
{
	struct frameDef box2;
	struct frameDef box3;

	int bs=0;
	int blockpos=0;
	int d,e;

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

	box3.update=0;	
	box3.zoom=1;
	box3.frametype=0;

	box3.frame_colour.R=box.bar_colour.R;
	box3.frame_colour.G=box.bar_colour.G;
	box3.frame_colour.B=box.bar_colour.B;

	// draw Frame
	if ( box.frame )
		DrawFrame(screen, box2);

	bs=(box.area.h-box.area.y)/box.total;
	//bs=60;
	//blockpos=area.y+((total/position)*bs);

	box3.area.x=box.area.x+6;
	box3.area.y=box.area.y+box.position;
	box3.area.h=box.position+bs;
	box3.area.w=box.area.w-6;

	DrawFrame(screen, box3);

	if ( box.update )
		SDL_UpdateTexture(screen->image, 1, &box.area,NULL);

	return(0);
}

