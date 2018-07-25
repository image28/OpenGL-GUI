
#include "stdafx.h"

#include "../include/container.h"
#include "../include/draw.h"
#include "../include/font.h"
#include "../include/window.h"
#include "../include/frame.h"
#include "../include/popup.h"
#include "../include/button.h"

// title/shading on any of the four sides

int windowStack(struct container *screen, struct winDef box[255], int stacking[255], int windows)
{
	int d,e;

	for(d=0; d < windows; d++)
	{
		for ( e=0; e < windows; e++)
		{
			if ( stacking[d] == box[e].id )
			{
				printf("Drawing window %d at stack position %d\n",box[e].id,d);
				window(screen,box[e]);
			}
		}
	}
}

int orderStack(struct winDef box[255], int *stacking, int windows)
{
	int d,e;
	int temp=0;

	for(d=0; d < windows; d++ )
	{
		if ( box[d].hasfocus )
		{
			temp=*(stacking+d);

			for(e=d; e < (windows-1); e++)
			{
				*(stacking+e)=*(stacking+(e+1));
			}

			*(stacking+(windows-1))=temp;

			d=windows;
		}
	}

	printf("Stack\n----------\n");
	for(d=0; d < windows; d++)
	{
		printf("%d\n",*(stacking+d));
	}
}

void window(struct container *screen, struct winDef box)
{
	struct frameDef box2;
	struct frameDef box3;
	Uint32 temp=0;
	struct colour colour;
	int x,y;

	// box.shaded and box.titlebar should be autofilled

	// box2 == titlebar

	box2.update=0;	
	box2.zoom=1;
	box2.frametype=0;

	box2.frame_colour.R=box.frame_colour.R;
	box2.frame_colour.G=box.frame_colour.G;
	box2.frame_colour.B=box.frame_colour.B;

	box2.area.x=box.titlebar.x;
	box2.area.w=box.titlebar.w;
	box2.area.y=box.titlebar.y;
	box2.area.h=box.titlebar.h;

	box3.update=0;	
	box3.zoom=1;
	box3.frametype=0;

	box3.frame_colour.R=box.frame_colour.R;
	box3.frame_colour.G=box.frame_colour.G;
	box3.frame_colour.B=box.frame_colour.B;

	box3.area.x=box.area.x;
	box3.area.w=box.area.w;
	box3.area.y=box.area.y;
	box3.area.h=box.area.h;

	if ( box.bar )
	{

		//FillRect2(screen, box.titlebar_colour, box.titlebar, 0);
		// draw title bar if there is one
		DrawFrame(screen,box2);
		
		putText(screen, &box.title, box.font, box.title, 1,1, 0);

		// CHECK IF WINDOW IS SHADED
		if ( box.shade )
		{
			// CHECK IF THERE IS A BORDER
			if ( box.border )
			{
				box3.area.x=box.shaded.x+2;
				box3.area.w=box.shaded.w+1;
				box3.area.y=box.shaded.y+2;
				box3.area.h=box.shaded.h+2;
			
				DrawFrame(screen,box3);
			}
		}else{
			// CHECK IF THERE IS A BORDER
			if ( box.border )
			{
				box3.area.x=box.area.x+2;
				box3.area.w=box.area.w+1;
				box3.area.y=box.area.y+2;
				box3.area.h=box.area.h+2;
	
				DrawFrame(screen,box3);

			}

	

			// BLIT WINDOW CONTENT TO WINDOW	
			//SDL_BlitSurface(box.content.image, NULL, screen->image, &box.content.area);
			/*for(x=box.content.area.x;x<box.content.area.w;x++)
			{
				for(y=box.content.area.y;y<box.content.area.h;y++)
				{
					temp=GetPixel(box.content.image,x,y);
					SDL_GetRGB(temp, box.content.image->format, &colour.R, &colour.G, &colour.B);
					//DrawPixel(screen,colour,x,y,0);
				}
			}
		*/
		}
		
	}else{
		// CHECK IF THERE IS A BORDER
		if ( box.border )
			DrawFrame(screen,box3);

		//FillRect2(screen, box.background_colour, box.titlebar, 0);

		// BLIT WINDOW CONTENT TO WINDOW	
		//SDL_BlitSurface(box.content.image, NULL, screen->image, &box.area);
		/*for(x=box.content.area.x;x<box.content.area.w;x++)
		{
			for(y=box.content.area.y;y<box.content.area.h;y++)
			{
				temp=GetPixel(box.content.image,x,y);
				SDL_GetRGB(temp, box.content.image->format, &colour.R, &colour.G, &colour.B);
				DrawPixel(screen,colour,x,y,0);
			}
		}*/
	}
	
	// CHECK WEATHER TO UPDATE
	//if ( box.update )
	//	SDL_UpdateTexture(screen->image, 1, &box.area,NULL);
	
}

void moveWindow(struct container screen, SDL_Event event, struct winDef *box)
{
	char popupText[10][1000]={{"To top\0"},{"Raise\0"},{"Lower\0"},{"To bottom\0"},{"(un)Shade\0"},{"close\0"}};
	int buttondown=0;

	if ( event.type == SDL_MOUSEBUTTONDOWN )
	{
		box->hasfocus=0;

		if ( click(event,box->titlebar) ) // have to check if inside a window here
		{
			box->hasfocus=1;
		}
	}

	if ( ! box->moving ) 
	{

		/*if ( ! box->shade )
		{
			if ( ! mouseover(event,box->area) )
			{
				box->shade=1;
			}
		}else{
			if ( mouseover(event,box->area) )
			{
				box->shade=0;
			}
		}*/
	}else{
		if  ( ( event.motion.x > 0 ) && ( event.motion.x < screen.area.w ) ) 
		{

			if ( ( event.motion.y > 0 ) && ( event.motion.y < screen.area.h ) )
			{
			box->area.x=box->area.x+(event.motion.x-box->prevpos.x);
			box->area.w=box->area.w+(event.motion.x-box->prevpos.x);
			box->area.y=box->area.y+(event.motion.y-box->prevpos.y);
			box->area.h=box->area.h+(event.motion.y-box->prevpos.y);

			box->titlebar.x=box->titlebar.x+(event.motion.x-box->prevpos.x);
			box->titlebar.w=box->titlebar.w+(event.motion.x-box->prevpos.x);
			box->titlebar.y=box->titlebar.y+(event.motion.y-box->prevpos.y);
			box->titlebar.h=box->titlebar.h+(event.motion.y-box->prevpos.y);

			box->title_text.x=box->area.x+15;
			box->title_text.y=box->area.y+15;
			box->title_text.w=box->area.w-35;
			box->title_text.h=box->area.h+30;

			box->content.area.x=box->area.x+5;
			box->content.area.y=box->area.y+32;
			box->content.area.w=box->area.w-10;
			box->content.area.h=box->area.h-10;

			box->shaded.x=box->area.x;
			box->shaded.y=box->area.y;
			box->shaded.w=box->area.w;
			box->shaded.h=box->area.y+30;

			box->prevpos.x=event.motion.x;
			box->prevpos.y=event.motion.y;
			}
		}
	}

	switch( event.type ) 
	{
			case SDL_MOUSEBUTTONDOWN:
				if ( event.button.button == SDL_BUTTON_LEFT )
				{
					if ( ! box->moving )
					{
						if ( click(event,box->titlebar) )
						{
							box->moving=1;
							//box->shade=0;
							//focus=box->id;

							if ( ( ( event.motion.x > 0 ) && ( event.motion.x < screen.area.w ) ) && ( ( event.motion.y > 0 ) && ( event.motion.y < screen.area.h ) ) )
							{
								box->prevpos.x=event.motion.x;
								box->prevpos.y=event.motion.y;
							}
						}
					}
				}else if ( event.button.button == SDL_BUTTON_MIDDLE )
				{
					buttondown=2;
				}

				/*else if ( event.button.button == SDL_BUTTON_RIGHT )
				{
					popup->area.x=event.button.x;
					popup->area.y=event.button.y;
					popup->area.w=event.button.x+popup->width;
					popup->area.h=event.button.y+popup->height;

					//buttonbox(&screen,popupText,*popup);
					popupUpdate2(event,&popup);		
				}*/
			break;

			case SDL_MOUSEBUTTONUP:
				if ( box->moving )
					box->moving=0;

				if ( buttondown == 2 )
				{
					/*if ( box->shade )
					{
						box->shade=0;
					}else{
						box->shade=1;
					}*/

					buttondown=0;
				}

				/*if ( popup->buttondown )
				{
					// run code for popup
					// raise, lower, totop, tobottom, (un)shade, close
				}*/
			break;

		}

}

void initWindow( struct winDef *box)
{
	box->titlebar.x=box->area.x+4;
	box->titlebar.y=box->area.y+4;
	box->titlebar.w=box->area.w-1;
	box->titlebar.h=box->area.y+31;

	box->title_text.x=box->area.x+15;
	box->title_text.y=box->area.y+15;
	box->title_text.w=box->area.w-35;
	box->title_text.h=box->area.h+30;

	box->content.area.x=box->area.x+5;
	box->content.area.y=box->area.y+32;
	box->content.area.w=box->area.w-box->area.x-7;
	box->content.area.h=box->area.h-box->area.y-32;

	box->shaded.x=box->area.x;
	box->shaded.y=box->area.y;
	box->shaded.w=box->area.w-1;
	box->shaded.h=box->area.y+31;

	//box->content.image=SDL_CreateRGBSurface(SDL_SWSURFACE,box->area.w-box->area.x-7,box->area.h-box->area.y-32,32,0,0,0,0);
}

void resizeWindow( SDL_Event event, struct winDef *window)
{
	SDL_Rect top,bottom,left,right,topleft1,bottomleft1,topright1,bottomright1,topleft2,bottomleft2,topright2,bottomright2;

	top.x=window->area.x+5;
	top.w=window->area.w-5;
	top.y=window->area.y;
	top.h=window->area.y+10;

	bottom.x=window->area.x+5;
	bottom.w=window->area.w-5;
	bottom.y=window->area.h-2;
	bottom.h=window->area.h;

	left.x=window->area.x;
	left.w=window->area.x+2;
	left.y=window->area.y+5;
	left.h=window->area.h-5;

	right.x=window->area.w-2;
	right.w=window->area.w;
	right.y=window->area.y+5;
	right.h=window->area.h-5;

	topleft1.x=window->area.x;
	topleft1.w=window->area.x+5;
	topleft1.y=window->area.y;
	topleft1.h=window->area.y+2;

	topleft2.x=window->area.x;
	topleft2.w=window->area.x+2;
	topleft2.y=window->area.y;
	topleft2.h=window->area.y+5;

	bottomleft1.x=window->area.x;
	bottomleft1.w=window->area.x+5;
	bottomleft1.y=window->area.h-2;
	bottomleft1.h=window->area.h;

	bottomleft2.x=window->area.x;
	bottomleft2.w=window->area.x+2;
	bottomleft2.y=window->area.h-5;
	bottomleft2.h=window->area.h;

	topright1.x=window->area.w-5;
	topright1.w=window->area.w;
	topright1.y=window->area.y;
	topright1.h=window->area.y+2;

	topright2.x=window->area.w-2;
	topright2.w=window->area.w;
	topright2.y=window->area.y;
	topright2.h=window->area.y+5;

	bottomright1.x=window->area.w-5;
	bottomright1.w=window->area.w;
	bottomright1.y=window->area.h-2;
	bottomright1.h=window->area.h;

	bottomright2.x=window->area.w-2;
	bottomright2.w=window->area.w;
	bottomright2.y=window->area.h-5;
	bottomright2.h=window->area.h;

	if ( event.type == SDL_MOUSEBUTTONDOWN )
	{
		if ( ! window->resizing )
		{
		
			if ( click(event,top) ) // TOP
			{
				window->resizing=1;
			}
			else if ( click(event,bottom) ) // BOTTOM
			{
			window->resizing=2;
		}
		else if ( click(event,left) ) // LEFT
		{
			window->resizing=3;
		}
		else if ( click(event,right) ) // RIGHT
		{
			window->resizing=4;
		}
		else if ( ( ( click(event,topleft1) ) || ( click(event,topleft2) ) ) ) // TOP LEFT
		{
			window->resizing=5;
		}
		else if ( ( ( click(event,bottomleft1) ) || ( click(event,bottomleft2) ) ) ) // BOTTOM LEFT
		{
			window->resizing=6;
		}
		else if ( ( ( click(event,topright1) ) || ( click(event,topright2) ) ) ) // TOP RIGHT
		{
			window->resizing=7;
		}
		else if ( ( ( click(event,bottomright1) ) || ( click(event,bottomright2) ) ) ) // BOTTOM RIGHT
		{
			window->resizing=8;
		}
		}else{
			if ( window->resizing == 1 )
			{
				if ( event.motion.y > window->area.y )
				{
					window->area.y=window->area.y+event.motion.y;
				}
				else if ( event.motion.y < window->area.y )
				{
					window->area.y=window->area.y-event.motion.y;
				}
			}
			else if ( window->resizing == 2 )
			{
				if ( event.motion.y > window->area.y )
				{
					window->area.y=window->area.y+event.motion.y;
				}
				else if ( event.motion.y < window->area.y )
				{
					window->area.y=window->area.y-event.motion.y;
				}
			}
			else if ( window->resizing == 3 )
			{
				if ( event.motion.x > window->area.x )
				{
					window->area.x=window->area.x+event.motion.y;
				}
				else if ( event.motion.x < window->area.x )
				{
					window->area.x=window->area.x-event.motion.y;
				}
			}
			else if ( window->resizing == 4 )
			{
				if ( event.motion.x > window->area.w )
				{
					window->area.w=window->area.w+event.motion.y;
				}
				else if ( event.motion.x < window->area.w )
				{
					window->area.w=window->area.w-event.motion.y;
				}
			}
			else if ( window->resizing == 5 )
			{
				if ( event.motion.y > window->area.y )
				{
					window->area.y=window->area.y+event.motion.y;
				}
				else if ( event.motion.y < window->area.y )
				{
					window->area.y=window->area.y-event.motion.y;
				}

				if ( event.motion.x > window->area.x )
				{
					window->area.x=window->area.x+event.motion.y;
				}
				else if ( event.motion.x < window->area.x )
				{
					window->area.x=window->area.x-event.motion.y;
				}
			}
			else if ( window->resizing == 6 )
			{
				if ( event.motion.y > window->area.h )
				{
					window->area.h=window->area.h+event.motion.y;
				}
				else if ( event.motion.y < window->area.h )
				{
					window->area.h=window->area.h-event.motion.y;
				}

				if ( event.motion.x > window->area.x )
				{
					window->area.x=window->area.x+event.motion.y;
				}
				else if ( event.motion.x < window->area.x )
				{
					window->area.x=window->area.x-event.motion.y;
				}
			}
			else if ( window->resizing == 7 )
			{
				if ( event.motion.y > window->area.y )
				{
					window->area.y=window->area.y+event.motion.y;
				}
				else if ( event.motion.y < window->area.y )
				{
					window->area.y=window->area.y-event.motion.y;
				}

				if ( event.motion.x > window->area.w )
				{
					window->area.w=window->area.w+event.motion.y;
				}
				else if ( event.motion.x < window->area.w )
				{
					window->area.w=window->area.w-event.motion.y;
				}
			}
			else if ( window->resizing == 8 )
			{
				if ( event.motion.y > window->area.h )
				{
					window->area.h=window->area.h+event.motion.y;
				}
				else if ( event.motion.y < window->area.h )
				{
					window->area.h=window->area.h-event.motion.y;
				}

				if ( event.motion.x > window->area.w )
				{
					window->area.w=window->area.w+event.motion.y;
				}
				else if ( event.motion.x < window->area.w )
				{
					window->area.w=window->area.w-event.motion.y;
				}
			}
		}
	}
}
