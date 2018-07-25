#include "stdafx.h"

/*int listbox(struct container *screen, struct colour colour, SDL_Rect area, char text[MAXBTN][MAXLEN], int buttons, int direction, int frame, int update)
{
	int count=0;

	SDL_Rect temp;

	if ( direction == 0 )
	{
		temp.h=area.h;
		area.h=(((area.h-5)-area.y)*buttons);
	}
	else if ( direction == 1 )
	{
		temp.w=area.w;
		area.w=(((area.w-5)-area.x)*buttons);
	}
	
	if ( frame )
		DrawFrame(screen,colour,area,0,0,0);

	area.x=area.x+5;
	area.y=area.y+5;
	area.w=area.w-5;
	area.h=temp.h-5;

	while ( count < buttons )
	{
		button(screen,colour,area,text[count],frame,1,0);
		count++;

		if ( direction == 0 )
		{
			area.y=area.y+20;
			area.h=area.h+20;
		}
		else if ( direction == 1 )
		{
			area.x=area.x+temp.w;
			area.w=area.w+temp.w;
		}
	}

	if ( update )
		SDL_UpdateTexture(screen->image, 1, &area,NULL);
}

*/