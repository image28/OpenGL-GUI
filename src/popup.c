
#include "stdafx.h"

#include "../include/container.h"
#include "../include/draw.h"
#include "../include/button.h"

int popupUpdate( SDL_Event event, struct buttonDef *box)
{
/*	SDL_Rect buttonarea[box->buttons];
	int d;


	switch( event.type ) 
	{
		case SDL_MOUSEBUTTONDOWN:
		
			box->buttondown=1;

		box->area.x=event.motion.x;	
		box->area.y=event.motion.y;	
		box->area.w=event.motion.x+box->width;
		box->area.h=event.motion.y+box->height;
			// have to check that user is not clicking on any other
			// buttons/windows/etc..
		break;

		case SDL_MOUSEBUTTONUP:
			if ( box->buttondown )
			{
				box->buttondown=0;
			}

			// mark that this button has been clicked
			// programmer/user accesses this varable to	
			// make the gui do stuff when a popup item
			// is selected.

		break;
	}

	if ( box->buttondown )
	{

		if ( box->border )
		{
			buttonarea[0].x=box->area.x+8;
			buttonarea[0].w=box->area.w-8;
			buttonarea[0].y=box->area.y+8;
			buttonarea[0].h=box->area.h-8;
		}else{
			buttonarea[0].x=box->area.x;
			buttonarea[0].w=box->area.w;
			buttonarea[0].y=box->area.y;
			buttonarea[0].h=box->area.h;
		}

		for(d=1; d<box->buttons; d++)
		{

			// directional if here !!!!!!!!!!!
			buttonarea[d].x=buttonarea[0].x;
			buttonarea[d].w=buttonarea[0].w;
			buttonarea[d].y=buttonarea[d-1].y+(buttonarea[0].h-buttonarea[0].y);
			buttonarea[d].h=buttonarea[d-1].h+(buttonarea[0].h-buttonarea[0].y);

			if ( mouseover(event,buttonarea[d-1]) )
				box->selected[d-1]=1;
			else
				box->selected[d-1]=0;
		}

		buttonarea[box->buttons-1].h=buttonarea[box->buttons-1].h-5;

		if ( mouseover(event,buttonarea[box->buttons-1]) )
			box->selected[box->buttons-1]=1;
		else
			box->selected[box->buttons-1]=0;

	}
	*/
}

