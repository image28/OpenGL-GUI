
#include "stdafx.h"

#include "../include/container.h"
#include "../include/draw.h"
#include "../include/checkbox.h"
#include "../include/frame.h"
#include "../include/font.h"

#define MAXLEN 10
#define MAXBTN 10

int option(struct container *screen, struct checkDef box, char text[1000], int selected)
{
	int used=0;
	SDL_Rect textarea;
	SDL_Rect imagearea;

	imagearea.x=box.area.x+10;
	imagearea.y=box.area.y+8;
	imagearea.w=box.area.x+50;
	imagearea.h=box.area.h;
	
	char defaultoptimage[11][11] = {"0001111000\0",
						  "0010000100\0",
						  "0100000010\0",
						  "1000000001\0",
						  "1000000001\0",
						  "1000000001\0",
						  "1000000001\0",
						  "0100000010\0",
						  "0010000100\0",
						  "0001111000\0"};

	char defaultselectedimage[11][11] = {"0000000000\0",
						       "0000000000\0",
						  	 "0001111000\0",
						  	 "0011111100\0",
						 	 "0011111100\0",
						 	 "0011111100\0",
						 	 "0011111100\0",
						 	 "0001111000\0",
						 	 "0000000000\0",
						 	 "0000000000\0"};

	struct frameDef box2;

	box2.area.x=box.area.x;
	box2.area.y=box.area.y;
	box2.area.w=box.area.w;
	box2.area.h=box.area.h;

	box2.update=0;
	box2.zoom=1;
	box2.frametype=0;

	box2.frame_colour.R=box.frame_colour.R;
	box2.frame_colour.G=box.frame_colour.G;
	box2.frame_colour.B=box.frame_colour.B;

	// Draw Frame
	if ( box.frame )
		DrawFrame(screen, box2);

	// using default option image
	image(screen, box.box_colour, imagearea, defaultoptimage,2, 0);

	if ( selected )
	{
		image(screen, box.x_colour, imagearea, defaultselectedimage,2, 0);
	}

// calculate center
	used=strlen(box.text);
	
	if ( box.justified == 0 )
	{
		textarea.x=box.area.x+40;
		textarea.y=box.area.y+12;
		textarea.w=box.area.w-2;
		textarea.h=box.area.h-2;
	}
	else if ( box.justified == 1 )
	{
		textarea.x=((box.area.w-box.area.x)-(used*11))/2+box.area.x+15;
		textarea.y=box.area.y+5;
		textarea.w=box.area.w-2;
		textarea.h=box.area.h-2;
	}
	else if ( box.justified == 2 )
	{	
		textarea.x=box.area.x+((box.area.w-box.area.x)-(used*11))+15;
		textarea.y=box.area.y+5;
		textarea.w=box.area.w-2;
		textarea.h=box.area.h-2;
	}
	

	// draw text
	putText(screen, &box.text,  box.font, text,1,0,0);

	//if ( box.update )
	//	SDL_UpdateTexture(screen->image, 1, &box.area,NULL);

}

int optionbox(struct container *screen, char text[10][10], struct checkDef box)
{

	int count=0;
	struct frameDef box2;

	box2.area.x=box.area.x;
	box2.area.y=box.area.y;
	box2.area.w=box.area.w;
	box2.area.h=box.area.h;

	box2.update=0;
	box2.zoom=1;
	box2.frametype=0;

	box2.frame_colour.R=box.frame_colour.R;
	box2.frame_colour.G=box.frame_colour.G;
	box2.frame_colour.B=box.frame_colour.B;

	box.area.x=box.area.x+8;
	box.area.y=box.area.y+8;
	box.area.w=box.area.w-8;
	box.area.h=box.area.h-8;

	if ( box.direction == 0 )
	{
		box2.area.h=((box.area.h-box.area.y))*box.options+28;	
	}else{
		box2.area.w=((box.area.w-box.area.x))*box.options+28;
		box2.area.h=box.area.h+12;
	}

	int w=box.area.w-box.area.x;
	int h=box.area.h-box.area.y;


	if ( box.border )
		DrawFrame(screen,box2);

	while ( count < box.options )
	{
		if ( box.clicked == count )
			option(screen, box, text[count],1);
		else
			option(screen, box, text[count],0);

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

	}

	//if ( box.update )
	//	SDL_UpdateRects(screen->image, 1, &box2.area);

}

void optionboxUpdate(SDL_Rect window, SDL_Event event, struct checkDef *box)
{

	SDL_Rect temp;
	int d=0;

	temp.x=box->area.x+8;//+window.x;
	temp.y=box->area.y+8;//+window.y;
	temp.w=box->area.w-8;//+window.x;
	temp.h=box->area.h-8;//+window.y;	

	int w=temp.w-temp.x;
	int h=temp.h-temp.y;

	for(d=0; d < box->options; d++)
	{
			
		if ( event.type == SDL_MOUSEBUTTONUP )
		{
			if ( mouseover(event,temp) )
			{
				box->clicked = d;
			}
		}
	
		if ( box->direction )
		{
			temp.x=temp.x+w;
			temp.w=temp.w+w;
		}
		else
		{
			temp.y=temp.y+h;
			temp.h=temp.h+h;
		}
	}
}
