
#include "stdafx.h"

#include "../include/container.h"
#include "../include/draw.h"
#include "../include/image.h"
#include "../include/font.h"
#include "../include/button.h"
#include "../include/frame.h"

#define MAXLEN 1000
#define MAXBTN 10
#define MAX 11

int image4(struct container *screen, struct colour colour, SDL_Rect area, char *image,int zoom, int update);


int image4(struct container *screen, struct colour colour, SDL_Rect area, char *image,int zoom, int update)
{
	int d,e;

	for(e=0;e < MAX-1; e++)
	{
		for(d=0; d < MAX; d++)
		{
			if ( *(image+(d+(e*MAX))) == '1' )
			{
				DrawBox(screen, colour, (d*zoom)+area.x, (e*zoom)+area.y, zoom,0);
			}

		}

	}

	if ( update )
		SDL_UpdateTexture(screen->image, 1, &area,NULL);

	return(0);
}

int button(struct container *screen, struct buttonDef box, char text[1000], int selected)
{
	int used=0;
	SDL_Rect textarea;
	SDL_Rect imagearea;	
	SDL_Rect fillArea;
	struct frameDef box2;

	copyArea(&fillArea,box.area);
	fillArea.w++;
	fillArea.h=fillArea.h+2;

	box2.area.x=box.area.x;
	box2.area.y=box.area.y;
	box2.area.w=box.area.w;
	box2.area.h=box.area.h;

	box2.frame_colour.R=box.frame_colour.R;
	box2.frame_colour.G=box.frame_colour.G;
	box2.frame_colour.B=box.frame_colour.B;

	box2.frametype=0;
	box2.zoom=1;
	box2.update=0;

	struct colour black;
	black.R=0;
	black.G=0;
	black.B=0;
	
	if ( box.blank )
		FillRect2(screen, black, box.area, 0);

	if ( selected )
		FillRect2(screen, box.background_colour, fillArea, 0);

	// Draw Frame
	if ( box.frame )
		DrawFrame(screen, box2);

	if ( box.hasimage )
	{
		imagearea.x=box.area.x;
		imagearea.x=box.area.y;
		imagearea.x=box.area.w;
		imagearea.x=box.area.h;
		image4(screen, box.text_colour, imagearea, &box.image,box.zoom, 0);
	}

	if ( box.hastext )
	{
		// calculate center
		used=strlen(text);
	
		if ( box.justified == 0 )
		{
			textarea.x=box.area.x+5;
			textarea.y=box.area.y+5;
			textarea.w=box.area.w-2;
			textarea.h=box.area.h-2;
		}
		else if ( box.justified == 1 )
		{
			textarea.x=((box.area.w-box.area.x)-(used*11))/2+box.area.x;
			textarea.y=box.area.y+5;
			textarea.w=box.area.w-2;
			textarea.h=box.area.h-2;
		}
		else if ( box.justified == 2 )
		{	
			textarea.x=box.area.x+((box.area.w-box.area.x)-(used*11));
			textarea.y=box.area.y+5;
			textarea.w=box.area.w-2;
			textarea.h=box.area.h-2;
		}
	

		// draw text
		putText(screen, &text, box.font,1,1,0,0);
	}

	//if ( box.update )
	//	SDL_UpdateTexture(screen->image, 1, &box.area,NULL);
	
	return(0);
}

int buttonbox(struct container *screen, char text[MAXBTN][MAXLEN], struct buttonDef box)
{
	int count=0;

	SDL_Rect temp;

	struct frameDef box2;

	box2.area.x=box.area.x;
	box2.area.y=box.area.y;
	box2.area.w=box.area.w;
	box2.area.h=box.area.h;

	box2.frame_colour.R=box.frame_colour.R;
	box2.frame_colour.G=box.frame_colour.G;
	box2.frame_colour.B=box.frame_colour.B;

	box2.frametype=0;
	box2.zoom=1;
	box2.update=0;

	if ( box.border )
	{
		box.area.x=box.area.x+8;
		box.area.y=box.area.y+8;
		box.area.w=box.area.w-8;
		box.area.h=box.area.h-8;	
	}else{
		box.area.x=box.area.x;
		box.area.y=box.area.y;
		box.area.w=box.area.w;
		box.area.h=box.area.h;
	}

	int w=box.area.w-box.area.x;
	int h=box.area.h-box.area.y;

	if ( box.direction == 0 )
		box2.area.h=box.area.y+((box.area.h-box.area.y)*box.buttons)+10;	
	else
		box2.area.w=box.area.x+((box.area.w-box.area.x)*box.buttons)+10;

	if ( box.border )
		DrawFrame(screen,box2);

	while ( count < box.buttons )
	{
		if ( box.selected[count] )
			button(screen,box,text[count],1);
		else
			button(screen,box,text[count],0);

		count++;

		if ( box.direction == 0 )
		{
			box.area.y=box.area.y+h;
			box.area.h=box.area.h+h;

		}
		else if ( box.direction == 1 )
		{
			box.area.x=box.area.x+w;
			box.area.w=box.area.w+w;
		}

		if ( count == box.buttons-1 )
			box.area.h=box.area.h+1;

	}

	//if ( box.update )
	//	SDL_UpdateRects(screen->image, 1, &box2.area);

}

int click(SDL_Event event , SDL_Rect area)
{
	if ( event.button.x >= area.x ) 
	{
		if ( event.button.x <= area.w ) 
		{
			if ( event.button.y >= area.y ) 
			{
				if ( event.button.y <= area.h ) 
				{
					return(1);
				}else{
					return(0);
				}
			}else{
				return(0);
			}
		}else{
			return(0);
		}
	}else{
		return(0);
	}
}

int mouseover(SDL_Event event, SDL_Rect area)
{
	if ( event.motion.x >= area.x ) 
	{
		if ( event.motion.x <= area.w ) 
		{
			if ( event.motion.y >= area.y ) 
			{
				if ( event.motion.y <= area.h ) 
				{
					return(1);
				}else{
					return(0);
				}
			}else{
				return(0);
			}
		}else{
			return(0);
		}
	}else{
		return(0);
	}
}
