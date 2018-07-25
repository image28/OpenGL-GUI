
#include "stdafx.h"

#include "../include/container.h"
#include "../include/draw.h"
#include "../include/font.h"
#include <time.h>

int showTime(struct container *screen, struct colour colour, SDL_Rect area, int day, int month, int year, int time, int ampm, int frame, int update)
{
	time_t result;
	struct tm *locTime;

//	result=time(NULL);

//	locTime = localtime(&result);	

	if ( frame )
	{
		DrawFrame(screen,colour,area,0,1,0);

		area.x=area.x+2;
		area.y=area.y+2;	
		area.w=area.w-2;	
		area.h=area.h-2;
	}

	/*
	if ( time )
		putText(screen, &box.text, area, asctime(locTime),1, 0, 0);

	if ( day )
	
	if ( month )
	
	if ( year )
*/

	//if ( update )
	//	SDL_UpdateTexture(screen->image, 1, &area,NULL);
}
