
#include "stdafx.h"

#include "../include/container.h"
#include "../include/draw.h"
#include "../include/frame.h"

void DrawFrame(struct container *screen, struct frameDef box)
{
	int d=0; // y
	int e=0; // x

	d=box.area.y;
	e=box.area.x;
	
	if ( ( box.frametype == 0 ) || ( box.frametype == 4 ) || ( box.frametype == 5 ) || ( box.frametype == 7 ) || ( box.frametype == 10 ) )
	{
		for ( e=box.area.x; e <= box.area.w; e++ )
			DrawBox(screen, box.frame_colour, e+box.zoom, d+box.zoom,box.zoom,0);
	}
	
	e=box.area.x;

	if ( ( box.frametype == 0 ) || ( box.frametype == 3 ) || ( box.frametype == 5 ) || ( box.frametype == 8 ) || ( box.frametype == 11 ) )
	{
		for ( d=box.area.y; d <= box.area.h; d++ )
			DrawBox(screen, box.frame_colour, e+box.zoom, d+box.zoom,box.zoom,0);
	}

	e=box.area.w;
	if ( ( box.frametype == 0 ) || ( box.frametype == 2 ) || ( box.frametype == 4 ) || ( box.frametype == 9 ) || ( box.frametype == 11 ) )
	{
		for ( d=box.area.y; d <= box.area.h; d++ )
			DrawBox(screen, box.frame_colour, e+box.zoom, d+box.zoom,box.zoom,0);
	}

	d=box.area.h;	
	if ( ( box.frametype == 0 ) || ( box.frametype == 2 ) || ( box.frametype == 3 ) || ( box.frametype == 6 ) || ( box.frametype == 10 ) )
	{
		for ( e=box.area.x; e <= box.area.w; e++ )
			DrawBox(screen, box.frame_colour, e+box.zoom, d+box.zoom,box.zoom,0);
	}

}

